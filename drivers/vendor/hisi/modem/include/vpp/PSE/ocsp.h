/*

                Copyright 2005, Huawei Technologies Co. Ltd.
                           ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                              ocsp.h

   Project Code: SeCert
   Module Name: OCSP
   Date Created: 2005-06-30
   Author: Binil Nair
   @brief: This header file declares all the strutures and methods that are
			required to provide functions to support Online	Certificate Status
			Protocol
*/
#include "ipsi_pse_build_conf.h"

#ifndef __SEC_NO_OCSP__
#ifndef _IPSI_OCSP_H_
#define _IPSI_OCSP_H_

#include "asn-types.h"
#include "sec_sys.h"
//#include "x509.h"
#include "x509_basictypes.h"
#include "sec_crypto.h"
#include "ipsi_types.h"
#include "sec_list.h"
#include "x509v3_extn.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
	Version of OCSP Request/Response
*/
#define OCSP_VER 0

/**
* @defgroup ocsp
* This section contains ocsp Enums, Unions, Structures and Functions
*/


/*
	This enum contains the status(success/error) of OCSP Response that is returned by
	an OCSP Responder.

   OCSP_MALFORMEDREQUEST : It indicates that the request received does not conform to the
   OCSP syntax.

   OCSP_INTERNALERROR : It indicates that the OCSP server reached an inconsistent internal
   state. The query should be retried.

   OCSP_TRYLATER : It indicates that the service exists, but the OCSP server is temporarily
   unable to respond.

   Enum value 4 : Must not be used according to the standards.

   OCSP_SIGREQUIRED : It indicates that the server requires the client to sign the request in
   order to construct a response.

   OCSP_UNAUTHORIZED : It indicates that the client is not authorized to make this query to
   this OCSP server.

   OCSP_INVALID_RESP_STATUS : This value must not be used by the end user. It is used as a
   return value by OCSP_getRespStatusFromOCSPResp, if the status field is not set.
*/

/**
* @defgroup ocspEnums
* @ingroup ocsp
* This section contains ocsp Enums
*/


/**
* @defgroup OCSP_RESP_STATUS_E
* @ingroup ocspEnums
* @par Prototype
* @code
* typedef enum enOCSP_RespStatus
* {
*   OCSP_SUCCESSFUL          = 0,
*   OCSP_MALFORMEDREQUEST    = 1,
*   OCSP_INTERNALERROR       = 2,
*   OCSP_TRYLATER            = 3,
*   OCSP_SIGREQUIRED         = 5,
*   OCSP_UNAUTHORIZED        = 6,
*   OCSP_INVALID_RESP_STATUS = 7
* } OCSP_RESP_STATUS_E;
* @endcode
*
* @datastruct OCSP_SUCCESSFUL= 0 OCSP Response is Successful.
* @datastruct OCSP_MALFORMEDREQUEST= 1 Malformed OCSP Request.
* @datastruct OCSP_INTERNALERROR= 2 Internal error occurred.
* @datastruct OCSP_TRYLATER= 3 Try Later.
* @datastruct OCSP_SIGREQUIRED= 5 (4 is not used) Signature required in the OCSP Request.
* @datastruct OCSP_UNAUTHORIZED= 6 OCSP Request unauthorized.
* @datastruct OCSP_INVALID_RESP_STATUS= 7 Invalid OCSP Response - Should not be
* used by the user. Returned in the case of enum not set.
*/
typedef enum enOCSP_RespStatus
{
    OCSP_SUCCESSFUL = 0,		/* OCSP Response is Successful */
    OCSP_MALFORMEDREQUEST = 1,	/* Malformed OCSP Request */
    OCSP_INTERNALERROR = 2,		/* Internal error occurred */
    OCSP_TRYLATER = 3,			/* Try Later */
								/* 4 is not used */
    OCSP_SIGREQUIRED = 5,		/* Signature required in the OCSP Request */
	OCSP_UNAUTHORIZED = 6,		/* OCSP Request unauthorized */
	OCSP_INVALID_RESP_STATUS = 7/* Invalid OCSP Response - Should not be
									used by the user. Returned in the case of enum not set */
} OCSP_RESP_STATUS_E;


/*
	This enum value indicates the type used to identify the OCSP Responder. It can be based on :
		 Name
		 Hash[SHA1] of the public key.
		 Only SHA1 is used to calculate the digest of the publi key
*/
/**
* @defgroup OCSP_RESPID_TYPE_E
* @ingroup ocspEnums
* @par Prototype
* @code
* typedef enum enOCSP_ResponderID
* {
*   OCSP_RESP_ID_BYNAME  = 0,
*   OCSP_RESP_ID_BYKEY   = 1,
*   OCSP_INVALID_RESP_ID = 2
* } OCSP_RESPID_TYPE_E;
* @endcode
*
* @datastruct OCSP_RESP_ID_BYNAME= 0 Responder Id by Name.
* @datastruct OCSP_RESP_ID_BYKEY= 1 Responder id by KeyHash.
* @datastruct OCSP_INVALID_RESP_ID= 2 Invalid Responder id - Should not be used by the user.
* Returned in the case of enum not set.
*/
typedef enum enOCSP_ResponderID
{
    OCSP_RESP_ID_BYNAME = 0,	/* Responder Id by Name */
    OCSP_RESP_ID_BYKEY = 1,		/* Responder id by KeyHash */
	OCSP_INVALID_RESP_ID = 2	/* Invalid Responder id - Should not be
									used by the user. Returned in the case of enum not set */
} OCSP_RESPID_TYPE_E;


/*
	This enum value indicates the status of a certificate. It can be :
		* Good	  : The certificate is not revoked
		* Revoked : The certificate is revoked
		* Unknown : The status of the certificate is not known
*/
/**
* @defgroup OCSP_CERT_STATUS_TYPE_E
* @ingroup ocspEnums
* @par Prototype
* @code
* typedef enum enOCSP_CertStatus
* {
*   OCSP_CERT_STATUS_GOOD     = 0,
*   OCSP_CERT_STATUS_REVOKED  = 1,
*   OCSP_CERT_STATUS_UNKNOWN  = 2,
*   OCSP_INVALID_CERT_STATUS  = 3
* } OCSP_CERT_STATUS_TYPE_E;
* @endcode
*
* @datastruct OCSP_CERT_STATUS_GOOD= 0 Certificate status is good.
* @datastruct OCSP_CERT_STATUS_REVOKED= 1 Certificate status is revoked.
* @datastruct OCSP_CERT_STATUS_UNKNOWN= 2 Certificate status is unknown.
* @datastruct OCSP_INVALID_CERT_STATUS= 3 Invalid certificate status -  Should not be used by the user..
* Returned in the case of enum not set.
*/
typedef enum enOCSP_CertStatus
{
    OCSP_CERT_STATUS_GOOD = 0,		/* Certificate status is good */
    OCSP_CERT_STATUS_REVOKED = 1,	/* Certificate status is revoked */
    OCSP_CERT_STATUS_UNKNOWN = 2,	/* Certificate status is unknown */
	OCSP_INVALID_CERT_STATUS = 3	/* Invalid certificate status -  Should not be
										used by the user. Returned in the case of enum not set */
} OCSP_CERT_STATUS_TYPE_E;


/*
	This structure contains information(like revocation reason and time) about the
	revoked certificate. It is used only if the status of the certificate is set to
	'Revoked'.
	The revocation reason can be :
		* CRL_UNSPECIFIED = 0
		* CRL_KEY_COMPROMISE = 1		Reason is Key compromise
		* CRL_CA_COMPROMISE = 2			Reason is CA compromise
		* CRL_AFFILIATION_CHANGED = 3	Reason is Affilitaion chnaged
		* CRL_SUPERSEEDED = 4			Reason is Superseded
		* CRL_CESSATION_OPERATION = 5	Reason is Cessation of operation
		* CRL_CERTIFICATE_HOLD = 6		Reason is Certificate Hold
		* CRL_REM_FROM_CRL = 8			Reason is remove from CRL
		* CRL_PRIV_WITHDRAWN = 9		Reason is Privelge withdrawn
		* CRL_AUTH_ATTR_COMPROMISE = 10	Reason is ATTR cert compromise
*/

/**
* @defgroup ocspStructures
* @ingroup ocsp
* This section contains ocsp Structures
*/

/**
* @defgroup OCSP_REV_INFO_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_RevInfo
* {
*  SEC_GeneralizedTime_S stRevTime;
*  X509_CRL_REASON_E*    pRevReason;
* } OCSP_REV_INFO_S;
* @endcode
*
* @datastruct stRevTime Time at which the certificate is revoked.
* @datastruct pRevReason Revocation reason - OPTIONAL.
*/
typedef struct stOCSP_RevInfo
{
	SEC_GeneralizedTime_S	stRevTime;			/* Time at which the certificate is revoked */
	X509_CRL_REASON_E*		pRevReason;			/* Revocation reason - OPTIONAL */
} OCSP_REV_INFO_S;


/*
	This union contains information about the revocation status of the certificate.
	The field used depends on the value of certificate status enum value.
	If enum value is OCSP_CERT_STATUS_GOOD, good is set.
	If enum value is OCSP_CERT_STATUS_REVOKED, pstRevoked is set.
	If enum value is OCSP_CERT_STATUS_UNKNOWN, unknown is set.
*/

/**
* @defgroup ocspUnions
* @ingroup ocsp
* This section contains ocsp Unions
*/

/**
* @defgroup OCSP_CERT_STATUS_U
* @ingroup ocspUnions
* @code
* typedef union unOCSP_CertStatus
* {
*  SEC_AsnNull      good;
*  OCSP_REV_INFO_S* pstRevoked;
*  SEC_AsnNull      unknown;
* } OCSP_CERT_STATUS_U;
* @endcode
*
* @datastruct good Used when certificate status is good.
* @datastruct pstRevoked Used when certificate status is revoked.
* @datastruct unknown Used when certificate status is unknown.
*/

typedef union unOCSP_CertStatus
{
	SEC_AsnNull good;				 /* Used when certificate status is good */
	OCSP_REV_INFO_S* pstRevoked;	 /* Used when certificate status is revoked */
	SEC_AsnNull unknown;			 /* Used when certificate status is unknown */
} OCSP_CERT_STATUS_U;


/*
	This structure contains revocation status of the certificate. Also contains other information, in the
	case of revoked certificate.
	The status of the certificate is reflected in enCertStatus. The status can be :
	If enCertStatus is OCSP_CERT_STATUS_GOOD, good is used.
	If enCertStatus is OCSP_CERT_STATUS_REVOKED, pstRevoked is used.
	If enCertStatus is OCSP_CERT_STATUS_UNKNOWN, unknown is used.
*/

/**
* @defgroup OCSP_CERT_STATUS_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_CertStatus
* {
*	OCSP_CERT_STATUS_TYPE_E enCertStatus;
*	OCSP_CERT_STATUS_U unCertStatus;
* } OCSP_CERT_STATUS_S;
* @endcode
*
* @datastruct enCertStatus Enum value containing status of the certificate.
* @datastruct unCertStatus Union containing status of the certificate.
*/
typedef struct stOCSP_CertStatus
{
	OCSP_CERT_STATUS_TYPE_E enCertStatus;	/*	Enum value containing status of the certificate */
	OCSP_CERT_STATUS_U unCertStatus;		/*	Union containing status of the certificate */
} OCSP_CERT_STATUS_S;


/*
	Structures for supporting OCSP Request
*/

/*
	This structure contains version, information about the requestor, all the single requests
	and the extensions associated with the request. Currenly only V1(0) is supported. The different
	extensions applicable here are :
		* Nonce(SEC_AsnOcts_S)
		* Acceptable Responses(SEC_List_S).
	Nonce is an SEC_AsnOcts_S which is used in the request and response to prevent replay attacks.
	Acceptable Responses is a list of OIDs, which specifies the kinds of response types an OCSP client
	or responder understands.
*/

/**
* @defgroup OCSP_TBSREQ_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_TBSRequest
* {
*	SEC_UINT32*     pulVer;
*	SEC_GEN_NAME_S* pstRequestorName;
*	SEC_List_S*     pstReqList;
*	Extensions*     pstReqExtnList;
* } OCSP_TBSREQ_S;
* @endcode
*
* @datastruct pulVer Version of OCSP Request.
* @datastruct pstRequestorName Name of the Requestor - OPTIONAL.
* @datastruct pstReqList List of Single Requests.
* @datastruct pstReqExtnList List of extensions - OPTIONAL.
*/
typedef struct stOCSP_TBSRequest
{
	SEC_UINT32* pulVer;					/* Version of OCSP Request */
	SEC_GEN_NAME_S* pstRequestorName;	/* Name of the Requestor - OPTIONAL */
	SEC_List_S* pstReqList;				/* List of Single Requests */
	Extensions* pstReqExtnList;			/* List of extensions - OPTIONAL */
} OCSP_TBSREQ_S;

/*
	This structure contains signature, algorithm identifier and a list of certifcates to verify the
	signature. The list of certificates is added only if required. If present, the public key in these
	certificates should be used for signature verification. The signature algorithm indicates both sign
	and hash algorithm. This structure is used by both OCSP Request and OCSP Response.
*/

/**
* @defgroup OCSP_SIG_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_Sig
* {
*	SEC_ALG_IDENTIFIER_S* pstSigAlgId;
*	SEC_AsnBits_S         stSig;
*	SEC_List_S*           pstCertList;
* } OCSP_SIG_S;
* @endcode
*
* @datastruct pstSigAlgId Signature algorithm identifier.
* @datastruct stSig Signature.
* @datastruct pstCertList List of certificates for verifying the signature - OPTIONAL.
*/
typedef struct stOCSP_Sig
{
	SEC_ALG_IDENTIFIER_S* pstSigAlgId;	/* Signature algorithm identifier */
	SEC_AsnBits_S		  stSig;		/* Signature */
	SEC_List_S*			  pstCertList;	/* List of certificates for verifying the signature - OPTIONAL */
} OCSP_SIG_S;


/*
	The Online Certificate Status Protocol (OCSP) enables applications to determine the (revocation)
	state of an identified certificate. OCSP provides more timely revocation information than is possible
	with CRLs and is also used to obtain additional status information. An OCSP client issues a status
	request to an OCSP responder and suspends acceptance of the certificate in question until the responder
	provides a response.

	This structure is created by the End Entity and sent to the OCSP Responder.

	This structure contains the following information :

		* TBS Request	[OCSP_TBSREQ_S]
		  This structure contains version, information about the requestor, all the single requests
		  and the extensions associated with the request.

		* Signature		[OCSP_SIG_S]
		  This structure contains signature, algorithm identifier and a list of certifcates. It is
		  an optional field.

*/

/**
* @defgroup OCSP_REQUEST_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_OCSPRequest
* {
*	OCSP_TBSREQ_S* pstTBSReq;
*	OCSP_SIG_S*    pstSig;
* } OCSP_REQUEST_S;
* @endcode
*
* @datastruct pstTBSReq OCSP TBS Request - contains information about the requestor and all single requests.
* @datastruct pstSig Signature of the Requestor - OPTIONAL.
*/
typedef struct stOCSP_OCSPRequest
{
	OCSP_TBSREQ_S* pstTBSReq;		/* OCSP TBS Request - contains information about the requestor and all single requests */
	OCSP_SIG_S* pstSig;				/* Signature of the Requestor - OPTIONAL */
} OCSP_REQUEST_S;


/*
	This structure contains detailed information about a particular certificate. An OCSP Resquest/Response contains a list of
	Single Request/Response, where each Single Request/Response contains imformation about a particular certficate. It contains
	the following information :
		* Certificate Serial Number
		* Hash of issuer's name
		* Hash of issuer's public key
		* Hash algorithm used to calculate the digest
*/

/**
* @defgroup OCSP_CERT_ID_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_CertID
* {
*	SEC_ALG_IDENTIFIER_S* pstHashAlg;
*	SEC_AsnOcts_S         stIssuerNameHash;
*	SEC_AsnOcts_S         stIssuerKeyHash;
*	SEC_BIGINT_S          stSerialNumber;
* } OCSP_CERT_ID_S;
* @endcode
*
* @datastruct pstHashAlg Hash algorithm identifier.
* @datastruct stIssuerNameHash Issuer's name hash.
* @datastruct stIssuerKeyHash Hash of public key.
* @datastruct stSerialNumber Certificate Serial Number.
*/
typedef struct stOCSP_CertID
{
	SEC_ALG_IDENTIFIER_S*	pstHashAlg;		  /* Hash algorithm identifier */
	SEC_AsnOcts_S			stIssuerNameHash; /* Issuer's name hash */
	SEC_AsnOcts_S			stIssuerKeyHash;  /* Hash of public key */
	SEC_BIGINT_S			stSerialNumber;	  /* Certificate Serial Number */
} OCSP_CERT_ID_S;


/*
	This structure contains detailed information about a Single Request and the associated
	request extension list. An OCSP Resquest contains a list of Single Requests, where each
	Single Request contains information about a particular certficate. It contains the following
	information :
		* Certificate Serial Number
		* Hash of issuer's name
		* Hash of issuer's public key
		* Hash algorithm used to calculate the digest
		* List of extensions (optional) : The extension applicable here is only OCSP_SERV_LOC_S.
		  OCSP Service Locator :
		  This extension provides location information [like URL] about the OCSP server, which provides
		  status information about the identified certificates.
*/

/**
* @defgroup OCSP_SINGLE_REQ_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_Request
* {
*	OCSP_CERT_ID_S* pstCertID;
*	Extensions*     pstReqExtnList;
* } OCSP_SINGLE_REQ_S;
* @endcode
*
* @datastruct pstCertID Information about the Single Request.
* @datastruct pstReqExtnList List of extensions - OPTIONAL.
*/
typedef struct stOCSP_Request
{
	OCSP_CERT_ID_S* pstCertID;		/* Information about the Single Request */
	Extensions*		pstReqExtnList; /* List of extensions - OPTIONAL */
} OCSP_SINGLE_REQ_S;



/*
	Structures for supporting OCSP Response
*/

/*
	This structure contains the response type and encoded ocsp basic ocsp response.
	For a basic OCSP responder, stRespType type must be CID_PKIX_OCSP_BASIC. Currently,
	only this type is supported.
	stResp contains the DER encoding of Basic OCSP Response.
*/

/**
* @defgroup OCSP_RESP_BYTES_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_RespBytes
* {
*	SEC_AsnOid_S	stRespType;
*	SEC_AsnOcts_S	stResp;
* } OCSP_RESP_BYTES_S;
* @endcode
*
* @datastruct stRespType Response type.
* @datastruct stResp Encoded Basic Response.
*/
typedef struct stOCSP_RespBytes
{
	SEC_AsnOid_S	stRespType;	/* Response type  */
	SEC_AsnOcts_S	stResp;		/* Encoded Basic Response  */
} OCSP_RESP_BYTES_S;


/*
   This structure contains the status of the OCSP Response and the Basic OCSP Response.
   An OCSP response at a minimum consists of a responseStatus field indicating the processing
   status of the prior request. If the value of responseStatus is one of the error conditions,
   responseBytes are not set.
   Value of enRespStatus can be :
		OCSP_SUCCESSFUL = 0			OCSP Response is Successful
		OCSP_MALFORMEDREQUEST = 1	Malformed OCSP Request
		OCSP_INTERNALERROR = 2		Internal error occurred
		OCSP_TRYLATER = 3			Try Later
		OCSP_SIGREQUIRED = 5		Signature required in the OCSP Request
		OCSP_UNAUTHORIZED = 6		OCSP Request unauthorized

	A response message is composed of:
		* Status of the OCSP Response
		* Type of the Response and the Response [OCSP_RESP_BYTES_S]
*/

/**
* @defgroup OCSP_RESP_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_OCSPResponse
* {
*	OCSP_RESP_STATUS_E enRespStatus;
*	OCSP_RESP_BYTES_S* pstRespBytes;
* } OCSP_RESP_S;
* @endcode
*
* @datastruct enRespStatus Status of Basic OCSP Response.
* @datastruct pstRespBytes Basic OCSP Response.
*/
typedef struct stOCSP_OCSPResponse
{
	OCSP_RESP_STATUS_E enRespStatus; /* Status of Basic OCSP Response */
	OCSP_RESP_BYTES_S* pstRespBytes; /* Basic OCSP Response */
} OCSP_RESP_S;


/*
	This union contains information about the Responder. The field used is based on the Responder ID enum value.
	If  OCSP_RESPID_TYPE_E is set to OCSP_RESP_ID_BYNAME, pstByName structure is used.
	If  OCSP_RESPID_TYPE_E is set to OCSP_RESP_ID_BYKEY, pstByKey structure is used.
	pstByName : It contains the name of the responder.
	pstByKey  : It contains the SHA1-digest of the public key of the responder.
*/
/**
* @defgroup OCSP_RESPID_U
* @ingroup ocspUnions
* @code
* typedef union unOCSP_ResponderID
* {
*	SEC_NAME_S*    pstByName;
*	SEC_AsnOcts_S* pstByKey;
* } OCSP_RESPID_U;
* @endcode
*
* @datastruct pstByName Name of the responder.
* @datastruct pstByKey KeyHash of the responder's public key.
*/
typedef union unOCSP_ResponderID
{
	SEC_NAME_S*		pstByName;		/* Name of the responder */
	SEC_AsnOcts_S*	pstByKey;		/* KeyHash of the responder's public key */
} OCSP_RESPID_U;


/*
	This structure contains information about the Responder. Responder can be identified based on Name or Key hash
	If  OCSP_RESPID_TYPE_E is set to OCSP_RESP_ID_BYNAME, unRespID contains name of the responder.
	If  OCSP_RESPID_TYPE_E is set to OCSP_RESP_ID_BYKEY, unRespID contains the SHA1-digest of the public key of the responder.
*/
/**
* @defgroup OCSP_RESPID_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_RespID
* {
*	OCSP_RESPID_TYPE_E enRespChoiceId;
*	OCSP_RESPID_U      unRespID;
* } OCSP_RESPID_S;
* @endcode
*
* @datastruct enRespChoiceId Reponder Type - Name/KeyHash.
* @datastruct unRespID Information about the Responder.
*/
typedef struct stOCSP_RespID
{
	OCSP_RESPID_TYPE_E	enRespChoiceId;	/* Reponder Type - Name/KeyHash */
	OCSP_RESPID_U		unRespID;		/* Information about the Responder */
} OCSP_RESPID_S;


/*
	This structure contains information about the OCSP Response. It contains the following information :
		* Version of the OCSP Response
		* Information about the responder. It can be Name or Hash of the public key of the OCSP Responder.
		* ProducedAt : Time at which the Basic Response is signed.
		* List of Single Responses :
		  Single Response contains status information about each certificate mentioned in the OCSP request.
		  It contains the following information:
				* Certificate Serial Number
				* Hash of issuer's name
				* Hash of issuer's public key
				* Hash algorithm used to calculate the digest
		* List of extensions in OCSP Response (optional) : The extension applicable in the extension list is Nonce extension.
		  Nonce Extn: Nonce extn is SEC_EXTN_S, with SEC_AsnOcts_S set as the extension value.
*/
/**
* @defgroup OCSP_RESP_DATA_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_RESP_DATA_S
* {
*	SEC_UINT32*           pulVer;
*	OCSP_RESPID_S*        pstRespID;
*	SEC_GeneralizedTime_S stProducedAt;
*	SEC_List_S*           pstResponseList;
*	Extensions*           pstRespExtns;
* } OCSP_RESP_DATA_S;
* @endcode
*
* @datastruct pulVer Version of OCSP response.
* @datastruct pstRespID Information about the Responder.
* @datastruct stProducedAt ProducedAt time.
* @datastruct pstResponseList List of Single Responses.
* @datastruct pstRespExtns List of Extension - OPTIONAL.
*/
typedef struct stOCSP_RESP_DATA_S
{
	SEC_UINT32* pulVer;					/* Version of OCSP response */
	OCSP_RESPID_S* pstRespID;			/* Information about the Responder */
	SEC_GeneralizedTime_S stProducedAt;	/* ProducedAt time */
	SEC_List_S* pstResponseList;		/* List of Single Responses */
	Extensions* pstRespExtns;			/* List of Extension - OPTIONAL */
} OCSP_RESP_DATA_S;


/*
	This structure contains information about the single responses generated for each single requests, signature, alogirthm
	used to sign the OCSP Response and a list of certiticates.
	It contains the following information:
  		* Response Data
		  It contains the version, producedAt time, information about the responder, list of single responses and optionally
		  a list of extensions.
		* Signature algorithm
		* Signature computed across hash of the response
		* List of certificates which are used for signature verification (optional)
*/
/**
* @defgroup OCSP_BASIC_RESP_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSPBasicResponse
* {
*	OCSP_RESP_DATA_S*     pstTBSRespData;
*	SEC_ALG_IDENTIFIER_S* pstSigAlgId;
*	SEC_AsnBits_S         stSig;
*	SEC_List_S*           pstCertList;
* } OCSP_BASIC_RESP_S;
* @endcode
*
* @datastruct pstTBSRespData Contains detailed information about the OCSP Response
* @datastruct pstSigAlgId Signature Algorithm identifier
* @datastruct stSig Signature
* @datastruct pstCertList List of certificates, used for signature verification - OPTIONAL
*/
typedef struct stOCSPBasicResponse
{
	OCSP_RESP_DATA_S* pstTBSRespData;	/* Contains detailed information about the OCSP Response */
	SEC_ALG_IDENTIFIER_S* pstSigAlgId;	/* Signature Algorithm identifier */
	SEC_AsnBits_S stSig;				/* Signature */
	SEC_List_S* pstCertList;			/* List of certificates, used for signature verification - OPTIONAL */
} OCSP_BASIC_RESP_S;


/*
	This structure contains information about the single response, for a particular certificate.
	Single Response contains status information about each certificate mentioned in the OCSP request.
	It contains the following information:
		* Certificate ID
		  It contains the information like certificaet serial number, hash of issuer's name/public key etc. about
		  a particular certificate.
		* Status of the certificate
		* ThisUpdate : Time at which the status being indicated is known to be correct
		* NextUpdate (optional) : Time at or before which newer information will be available about the status
		  of the certificate
		* List of extensions in Single Response (optional): The different extensions applicable here are CRL
		  References and Archive Cut off.
		  CRL References (CRL_CID_S) :
		  This structure is used by OCSP responder to indicate the CRL on which a revoked or onHold certificate
		  is found. The CRL may be specified by a URL (the URL at which the CRL is available), a number (CRL number)
		  or a time (the time at which the relevant CRL was created).
		  Archive Cut off (SEC_GeneralizedTime_S) :
		  An OCSP responder may choose to retain revocation information beyond a certificate's expiration. The date
		  obtained by subtracting this retention interval value from the producedAt time in a response is defined as
		  the certificate's archive cutoff date.
*/
/**
* @defgroup OCSP_SINGLE_RESP_S
* @ingroup ocspStructures
* @code
* typedef struct stOCSP_SingleResponse
* {
*	OCSP_CERT_ID_S* pstCertID;
*	OCSP_CERT_STATUS_S*   pstCertStatus;
*	SEC_GeneralizedTime_S stThisUpdate;
*	SEC_GeneralizedTime_S stNextUpdate;
*	Extensions*           pstExtnList;
* } OCSP_SINGLE_RESP_S;
* @endcode
*
* @datastruct pstCertID Information about the response
* @datastruct pstCertStatus Status of a particular certifcate
* @datastruct stThisUpdate ThisUpdate time
* @datastruct stNextUpdate NextUpdate time - OPTIONAL
* @datastruct pstExtnList List of extensions - OPTIONAL
*/
typedef struct stOCSP_SingleResponse
{
	OCSP_CERT_ID_S* pstCertID;			/* Information about the response */
	OCSP_CERT_STATUS_S* pstCertStatus;	/* Status of a particular certifcate */
	SEC_GeneralizedTime_S stThisUpdate;	/* ThisUpdate time */
	SEC_GeneralizedTime_S stNextUpdate;	/* NextUpdate time - OPTIONAL */
	Extensions*		pstExtnList;		/* List of extensions - OPTIONAL */
} OCSP_SINGLE_RESP_S;


/*
	API for creating a Single Request
*/

/** @defgroup ocspFunctions
* @ingroup ocsp
* This section contains the ocsp Functions
*/



/**
* @defgroup OCSP_createSingleReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_SINGLE_REQ_S* OCSP_createSingleReq(SEC_BIGINT_S* pstCertSerNumber,
* X509_CERT_S* pIssuerCert, SEC_UINT32   ulHashAlg);
* @endcode
*
* @par Purpose
* This function creates a single OCSP Request.
* @par Description
* This function gets the serial number of the certificate to be validated from the user. It also gets the key and name
* from the issuer certificate. Once a single request is generated, the following APIs may be called to make the Single
* Request complete and valid OCSP_setExtnsToSingleReq (Optional). To create pstCertSerNumber, call X509_getSN() and pass
* X509_CERT_S(certificate). The algorithm passed must be a hash algorithm identifier. The single request generated must be
* added to the OCSP request, using the API OCSP_addSingleReqToOCSPReq().
*
* @param[in] pstCertSerNumber Serial number of the certificate to be
*							  validated
* @param[in] pIssuerCert Issuer certifcate [N/A]
* @param[in] ulHashAlg Hash algorithm identifier [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_SINGLE_REQ_S* Single request generation may fail due to :\n
* 1. Version passed to the API is invalid\n
* 2. Serial number or Issuer certificate is NULL\n
* 3. Algorithm passed is not a hash algorithm\n
* 4. Memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
*
* IssuerCert must be valid and signed
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL OCSP_SINGLE_REQ_S* OCSP_createSingleReq(SEC_BIGINT_S* pstCertSerNumber,
										X509_CERT_S* pIssuerCert,
										SEC_UINT32   ulHashAlg);




/**
* @defgroup OCSP_setExtnsToSingleReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_setExtnsToSingleReq(Extensions* pstExtnList,
* OCSP_SINGLE_REQ_S* pstSingleReq);
* @endcode
*
* @par Purpose
* This function is used to add the list of extensions to the OCSP SingleRequest.
*
* @par Description
* The extension applicable here is only OCSP Service Locator.\n
* OCSP Service Locator : This extension provides location information [like URL]
* about the OCSP server, which can provide status information about the identified
* certificate.
* If the request already has an extension list, that list is replaced by
* the new list of extensions.
* To create pstSingleReq, call OCSP_createSingleReq().
* To create pstExtnList, call the following APIs :\n
* SEC_LIST_NEW()
* Initialize the structure OCSP_SERV_LOCATOR_S
* X509_createExtn() : Pass the initialized OCSP_SERV_LOCATOR_S
* SEC_LIST_ADD_ELEMENT
* Once, the single request is generated it should be added to the OCSP
* request, using the API OCSP_addSingleReqToOCSPReq().
*
* @param[in] pstExtnList List of extension [N/A]
* @param[in] pstSingleReq Single request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Extensions are set successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input parameter(pstExtnList/pstSingleReq)is NULL
*			      Or no. of extensions in pstExtnList is 0 [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Extensions available is not a service
*			       locator extension [SEC_ERR_INVALID_EXTN|N/A]
* @retval SEC_UINT32 Dup of extensions(SEC_dupExtensions) failed [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If the extension list has an extension other than 'service locator'
* extension will not be set.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_setExtnsToSingleReq(Extensions* pstExtnList,
									OCSP_SINGLE_REQ_S*	pstSingleReq);

/*
	API for creating an OCSP Request
*/




/**
* @defgroup OCSP_createOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_REQUEST_S* OCSP_createOCSPReq(SEC_UINT32 ulVer);
* @endcode
*
* @par Purpose
* To generate an OCSP request.
* @par Description
* This function generates an OCSP request which contains status information
* about the list of certificates whose status is to be determined.
* Currently, only version V1(0) is supported. So, only 0 should be passed for ulVer.
* This API generates an OCSP Request with just version set to V1.
* Following APIs need to be called to generate a complete and valid OCSP Request:\n
* * OCSP_createSingleReq can be called any number of times\n
* * OCSP_addSingleReqToOCSPReq	can be called any number of times\n
* * OCSP_setRequestorToOCSPReq	(Optional)\n
* * OCSP_setReqExtnsToOCSPReq	(Optional)\n
* * OCSP_signOCSPReq			(Optional)\n
* * OCSP_addCertToOCSPReq		(Optional).
*
* @param[in] ulVer Version of the OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_REQUEST_S* Generated OCSP Request is returned [OCSP_REQUEST_S*|N/A]
* @retval OCSP_REQUEST_S* SEC_NULL Returned due to :\n
* 1. Invalid version passed to the API\n
* 2. Memory allocation failure [SEC_NULL|N/A]
* @par Dependency
* ocsp.h
*
* @par Note
*
* 1. If version value passed is not 0(for V1), request generation will fail.\n
* 2. If the version passed is V1 i.e 0, its value is not set in the OCSP request, because it is the default version.
*    But, currently only V1 is supported.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL OCSP_REQUEST_S* OCSP_createOCSPReq(SEC_UINT32 ulVer);




/**
* @defgroup OCSP_setRequestorToOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_setRequestorToOCSPReq(SEC_GEN_NAME_S* pRequestorName,
* const OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* This function adds the requestor name to the OCSPRequest.
*
* @par Description
* The requestor name must be valid.
* To generate pOCSPReq, call OCSP_createOCSPReq().
* To generate pRequestorName, call X509_createGeneralName().
* If the requestor name in the OCSP request is already set, the execution
* of this API will replace the old requestor name with the new name.
*
* @param[in] pRequestorName Name of the Requestor [N/A]
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Requestor name is set successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter(pRequestorName/pOCSPReq) is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Dup of pRequestorName is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
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

PSELINKDLL SEC_UINT32 OCSP_setRequestorToOCSPReq(SEC_GEN_NAME_S* pRequestorName,
							  		  const OCSP_REQUEST_S* pOCSPReq);




/**
* @defgroup OCSP_setReqExtnsToOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_setReqExtnsToOCSPReq(Extensions* pstReqExtns,
* const OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* This function is used to add a list of request extensions to the OCSP Request.
*
* @par Description
* The different extensions applicable here are: Nonce and Acceptable reponses.\n
* Nonce: Nonce is SEC_AsnOcts_S which is used in the request and response
* to prevent replay attacks. It makes sure that the Response sent for a
* particular Request is not outdated.\n
* Acceptable Responses: Acceptable Responses is a list of OIDs, which specifies the kinds of
* response types an OCSP client or responder understands.
*
* If any of the extension is neither Nonce nor Acceptable response, the
* extensions is not set.
* To create pOCSPReq, call OCSP_createOCSPReq().
* To create pstReqExtns, call the following APIs :
* SEC_LIST_NEW()
* Initialize the structure SEC_AsnOcts_S(for Nonce)/ Acceptable Response
* List(List of OIDs).
* X509_createExtn(): Pass the initialized Nonce/AcceptableRespList
* SEC_LIST_ADD_ELEMENT.
*
* @param[in] pstReqExtns List of extension [N/A]
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Extensions is added successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter(pstReqExtns/pOCSPReq) is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Number of extension in the list is 0 [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Extension in the list is neither nonce
* 							   nor acceptable response [SEC_ERR_INVALID_EXTN|N/A]
* @retval SEC_UINT32 Dup of extensions is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If any of the extension is neither Nonce or Acceptable response, the extensions is not set.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_setReqExtnsToOCSPReq(Extensions* pstReqExtns,
						     const OCSP_REQUEST_S* pOCSPReq);




/**
* @defgroup OCSP_addSingleReqToOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_addSingleReqToOCSPReq(OCSP_SINGLE_REQ_S* pSingleReq,
* const OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* This function adds a SingleRequest to the list of single requests in the OCSPRequest structure.
*
* @par Description
* This API must be called atleast once for generating
* a complete and valid OCSP request.
* To generate pOCSPReq, call OCSP_createOCSPReq.
* To generate pSingleReq, call OCSP_createSingleReq.
* More than one single requests can be added to the OCSP request.
*
* @param[in] pSingleReq Single Request [N/A]
* @param[in] pOCSPReq OCSP request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Single request was added successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter(pSingleReq/pOCSPReq) is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Dup of single request is failed[SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Single reqquest list creation or addition of the
*										single request to the OCSP request is failed [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Single OCSP request already exists [SEC_OCSP_ERR_REQ_EXISTS|N/A]
*
* @par Dependency
* ocsp.h
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

PSELINKDLL SEC_UINT32 OCSP_addSingleReqToOCSPReq(OCSP_SINGLE_REQ_S* pSingleReq,
									  const OCSP_REQUEST_S* pOCSPReq);




/**
* @defgroup OCSP_addCertToOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_addCertToOCSPReq(OCSP_REQUEST_S* pOCSPReq,
* X509_CERT_S* pCert);
* @endcode
*
* @par Purpose
* This function adds a certificate to the OCSP Request.
*
* @par Description
* These certificates are used for signature verification. More than one certificate
* can be added to the OCSP request. This API fails if the OCSP request is
* not signed.
* To generate pOCSPReq, call OCSP_createOCSPReq.
* To generate pCert, call X509_createCert.
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[in] pCert Certificate to be added to the request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Certificate is added to the request successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter(pOCSPReq/pCert) is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Certificate list creation or addition of the
*										single request to the OCSP request is failed [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Dup of certificate is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* These certificates are used for signature verification. The certificate passed to the API must be valid and signed.
* This API does not checks the validity of the certificate.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_addCertToOCSPReq(OCSP_REQUEST_S* pOCSPReq,
							 X509_CERT_S* pCert);




/**
* @defgroup OCSP_signOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_signOCSPReq(SEC_UINT32 ulHashAlg,
* SEC_PKEY_S* pPrivkey,
* SEC_List_S* pstCertList,
* OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* This function signs the OCSP Request using the private key and the
* algorithm provided by the application.
*
* @par Description
* The algorithm passed should be the hash algorithm. Signing algorithm is obtained from the private
* key. This API sets the signature and signature algorithm in OCSP Request.
* Follwowing APIs need to be called before calling this API:\n
* * OCSP_createOCSPReq\n
* * OCSP_createSingleReq can be called any number of times.\n
* * OCSP_addSingleReqToOCSPReq can be called any number of times.\n
* * OCSP_setRequestorToOCSPReq (Optional).\n
* * OCSP_setReqExtnsToOCSPReq (Optional).
* The OCSP_addCertToOCSPReq can be called after signing the OCSP Request.
* To generate pPrivkey, call CRYPT_genKeyPair.
* To generate pOCSPReq, call OCSP_createOCSPReq.
* To generate pstCertList, call the following APIs:\n
* SEC_LIST_NEW()\n
* X509_createCert\n
* SEC_LIST_ADD_ELEMENT
*
* @param[in] ulHashAlg Hash algorithm identifier [N/A]
* @param[in] pPrivkey Private key for signing [N/A]
* @param[in] pstCertList Certifcate list to be added to the Request [N/A]
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Signing of OCSP request is performed successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter(pPrivkey/pstCertList/pOCSPReq) is NULL
*					Or number of certificate in the pstCertList is 0 [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the OCSP request is invalid [SEC_OCSP_ERR_INVALID_REQUEST|N/A]
* @retval SEC_UINT32 Memory allocation is failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Encode of OCSP request is failed [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 ExpBufCopy is failed [SEC_ERR_BUF_COPY_FAILED|N/A]
* @retval SEC_UINT32 Signing of OCSP request is failed [SEC_ERR_SIGNING_FAILED|N/A]
* @retval SEC_UINT32 Dup of SEC_AsnOid_S or list copy is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Hash algorithm passed is invald [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Signature algorithm generated internally is invalid [SEC_ERR_INVALID_CID|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* The key passed must be a private key or a key pair.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_signOCSPReq(SEC_UINT32 ulHashAlg,
							SEC_PKEY_S* pPrivkey,
							SEC_List_S* pstCertList,
							OCSP_REQUEST_S* pOCSPReq);




/**
* @defgroup OCSP_encodeOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UCHAR* OCSP_encodeOCSPReq(OCSP_REQUEST_S*  pstOCSPReq,
* SEC_UINT32* pulOCSPReqLen);
* @endcode
*
* @par Purpose
* This function encodes the OCSP Request.
*
* @par Description
* All the mandatory fields in the OCSP Request must be set, before this API is called.
* Length of encoded OCSP request is set in pulOCSPReqLen.
* Following APIs need to be called before calling this API:\n
* * OCSP_createOCSPReq\n
* * OCSP_createSingleReq can be called any number of times\n
* * OCSP_addSingleReqToOCSPReq can be called any number of times\n
* * OCSP_setRequestorToOCSPReq (Optional)\n
* * OCSP_setReqExtnsToOCSPReq (Optional)\n
* * OCSP_signOCSPReq (Optional)\n
* * OCSP_addCertToOCSPReq (Optional)\n
* To generate pOCSPReq, call OCSP_createOCSPReq.
* To encode the OCSP request, call OCSP_encodeOCSPReq.
*
* @param[in] pstOCSPReq OCSP Request [N/A]
* @param[out] pulOCSPReqLen Length of encoded request [N/A]
*
* @retval SEC_UCHAR* Encoded OCSP Request [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* Encode of OCSP request generation may fail due to :\n
* 1. Input parameter is NULL\n
* 2. Encode failure\n
* 3. Memory allocation failure\n
* 4. ExpBufCopy failure [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* All the mandatory fields in the OCSP Request must be set, before this API is called.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* OCSP_encodeOCSPReq(OCSP_REQUEST_S* pstOCSPReq,
							 SEC_UINT32* pulOCSPReqLen);




/**
* @defgroup OCSP_decodeOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_REQUEST_S* OCSP_decodeOCSPReq(SEC_UCHAR* pucEncOCSPReq,
* SEC_UINT32  ulLen,
* SEC_UINT32* pulLenDecoded);
* @endcode
*
* @par Purpose
* This function decodes the encoded OCSP Request.
* @par Description
* This API returns the decoded OCSP request and sets the parameter 'pulLenDecoded' to number
* of bytes decoded. pucEncOCSPReq passed to this API must be a valid
* encoded OCSP request. After execution of this API, value of ulLen and
* *pulLenDecoded must be same.
* To encode the OCSP request, call OCSP_encodeOCSPReq.
*
* @param[in] pucEncOCSPReq Encoded OCSP Request [N/A]
* @param[in] ulLen Length of encoded request [N/A]
* @param[out] pulLenDecoded Number of bytes decoded [N/A]
*
* @retval OCSP_REQUEST_S* OCSP Request is returned [OCSP_REQUEST_S*|N/A]
* @retval OCSP_REQUEST_S* SEC_NULL Decode encoded OCSP request generation may fail due to:\n
* 1. Input parameter is NULL\n
* 2. ulLen is 0\n
* 3. Memory allocation failure\n
* 4. Decode failure\n [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_REQUEST_S* OCSP_decodeOCSPReq(SEC_UCHAR* pucEncOCSPReq,
								     SEC_UINT32  ulLen,
									 SEC_UINT32* pulLenDecoded);




/**
* @defgroup OCSP_verifyOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_verifyOCSPReq(OCSP_REQUEST_S* pOCSPReq,
* SEC_PKEY_S* pstPubKey);
* @endcode
*
* @par Purpose
* This function verifies the signature in the OCSP Request.
*
* @par Description
* The public key must be corresponding to the private key used for signing. The OCSP
* request passed to this API should have been signed.
* Follwowing APIs need to be called before calling this API:\n
* * OCSP_createOCSPReq\n
* * OCSP_createSingleReq can be called any number of times\n
* * OCSP_addSingleReqToOCSPReq dan be called any number of times\n
* * OCSP_setRequestorToOCSPReq (Optional)\n
* * OCSP_setReqExtnsToOCSPReq (Optional)\n
* * OCSP_signOCSPReq (Optional)\n
* * OCSP_addCertToOCSPReq (Optional)
*
* @param[in] pOCSPReq CSP Request [N/A]
* @param[in] pstPubKey Public key/keypair corresponding [N/A]
*					   to the private key used for signing [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Signature in the request is valid [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL Or request is unsigned [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Memory allocation is failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 ExpBufCopy is failed [SEC_ERR_BUF_COPY_FAILED|N/A]
* @retval SEC_UINT32 Signature alg id in the req is invalid [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Encode is failed [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Signature verification of OCSP Request is failed [SEC_ERR_SIGN_VERIFY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* The public key/Keypiar passed to this API must be corresponding to the private key used for signing.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_verifyOCSPReq(OCSP_REQUEST_S* pOCSPReq,
							  SEC_PKEY_S* pstPubKey);

/*
	Get functions for retrieving information from the OCSP Request
*/



/**
* @defgroup OCSP_getVerFromOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_getVerFromOCSPReq(const OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* To fetch the version from the given OCSP request message.
* @par Descritpion
* This function retrieves the Version from the OCSP Request.
* If it is not set, V1(0) is returned.
* If the request is invalid, SEC_ERR_INVALID_ARG is returned.
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Version of OCSP Request is returned [SEC_UINT32|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If it set to other than 0, the value set is returned.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_getVerFromOCSPReq(const OCSP_REQUEST_S* pOCSPReq);





/**
* @defgroup OCSP_checkRequestVersion
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_checkRequestVersion(const OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* To check whether a valid version is set in the OCSP Request message or not.
* @par Description
* This function checks the Version set in the OCSP Request structure.
* Version is not set in the case of V1(0) because it is the default.
* If it is not set, SEC_SUCCESS is returned, Else, SEC_OCSP_ERR_INVALID_VERSION
* is returned
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Version of OCSP Request is valid [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Version in the request is not V1(0) [SEC_OCSP_ERR_INVALID_VERSION|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* 1. If it is not set, V1(0) is returned.\n
* 2. If it set to other than 0, SEC_OCSP_ERR_INVALID_VERSION is returned.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_checkRequestVersion(const OCSP_REQUEST_S* pOCSPReq);




/**
* @defgroup OCSP_getRequestorFromOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_GEN_NAME_S* OCSP_getRequestorFromOCSPReq(const OCSP_REQUEST_S *pOCSPReq);
* @endcode
*
* @par Purpose
* To get the Requester's name from the OCSP request message.
* @par Description
* This function gets the Requester Name from the OCSP request.
* If name is not set in the request, SEC_NULL is returned.
* To generate OCSP request, call OCSP_createOCSPReq.
* To set requestor name in OCSP request, call OCSP_setRequestorToOCSPReq.
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_GEN_NAME_S* Requester Name is returned [SEC_GEN_NAME_S*|N/A]
* @retval SEC_GEN_NAME_S* SEC_NULL If input parameter is NULL Or Name is not available
* in the OCSP request [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_GEN_NAME_S* OCSP_getRequestorFromOCSPReq(const OCSP_REQUEST_S *pOCSPReq);




/**
* @defgroup OCSP_getReqExtnsFromOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* Extensions* OCSP_getReqExtnsFromOCSPReq(const OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* To fetch the request extensions from the given OCSP request message.
* @par Description
* This function parses the OCSP Request to get the list of request's extensions.
* If request's extension list in the request is not set,
* SEC_NULL is returned. The different extensions that can be there
* in the list are: Nonce and Acceptable reponses.
* To create pOCSPReq, call OCSP_createOCSPReq().
* To set request extensions in OCSP request, call OCSP_setReqExtnsToOCSPReq.
* To retrieve extension from the list of extensions, call SEC_LIST_GET_ELEMENT.
* To retrieve Nonce/AcceptableRespList from the extension, call
* X509Extn_getContent.
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Extensions* List of extensions is returned [Extensions*|N/A]
* @retval Extensions* If input parameter is NULL Or extension list is not set [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL Extensions* OCSP_getReqExtnsFromOCSPReq(const OCSP_REQUEST_S* pOCSPReq);




/**
* @defgroup OCSP_getSignCertListFromOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_List_S* OCSP_getSignCertListFromOCSPReq(const OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* To fetch the certificate list from the given OCSP Request message.
* @par Description
* This function extracts the certificate list from the OCSPRequest.
* This certificate can be used for signature verification. If certificate
* list in the request is not set, SEC_NULL is returned.
* To create pOCSPReq, call OCSP_createOCSPReq().
* Certificates in the OCSP request can be set by the APIs:\n
* OCSP_addCertToOCSPReq or OCSP_signOCSPReq.
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Certificate list set in the OCSP request is returned [SEC_List_S*|N/A]
* @retval SEC_List_S* Input parameter is NULL Or certificate list is not set [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* OCSP_getSignCertListFromOCSPReq(const OCSP_REQUEST_S* pOCSPReq);

/*
	Get functions for retrieving information from the Single Request
*/



/**
* @defgroup OCSP_getSingleReqFromOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_SINGLE_REQ_S* OCSP_getSingleReqFromOCSPReq(const OCSP_REQUEST_S* pOCSPReq,
* SEC_UINT32 ulIndex);
* @endcode
*
* @par Purpose
* To extract the Single Request from the OCSP Request based on the given index.
* @par Description
* This function extracts the Single Request from the OCSP Request based on the index passed.
* To retrieve the nth Single Request, index passed
* should be n-1. If the number of single requests in OCSP request is n, the
* index passed should be between 0 and n-1 (including 0 and N-1).
* To create pOCSPReq, call OCSP_createOCSPReq.
* To create a single request, call OCSP_createSingleReq.
* To add a single request to the OCSP request, call OCSP_addSingleReqToOCSPReq.
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[in] ulIndex Index of the Single request to be
*					 retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_SINGLE_REQ_S* Single Request in (ulIndex + 1)th position in
*							 the list is returned [OCSP_SINGLE_REQ_S*|N/A]
* @retval OCSP_SINGLE_REQ_S* SEC_NULL is returned in case of:\n
* 1. Input parameter is NULL Or\n
* 2. ulIndex < 0\n
* 3. ulIndex is greater than the number of Single requests\n
* 4. Number of Single requests in the OCSP request is 0 [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_SINGLE_REQ_S* OCSP_getSingleReqFromOCSPReq(const OCSP_REQUEST_S* pOCSPReq,
												SEC_UINT32 ulIndex);





/**
* @defgroup OCSP_getSerialNumFromSingleReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_BIGINT_S* OCSP_getSerialNumFromSingleReq(const OCSP_SINGLE_REQ_S *pSingleReq);
* @endcode
*
* @par Purpose
* To fetch the Serial Number of the certificate from the given OCSP Single request message.
* @par Description
* This function extracts the serial number of the certificate, whose
* status is there in the Single Request.
* If the serial number is not set, SEC_NULL is returned.
* Serial number returned is of type SEC_BIGINT_S
* uiLength contains the length of the serial number and aVal stores the
* serial number value.
* To create pSingleReq, call OCSP_createSingleReq.
*
* @param[in] pSingleReq Single Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BIGINT_S* Serial number of the certificate, corresponding to
*						the single request is returned [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* If input parameter is NULL Or Serial number is not
*				   set in the single request [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BIGINT_S* OCSP_getSerialNumFromSingleReq(const OCSP_SINGLE_REQ_S *pSingleReq);




/**
* @defgroup OCSP_checkSingleReqIssuer
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_checkSingleReqIssuer(X509_CERT_S* pIssuerCert,
* const OCSP_SINGLE_REQ_S* pSingleReq);
* @endcode
*
* @par Purpose
* To check whether the Issuer name and key are the same in the issuer's certificate
* and the given Single Request message.
* @par Description
* This function checks if the issuer name and the key (from which Keyhash is generated)
* in the SingleRequest is same as in the issuer's certificate.
* If either name or hash of the public key mismatches, an error code is returned.
* To create pSingleReq, call OCSP_createSingleReq.
* To create pIssuerCert, call X509_createCert.
*
* @param[in] pIssuerCert Issuer certificate [N/A]
* @param[in] pSingleReq Single Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Issuer name and key(from which Keyhash
*					  is generated) in the SingleRequest is same as in
*					  the certificate [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL Or
*			             	  Name/KeyHash is not set [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Issuer name is not set in the certificate[SEC_ERR_INVALID_ISSUERNAME|N/A]
* @retval SEC_UINT32 Hash calculation of Name/Key is failed [SEC_ERR_HASH_FAILED|N/A]
* @retval SEC_UINT32 Issuer name and key in the SingleRequest is
* 					  not same as in the certificate [SEC_ERR_ISSUER_MISMATCH|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* The certificate passed must be signed and valid.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_checkSingleReqIssuer(X509_CERT_S* pIssuerCert,
									 const OCSP_SINGLE_REQ_S* pSingleReq);




/**
* @defgroup OCSP_getExtnsFromSingleReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* Extensions* OCSP_getExtnsFromSingleReq(const OCSP_SINGLE_REQ_S* pSingleReq);
* @endcode
*
* @par Purpose
* To fetch the extensions from the given Single Request message.
* @par Description
* This function gets the extension list from a particular SingleRequest.
* If the extension list in the request is not set in the single request
* SEC_NULL is returned. The extension in the single request should have
* only service locator.
* To create pSingleReq, call OCSP_createSingleReq.
* To set extensions in OCSP request, call OCSP_setExtnsToSingleReq.
* To retrieve extension from the list of extensions, call SEC_LIST_GET_ELEMENT.
* To retrieve service locator structure from the extensiion, call
* X509Extn_getContent.
*
* @param[in] pSingleReq Single Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Extensions* List of extension is returned [Extensions*|N/A]
* @retval Extensions* If input parameter is NULL Or
* Extension list is not set in the single request [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL Extensions* OCSP_getExtnsFromSingleReq(const OCSP_SINGLE_REQ_S* pSingleReq);


/*
	API for creating a Single Response
*/



/**
* @defgroup OCSP_createSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_SINGLE_RESP_S*  OCSP_createSingleResp( OCSP_SINGLE_REQ_S*	pstSingleReq,
* OCSP_CERT_STATUS_TYPE_E ulCertStatus,
* DATETIME_S*  pRevTime,
* X509_CRL_REASON_E  enCRLReason,
* DATETIME_S*  pThisUpdate);
* @endcode
*
* @par Purpose
* To create an OCSP Single Request message.
* @par Description
* This function creates a Single Response for a single certificate
* with status (good, revoked or unknown).
* This API is used by an OCSP Responder to generate a single response.
* Serial number, issuer name hash and key hash is taken from the single request.
* If the status is revoked(OCSP_CERT_STATUS_REVOKED),
* Revoked Info structure in Single Response is set.
* If the CRL reason value is out of bound, CRL Reason is not set.
* The pRevTime must not be NULL.
* If the status is good(OCSP_CERT_STATUS_GOOD)/unknown(OCSP_CERT_STATUS_UNKNOWN)
* Revoked Info structure in Single Response is not set.
* CRL Reason is not set.
* The pRevTime should be NULL. If it is not NULL, its value is ignored.
* Following APIs may be called to make the generated single reponse complete and valid.\n
* OCSP_setNextUpdToSingleResp  (Optional)\n
* OCSP_setExtnsToSingleResp	   (Optional).\n
* To create pstSingleReq, call OCSP_createSingleReq.
* The ulCertStatus passed should be any one of these:\n
* OCSP_CERT_STATUS_GOOD\n
* OCSP_CERT_STATUS_REVOKED\n
* OCSP_CERT_STATUS_UNKNOWN.\n
* The enCRLReason passed should one of the values defined in X509_CRL_REASON_E.
*
* @param[in] pstSingleReq Single request for which the response is generated [N/A]
* @param[in] ulCertStatus Status of the certificate [N/A]
* @param[in] pRevTime Revocation time of the certificate [N/A]
* @param[in] enCRLReason Reason of revocation [N/A]
* @param[in] pThisUpdate Time at which the status was
* updated last [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_SINGLE_RESP_S* Single Response is returned [OCSP_SINGLE_RESP_S*|N/A]
* @retval OCSP_SINGLE_RESP_S* SEC_NULL is returned in case of:\n
* 1. If input parameter is NULL\n
* 2. ulCertStatus is OCSP_CERT_STATUS_REVOKED and pRevTime is NULL\n
* 3. enCertStatus value is invalid\n
* 4. pThisUpdate is not valid\n
* 5. pRevTime is not valid and ulCertStatus is OCSP_CERT_STATUS_REVOKED\n
* 6. Memory allocation failure\n
* 7. Copy function failed\n
* 8. SEC_DateTimeToGenTime failed [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
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

PSELINKDLL OCSP_SINGLE_RESP_S*  OCSP_createSingleResp( OCSP_SINGLE_REQ_S* pstSingleReq,
											OCSP_CERT_STATUS_TYPE_E ulCertStatus,
											DATETIME_S* 			pRevTime,
											X509_CRL_REASON_E 		enCRLReason,
											DATETIME_S* 			pThisUpdate);





/**
* @defgroup OCSP_setNextUpdToSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_setNextUpdToSingleResp(DATETIME_S* pNextUpdate,
* OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To set the Next Update time and date for the OCSP Single Request message.
*
* @par Description
* This function sets the date and time, at which the status of the
* certificate may be updated, in the single response.
* To create pSingleResp, call OCSP_createSingleResp.
*
* @param[in] pNextUpdate Time at which the response
* 						 might be updated next [N/A]
* @param[in] pSingleResp Single Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Next Update time is set successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL Or pNextUpdate
*					  date is invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 SEC_DateTimeToGenTime is failed [SEC_ERR_INVALID_DATETIME|N/A]
* @retval SEC_UINT32 Memory allocation is failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Copy function is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* The NextUpdate time passed must be greater than ThisUpdate time set in the single response.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_setNextUpdToSingleResp(DATETIME_S* pNextUpdate,
							 OCSP_SINGLE_RESP_S* pSingleResp);




/**
* @defgroup OCSP_setExtnsToSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_setExtnsToSingleResp(Extensions*  pstExtnList,
* OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To set the extensions list in the given OCSP Single Request message.
* @par Description
* This function sets extension list in the Single Response. The different
* extensions applicable here are: CRL References and Archive Cut off.\n
* CRL References (CRL_CID_S) :
* This structure is used by OCSP responder to indicate the CRL on which a revoked
* or onHold certificate is found. The CRL may be specified by a URL (the URL at
* which the CRL is available),  a number (CRL number) or a time (the time at which
* the relevant CRL was created).\n
* Archive Cut off (SEC_GeneralizedTime_S) :
* An OCSP responder may choose to retain revocation information beyond a certificate's
* expiration. The date obtained by subtracting this retention interval value from the
* producedAt time in a response is defined as the certificate's archive cutoff date.\n
* If the extension list is already set in the Single Response, it is replaced by the
* new list of extensions.
* To create pstExtnList, call the following APIs :
* SEC_LIST_NEW()
* Initialize the structure ARCHIVE_CUT_OFF_S / CRL_CID_S.
* X509_createExtn(): Pass the initialized ARCHIVE_CUT_OFF_S/CRL_CID_S
* SEC_LIST_ADD_ELEMENT.
* Once, the single request is generated it should be added to the Basic Response, using
* the API OCSP_addSingleRespToBasicResp().
*
* @param[in] pstExtnList List of extension [N/A]
* @param[in] pSingleResp Single Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Extension list is set successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the extension list is empty [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Extension in the list is neither
*					   CRL References nor Archive Cut off [SEC_ERR_INVALID_EXTN|N/A]
* @retval SEC_UINT32 Copy function is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If any of the extension in the list is neither CRL reference or Archive Cut Off extension,the extension list is not set.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_setExtnsToSingleResp(Extensions*	pstExtnList,
									 OCSP_SINGLE_RESP_S* pSingleResp);

/*
	API for creating a Basic Response
*/



/**
* @defgroup OCSP_createBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_BASIC_RESP_S* OCSP_createBasicResp(SEC_UINT32  ulVer);
* @endcode
*
* @par Purpose
* To create a basic OCSP Response message.
* @par Description
* This function creates the Basic OCSP response containing the status
* information about the certificates. Only version is set by this API.
* Following API need to be called to make the Basic Response complete and valid:\n
* * OCSP_createSingleResp can be called any number of times\n
* * OCSP_addSingleRespToBasicResp can be called any number of times\n
* * OCSP_setRespExtnsToBasicResp (Optional)\n
* * OCSP_addRespIdToBasicResp\n
* * OCSP_signBasicResp\n
* * OCSP_addCertToBasicResp (Optional)\n
*
* @param[in] ulVer Version of BasicResponse [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_BASIC_RESP_S* Basic Response is returned [OCSP_BASIC_RESP_S*|N/A]
* @retval OCSP_BASIC_RESP_S* SEC_NULL is returned in the case of:\n
* 1. Invalid version set in Basic Response\n
* 2. Memory allocation failure\n
* 3. Copy function failure\n [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If the version passed is V1 i.e 0, its value is not set in the Basic Response, because it is the default version.
* But, currently only V1 is supported.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL OCSP_BASIC_RESP_S* OCSP_createBasicResp(SEC_UINT32  ulVer);





/**
* @defgroup OCSP_addSingleRespToBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_addSingleRespToBasicResp(OCSP_SINGLE_RESP_S* pSingleResp,
* const OCSP_BASIC_RESP_S*  pResp);
* @endcode
*
* @par Purpose
* To add a Single Response message to existing list in the given OCSP Basic response message.
* @par Description
* This function adds a Single Response to the list of Single Responses
* in the Basic Response. This API must be called atleast once, before
* signing or encoding the Basic OCSP Response.
* To create pSingleResp, call OCSP_createSingleResp.
* To create pResp, call OCSP_createBasicResp.
*
* @param[in] pSingleResp Single Response [N/A]
* @param[in] pResp Basic Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Single response added successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Copy function is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 List creation or addition of single
* 					response to the Basic Response is failed [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Single response exists already [SEC_OCSP_ERR_RESP_EXISTS|N/A]
* @retval SEC_UINT32 Memory allocation is failed [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* ocsp.h
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

PSELINKDLL SEC_UINT32 OCSP_addSingleRespToBasicResp(OCSP_SINGLE_RESP_S* pSingleResp,
										const OCSP_BASIC_RESP_S*  pResp);




/**
* @defgroup OCSP_setRespExtnsToBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_setRespExtnsToBasicResp(Extensions* pRespExtn,
* OCSP_BASIC_RESP_S* pstBasicResp);
* @endcode
*
* @par Purpose
* To set the response extensions list to the given OCSP Basic response message.
* @par Description
* This function sets the Response Extension list in Basic Response.
* The extension applicable in the extension list is Nonce.\n
* Nonce :
* Nonce is SEC_AsnOcts_S which is used in the request and response to prevent
* replay attacks. It makes sure that the response sent for a particular request
* is not outdated.\n
* To create pRespExtn, call the following APIs:\n
* SEC_LIST_NEW()
* Initialize the structure SEC_AsnOcts_S.
* X509_createExtn() : Pass the initialized SEC_AsnOcts_S
* SEC_LIST_ADD_ELEMENT.
* To create pstBasicResp, call OCSP_createBasicResp.
*
* @param[in] pRespExtn List of extensions to be added to the response [N/A]
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Response extensions is added succesfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Extension list is empty [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Copy function is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Extension in the list is not Nonce [SEC_ERR_INVALID_EXTN|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If any of the extension in the list is not Nonce, the extension list will not be set.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_setRespExtnsToBasicResp(Extensions* pRespExtn,
										OCSP_BASIC_RESP_S* pstBasicResp);



/**
* @defgroup OCSP_addCertToBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_addCertToBasicResp(OCSP_BASIC_RESP_S* pstBasicResp,
* X509_CERT_S*	pCert);
* @endcode
*
* @par Purpose
* To add a certificate to the given OCSP basic Response message.
* @par Description
* This function adds a certificate to the OCSP Response. These certificates
* can be used for signature verification.There is one more alternative to
* this API. The list of certificates can be added at the time of signing
* Basic Response. Before calling this API, OCSP_signBasicResp must be called
* that is Basic OCSP Response must be signed.
* To create pstBasicResp, call OCSP_createBasicResp.
* To create pCert, call X509_createCert.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[in] pCert Certificate to be added [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Certificate is added to the BasicResp successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input parameter is NULL Or
*					  Basic Response is not signed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Certificate list creation or addition of
*						certificate to the list is failed [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Dup of certificate is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* These certificates are used for signature verification. The certificate passed to the API must be valid and signed.
* This API does not checks the validity of the certificate.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_addCertToBasicResp(OCSP_BASIC_RESP_S* pstBasicResp,
								   X509_CERT_S* pCert);




/**
* @defgroup OCSP_addRespIdToBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_addRespIdToBasicResp(const OCSP_BASIC_RESP_S* pstBasicResp,
* OCSP_RESPID_TYPE_E  enRespIdtype,
* SEC_VOID*  pKeyOrName);
* @endcode
*
* @par Purpose
* To add a responder ID to the given OCSP Basic response.
* @par Description
* This function adds a Responder ID to the Basic Response. The responder
* ID can be Name or Keyhash[SHA1] of public key. This responder ID is used
* for identifying the OCSP Reponder. KeyHash is SEC_AsnOcts_S where octs is
* set to the hash[only SHA1] of public key and octetLen is set to the hash
* length.
* The enRespIdtype passed should be either OCSP_RESP_ID_BYNAME or OCSP_RESP_ID_BYKEY.
* If enRespIdtype is OCSP_RESP_ID_BYNAME, Name(SEC_NAME_S) must be passed for pKeyOrName.
* If enRespIdtype is OCSP_RESP_ID_BYKEY, Key(SEC_PKEY_S) must be passed for pKeyOrName.
* To create pstBasicResp, call OCSP_createBasicResp.
* To create Name, call X509_createDN.
* To create Key, call CRYPT_genKeyPair.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[in] enRespIdtype ResponserID type [N/A]
* @param[in] pKeyOrName Name/Key of the Responder [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Responder Id added successfully [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Data copy is failed [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Key Encode failed [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Key digest calculation failed [SEC_ERR_CREATE_DIGEST_FAIL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* User needs to pass SEC_NAME_S or SEC_PKEY_S as pKeyOrName. If the key is passed, key digest[SHA1] is calculated
* internally and set.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_addRespIdToBasicResp(const OCSP_BASIC_RESP_S* pstBasicResp,
									 OCSP_RESPID_TYPE_E		  enRespIdtype,
									 SEC_VOID*				  pKeyOrName);



/**
* @defgroup OCSP_createRespId
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESPID_S* OCSP_createRespId(OCSP_RESPID_TYPE_E enChoice,
* SEC_VOID* pKeyOrName);
* @endcode
*
* @par Purpose
* To create an OCSP Responder ID structure.
* @par Description
* This function creates a Responder ID. The responder id can be Name or
* Keyhash[SHA1] of public key. This responder id is used for identifying
* the OCSP Reponder. KeyHash is SEC_AsnOcts_S where octs is set to the
* hash[only SHA1] of public key and octetLen is set to the hash length.
* enRespIdtype passed should be either OCSP_RESP_ID_BYNAME or OCSP_RESP_ID_BYKEY.
* If enRespIdtype is OCSP_RESP_ID_BYNAME, Name(SEC_NAME_S) must be passed for pKeyOrName.
* If enRespIdtype is OCSP_RESP_ID_BYKEY, Key(SEC_PKEY_S) must be passed for pKeyOrName.
* To create pstBasicResp, call OCSP_createBasicResp.
* To create Name, call X509_createDN.
* To create Key, call CRYPT_genKeyPair.
*
* @param[in] enChoice The responder ID type,either of OCSP_RESP_ID_BYNAME or OCSP_RESP_ID_BYKEY [N/A]
* @param[in] pKeyOrName Name or Key of the Responder [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_RESPID_S* Pointer to Responder Id [OCSP_RESPID_S*|N/A]
* @retval OCSP_RESPID_S* If creation of responder Id failed [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* User need to pass SEC_NAME_S or SEC_PKEY_S as pKeyOrName. If the key is passed, key digest[SHA1] is calculated
* internally and set.
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_RESPID_S* OCSP_createRespId(OCSP_RESPID_TYPE_E enChoice,
								 SEC_VOID* pKeyOrName);



/**
* @defgroup OCSP_checkBasicRespResponderId
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_checkBasicRespResponderId(const OCSP_BASIC_RESP_S* pstBasicResp,
* X509_CERT_S* pCert);
* @endcode
*
* @par Purpose
* To check whether the OCSP Responder ID in the given Basic response message
* is the same as the one in the given certificate.
* @par Description
* This function verifies whether the Responder ID(Issuer's Name/Key) in the
* Basic Response is same as in the certificate. The responder id can be name
* or hash of public key.
* If responder id set in the basic response is OCSP_RESP_ID_BYNAME, comparison
* of Name is performed.
* If responder id set in the basic response is OCSP_RESP_ID_BYKEY, comparison
* of Key hash is performed. Hash of the key(set in pCert)calculated must be
* same as set in pstBasicResp.
* To create pstBasicResp, call OCSP_createBasicResp.
* To create pCert, call X509_createCert
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[in] pCert Certificate of the Responder[N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Responder Id is valid [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Issuer name is not set in pCert [SEC_ERR_INVALID_ISSUERNAME|N/A]
* @retval SEC_UINT32 Name in the Basic Response and pCert are different [SEC_X509_ERR_NAME_MISMATCH|N/A]
* @retval SEC_UINT32 X509_extractPublicKey function is failed [SEC_ERR_KEY_GEN_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Key Encode failed [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 If hash calculation of Key failed [SEC_ERR_HASH_FAILED|N/A]
* @retval SEC_UINT32 If Responder ID type is neither name nor key-hash [SEC_ERR_INVALID_MODE|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_checkBasicRespResponderId(const OCSP_BASIC_RESP_S* pstBasicResp,
										  X509_CERT_S* pCert);




/**
* @defgroup OCSP_signBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_signBasicResp(SEC_UINT32  ulHashAlgId,
* SEC_PKEY_S* 	pPrivKey,
* SEC_List_S*   pstCertList,
* OCSP_BASIC_RESP_S*  pstBasicResp,
* DATETIME_S*	pstProducedAt);
* @endcode
*
* @par Purpose
* To sign a basic OCSP Response message.
* @par Description
* This function is used to sign Basic Response. This API sets the
* signature and signature algorithm in Basic Response. The algorithm
* passed must be a hash algorithm. The list of certificates can be empty.
* Instead of passing the list of certificates while signing, it can be
* added later.
* To create pstBasicResp, call OCSP_createBasicResp.
* To create pPrivKey, call CRYPT_genKeyPair.
* To create pstCertList, call the following APIs:\n
* SEC_LIST_NEW().
* X509_createCert.
* SEC_LIST_ADD_ELEMENT.
* Following APIs need to be called before calling this API:\n
* * OCSP_createBasicResp\n
* * OCSP_createSingleResp can be called any number of times\n
* * OCSP_addSingleRespToBasicResp can be called any number of times\n
* * OCSP_setRespExtnsToBasicResp (Optional)\n
* * OCSP_addRespIdToBasicResp.
*
* @param[in] ulHashAlgId Hash algorithm identifier [N/A]
* @param[in] pPrivKey Private key for signing [N/A]
* @param[in] pstCertList Certificate list to be added [N/A]
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[in] pstProducedAt Time at which the Basic Response is signed [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Signing of Basic Response is successful [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Signing of Basic OCSP Response failed [SEC_ERR_SIGNING_FAILED|N/A]
* @retval SEC_UINT32 ExpBufCopy failed [SEC_ERR_BUF_COPY_FAILED|N/A]
* @retval SEC_UINT32 Copy function failed [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Hash alg id passed invalid [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Encode failed [SEC_ERR_ENCODE_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If the Basic Response is already signed, the signature is replaced with the new signature. ProducedAt time is not
* compared with ThisUpdate and NextUpdate set in the single responses. Ideally, producedAt time should be greater than
* thisUpdate time.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_signBasicResp(SEC_UINT32	 ulHashAlgId,
						  SEC_PKEY_S* 			pPrivKey,
						  SEC_List_S* 			pstCertList,
						  OCSP_BASIC_RESP_S* 	pstBasicResp,
						  DATETIME_S*			pstProducedAt);




/**
* @defgroup OCSP_verifyBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_verifyBasicResp(const OCSP_BASIC_RESP_S* pstBasicResp,
* X509_CERT_S*	pCert);
* @endcode
*
* @par Purpose
* To verify the signature in the given OCSP Basic response message.
* @par Description
* This function verifies the signature in the Basic Response. The public
* key/ Keypair corresponding to the private key used for signing, should
* be used for verification. Else, verify will fail. So the certificate
* having the required public key must be passed.
* To create pstBasicResp, call OCSP_createBasicResp.
* To create pCert, call X509_createCert.
*
* @param[in] pstBasicResp Basic OCSP response [N/A]
* @param[in] pCert Certificate which has the public corresponding to the private key used for signing [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Signature in the Basic Response is valid [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL Or
*					  Basic Response is not signed [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 X509_extractPublicKey failed [SEC_ERR_KEY_GEN_FAILED|N/A]
* @retval SEC_UINT32 Encode failed [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 ExpBufCopy failed [SEC_ERR_BUF_COPY_FAILED|N/A]
* @retval SEC_UINT32 Algorithm identifier set in Basic Response
* 		 				is invalid [SEC_ERR_INVALID_ALGID|N/A]
* @retval SEC_UINT32 Signature verification failed [SEC_ERR_SIGN_VERIFY_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_verifyBasicResp(const OCSP_BASIC_RESP_S* pstBasicResp,
									  X509_CERT_S*	pCert);

/*
	API for creating an OCSP Response
*/



/**
* @defgroup OCSP_createOCSPResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESP_S* OCSP_createOCSPResp( SEC_UINT32 ulRespStatus,
* SEC_INT32      ulRespType,
* OCSP_BASIC_RESP_S* pstBasicResp);
* @endcode
*
* @par Purpose
* To create an OCSP response message.
* @par Description
* This function creates the OCSP response containing the status
* information about the certificates. Before calling this API, a Basic
* Response must be generated. If the status is not successful, pstBasicResp
* passed can be NULL. Response type can only be CID_PKIX_OCSP_BASIC.
* If the status of the response is OCSP_SUCCESSFUL, following APIs need
* to be called before calling this API.\n
* * OCSP_createBasicResp\n
* * OCSP_createSingleResp can be called any number of times\n
* * OCSP_addSingleRespToBasicResp can be called any number of times\n
* * OCSP_setRespExtnsToBasicResp (Optional)\n
* * OCSP_addRespIdToBasicResp\n
* * OCSP_addCertToBasicResp (Optional)\n
* * OCSP_signBasicResp.
* If the status of the response is one of the error conditions, this API
* can directly be called. In that case, SEC_NULL should be passed for
* pstBasicResp.
* To create pstBasicResp, call OCSP_createBasicResp().
* Value of ulRespType must be CID_PKIX_OCSP_BASIC.
*
* @param[in] ulRespStatus Status of the response [N/A]
* @param[in] ulRespType Response type [N/A]
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_RESP_S* pOCSPResp OCSP Response is returned [OCSP_RESP_S*|N/A]
* @retval OCSP_RESP_S* SEC_NULL is returned in case of:\n
* 1. Input parameter is NULL\n
* 2. pstBasicResp is NULL and ulRespStatus is OCSP_SUCCESSFUL\n
* 3. pstBasicResp is Unsigned and ulRespStatus is OCSP_SUCCESSFUL\n
* 4. pstBasicResp does not have any single resp and ulRespStatus is OCSP_SUCCESSFUL\n
* 5. Encode failed\n
* 6. ExpBufCopy failed\n
* 7. Memory allocation failure\n
* 8. ulRespStatus is not CID_PKIX_OCSP_BASIC [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If the status is not successful, pstBasicResp passed should not be null.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL OCSP_RESP_S* OCSP_createOCSPResp( SEC_UINT32	 ulRespStatus,
								  SEC_INT32			 ulRespType,
								  OCSP_BASIC_RESP_S* pstBasicResp);


/**
* @defgroup OCSP_createErrorResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESP_S* OCSP_createErrorResp(OCSP_RESP_STATUS_E enRespStatus);
* @endcode
*
* @par Purpose
* To create an OCSP response when the status of the response is other than OCSP_SUCCESSFUL.
* @par Description
* This function generates an OCSP Response, when status of the Response
* is one of the error conditions(malformed request, internal error,
* try later, signature required, unauthorized). If the status passed to this API
* is OCSP_SUCCESSFUL, response generation fails. In that case,
* OCSP_createOCSPResp API must be used to generate the OCSP Response.
* Value of enRespStatus can be:\n
* OCSP_MALFORMEDREQUEST : 1, If OCSP Request is malformed\n
* OCSP_INTERNALERROR : 2, If internal error occurred\n
* OCSP_TRYLATER : 3, Try Later\n
* According to the standard, 4 must not be passed.\n
* OCSP_SIGREQUIRED = 5, If signature is required in the OCSP Request\n
* OCSP_UNAUTHORIZED = 6, If OCSP Request is unauthorized.
*
* @param[in] enRespStatus Status of the Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_RESP_S* Generated OCSP Response is returned [OCSP_RESP_S*|N/A]
* @retval OCSP_RESP_S* SEC_NULL is returned in case of:\n
* 1. enRespStatus is not any one of the above defined values\n
* 2. Memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* If the status passed is OCSP_SUCCESSFUL, response generation will fail
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL OCSP_RESP_S* OCSP_createErrorResp(OCSP_RESP_STATUS_E enRespStatus);





/**
* @defgroup OCSP_encodeOCSPResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UCHAR* OCSP_encodeOCSPResp(OCSP_RESP_S*  pOCSPResp,
* SEC_UINT32*  pulOCSPRespLen);
* @endcode
*
* @par Purpose
* To encode the given OCSP Response message.
* @par Description
* This function encodes the OCSP Response. All the mandatory fields in
* the OCSP Response must be set, before this API is called. Length of
* the encoded OCSP response is set in pulOCSPRespLen.
* If the status of the response is OCSP_SUCCESSFUL, following APIs need to be called before calling this API.\n
* * OCSP_createBasicResp\n
* * OCSP_createSingleResp  can be called any number of times\n
* * OCSP_addSingleRespToBasicResp can be called any number of times\n
* * OCSP_setRespExtnsToBasicResp (Optional)\n
* * OCSP_addRespIdToBasicResp\n
* * OCSP_signBasicResp\n
* * OCSP_addCertToBasicResp	 (Optional)\n
* * OCSP_createOCSPResp\n
* If the status of the response is one of the error conditions, either of
* these API need to be called.\n
* * OCSP_createOCSPResp\n
* * OCSP_createErrorResp
*
* @param[in] pOCSPResp OCSP Response [N/A]
* @param[out] pulOCSPRespLen Length of encoded response [N/A]
*
* @retval SEC_UCHAR* Encoded OCSP Response is returned [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* SEC_NULL is returned in case of:\n
* 1. Input parameter is NULL\n
* 2. Memory allocation failure\n
* 3. Encode failure\n
* 4. ExpBufCopy failure [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* All the mandatory fields in the OCSP Response must be set, before this API is called.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* OCSP_encodeOCSPResp(OCSP_RESP_S*  pOCSPResp,
							 SEC_UINT32*     pulOCSPRespLen);




/**
* @defgroup OCSP_decodeOCSPResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESP_S* OCSP_decodeOCSPResp(SEC_UCHAR*  pucEncOCSPResp,
* SEC_UINT32  ulLen,
* SEC_UINT32* pulLenDecoded);
* @endcode
*
* @par Purpose
* To generate a decoded OCSP Response message from the given encoded
* OCSP response message.
* @par Description
* This function decodes the encoded OCSP Response. This API returns the
* decoded OCSP Response and sets the parameter 'pulLenDecoded' to number
* of bytes decoded. After execution of this API, value of ulLen and
* pulLenDecoded must be same.
* To encode the OCSP response, call OCSP_encodeOCSPResp.
*
* @param[in] pucEncOCSPResp Encoded OCSP Response [N/A]
* @param[in] ulLen Length of encoded response [N/A]
* @param[out] pulLenDecoded Number of bytes decoded [N/A]
*
* @retval OCSP_RESP_S* OCSP Response [OCSP_RESP_S*|N/A]
* @retval OCSP_RESP_S* SEC_NULL is returned in case of:\n
* 1. Input parameter is NULL\n
* 2. Value of ulLen passed is 0\n
* 3. Decode failure\n
* 4. Memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_RESP_S* OCSP_decodeOCSPResp(SEC_UCHAR*	pucEncOCSPResp,
								     SEC_UINT32  ulLen,
									 SEC_UINT32* pulLenDecoded);




/**
* @defgroup OCSP_validateResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_validateResp(const OCSP_SINGLE_REQ_S* pSingleReq,
* OCSP_SINGLE_RESP_S* pSingleResp,
* SEC_UINT32         ulValidityPeriod);
* @endcode
*
* @par Purpose
* To check the validity of the given OCSP Signed response.
* @par Description
* This function checks the validity of a signed response. It checks for
* the following conditions:\n
* 1) Checks whether the certificate identified in a received single
* response corresponds to that in the single request. that is Certificate
* serial number and keyhash in the single request and single response
* are same.\n
* 2) The time at which the status being indicated is known to be correct
* (ThisUpdate) is sufficiently recent.\n
* 3) ThisUpdate time is earlier than the current time.\n
* 4) Time interval between the current time and thisUpdate time is not
* greater than ulValidityPeriod.\n
* 5) When available, the NextUpdate time, at or before which newer
* information will be available about the status of the certificate
* is greater than or same as the current time.\n
* To generate pSingleReq call,\n
* OCSP_createSingleReq\n
* OCSP_setExtnsToSingleReq  (Optional)\n
* To generate pSingleResp call,\n
* OCSP_createSingleResp\n
* OCSP_setNextUpdToSingleResp  (Optional)\n
* OCSP_setExtnsToSingleResp  (Optional)
*
* @param[in] pSingleReq Single request [N/A]
* @param[in] pSingleResp Single Response [N/A]
* @param[in] ulValidityPeriod Validity period(Seconds) [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Single response is valid [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL Or Certificate
*							  serial number is not set [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Certificate serial number in req and resp
*							does not match [SEC_ERR_REQ_RESP_MISMATCH|N/A]
* @retval SEC_UINT32 GenTimeToDateTime function is failed [SEC_ERR_INVALID_DATETIME SEC|N/A]
* @retval SEC_UINT32 It is returned in case pf:\n
* 1. pstCurrDate is earlier than pstThisUpd
* 2. Time interval between current time and thisUpdate
* 3. Time is greater than ulValidityPeriod
* 4. pstNextUpd is earlier than the current time [SEC_OCSP_ERR_INVALID_RESPONSE|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* 1. Validity period needs to be entered in Seconds.\n
* 2. Signature verification is not performed by this API.\n
* 3. Current time is taken from the local system. So, user need to make sure
*    the system date and time is correct.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_validateResp(const OCSP_SINGLE_REQ_S* pSingleReq,
							 OCSP_SINGLE_RESP_S*	  pSingleResp,
							 SEC_UINT32				  ulValidityPeriod);


/*
	Get functions for retrieving information from the OCSP Response
*/



/**
* @defgroup OCSP_getRespStatusFromOCSPResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESP_STATUS_E OCSP_getRespStatusFromOCSPResp(const OCSP_RESP_S *pResp);
* @endcode
*
* @par Purpose
* To fetch the status of the given OCSP Response message.
* @par Description
* This function obtains the status of the OCSP Response. The reponse
* status can be successful, malformed request, internal error, try later,
* signature required, unauthorized. If the OCSP Response is invalid,
* OCSP_INVALID_RESP_STATUS is returned.
* To generate a complete and valid OCSP response following APIs need
* to be called:\n
* * OCSP_createBasicResp\n
* * OCSP_createSingleResp			can be called any number of times\n
* * OCSP_addSingleRespToBasicResp  can be called any number of times\n
* * OCSP_setRespExtnsToBasicResp  (Optional)\n
* * OCSP_addRespIdToBasicResp\n
* * OCSP_signBasicResp\n
* * OCSP_addCertToBasicResp	 (Optional)\n
* * OCSP_createOCSPResp or\n
* * OCSP_createErrorResp\n
*
* @param[in] pResp OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_RESP_STATUS_E Status of the OCSP Response is returned [OCSP_RESP_STATUS_E|N/A]
* @retval OCSP_RESP_STATUS_E If input parameter is NULL Or
*							  Response status is not set [OCSP_INVALID_RESP_STATUS|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_RESP_STATUS_E OCSP_getRespStatusFromOCSPResp(const OCSP_RESP_S *pResp);




/**
* @defgroup OCSP_getRespTypeFromOCSPResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* OCSP_getRespTypeFromOCSPResp(const OCSP_RESP_S *pResp);
* @endcode
*
* @par Purpose
* To fetch the Response type from the given OCSP Response message.
* @par Description
* This function obtains the Response Type from the OCSPResponse. If the
* reponse is set to CID_PKIX_OCSP_BASIC, OID corresponding to
* CID_PKIX_OCSP_BASIC is returned.
* To generate a complete and valid OCSP response following APIs need
* to be called :\n
* * OCSP_createBasicResp\n
* * OCSP_createSingleResp	can be called any number of times\n
* * OCSP_addSingleRespToBasicResp  can be called any number of times\n
* * OCSP_setRespExtnsToBasicResp  (Optional)\n
* * OCSP_addRespIdToBasicResp\n
* * OCSP_signBasicResp\n
* * OCSP_addCertToBasicResp	(Optional)\n
* * OCSP_createOCSPResp.
*
* @param[in] pResp OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* OCSP Response type is returned [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If input parameter is NULL Or Response type is not set [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnOcts_S* OCSP_getRespTypeFromOCSPResp(const OCSP_RESP_S *pResp);





/**
* @defgroup OCSP_extractBasicRespFromOCSPResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_BASIC_RESP_S* OCSP_extractBasicRespFromOCSPResp(const OCSP_RESP_S *pResp);
* @endcode
*
* @par Purpose
* To extract the OCSP Basic Response message from the given OCSP Response message.
* @par Description
* This function retrieves the Basic Response from the DER encoding in
* the OCSP Response. The encoded basic response stored in the OCSP
* response is decoded and returned. Pointer to OCSP_BASIC_RESP_S returned
* MUST be freed by the user.
* To generate a complete and valid OCSP response following APIs need
* to be called :\n
* * OCSP_createBasicResp\n
* * OCSP_createSingleResp   can be called any number of times\n
* * OCSP_addSingleRespToBasicResp  Can be called any number of times\n
* * OCSP_setRespExtnsToBasicResp  (Optional)\n
* * OCSP_addRespIdToBasicResp\n
* * OCSP_signBasicResp\n
* * OCSP_addCertToBasicResp	(Optional)\n
* * OCSP_createOCSPResp.
*
* @param[in] pResp OCSP Response [N/A]
* @param[out] N/A
*
* @retval OCSP_BASIC_RESP_S* Basic Response retrieved from the OCSP response [OCSP_BASIC_RESP_S*|N/A]
* @retval OCSP_BASIC_RESP_S* SEC_NULL is returned in case of :\n
* 1. Input parameter is NULL\n
* 2. Decode failure\n
* 3. Memory allocation failure [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_BASIC_RESP_S* OCSP_extractBasicRespFromOCSPResp(const OCSP_RESP_S *pResp);


/*
	Get functions for retrieving information from the Basic Response
*/



/**
* @defgroup OCSP_getSignCertListFromBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_List_S* OCSP_getSignCertListFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);
* @endcode
*
* @par Purpose
* To fetch the list of certificates from the given OCSP Basic Response message.
* @par Description
* This function extracts the list of certificates from the Basic Response.
* These certificates can be used for signature verification. Validity
* of the certificate returned is not ensured by this API.
* To generate a complete and valid basic ocsp response following APIs need
* to be called :\n
* * OCSP_createBasicResp\n
* * OCSP_createSingleResp		can be called any number of times\n
* * OCSP_addSingleRespToBasicResp  can be called any number of times\n
* * OCSP_setRespExtnsToBasicResp	 (Optional)\n
* * OCSP_addRespIdToBasicResp\n
* * OCSP_signBasicResp\n
* * OCSP_addCertToBasicResp	  (Optional).
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* List of certificates used for sign verification is returned [SEC_List_S*|N/A]
* @retval SEC_List_S* SEC_NULL is returned in case of :\n
* 1. Input parameter is NULL\n
* 2. No certificates available in the basic response [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* OCSP_getSignCertListFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);




/**
* @defgroup OCSP_getVersionFromBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_getVersionFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);
* @endcode
*
* @par Purpose
* To fetch the version from the given OCSP Response message.
* @par Description
* This function retrieves the Version from the BasicResponse. If the
* version is not set in the Basic response, default V1(0) is returned.
* To create basic ocsp response, call OCSP_createBasicResp.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Version of Basic OCSP Response is returned [SEC_UINT32|N/A]
* @retval SEC_UINT32 If input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_getVersionFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);




/**
* @defgroup OCSP_checkBasicRespVersion
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_checkBasicRespVersion(const OCSP_BASIC_RESP_S *pstBasicResp);
* @endcode
*
* @par Purpose
* To verify whether the version in the given OCSP Basic response message
* is a valid version or not.
* @par Description
* This function checks whether the version in Basic Response is V1(0)
* or not. If it is set to something other than 0, SEC_OCSP_ERR_INVALID_VERSION is returned
* because currently only V1(0) is supported and since this is the default value,
* it is not set.
* To create basic ocsp response, call OCSP_createBasicResp.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Version of Basic OCSP Response is valid [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is SEC_NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Version of Basic OCSP Response is invalid [SEC_ERR_INVALID_VERSION|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_checkBasicRespVersion(const OCSP_BASIC_RESP_S *pstBasicResp);




/**
* @defgroup OCSP_getResponderTypeFromBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESPID_TYPE_E OCSP_getResponderTypeFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);
* @endcode
*
* @par Purpose
* To fetch the OCSP Responder type from the given OCSP Basic response message.
* @par Description
* This function gets the OCSP responder type (name/key-hash) from the
* Basic Response. If the responder type is not set, OCSP_INVALID_RESP_ID
* is returned.
* To add the Responder ID to basic response call.\n
* * OCSP_createBasicResp\n
* * OCSP_addRespIdToBasicResp.
*
* @param[in] pstBasicResp OCSP Basic Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_RESPID_TYPE_E Responder type(Name/KeyHash) is returned [OCSP_RESP_ID_BYNAME / OCSP_RESP_ID_BYKEY|N/A]
* @retval OCSP_RESPID_TYPE_E If input parameter is NULL Or Responder ID not set [OCSP_INVALID_RESP_ID|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_RESPID_TYPE_E OCSP_getResponderTypeFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);




/**
* @defgroup OCSP_getResponderIdFromBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_VOID* OCSP_getResponderIdFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);
* @endcode
*
* @par Purpose
* To fetch the OCSP Responder ID from the given OCSP Basic Response.
* @par Description
* This function gets the OCSP responder Name/KeyHash from the Basic
* Response. Before calling this API, OCSP_getResponderTypeFromBasicResp
* function should be called to find whether keyhash or name is returned
* by this API.
* If Name is returned, use a pointer to SEC_NAME_S as left value.
* If KeyHash is returned, use a pointer to SEC_AsnOcts_S as left value.
* To add the Responder ID to basic response call.\n
* * OCSP_createBasicResp\n
* * OCSP_addRespIdToBasicResp.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Name/KeyHash[SEC_AsnOcts_S] from the Basic OCSP Response
*					is returned [SEC_VOID*|N/A]
* @retval SEC_VOID* SEC_NULL is returned in case of :\n
* 1. Input parameter is NULL\n
* 2. Responder ID type is not set to either Name or KeyHash [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* The OCSP_getResponderTypeFromBasicResp API tells whether KeyHash or Name is returned by the API.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID* OCSP_getResponderIdFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);




/**
* @defgroup OCSP_extractProducedAtFromBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* DATETIME_S* OCSP_extractProducedAtFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);
* @endcode
*
* @par Purpose
* To extract the time at which the OCSP response message was produced.
* @par Description
* This function gets the time at which the OCSP response was
* generated, from the Basic response. If the "Produced at" time is not set in
* Basic response, SEC_NULL is returned.
* To create the basic response, call OCSP_createBasicResp.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* Upon success, the "Produced at" time is returned [DATETIME_S*|N/A]
* @retval DATETIME_S* If Input parameter is NULL Or SEC_GenTimeToDateTime
*				   function fails [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* Pointer to the returned DATETIME_S structure must be freed by the user.
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* OCSP_extractProducedAtFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);




/**
* @defgroup OCSP_getRespExtnsFromBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* Extensions* OCSP_getRespExtnsFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);
* @endcode
*
* @par Purpose
* To fetch the Response Extensions' list from the given OCSP Basic Response.
* @par Description
* This function gets the Response Extension list from the Basic Response.
* If the response extension list is not set in Basic response, SEC_NULL
* is returned.
* To create pstBasicResp, call OCSP_createBasicResp.
* To set extensions in OCSP request, call OCSP_setRespExtnsToBasicResp.
* To retrieve extension from the list of extensions, call SEC_LIST_GET_ELEMENT.
* To retrieve Nonce from the extension, call X509Extn_getContent.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Extensions* Extension list is returned [Extensions*|N/A]
* @retval Extensions* If input parameter is NULL Or Extension list is empty [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL Extensions* OCSP_getRespExtnsFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp);




/**
* @defgroup OCSP_getSingleRespFromBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_SINGLE_RESP_S* OCSP_getSingleRespFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp,
* SEC_BIGINT_S*   pstCertSerNum,
* X509_CERT_S*	  pstIssuer);
* @endcode
*
* @par Purpose
* To fetch a Single Response message from the given OCSP Basic Response message.
* @par Description
* This function retrieves the Single Response corresponding to a
* particular Certificate from the list of single responses in Basic
* Response. Single response is searched on the basis of certificate serial
* number. If there is no Single Reponse with the certificate serial
* number in the certificate, SEC_NULL is returned.
* Following APIs need to be called to add a single response to the basic response.\n
* * OCSP_createBasicResp\n
* * OCSP_createSingleResp\n
* * OCSP_addSingleRespToBasicResp\n
* To create pstCertSerNum, call X509_getSN and the pass the certificate
* containing that certificate serial number.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[in] pstCertSerNum Serial number of the certificate to be validated [N/A]
* @param[in] pstIssuer Issuer's certificate [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_SINGLE_RESP_S* Single Response corresponding to pCertToBeValidated
*							  is returned [OCSP_SINGLE_RESP_S*|N/A]
* @retval OCSP_SINGLE_RESP_S* SEC_NULL is returned in the following conditions:\n
* 1. If input parameter is NULL\n
* 2. Failure of CopyBigInt function\n
* 3. If there is no single response having that serial number [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_SINGLE_RESP_S* OCSP_getSingleRespFromBasicResp(const OCSP_BASIC_RESP_S *pstBasicResp,
													SEC_BIGINT_S*			 pstCertSerNum,
													X509_CERT_S*			 pstIssuer);


/*
	Get functions for retrieving information from the Single Response
*/



/**
* @defgroup OCSP_getSerialNumFromSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_BIGINT_S* OCSP_getSerialNumFromSingleResp(const OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To fetch the Serial Number set in the given OCSP Single Response message.
* @par Description
* This function gets the serial number(of the certificate) set in the
* Single Response. If the serial number is not set, SEC_NULL is returned.
* To create a sinle response call, OCSP_createSingleResp.
*
* @param[in] pSingleResp Single Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BIGINT_S* Serial number of the certificate is returned [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* If input parameter is NULL Or
*				   Serial number is not set in the single response [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_BIGINT_S* OCSP_getSerialNumFromSingleResp(const OCSP_SINGLE_RESP_S* pSingleResp);




/**
* @defgroup OCSP_checkSingleRespIssuer
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_checkSingleRespIssuer(const OCSP_SINGLE_RESP_S* pSingleResp,
* X509_CERT_S*   pIssuerCert);
* @endcode
*
* @par Purpose
* To verify whether the Issuer name and key has in the Single Response is the same as
* in the given Certificate.
* @par Description
* This function checks whether the issuer Name and KeyHash in the Single
* Response are same as in the certificate. If the Name/KeyHash does not match,
* an error code is returned.
* To add the Responder ID to basic response call following API's:\n
* * OCSP_createBasicResp\n
* * OCSP_addRespIdToBasicResp\n
* To create pIssuerCert, call X509_createCert.
*
* @param[in] pSingleResp Single response [N/A]
* @param[in] pIssuerCert Issuer certificate [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Issuer's Name and KeyHash in the response
*					  and certificate are same [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Issuer name not set in the certificate [SEC_ERR_INVALID_ISSUERNAME|N/A]
* @retval SEC_UINT32 Issuer name in the cerificate and single
*						  response does not match [SEC_ERR_ISSUER_MISMATCH|N/A]
* @retval SEC_UINT32 Hash calculation is failed [SEC_ERR_HASH_FAILED|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* The certificate passed must be signed and valid.
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_checkSingleRespIssuer(const OCSP_SINGLE_RESP_S* pSingleResp,
											X509_CERT_S*		pIssuerCert);




/**
* @defgroup OCSP_getCertStatusFromSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_CERT_STATUS_TYPE_E OCSP_getCertStatusFromSingleResp(const OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To fetch the Status of the certificate in the given OCSP Single Response message.
* @par Description
* This function obtains the status value of the certifiate from the
* single response. Status can be Good, Revoked, Unknown. If the status
* is not set, OCSP_INVALID_CERT_STATUS is returned.
* To create pSingleResp, OCSP_createSingleResp.
*
* @param[in] pSingleResp OCSP Single Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_CERT_STATUS_TYPE_E Status of the certificate is returned [OCSP_CERT_STATUS_TYPE_E|N/A]
* @retval OCSP_CERT_STATUS_TYPE_E If input parameter is NULL [OCSP_INVALID_CERT_STATUS|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_CERT_STATUS_TYPE_E OCSP_getCertStatusFromSingleResp(const OCSP_SINGLE_RESP_S* pSingleResp);





/**
* @defgroup OCSP_getRevInfoFromSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_REV_INFO_S* OCSP_getRevInfoFromSingleResp(const OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To fetch the Revocation information about the certificate in the given OCSP Single Response message.
* @par Description
* This function obtains revocation information about the revoked
* certificate from the Single Response. If the status is not revoked or
* Rev Info is not set, SEC_NULL is returned.
* To create pSingleResp, OCSP_createSingleResp.
*
* @param[in] pSingleResp Single Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_REV_INFO_S* Revoked Info about the certificate is returned [OCSP_REV_INFO_S*|N/A]
* @retval OCSP_REV_INFO_S* If input parameter is NULL Or
*				   Certificate status set in the single response
*				   is not OCSP_CERT_STATUS_REVOKED [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_REV_INFO_S* OCSP_getRevInfoFromSingleResp(const OCSP_SINGLE_RESP_S* pSingleResp);




/**
* @defgroup OCSP_extractThisUpdFromSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* DATETIME_S* OCSP_extractThisUpdFromSingleResp(OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To fetch the 'This update' time from the given OCSP Single Response message.
* @par Description
* This function obtains ThisUpdate time (time at which the status being
* indicated is known to be correct) from the single response.
* To create pSingleResp, OCSP_createSingleResp.
*
* @param[in] pSingleResp Single response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* ThisUpdate time is returned [DATETIME_S*|N/A]
* @retval DATETIME_S* If input parameter is NULL Or
*				   ThisUpdate datetime set in the single response is
*				   invalid [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* Pointer to ThisUpdate must be freed by the user.
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* OCSP_extractThisUpdFromSingleResp(OCSP_SINGLE_RESP_S* pSingleResp);





/**
* @defgroup OCSP_extractNextUpdFromSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* DATETIME_S* OCSP_extractNextUpdFromSingleResp(OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To fetch the 'Next Update' time from the given OCSP Single Response message.
* @par Description
* This function obtains the NextUpdate time(time at or before which
* newer information will be available about the status of the certificate)
* value from the Single Response.
*
* @param[in] pSingleResp Single Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* NextUpdate time is returned [DATETIME_S*|N/A]
* @retval DATETIME_S* If input parameter is NULL Or
*				   NextUpdate datetime set in the single response is
*				   invalid [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* Pointer to NextUpdate must be freed by the user.
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* OCSP_extractNextUpdFromSingleResp(OCSP_SINGLE_RESP_S* pSingleResp);




/**
* @defgroup OCSP_getExtnsFromSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* Extensions* OCSP_getExtnsFromSingleResp(const OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To fetch the extensions' list from the given OCSP Single Response message.
* @par Description
* This function retrieves extension list from the Single Response.
* If this list is not set, SEC_NULL is returned.
* To create pSingleReq, call OCSP_createSingleResp.
* To set extensions in OCSP request, call OCSP_setExtnsToSingleResp.
* To retrieve extension from the list of extensions, call SEC_LIST_GET_ELEMENT.
* To retrieve ARCHIVE_CUT_OFF_S/CRL_ID_S structure from the extension, call
* X509Extn_getContent.
*
* @param[in] pSingleResp Single Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Extensions* Extension list [Extensions*|N/A]
* @retval Extensions* If input parameter is NULL Or
*				   Extension list is not set in the single request [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL Extensions* OCSP_getExtnsFromSingleResp(const OCSP_SINGLE_RESP_S* pSingleResp);




/**
* @defgroup OCSP_extractRevTimeFromRevInfo
* @ingroup ocspFunctions
* @par Prototype
* @code
* DATETIME_S* OCSP_extractRevTimeFromRevInfo(OCSP_REV_INFO_S* pstRevInfo);
* @endcode
*
* @par Purpose
* To fetch the revocation time from the given revoked info structure.
* @par Description
* This function retrieves the revocation time from Revoked Info. If
* status of the certificate is other than 'Revoked', SEC_NULL is
* returned. The date returned is the date at which the certifiate was revoked.
* To get pstRevInfo from a single response, call OCSP_getRevInfoFromSingleResp.
*
* @param[in] pstRevInfo Revocation Info [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* Revocation time is returned [DATETIME_S*|N/A]
* @retval DATETIME_S* If input parameter is NULL Or Revocation time is not set [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* Pointer to revocation time must be freed by the user.
*
* @par Related Topics
* N/A
*/

PSELINKDLL DATETIME_S* OCSP_extractRevTimeFromRevInfo(OCSP_REV_INFO_S* pstRevInfo);




/**
* @defgroup OCSP_getRevReasonFromRevInfo
* @ingroup ocspFunctions
* @par Prototype
* @code
* X509_CRL_REASON_E* OCSP_getRevReasonFromRevInfo(const OCSP_REV_INFO_S* pstRevInfo);
* @endcode
*
* @par Purpose
* To fetch the revocation reason from the given Revoked Info structure.
* @par Description
* This function retrieves revocation reason from Revoked Info. If
* status of the certificate is other than Revoked, SEC_NULL is
* reurned.
* To get pstRevInfo from a single response, call OCSP_getRevInfoFromSingleResp.
*
* @param[in] pstRevInfo Revocation Info [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CRL_REASON_E* Pointer to revocation reason is returned [X509_CRL_REASON_E*|N/A]
* @retval X509_CRL_REASON_E* If input parameter is NULL Or Revocation reason
*				   is not set [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_CRL_REASON_E* OCSP_getRevReasonFromRevInfo(const OCSP_REV_INFO_S* pstRevInfo);





/**
* @defgroup OCSP_checkNonce
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_checkNonce(const OCSP_REQUEST_S*	pOCSPReq,
* const OCSP_BASIC_RESP_S* pstBasicResp);
* @endcode
*
* @par Purpose
* To verify whether the nonce in the given OCSP Request is the same as
* the one in the given OCSP Basic response.
* @par Description
* This function checks whether the nonce in the OCSP request and Basic
* response are same or not.\n
* Nonce :
* Nonce is SEC_AsnOcts_S which is used in the request and response to prevent
* replay attacks. It makes sure that the response sent for a particular request
* is not outdated. Nonce extension contains the Nonce(SEC_AsnOcts) as the
* extension value.\n
* To create pOCSPReq, call OCSP_createOCSPReq.\n
* To create pstBasicResp, call OCSP_createBasicResp.\n
* To create a Nonce\n
* 1) Initialize SEC_AsnOcts_S.\n
* 2) Set the Nonce value(string) in octs field.\n
* 3) Set the Nonce length in octetLen field.\n
* To create a Nonce extension, call X509_createExtn and pass the Nonce(SEC_AsnOcts_S).\n
* To add the Nonce extension to pstBasicResp, call the following APIs :\n
* SEC_LIST_NEW() : Initialize the structure SEC_AsnOcts_S.\n
* X509_createExtn() : Pass the initialized SEC_AsnOcts_S.\n
* SEC_LIST_ADD_ELEMENT\n
* OCSP_setRespExtnsToBasicResp\n
* To add the Nonce extension to pOCSPReq, call the following APIs :\n
* SEC_LIST_NEW() : Initialize the structure SEC_AsnOcts_S(for Nonce).\n
* X509_createExtn() : Pass the initialized Nonce\n
* SEC_LIST_ADD_ELEMENT\n
* OCSP_setReqExtnsToOCSPReq\n
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Value of Nonce in the req and resp is same [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Input parameter is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Nonce Oid is invalid [SEC_ERR_INVALID_CID|N/A]
* @retval SEC_UINT32 If the extension list is empty [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 Nonce extension is not available in
*					OCSP request and/or Basic response [SEC_ERR_EXTN_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 If the Nonce value in the req and resp is
*								 not same [SEC_ERR_NONCE_MISMATCH|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 OCSP_checkNonce(const OCSP_REQUEST_S*	pOCSPReq,
						   const OCSP_BASIC_RESP_S* pstBasicResp);




/**
* @defgroup OCSP_freeOCSPReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_VOID OCSP_freeOCSPReq(OCSP_REQUEST_S* pOCSPReq);
* @endcode
*
* @par Purpose
* To free a OCSP_REQUEST_S structure.
* @par Description
* This function is used to free the OCSP Request.
*
* @param[in] pOCSPReq OCSP Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID OCSP_freeOCSPReq(OCSP_REQUEST_S* pOCSPReq);




/**
* @defgroup OCSP_freeSingleReq
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_VOID OCSP_freeSingleReq(OCSP_SINGLE_REQ_S* pSingleReq);
* @endcode
*
* @par Purpose
* To free a OCSP_SINGLE_REQ_S structure.
* @par Description
* This function is used to free the OCSP Single Request.
*
* @param[in] pSingleReq OCSP Single Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID OCSP_freeSingleReq(OCSP_SINGLE_REQ_S* pSingleReq);





/**
* @defgroup OCSP_freeOCSPResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_VOID OCSP_freeOCSPResp(OCSP_RESP_S* pOCSPResp);
* @endcode
*
* @par Purpose
* To free a OCSP_RESP_S structure.
* @par Description
* This function is used to free the OCSP Response.
*
* @param[in] pOCSPResp OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID OCSP_freeOCSPResp(OCSP_RESP_S* pOCSPResp);




/**
* @defgroup OCSP_freeBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_VOID OCSP_freeBasicResp(OCSP_BASIC_RESP_S* pstBasicResp);
* @endcode
*
* @par Purpose
* To free a OCSP_BASIC_RESP_S structure.
* @par Description
* This function is used to free the OCSP Basic Response.
*
* @param[in] pstBasicResp Basic OCSP Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID OCSP_freeBasicResp(OCSP_BASIC_RESP_S* pstBasicResp);



/**
* @defgroup OCSP_freeSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_VOID OCSP_freeSingleResp(OCSP_SINGLE_RESP_S* pSingleResp);
* @endcode
*
* @par Purpose
* To free a OCSP_SINGLE_RESP_S structure.
* @par Description
* This function is used to free the OCSP Single Response.
*
* @param[in]  pSingleResp OCSP Single Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID OCSP_freeSingleResp(OCSP_SINGLE_RESP_S* pSingleResp);




/**
* @defgroup OCSP_encodeRespId
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UCHAR* OCSP_encodeRespId(OCSP_RESPID_S* pstRespId,
* SEC_UINT32*  pulEncLen);
* @endcode
*
* @par Purpose
* To encode the given OCSP Responder ID structure.
* @par Description
* This function encodes the ResponderID structure.
*
* @param[in] pstRespId Responder ID [N/A]
* @param[out] pulEncLen The length of the Encoded responder ID [N/A]
*
* @retval SEC_UCHAR* Encoded responder id [SEC_UCHAR*|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UCHAR* OCSP_encodeRespId(OCSP_RESPID_S* pstRespId,
							 SEC_UINT32* pulEncLen);



/**
* @defgroup OCSP_decodeRespId
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESPID_S* OCSP_decodeRespId(SEC_UCHAR* pucEncRespId,
* SEC_UINT32  ulEncLen,
* SEC_UINT32*  pulDecLen);
* @endcode
*
* @par Purpose
* To generate the decoded OCSP Responder ID from the buffer
* containing the encoded OCSP Responder ID.
* @par Description
* This function decodes the ResponderID structure.
*
* @param[in] pucEncRespId Encoded Responder ID [N/A]
* @param[in] ulEncLen Length of the encoded responder ID [N/A]
* @param[out] pulDecLen Length of the decoded responder ID [N/A]
*
* @retval OCSP_RESPID_S* Decoded responder ID [OCSP_RESPID_S*|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL OCSP_RESPID_S* OCSP_decodeRespId(SEC_UCHAR* pucEncRespId,
								 SEC_UINT32 ulEncLen,
								 SEC_UINT32* pulDecLen);



/**
* @defgroup OCSP_freeRespId
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_VOID OCSP_freeRespId(OCSP_RESPID_S* pstRespId);
* @endcode
*
* @par Purpose
* To free a OCSP_RESPID_S structure.
* @par Description
* This function is used to free the Responder Id.
*
* @param[in] pstRespId OCSP Responder Id [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID OCSP_freeRespId(OCSP_RESPID_S* pstRespId);



/**
* @defgroup OCSP_dupRespID
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESPID_S* OCSP_dupRespID(OCSP_RESPID_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate the given OCSP_RESPID_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_RESPID_S* Pointer to destination [OCSP_RESPID_S*|N/A]
* @retval OCSP_RESPID_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval OCSP_RESPID_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL OCSP_RESPID_S* OCSP_dupRespID(OCSP_RESPID_S* pSrc);



/**
* @defgroup OCSP_dupSingleRequest
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_SINGLE_REQ_S* OCSP_dupSingleRequest(OCSP_SINGLE_REQ_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate the given OCSP_SINGLE_REQ_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_SINGLE_REQ_S* Pointer to destination [OCSP_SINGLE_REQ_S*|N/A]
* @retval OCSP_SINGLE_REQ_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval OCSP_SINGLE_REQ_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL OCSP_SINGLE_REQ_S* OCSP_dupSingleRequest(OCSP_SINGLE_REQ_S* pSrc);



/**
* @defgroup OCSP_dupRequest
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_REQUEST_S* OCSP_dupRequest(OCSP_REQUEST_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate the given OCSP_REQUEST_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_REQUEST_S* Pointer to destination [OCSP_REQUEST_S*|N/A]
* @retval OCSP_REQUEST_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval OCSP_REQUEST_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL OCSP_REQUEST_S* OCSP_dupRequest(OCSP_REQUEST_S* pSrc);



/**
* @defgroup OCSP_dupOCSPResponse
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_RESP_S* OCSP_dupOCSPResponse(OCSP_RESP_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate the given OCSP_RESP_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_RESP_S* Pointer to destination [OCSP_RESP_S*|N/A]
* @retval OCSP_RESP_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval OCSP_RESP_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL OCSP_RESP_S* OCSP_dupOCSPResponse(OCSP_RESP_S* pSrc);



/**
* @defgroup OCSP_dupBasicResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_BASIC_RESP_S* OCSP_dupBasicResp(OCSP_BASIC_RESP_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate the given OCSP_BASIC_RESP_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_BASIC_RESP_S* Pointer to destination [OCSP_BASIC_RESP_S*|N/A]
* @retval OCSP_BASIC_RESP_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval OCSP_BASIC_RESP_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL OCSP_BASIC_RESP_S* OCSP_dupBasicResp(OCSP_BASIC_RESP_S* pSrc);



/**
* @defgroup OCSP_dupSingleResp
* @ingroup ocspFunctions
* @par Prototype
* @code
* OCSP_SINGLE_RESP_S* OCSP_dupSingleResp(OCSP_SINGLE_RESP_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate the given OCSP_SINGLE_RESP_S structure.
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval OCSP_SINGLE_RESP_S* Pointer to destination [OCSP_SINGLE_RESP_S*|N/A]
* @retval OCSP_SINGLE_RESP_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval OCSP_SINGLE_RESP_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL OCSP_SINGLE_RESP_S* OCSP_dupSingleResp(OCSP_SINGLE_RESP_S* pSrc);

//This function has been moved here from ocsp.c as the test code is using it - Jay



/**
* @defgroup OCSP_calcKeyHash
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UCHAR* OCSP_calcKeyHash(SEC_PUBKEY_INFO_S* pstPubKey,
* SEC_UINT32  ulHashAlg,
* SEC_UINT32*  pulHashLength);
* @endcode
*
* @par Purpose
* To calculate hash of the given public key.
* @par Description
* This Function calculates hash of the encoded key for the given key.
*
* @param[in] pstPubKey Public Key [N/A]
* @param[in] ulHashAlg Algorithm to be used for Hash [N/A]
* @param[out] pulHashLength Length of the hash output [N/A]
*
* @retval SEC_UCHAR* hash of the encoded issuer key [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* If the input is NULL [SEC_NULL|N/A]
* @retval SEC_UCHAR* If memory allocation fails [SEC_NULL|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SEC_UCHAR* ocsp_calcKeyHash(SEC_PUBKEY_INFO_S* pstPubKey,
							SEC_UINT32 ulHashAlg,
							SEC_UINT32* pulHashLength);

#ifdef __cplusplus
}
#endif

#endif /* _IPSI_OCSP_H_ */
#endif  /* __SEC_NO_OCSP__ */




