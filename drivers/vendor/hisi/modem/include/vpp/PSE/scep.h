/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                              scep.h

  Project Code: SeCert
   Module Name: SCEP
  Date Created: 2005-07-01
        Author: Vinod Duggirala N
    Descrption: Simple Certificate Enrollment Protocol funtions and datatypes
                declerations.
*/

#include "ipsi_pse_build_conf.h"

#ifndef __SEC_NO_SCEP__
#ifndef _IPSI_SCEP_H_
#define _IPSI_SCEP_H_


#include "pkcs10.h"
#include "pkcs7.h"
//#include "sec_common.h"
#include "sec_error.h"
#include "sec_sys.h"
#include "x509_basictypes.h"
#include "asn-types.h"
#include "sec_crypto.h"
#include "sec_list.h"
#include "x509v3_extn.h"

#ifdef	  __cplusplus
extern	"C"{
#endif


/*
 * CA server capabilities
 */

/*CA Supports the GetNextCACert message. This capability allows clients to request for the
	next CA certificate if the current CA certificate's validity period is near its end period.*/
#define SEC_CAPS_NEXTCACERT 1

/*PKIOPeration messages may be sent via HTTP POST. This capability means that the CA server can recieve HTTP POST
	messages and hence the client can use the same.*/
#define SEC_CAPS_POSTPKIOPS 2

/*CA Supports the SHA-1 hashing algorithm in signatures
   and fingerprints*/
#define SEC_CAPS_SHA1       4

/*Clients may use current certificate and key to authenticate
   an enrollment request for a new certificate*/
#define SEC_CAPS_RENEW      8

/*CA Supports the SHA256 hashing algorithm in signatures
   and fingerprints*/
#define SEC_CAPS_SHA256     16

/*CA Supports the SHA512 hashing algorithm in signatures
   and fingerprints*/
#define SEC_CAPS_SHA512     32

/*CA Supports triple-DES algorithm for encryption*/
#define SEC_CAPS_3DES       64

/*Nonce Length as per Specification*/
#define SCEP_NONCE_LEN      16

/*
 Types of valid SCEP messages
 */

/** @defgroup scep
* This section contains the scep Enums Structures and Functions
*/

/** @defgroup scepEnums
* @ingroup scep
* This section contains the scep Enums
*/

/**
* @defgroup SCEP_MSGTYPE_E
* @ingroup scepEnums
* @par Prototype
* @code
* typedef enum enSCEPMessageType {
*   SCEP_MSG_CERTREP       =3,
*   SCEP_MSG_PKCSREQ       =19,
*   SCEP_MSG_GETCERTINITIAL=20,
*   SCEP_MSG_GETCERT       =21,
*   SCEP_MSG_GETCRL        =22,
*   SCEP_MSG_GETCACERT     =23,
*   SCEP_MSG_NEXTCACERT    =24,
*   SCEP_MSG_CACAPS        =25,
*   SCEP_MSG_CACERTCHAIN   =26,
*   SCEP_MSG_PKIMESSAGE    =27,
*   SCEP_MSG_MIMECACERT    =28,
*   SCEP_MSG_MIMECARACERT  =29,
*   SCEP_MSG_MIMECACAPS    =30,
*   SCEP_MSG_MIMECERTCHAIN =31,
*   SCEP_MSG_TYPE_UNKNOWN
* } SCEP_MSGTYPE_E;
* @endcode
*
* @datastruct SCEP_MSG_CERTREP=3 Response by CA server for a Certificate or CRL request.
* @datastruct SCEP_MSG_PKCSREQ=19 PKCS#10 Certificate request.
* @datastruct SCEP_MSG_GETCERTINITIAL=20 Certificate polling request in manual enrollment.
* @datastruct SCEP_MSG_GETCERT=21 Retrieve a certificate.
* @datastruct SCEP_MSG_GETCRL=22 Retrieve a CRL.
* @datastruct SCEP_MSG_GETCACERT=23 Get CA certificate (RA also if present).
* @datastruct SCEP_MSG_NEXTCACERT=24 Message to request for the next CA Certificate.
* @datastruct SCEP_MSG_CACAPS=25 Request message to get capabilities from CA.
* @datastruct SCEP_MSG_CACERTCHAIN=26 Request message to get the entire certificate chain.
* @datastruct SCEP_MSG_PKIMESSAGE=27 Only way to Communicate between client & server.
* @datastruct SCEP_MSG_MIMECACERT=28 A binary X.509 CA certificate is sent back as a MIME object with a
* Content-Type of application/x-x509-ca-cert.
* @datastruct SCEP_MSG_MIMECARACERT=29 CA/RA server will return a MIME object via HTTP for CA cert request.
* @datastruct SCEP_MSG_MIMECACAPS=30 CA/RA server will return a MIME object via HTTP for CACAPS request.
* @datastruct SCEP_MSG_MIMECERTCHAIN=31 CA/RA server will return a MIME object via HTTP for CACERTCHAIN request.
* @datastruct SCEP_MSG_TYPE_UNKNOWN Unknown message type. When value is not yet set or erroneous.
*/
typedef enum enSCEPMessageType {
            /*Response by CA server for a Certificate or CRL request*/
            SCEP_MSG_CERTREP=3,

            /*PKCS#10 Certificate request*/
            SCEP_MSG_PKCSREQ=19,

            /*Certificate polling request in manual enrollment*/
            SCEP_MSG_GETCERTINITIAL=20,

            /*Retrieve a certificate*/
            SCEP_MSG_GETCERT=21,

            /*Retrieve a CRL*/
            SCEP_MSG_GETCRL=22,

            /*Get CA certificate (RA also if present) */
            SCEP_MSG_GETCACERT=23,

            /*Message to request for the next CA Certificate*/
            SCEP_MSG_NEXTCACERT=24,

            /*Request message to get capabilities from CA*/
            SCEP_MSG_CACAPS=25,

            /*Request message to get the entire certificate chain*/
            SCEP_MSG_CACERTCHAIN=26,

            /*Only way to Communicate between client & server*/
            SCEP_MSG_PKIMESSAGE=27,

            /*A binary X.509 CA certificate is sent back as a MIME object with a
               Content-Type of application/x-x509-ca-cert*/
            SCEP_MSG_MIMECACERT=28,

            /*CA/RA server will return a MIME object via HTTP for CA cert request*/
            SCEP_MSG_MIMECARACERT=29,

            /*CA/RA server will return a MIME object via HTTP for CACAPS request*/
            SCEP_MSG_MIMECACAPS=30,

            /*CA/RA server will return a MIME object via HTTP for CACERTCHAIN request */
            SCEP_MSG_MIMECERTCHAIN=31,

			/*Unknown message type. When value is not yet set or erroneous*/
            SCEP_MSG_TYPE_UNKNOWN
} SCEP_MSGTYPE_E;


/*
 The possible status values in the response
 to a certificate request or polling message
 */
/**
* @defgroup SCEP_STATUS_E
* @ingroup scepEnums
* @par Prototype
* @code
* typedef enum enSCEPStatus{
*   SCEP_STATUS_SUCCESS =0,
*   SCEP_STATUS_FAILURE =2,
*   SCEP_STATUS_PENDING =3,
*   SCEP_STATUS_UNKNOWN
* } SCEP_STATUS_E;
* @endcode
*
* @datastruct SCEP_STATUS_SUCCESS=0 Request granted.
* @datastruct SCEP_STATUS_FAILURE=2 Request rejected.
* @datastruct SCEP_STATUS_PENDING=3 Request pending for manual approval.
* @datastruct SCEP_STATUS_UNKNOWN Request status not yet set or erroneous.
*/

typedef enum enSCEPStatus{
    /*Request granted */
    SCEP_STATUS_SUCCESS=0,

    /*Request rejected */
    SCEP_STATUS_FAILURE=2,

    /*Request pending for manual approval*/
    SCEP_STATUS_PENDING=3,

	/*Request status not yet set or erroneous*/
    SCEP_STATUS_UNKNOWN
} SCEP_STATUS_E;

/*
  The possible reasons for failure of a certificate
  enrollment request
 */
/**
* @defgroup SCEP_REASON_E
* @ingroup scepEnums
* @par Prototype
* @code
* typedef enum enSCEPReason{
*  SCEP_REASON_BADALG    =0,
*  SCEP_REASON_BADMSGCHK =1,
*  SCEP_REASON_BADREQ    =2,
*  SCEP_REASON_BADTIME   =3,
*  SCEP_REASON_BADCERTID =4,
*  SCEP_REASON_UNKNOWN
* } SCEP_REASON_E;
* @endcode
*
* @datastruct SCEP_REASON_BADALG=0 Unrecognized or unsupported algorithm identifier.
* @datastruct SCEP_REASON_BADMSGCHK=1 Integrity check failed.
* @datastruct SCEP_REASON_BADREQ=2 Transaction not permitted or supported.
* @datastruct SCEP_REASON_BADTIME=3 Message created time field was not sufficiently close to
* the current system time (old message).
* @datastruct SCEP_REASON_BADCERTID=4 No certificate could be identified matching the provided criteria.
* @datastruct SCEP_REASON_UNKNOWN Message type not set or erroneous.
*/
typedef enum enSCEPReason{
    /*Unrecognized or unsupported algorithm identifier*/
    SCEP_REASON_BADALG=0,

    /*Integrity check failed */
    SCEP_REASON_BADMSGCHK=1,

    /*Transaction not permitted or supported */
    SCEP_REASON_BADREQ=2,

    /*Message created time field was not sufficiently close to
	the current system time (old message)*/
    SCEP_REASON_BADTIME=3,

    /*No certificate could be identified matching the provided criteria */
    SCEP_REASON_BADCERTID=4,

	/*Message type not set or erroneous*/
    SCEP_REASON_UNKNOWN
} SCEP_REASON_E;

/** @defgroup scepStructures
* @ingroup scep
* This section contains the scep Structures
*/
/*
 Certficate poll request include the Issuer name & subject name. Used
 to poll the CA after a certificate enrollment request if manual authentication is used
 */
/**
* @defgroup SCEP_CERTPOLLREQ_S
* @ingroup scepStructures
* @par Prototype
* @code
* typedef struct stCertPollReq
* {
*   SEC_NAME_S* pstIssuer;
*   SEC_NAME_S* pstSubject;
* } SCEP_CERTPOLLREQ_S;
* @endcode
*
* @datastruct pstIssuer The certificate authority issuer name.
* @datastruct pstSubject The requester subject name as given in PKCS#10 during enrollment request.
*/
typedef struct stCertPollReq
{
    SEC_NAME_S* pstIssuer;   /*The certificate authority issuer name*/

    SEC_NAME_S* pstSubject;  /*The requester subject name as given in PKCS#10 during enrollment request*/

} SCEP_CERTPOLLREQ_S;

/*
 CRL query include the issuer, serial name & DistributionPoint. Used when querying the CA
 for a CRL
 */
/**
* @defgroup SCEP_CRLQUERY_S
* @ingroup scepStructures
* @par Prototype
* @code
* typedef struct stCRLQuery
{
    SEC_ISSUER_AND_SERIAL_S* pstCRLIssuerAndSN;
    CRLDistributionPoints*   pstDistributionPoint;
} SCEP_CRLQUERY_S;
* @endcode
*
* @datastruct pstCRLIssuerAndSN CA certificate issuer & serial number.
* @datastruct pstDistributionPoint CRL Distribution Point.
*/
typedef struct stCRLQuery
{

    SEC_ISSUER_AND_SERIAL_S* pstCRLIssuerAndSN;  /*CA certificate issuer & serial number*/

    CRLDistributionPoints*   pstDistributionPoint;  /*CRL Distribution Point */

} SCEP_CRLQUERY_S;


/*
  Corresponding structures from other components need to be
  typedefed for this component names
 */
/*Certificate Query (CertQuery) IS issuer name & serial number*/
typedef SEC_ISSUER_AND_SERIAL_S SCEP_CERTQUERY_S;

/*SCEP message IS PKCS7 message*/
typedef PKCS7_MSG_S         SCEP_MSG_S;

/*SCEP Certificate responce IS PKCS7 Signed data*/
typedef PKCS7_SIGNED_S      SCEP_CERTRESP_S;

/*SCEP CRL responce IS PKCS7 Signed data*/
typedef PKCS7_SIGNED_S      SCEP_CRLRESP_S;

/*HTTP Content structure IS AsnOcts which holds data and data length*/
typedef SEC_AsnOcts_S       SCEP_HTTPCONTENT_S;

/*Crl Query (CrlQuery) IS issuer name & serial number*/
typedef SEC_ISSUER_AND_SERIAL_S SCEP_CRLQUERY_EX_S;


/** @defgroup scepFunctions
* @ingroup scep
* This section contains the scep Functions
*/


/**
* @defgroup SCEP_createTID
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_CHAR* SCEP_createTID(SEC_PKEY_S* pstPublicKey, SEC_UINT32 enHashAlg);
* @endcode
*
* @par Purpose
* To create a TID from the hash of public key.
* @par Description
* This function creates transaction ID for client from the hash of public key.
* An MD5/SHA1/SHA256/SHA512 hash is used here.If algorithm is not
* given it is an error. Transaction ID is used to keep track of a
* transaction by the server. It returns the Created transaction ID.
* Transaction Id is a base 64 encoded string.
*
* @param[in] pstPublicKey Pointer to the public Key. Only RSA is supported [N/A]
* @param[in] enHashAlg Hash Algorithm to be used to generate
* TransactionID (hash of public key). Possible
* values are ALGID_MD5, ALGID_SHA1,
* ALGID_SHA256 and ALGID_SHA512 [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* If successful [Pointer to the created transaction ID|N/A]
* @retval SEC_CHAR* In case of error during CRYPT_digest()
*                   [Error codes returned by CRYPT_digest()|N/A]
* @retval SEC_CHAR* Input arguments are invalid during CRYPT_digest() [SEC_NULL_PTR|N/A]
* @retval SEC_CHAR* Memory allocation failed during CRYPT_digest() [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_CHAR* Base64 encoding failed during CRYPT_digest() [SEC_ERR_ENCODE_BASE64_FAILED|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates transaction ID */
PSELINKDLL SEC_CHAR* SCEP_createTID(SEC_PKEY_S* pstPublicKey,
                             SEC_UINT32 enHashAlg);



/**
* @defgroup SCEP_createCertReq
* @ingroup scepFunctions
* @par Prototype
* @code
* PKCS10_REQ_S* SCEP_createCertReq(SEC_NAME_S* pstRequestorName,
* SEC_PKEY_S* pstPubKey,
* SEC_UCHAR* pcChallengPass,
* SEC_INT32  ulPassLen,
* SEC_PKEY_S* pstPvtKey,
* SEC_EXTN_S* pstSubAltNameExtnAttr,
* SEC_EXTN_S* pstKeyUsageExtnAttr,
* SEC_EXTN_S* pstExtKeyUsageExtnAttr,
* SEC_UINT32 enHashAlgID);
* @endcode
*
* @par Purpose
* To create an SCEP certificate request.
* @par Description
* This function Creates an SCEP CertReq(PKCS10 request structure)
* message from user supplied data. It returns the Created
* Certificate Request. This is required for new certificate enrollment.
*
* @param[in] pstRequestorName Pointer to the name of the requester [N/A]
* @param[in] pstPubKey Pointer to the public key of the requester
*					   Only RSA is supported [N/A]
* @param[in] pcChallengPass Pointer to the challenge password
*							(for automatic authentication) [N/A]
* @param[in] ulPassLen Length of the  challenge password [N/A]
* @param[in] pstPvtKey Pointer to the private key of the requester
*					   Only RSA is supported [N/A]
* @param[in] pstSubAltNameExtnAttr Subject Alternate Name Extn Attr (Optional)
*								   Alternate name of the subject. Additional information
*                                  of the entity requesting the certificate [N/A]
* @param[in] pstKeyUsageExtnAttr KeyUsage Extn Attr (Optional)
*								 This specifies the reasons for which the certificate will
*                                be used [N/A]
* @param[in] pstExtKeyUsageExtnAttr ExtKeyUsageExtnAttr (Optional)
*									Combination of key usages, meant for a particular service;
*                                   such as email protection, client authentication, etcetera [N/A]
* @param[in] enHashAlgID Hash algorithm to be used while sigining.
*						 Possible values are ALGID_MD5, ALGID_SHA1, ALGID_SHA256
*						 and ALGID_SHA512 [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PKCS10_REQ_S* Pointer to the generated pkcs10 request [PKCS10_REQ_S*|N/A]
* @retval PKCS10_REQ_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
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

/* Creates an SCEP CertReq(PKCS10 request structure) */
PSELINKDLL PKCS10_REQ_S*
SCEP_createCertReq(SEC_NAME_S* pstRequestorName,
                   SEC_PKEY_S* pstPubKey,
                   SEC_UCHAR* pcChallengPass,
                   SEC_INT32 ulPassLen,
                   SEC_PKEY_S* pstPvtKey,
                   SEC_EXTN_S* pstSubAltNameExtnAttr,
                   SEC_EXTN_S* pstKeyUsageExtnAttr,
                   SEC_EXTN_S* pstExtKeyUsageExtnAttr,
                   SEC_UINT32 enHashAlgID);




/**
* @defgroup SCEP_createCertResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CERTRESP_S* SCEP_createCertResp(X509_CERT_S* pstIssued,
* X509_CERT_S* pstCACert, X509_CERT_S* pstRACert);
* @endcode
*
* @par Purpose
* To create an SCEP certificate response message.
* @par Description
* This function Creates and returns an SCEP Certificate Response
* message for the case when status is SUCCESS. It is a PKCS7 Signed
* data portion.
*
* @param[in] pstIssued Pointer to the Issued Certificate [N/A]
* @param[in] pstCACert Pointer to the CA Certificate,(Optional) [N/A]
* @param[in] pstRACert Pointer to the RA Certificate,(Optional) [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CERTRESP_S* Pointer to the generated Certificate Response [SCEP_CERTRESP_S*|N/A]
* @retval SCEP_CERTRESP_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Creates and returns an SCEP Certificate Response message for the status SUCCESS */
PSELINKDLL SCEP_CERTRESP_S*
SCEP_createCertResp(X509_CERT_S* pstIssued,
                    X509_CERT_S* pstCACert,
                    X509_CERT_S* pstRACert);



/**
* @defgroup SCEP_createPendFailCertResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_MSG_S* SCEP_createPendFailCertResp(SCEP_STATUS_E enStatus,
* SCEP_REASON_E enReason,
* SEC_CHAR* pcTId,
* SEC_CHAR* pcSNonce,
* SEC_UINT32 ulSLen,
* SEC_CHAR*  pcRNonce,
* SEC_UINT32 ulRLen,
* SEC_PKEY_S* pstPvtKey,
* SEC_NAME_S* pstIssuer,
* SEC_BIGINT_S* pstSerialNum,
* SEC_UINT32 enDigestAlgo,
* SEC_UINT32 enDigEncryAlgo);
* @endcode
*
* @par Purpose
* To create an SCEP Certificate Response when Certificate enrollment status is Failure or Pending.
* @par Description
* This function Creates and returns an SCEP Certificate Response
* message when Certificate enrollment status is Failure or Pending.
* If the status is failure then the reason for certificate enrollment
* failure must be specified.
*
* @param[in] enStatus Status FAILURE or PENDING [N/A]
* @param[in] enReason  Identifies the reason if status is failure [N/A]
* @param[in] pcTId Transaction ID, used to track a transaction between
*                  requester and server [N/A]
* @param[in] pcSNonce Sender Nonce [N/A]
* @param[in] ulSLen Length of the sender nonce [N/A]
* @param[in] pcRNonce Recipient Nonce [N/A]
* @param[in] ulRLen Length of the Recipient Nonce [N/A]
* @param[in] pstPvtKey Private Key of the CA.
*                      Only RSA is supported [N/A]
* @param[in] pstIssuer Signer's Issuer Name (CA's name) [N/A]
* @param[in] pstSerialNum Signer's Serial Number (CA's serial number) [N/A]
* @param[in] enDigestAlgo Hash Algorithm to be used to generate
*                         digest during signing process. Possible
*						  values are ALGID_MD5, ALGID_SHA1,
*						  ALGID_SHA256 and ALGID_SHA512 [N/A]
* @param[in] enDigEncryAlgo Symmetric digest encryption algorithm: ALGID_RSA [N/A]
* @param[out] N/A N/A [N/A]
* @retval SCEP_MSG_S* Pointer to the Generated Message [SCEP_MSG_S*|N/A]
* @retval SCEP_MSG_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns an SCEP Certificate Response message for the status Failure or Pending */
PSELINKDLL SCEP_MSG_S*
SCEP_createPendFailCertResp(SCEP_STATUS_E enStatus,
                            SCEP_REASON_E enReason,
                            SEC_CHAR* pcTId,
                            SEC_CHAR* pcSNonce,
                            SEC_UINT32 ulSLen,
                            SEC_CHAR* pcRNonce,
                            SEC_UINT32 ulRLen,
                            SEC_PKEY_S* pstPvtKey,
                            SEC_NAME_S* pstIssuer,
                            SEC_BIGINT_S* pstSerialNum,
                            SEC_UINT32 enDigestAlgo,
                            SEC_UINT32 enDigEncryAlgo);



/**
* @defgroup SCEP_createCertPollReq
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CERTPOLLREQ_S* SCEP_createCertPollReq(SEC_NAME_S* pstCAName,
* SEC_NAME_S* pstReqName);
* @endcode
*
* @par Purpose
* To create an SCEP certificate poll request by generating GerCertInitial message..
* @par Description
* Either triggered by the PENDING status received from the Certificate Response,
* or by the non-response timeout for the previous enrollment Request, a requester
* will enter the polling state by periodically sending GetCertInitial
* to the server, until either the request is granted and the certificate
* is sent back, or the request is rejected, or the configured time limit for
* polling is exceeded. This function Creates and returns an SCEP GetCertInitial
* message which is used to poll the CA.
*
* @param[in] pstCAName Pointer to CA Name [N/A]
* @param[in] pstReqName Pointer to requester/Subject Name [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CERTPOLLREQ_S* Pointer to the generated structure [SCEP_CERTPOLLREQ_S*|N/A]
* @retval SCEP_CERTPOLLREQ_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns an SCEP GetCertInitial message which is used to poll the CA */
PSELINKDLL SCEP_CERTPOLLREQ_S*
SCEP_createCertPollReq(SEC_NAME_S* pstCAName,
                       SEC_NAME_S* pstReqName);





/**
* @defgroup SCEP_createCertQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CERTQUERY_S* SCEP_createCertQuery(SEC_NAME_S* pstCAName,
* SEC_BIGINT_S* pstSerial);
* @endcode
*
* @par Purpose
* To create an SCEP Certificate query message.
* @par Description
* This function Creates and returns an SCEP Certificate query message,
* which is used to query for certificates from the CA.
* To query a certificate from the certificate authority, a requester
* sends a request consisting of the certificate's issuer name and the
* serial number.
*
* @param[in] pstCAName CA's Name [N/A]
* @param[in] pstSerial Serial Number of the certificate which is being queried [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CERTQUERY_S* Pointer to the generated Certificate Query [SCEP_CERTQUERY_S*|N/A]
* @retval SCEP_CERTQUERY_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns an SCEP GetCert message, which is used to query for certificates from the CA */
PSELINKDLL SCEP_CERTQUERY_S*
SCEP_createCertQuery(SEC_NAME_S* pstCAName,
                     SEC_BIGINT_S* pstSerial);



/**
* @defgroup SCEP_createCRLQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CRLQUERY_S* SCEP_createCRLQuery(SEC_NAME_S* pstCAName,
* SEC_BIGINT_S* pstSerialNum, SEC_List_S* pstDistPoint);
* @endcode
*
* @par Purpose
* To create an SCEP CRL query message.
*
* @par Description
* This function Creates and returns an SCEP GetCRL message. The query of the CRL can only be initialized by the requester.
* The CRL may be retrieved by a simple HTTP GET. If the CA supports this method, it should encode the URL into a CRL
* Distribution Point extension in the certificates it issues. Refer RFC 2587 to study CRL Distribution Point.
*
* @param[in] pstCAName CA's Name [N/A]
* @param[in] pstSerialNum CA's Certificate SerialNumber [N/A]
* @param[in] pstDistPoint CRL Distribution Point [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CRLQUERY_S* Created CRL Query [SCEP_CRLQUERY_S*|N/A]
* @retval SCEP_CRLQUERY_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns an SCEP GetCRL message, which is used to query for CRLs from the CA */
PSELINKDLL SCEP_CRLQUERY_S*
SCEP_createCRLQuery(SEC_NAME_S* pstCAName,
                    SEC_BIGINT_S* pstSerialNum,
                    SEC_List_S* pstDistPoint);




/**
* @defgroup SCEP_createCRLResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CRLRESP_S* SCEP_createCRLResp(X509_CRL_S* pstCRL);
* @endcode
*
* @par Purpose
* To create a CRL response message.
* @par Description
* This function Creates and returns CRL Response,
* The CRL is sent back to the requester through CertRep message. The
* information portion of this message is a degenerated PKCS#7 SignedData
* which contains only a CRL.
*
* @param[in] pstCRL The CRL to be included in the response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CRLRESP_S* Created CRL Response [SCEP_CRLRESP_S*|N/A]
* @retval SCEP_CRLRESP_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns CRL Response, */

PSELINKDLL SCEP_CRLRESP_S*
SCEP_createCRLResp(X509_CRL_S* pstCRL);




/**
* @defgroup SCEP_createEnvAndSignReq
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_MSG_S* SCEP_createEnvAndSignReq(SEC_VOID* pData,
* SCEP_MSGTYPE_E enMsgType,
* X509_CERT_S* pstRecv,
* X509_CERT_S* pstSign,
* SEC_CHAR* pcTId,
* SEC_CHAR* pcSNonce,
* SEC_UINT32 ulSLen,
* SEC_PKEY_S* pstSignKey,
* SEC_UINT32 enDigestAlgo,
* SEC_UINT32 enDigEncryAlgo,
* SEC_UINT32 enCEAlgo);
* @endcode
*
* @par Purpose
* To create an enveloped and signed SCEP request message.
*
* @par Description
* This function Creates and returns the envoloped and signed Request. The user must envelop and sign the request
* messages to provide security, authenticity and non-repudiation. For Envelope: Encrypt the PKCS#10 certificate request
* using a randomly generated content-encryption key. This content-encryption key is then encrypted by the CA's public
* key and included in the recipientInfo. Create SignedData by adding the requester's self or CA-certificate as the
* signer's public key certificate. Include the message type, transaction id, the senderNonce and the message digest as
* the authenticated attributes and sign the attributes using the end entity's private key. The user must verify the
* request (pData) and type of request (enMsgType) before passing the same to this function.
*
* @param[in] pData Pointer to the request message which has to be
*                  enveloped and signed for sending to CA server [N/A]
* @param[in] enMsgType Type of the request message(pData) [N/A]
* @param[in] pstRecv Recipient (CA) Certificate, to envolope [N/A]
* @param[in] pstSign Self-sign cert(transID as serial
*                    Number) OR issued certificate [N/A]
* @param[in] pcTId Transaction ID,to be added as the attribute [N/A]
* @param[in] pcSNonce Sendor Nonce [N/A]
* @param[in] ulSLen Length of the sender nonce [N/A]
* @param[in] pstSignKey Pointer to the requester's private key,
*					    for signing. Only RSA is supported [N/A]
* @param[in] enDigestAlgo Hash Algorithm to be used to calculate
*                         digest and hash while signing. Possible
*						  values are ALGID_MD5, ALGID_SHA1,
*						  ALGID_SHA256 and ALGID_SHA512 [N/A]
* @param[in] enDigEncryAlgo Symmetric algorithm for encrypting the digest: ALGID_RSA [N/A]
* @param[in] enCEAlgo Asymmetric algorithm to be used to encrypt the content:
*                     ALGID_DES_ECB, ALGID_DES_CBC, ALGID_DES_EDE3_CBC [N/A]
* @param[out] N/A N/A [N/A]
* @retval SCEP_MSG_S* Envoloped and signed request message [SCEP_MSG_S*|N/A]
* @retval SCEP_MSG_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
* - If SCEP_MSGTYPE_E enum passed to th API is SCEP_MSG_GETCRL then the SEC_VOID* pData
* should be SCEP_CRLQUERY_EX_S pointer.
* - If SCEP_MSGTYPE_E enum passed to th API is SCEP_MSG_CERTREP then the SEC_VOID* pData
* should be PKCS7_MSG_S pointer.
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns the envoloped and signed Request */
PSELINKDLL SCEP_MSG_S*
SCEP_createEnvAndSignReq(SEC_VOID* pData,
                         SCEP_MSGTYPE_E enMsgType,
                         X509_CERT_S* pstRecv,
                         X509_CERT_S* pstSign,
                         SEC_CHAR* pcTId,
                         SEC_CHAR* pcSNonce,
                         SEC_UINT32 ulSLen,
                         SEC_PKEY_S* pstSignKey,
                         SEC_UINT32 enDigestAlgo,
                         SEC_UINT32 enDigEncryAlgo,
                         SEC_UINT32 enCEAlgo);




/**
* @defgroup SCEP_createEnvAndSignResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_MSG_S* SCEP_createEnvAndSignResp(SEC_VOID* pData,
* SCEP_MSGTYPE_E enMsgType,
* X509_CERT_S* pstRecv,
* X509_CERT_S* pstSign,
* SEC_CHAR* pcTId,
* SEC_CHAR* pcSNonce,
* SEC_UINT32 ulSLen,
* SEC_CHAR* pcRNonce,
* SEC_UINT32 ulRLen,
* SEC_PKEY_S* pstSignKey,
* SEC_UINT32 enDigestAlgo,
* SEC_UINT32 enDigEncryAlgo,
* SEC_UINT32 enCEAlgo);
* @endcode
*
* @par Purpose
* To create an enveloped and signed SCEP response message.
* @par Description
* This function Creates and returns the envoloped and signed
* Response. The user must envelop and sign the response messages to
* provide security, authenticity and non-repudiation.
* The information portion of CertRep will be a degenerated
* PKCS#7 which contains the requester's certificate.  The user must
* verify the response (pData) and type of response (enMsgType) before
* passing the same to this function.
*
* @param[in] pData Pointer to the response message which has to be
*                  enveloped and signed before sending to requester (client) [N/A]
* @param[in] enMsgType Type of the response message(pData) [N/A]
* @param[in] pstRecv Recipient's Certificate, used to envelope [N/A]
* @param[in] pstSign Signer certificate (CA's certificate) [N/A]
* @param[in] pcTId Transaction ID to be added as the attribute
*				   (Same as recieved in request message) [N/A]
* @param[in] pcSNonce Sender Nonce [N/A]
* @param[in] ulSLen Length of the sender nonce [N/A]
* @param[in] pcRNonce Recipient Nonce [N/A]
* @param[in] ulRLen Length of the Recipient nonce [N/A]
* @param[in] pstSignKey Pointer to the Signer's (CA's) private key,
*						for signing. Only RSA is supported [N/A]
* @param[in] enDigestAlgo Hash Algorithm to be used to calculate
*                         digest and hash while signing. Possible
*						  values are ALGID_MD5, ALGID_SHA1,
*						  ALGID_SHA256 and ALGID_SHA512 [N/A]
* @param[in] enDigEncryAlgo Symmetric algorithm for encrypting the digest: ALGID_RSA
* @param[in] enCEAlgo Asymmetric algorithm to be used to encrypt the content:
*                     ALGID_DES_ECB, ALGID_DES_CBC, ALGID_DES_EDE3_CBC [N/A]
* @param[out] N/A N/A [N/A]
* @retval SCEP_MSG_S* Envoloped and signed response message [SCEP_MSG_S*|N/A]
* @retval SCEP_MSG_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Creates and returns the envoloped and signed Response */
PSELINKDLL SCEP_MSG_S*
SCEP_createEnvAndSignResp(SEC_VOID* pData,
                          SCEP_MSGTYPE_E enMsgType,
                          X509_CERT_S* pstRecv,
                          X509_CERT_S* pstSign,
                          SEC_CHAR* pcTId,
                          SEC_CHAR* pcSNonce,
                          SEC_UINT32 ulSLen,
                          SEC_CHAR* pcRNonce,
                          SEC_UINT32 ulRLen,
                          SEC_PKEY_S* pstSignKey,
                          SEC_UINT32 enDigestAlgo,
                          SEC_UINT32 enDigEncryAlgo,
                          SEC_UINT32 enCEAlgo);



/**
* @defgroup SCEP_createHTTPContent
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_HTTPCONTENT_S* SCEP_createHTTPContent(SCEP_MSGTYPE_E enMsgType,
* SEC_CHAR* pcCgiPath, SEC_BOOL bPost, SEC_CHAR* pMsg, SEC_UINT32 ulMsgLen);
* @endcode
*
* @par Purpose
* To Create and return HTTP Content
* @par Description
* HTTP is used as the transport protocol for the PKI messages
* SCEP uses the HTTP "GET" and "POST" messages to request information
* from the CA. Requests for CA certificate or capabilities are sent as
* simple HTTP requests, using "GET",With the OPERATION and MESSAGE fields
* identifying the requested data.CRLs may also be requested in the clear
* if the CA supports it.
*
* @param[in] enMsgType The type of the message [N/A]
* @param[in] pcCgiPath The path of CGI Program, This is a string [N/A]
* @param[in] bPost The Flag. TRUE for POST and FALSE for GET [N/A]
* @param[in] pMsg Message to be included in the HTTP Content [N/A]
* @param[in] ulMsgLen Length of the message (pMsg) [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_HTTPCONTENT_S* Created HTTP Content [SCEP_HTTPCONTENT_S*|N/A]
* @retval SCEP_HTTPCONTENT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns HTTP Content */
PSELINKDLL SCEP_HTTPCONTENT_S*
SCEP_createHTTPContent(SCEP_MSGTYPE_E enMsgType,
                       SEC_CHAR* pcCgiPath,
                       SEC_BOOL bPost,
                       SEC_CHAR* pMsg,
                       SEC_UINT32 ulMsgLen);



/**
* @defgroup SCEP_createPKIMsgHTTPResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_HTTPCONTENT_S* SCEP_createPKIMsgHTTPResp(SEC_CHAR* pMsg, SEC_UINT32 ulMsgLen);
* @endcode
*
* @par Purpose
* To create PKI message HTTP response.
* @par Description
* This function Creates and returns PKI Message HTTP Response.
* For each GET operation, the CA/RA server will return a MIME object via
* HTTP. For a GET operation with PKIOperation as its type, the response is
* tagged as having a Content Type of application/x-pki-message. The body
* of this message is a BER encoded binary PKI message
*
* @param[in] pMsg BER encoded PKI Message for HTTP Response [N/A]
* @param[in] ulMsgLen Length of the given PKI Message [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_HTTPCONTENT_S* Pointer to the generated HTTP response[SCEP_HTTPCONTENT_S*|N/A]
* @retval SCEP_HTTPCONTENT_S* In case of failure[SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns PKI Message HTTP Response */
PSELINKDLL SCEP_HTTPCONTENT_S*
SCEP_createPKIMsgHTTPResp(SEC_CHAR* pMsg,
                          SEC_UINT32 ulMsgLen);




/**
* @defgroup SCEP_createCACertResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_HTTPCONTENT_S* SCEP_createCACertResp(X509_CERT_S* pstCACert, X509_CERT_S* pstRACert);
* @endcode
*
* @par Purpose
* To create a CA Certificate Response.
* @par Description
* This function Creates and returns CA Certificate Response.
* The MIME content type returned will depend on whether or not an RA
* is in use. If there is no RA in use, only the CA certificate is
* sent back in the response with the response CONTENT TYPE as
* 'application/x-x509-ca-cert'. The content of the response message
* is a DER encoded binary X.509 certificate. If an RA is in use, then
* RA certificates are sent back together with the CA certificates with
* the response CONTENT TYPE as 'application/x-x509-ca-ra-cert'.
* For this a PKCS#7 SignedData having only certificates is sent back
* in the response and the SignerInfo is empty. The RA certificate
* if present must be signed by the CA. This must be validated before
* passing the certificates to this function.
*
* @param[in] pstCACert CA Certificate [N/A]
* @param[in] pstRACert RA Certificate, (Optional) [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_HTTPCONTENT_S* Pointer to the generated Cert response [SCEP_HTTPCONTENT_S*|N/A]
* @retval SCEP_HTTPCONTENT_S* In case of failure[SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
/* Creates and returns CA Certificate Response */
PSELINKDLL SCEP_HTTPCONTENT_S*
SCEP_createCACertResp(X509_CERT_S* pstCACert,
                      X509_CERT_S* pstRACert);




/**
* @defgroup SCEP_createNextCACertResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_HTTPCONTENT_S* SCEP_createNextCACertResp(X509_CERT_S* pstNextCert,
* X509_CERT_S* pstRACert,
* X509_CERT_S* pstCurrCACert,
* SEC_PKEY_S* pstSignKey,
* SEC_UINT32 enDigestAlgo,
* SEC_UINT32 enDigEncryAlgo);
* @endcode
*
* @par Purpose
* To create the Next CA Certificate response.
* @par Description
* This function Creates and returns Next CA Certificate Response
* The response to GetNextCACert is always a PKCS#7 SignedData having
* only certificates and has content type as application/x-x509-ca-ra-cert.
* If there is an RA, The signer is the current RA certificate otherwise,
* the signer is the current CA certificate.
*
* @param[in] pstNextCert Pointer to the next CA Certificate [N/A]
* @param[in] pstRACert Pointer to the RA Certificate [N/A]
* @param[in] pstCurrCACert Pointer to the Current CA Certificate [N/A
* @param[in] pstSignKey Pointer to the Private Key of signer
*						Only RSA is supported [N/A]
* @param[in] enDigestAlgo Algorithm used to calculate digest.
*						  Possible values are ALGID_MD5, ALGID_SHA1,
*						  ALGID_SHA256 and ALGID_SHA512 [N/A]
* @param[in] enDigEncryAlgo Symmetric Algorithm used to encrypt digest: ALGID_RSA [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_HTTPCONTENT_S* Pointer to the created HTTPContent[SCEP_HTTPCONTENT_S*|N/A]
* @retval SCEP_HTTPCONTENT_S* In case of failure[SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* 1. If RA Certificate is not there, pstCurrCACert should be given.\n
* 2. If RA Certificate is passed,pstSignKey is the private key of RA Certificate. Then pstCurrCACert is Not required.\n
* 3. Ensure that private key is correct one as per above points. No validation has been done to check the correctness
* of this.
*
* @par Related Topics
* N/A
*/
/* Creates and returns Next CA Certificate Response  */

PSELINKDLL SCEP_HTTPCONTENT_S*
SCEP_createNextCACertResp(X509_CERT_S* pstNextCert,
                          X509_CERT_S* pstRACert,
                          X509_CERT_S* pstCurrCACert,
                          SEC_PKEY_S* pstSignKey,
                          SEC_UINT32 enDigestAlgo,
                          SEC_UINT32 enDigEncryAlgo);




/**
* @defgroup SCEP_createCACapsResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_HTTPCONTENT_S* SCEP_createCACapsResp(SEC_UINT32 ulCaps);
* @endcode
*
* @par Purpose
* To create CA Capabilities Response.
* @par Description
* This function Creates and returns CA Capabilities Response
* The response for a GetCACaps message is a list of CA capabilities, in
* plain text, separated by <LF> characters.
* A client must be able to accept and ignore any unknown keywords that
* might be sent back by a CA that implements a future version of SCEP.
* If none of the above capabilities are supported by the CA, blank data
* is returned.
*
* @param[in] ulCaps Capabalities, As ORed Bit Flags:
*                   SEC_CAPS_NEXTCACERT, SEC_CAPS_POSTPKIOPS
*                   SEC_CAPS_SHA1, SEC_CAPS_RENEW, SEC_CAPS_SHA256
*                   SEC_CAPS_SHA512 SEC_CAPS_3DES [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_HTTPCONTENT_S* Pointer to the created HTTP Content [SCEP_HTTPCONTENT_S*|N/A]
* @retval SCEP_HTTPCONTENT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Creates and returns CA Capabilities Response */
PSELINKDLL SCEP_HTTPCONTENT_S*
SCEP_createCACapsResp(SEC_UINT32 ulCaps);





/**
* @defgroup SCEP_createCACertChainResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_HTTPCONTENT_S* SCEP_createCACertChainResp(SEC_List_S* pCertChain);
* @endcode
*
* @par Purpose
* To create CA Certificate Chain Response.
* @par Description
* This function Creates and returns CA Certificate Chain Response.
* The response for GetCACertChain is a PKCS#7 SignedData having only
* certificates and has Content-Type set as application/x-x509-ca-ra-cert-chain.
*
* @param[in] pCertChain Pointer to the certificate list [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_HTTPCONTENT_S* Pointer to the created HTTP Content[SCEP_HTTPCONTENT_S*|N/A]
* @retval SCEP_HTTPCONTENT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Creates and returns CA Certificate Chain Response */
PSELINKDLL SCEP_HTTPCONTENT_S*
SCEP_createCACertChainResp(SEC_List_S* pCertChain);



/**
* @defgroup SCEP_extractContentFromMsg
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID* SCEP_extractContentFromMsg(SCEP_MSG_S* pMsg, SEC_PKEY_S* pstPvtKey,
* SEC_NAME_S* pstIssuer, SEC_BIGINT_S* pstSerialNum,
* SCEP_MSGTYPE_E* pMessageType);
* @endcode
*
* @par Purpose
* To extract the content from the given message.
* @par Description
* This function gets the content from the given Message.
*
* @param[in] pMsg Pointer to the SCEP Message from [N/A]
* @param[in] pstPvtKey Pointer to the Private Key
*					   Only RSA is supported [N/A]
* @param[in] pstIssuer Pointer to the Issuer Name [N/A]
* @param[in] pstSerialNum Pointer to Issuer's Serial Number
* @param[out] pMessageType Type of the Message extracted from
* the input message [N/A]
*
* @retval SEC_VOID* In case of success [Pointer to the decoded Message|N/A]
* @retval SEC_VOID* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Get content from the given Message */
PSELINKDLL SEC_VOID*
SCEP_extractContentFromMsg(SCEP_MSG_S* pMsg,
                       SEC_PKEY_S* pstPvtKey,
                       SEC_NAME_S* pstIssuer,
                       SEC_BIGINT_S* pstSerialNum,
                       SCEP_MSGTYPE_E* pMessageType);




/**
* @defgroup SCEP_extractContentFromHTTPMsg
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID* SCEP_extractContentFromHTTPMsg(SCEP_HTTPCONTENT_S* pMsg,
* SCEP_MSGTYPE_E* pMessageType);
* @endcode
*
* @par Purpose
* To extract the content from the given HTTP Message.
* @par Description
* This function gets content from the given HTTP Message. If the
* message is PKI Message, returns AsnOcts pointer with PKIMessage.
* If the message CACert type, returns the pointer to Certificate.
* If the message CARACert type,returns the pointer to SignedData.
* If the message CACaps type, returns the CA Capabilities.
* Out value pMessageType, holds the type of message.
*
* @param[in] pMsg Pointer to HTTP Content Message [N/A]
* @param[out] pMessageType Type of the Message extracted from
* the input [N/A]
*
* @retval SEC_VOID* Pointer to the Message [SEC_VOID*|N/A]
* @retval SEC_VOID* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Get content from the given HTTP Message */
PSELINKDLL SEC_VOID*
SCEP_extractContentFromHTTPMsg(SCEP_HTTPCONTENT_S* pMsg,
                           SCEP_MSGTYPE_E* pMessageType);


/**
* @defgroup SCEP_verifyMsg
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UINT32 SCEP_verifyMsg(PKCS7_MSG_S*  pstPKCS7,
* SEC_List_S*  pCertList,
* SEC_NAME_S* pstSignerIssuer ,
* SEC_BIGINT_S  signerSN,
* SEC_NAME_S* pstRecipIssuer ,
* SEC_BIGINT_S  recipSN,
* SEC_PKEY_S* pstPrivKeyInfo );
* @endcode
*
* @par Purpose
* To verify the signature on the given PKCS7 Message.
* @par Description
* This function verifies the signature on given Message
* If the requester does not have a certificate path to a
* trusted CA certificate, then fingerprint may
* be used to verify the certificate.
*
* @param[in] pstPKCS7 Message to be Verified [N/A]
* @param[in] pCertList List of certificates [N/A]
* @param[in] pstSignerIssuer Certificate Issuer Name [N/A]
* @param[in] signerSN Issuer's Serial Number [N/A]
* @param[in] pstRecipIssuer Recipient Name [N/A]
* @param[in] recipSN Recipient's Serial Number [N/A]
* @param[in] pstPrivKeyInfo Recipient's Private Key
*			 Only RSA is supported [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Status of the signature verification [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 Some of the Inputs are NULL/invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 Verification of sign on message failed [SEC_ERR_SIGN_VERIFY_FAILED|N/A]
* @retval SEC_UINT32 Memory allocation failed [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Verifies the signature on given Message */
PSELINKDLL SEC_UINT32 SCEP_verifyMsg(PKCS7_MSG_S*  pstPKCS7,
                    SEC_List_S*  pCertList,
                    SEC_NAME_S* pstSignerIssuer ,
                    SEC_BIGINT_S  signerSN,
                    SEC_NAME_S* pstRecipIssuer ,
                    SEC_BIGINT_S  recipSN,
                    SEC_PKEY_S* pstPrivKeyInfo );




/**
* @defgroup SCEP_genChallengePasswd
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_genChallengePasswd(SEC_UINT32 ulLen);
* @endcode
*
* @par Purpose
* To generate the Challenge password.
* @par Description
* This function generates the challenge password. This can be used
* for automatic authentication. In the manual authentication case,
* the challenge password is only used to authenticate a request for
* the certificate's revocation. This challenge password is included
* as a PKCS#10 attribute and is sent to the server as encrypted data.
* The PKCS#7 envelope protects the privacy of the challenge password
* by encrypting it.
*
* @param[in] ulLen Length of the required challenge Password [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* Pointer to the generated challenge Password [SEC_CHAR*|N/A]
* @retval SEC_CHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Generates the challenge password */
PSELINKDLL SEC_UCHAR*
SCEP_genChallengePasswd(SEC_UINT32 ulLen);




/**
* @defgroup SCEP_generateNonce
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_generateNonce(SEC_INT32* pulNonceLen);
* @endcode
*
* @par Purpose
* To generate the Nonce.
* @par Description
* This function generates the Nonce, length of 16 bytes, to be
* used to create Sender Nonce by the server and client.
* When a requester sends a PKI message to the server, a senderNonce is
* included in the message. The same is returned by the server as recipient
* nonce. This is used by requester(client) to prevent replay problems.
*
* @param[in] N/A N/A [N/A]
* @param[out] pulNonceLen Returned Nonce Length, Always 16 [N/A]
*
* @retval SEC_UCHAR* Generated Nonce. 16 Bytes Length [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Generates the Nonce, length of 16 bytes */
PSELINKDLL SEC_UCHAR*
SCEP_generateNonce(SEC_INT32* pulNonceLen);




/**
* @defgroup SCEP_compareNonce
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UINT32 SCEP_compareNonce(SEC_CHAR* pcSrcNonce, SEC_UINT32 ulSrcNonceLen,
* SEC_CHAR* pcDestNonce, SEC_UINT32 ulDestNonceLen);
* @endcode
*
* @par Purpose
* To compare whether two Nonce values are the same or different.
* @par Description
* When the requester send a PKI Message it adds a sender nonce in the
* message. The same is returned by the CA server as the recipient nonce.
* The requester on receiving the response must compare the sent and
* recieved nonce to prevent replay problems.
* This function provide the facility to compare two nonce values.
*
* @param[in] pcSrcNonce Source Nonce [N/A]
* @param[in] ulSrcNonceLen Source Nonce Length [N/A]
* @param[in] pcDestNonce Destination Nonce [N/A]
* @param[in] ulDestNonceLen Destination Nonce Length [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If both are same [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If input arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If nonce dont match [SEC_ERR_NONCE_MISMATCH|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Compares two given Nonce Values */
PSELINKDLL SEC_UINT32
SCEP_compareNonce(SEC_CHAR* pcSrcNonce,
                  SEC_UINT32 ulSrcNonceLen,
                  SEC_CHAR* pcDestNonce,
                  SEC_UINT32 ulDestNonceLen);



/**
* @defgroup SCEP_getMsgType
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_MSGTYPE_E SCEP_getMsgType(SCEP_MSG_S* pMsg);
* @endcode
*
* @par Purpose
* To fetch the type of the given SCEP message.
* @par Description
* This function gets the message type from the given SCEP message.
* The messageType attribute specify the type of operation performed by the
* transaction. This attribute is required in all PKI messages.
*
* @param[in] pMsg Pointer to the SCEP message [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_MSGTYPE_E Message Type of the given message [SCEP_MSGTYPE_E|N/A]
* @retval SCEP_MSGTYPE_E In case of any error [SCEP_MSG_TYPE_UNKNOWN|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the message type from the given message */
PSELINKDLL SCEP_MSGTYPE_E
SCEP_getMsgType(SCEP_MSG_S* pMsg);




/**
* @defgroup SCEP_getHTTPContentType
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_MSGTYPE_E SCEP_getHTTPContentType(SCEP_HTTPCONTENT_S* pMsg);
* @endcode
*
* @par Purpose
* To fetch the content type from the given HTTP Content message.
* @par Description
* This function gets the content type from the given HTTPContent.
* This method is used to process the response from the CA Server.
*
* @param[in] pMsg Pointer to the HTTP Content Message [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_MSGTYPE_E Message type of the given message [SCEP_MSGTYPE_E|N/A]
* @retval SCEP_MSGTYPE_E In case of any error [SCEP_MSG_TYPE_UNKNOWN|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the content type from the given HTTPContent  */
PSELINKDLL SCEP_MSGTYPE_E
SCEP_getHTTPContentType(SCEP_HTTPCONTENT_S* pMsg);




/**
* @defgroup SCEP_extractCACert
* @ingroup scepFunctions
* @par Prototype
* @code
* X509_CERT_S* SCEP_extractCACert(SCEP_HTTPCONTENT_S* pMsg);
* @endcode
*
* @par Purpose
* To get the CA Certificate from the given HTTP Content message.
* @par Description
* This function gets the CACert from the given HTTPContent
*
* @param[in] pMsg Pointer to HTTP Content Message [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* CA Certificate from Message [X509_CERT_S*|N/A]
* @retval X509_CERT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the CACert from the given HTTPContent */
PSELINKDLL X509_CERT_S*
SCEP_extractCACert(SCEP_HTTPCONTENT_S* pMsg);





/**
* @defgroup SCEP_getCert
* @ingroup scepFunctions
* @par Prototype
* @code
* X509_CERT_S* SCEP_getCert(SCEP_CERTRESP_S* pCertResp);
* @endcode
*
* @par Purpose
* To extract the Certificate from the given Certificate Response message.
* @par Description
* This function gets the Certificate from the given Certificate Response.
* It fetches the first certificate from the list in the Response message.
*
* @param[in] pCertResp Pointer to Certificate Response Message [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Certificate from Message [X509_CERT_S*|N/A]
* @retval X509_CERT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the Cert from the given Certificate Response */
PSELINKDLL X509_CERT_S*
SCEP_getCert(SCEP_CERTRESP_S* pCertResp);




/**
* @defgroup SCEP_getCRL
* @ingroup scepFunctions
* @par Prototype
* @code
* X509_CRL_S* SCEP_getCRL(SCEP_CRLRESP_S* pCRLResp);
* @endcode
*
* @par Purpose
* To extract the CRL from the given CRL Response message.
* @par Description
* This function gets the CRL from the given Response.
*
* @param[in] pCRLResp Pointer to the CRL Resonse [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CRL_S Pointer to the returned CRL [X509_CRL_S|N/A]
* @retval X509_CRL_S In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the CRL from the given Response */
PSELINKDLL X509_CRL_S*
SCEP_getCRL(SCEP_CRLRESP_S* pCRLResp);




/**
* @defgroup SCEP_getCARACert
* @ingroup scepFunctions
* @par Prototype
* @code
* X509_CERT_S* SCEP_getCARACert(SCEP_CERTRESP_S* pCertResp,
* SEC_NAME_S* pstIssuer, SEC_BIGINT_S* pstSerialNumber);
* @endcode
*
* @par Purpose
* To fetch the CA or RA certificate from the given SCEP Certificate response message.
* @par Description
* This function gets CA cert or RA cert from the CertRep message
* based on the given issuer name and serial number.
*
* @param[in] pCertResp Certificate Response [N/A]
* @param[in] pstIssuer Issuer Name [N/A]
* @param[in] pstSerialNumber Serial Number [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Fetched Certificate [X509_CERT_S*|N/A]
* @retval X509_CERT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets CA/RA cert fields from the CertRep message */
PSELINKDLL X509_CERT_S*
SCEP_getCARACert(SCEP_CERTRESP_S* pCertResp,
                            SEC_NAME_S* pstIssuer,
                            SEC_BIGINT_S* pstSerialNumber);



/**
* @defgroup SCEP_getCACaps
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UINT32 SCEP_getCACaps(SCEP_HTTPCONTENT_S* pMsg);
* @endcode
*
* @par Purpose
* To fetch the CA capabilities from the given HTTP Content message.
* @par Description
* This function gets the CA Capabilities from the HTTP Content Message.
*
* @param[in] pMsg Pointer to HTTP Content Message [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 CA Capabilities. (Possible values) [A value between 1 and 64|N/A]
* @retval SEC_UINT32 In case of any error [0|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the CA Capabilities from HTTP Messages */
PSELINKDLL SEC_UINT32
SCEP_getCACaps(SCEP_HTTPCONTENT_S* pMsg);




/**
* @defgroup SCEP_extractCertList
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_List_S* SCEP_extractCertList(SCEP_CERTRESP_S * pCertResp);
* @endcode
*
* @par Purpose
* To fetch the certificate list from the given SCEP certificate response message.
* @par Description
* This function gets the Certificate List from Certificate Response.
*
* @param[in] pCertResp Pointer to the Certificate Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Certificate List from the Response [SEC_List_S*|N/A]
* @retval SEC_List_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the Certificate List from Cert Response */
PSELINKDLL SEC_List_S*
SCEP_extractCertList(SCEP_CERTRESP_S * pCertResp);



/**
* @defgroup SCEP_getStatus
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_STATUS_E SCEP_getStatus(SCEP_MSG_S* pMsg);
* @endcode
*
* @par Purpose
* To fetch the Status of the given SCEP message.
* @par Description
* This function gets the status from the SCEP message.
*
* @param[in] pMsg Pointer to the Message [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval SCEP_STATUS_E Status in the message [SCEP_STATUS_E|N/A]
* @retval SCEP_STATUS_E In case of failure [SCEP_STATUS_UNKNOWN|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the status */
PSELINKDLL SCEP_STATUS_E
SCEP_getStatus(SCEP_MSG_S* pMsg);



/**
* @defgroup SCEP_getReason
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_REASON_E SCEP_getReason(SCEP_MSG_S* pMsg);
* @endcode
*
* @par Purpose
* To fetch the reason for failure from the given SCEP response message.
* @par Description
* This function gets the reason for failure from the SCEP response message.
*
* @param[in] pMsg Pointer to Message [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_REASON_E Failure Reason in the Message [SCEP_REASON_E|N/A]
* @retval SCEP_REASON_E In case of failure [SCEP_REASON_UNKNOWN|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the reason */
PSELINKDLL SCEP_REASON_E
SCEP_getReason(SCEP_MSG_S* pMsg);



/**
* @defgroup SCEP_getSenderNonce
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_CHAR* SCEP_getSenderNonce(SCEP_MSG_S* pMsg, SEC_UINT32* pLen);
* @endcode
*
* @par Purpose
* To fetch the sender nonce from the given SCEP message.
* @par Description
* This function gets the sender nonce from the SCEP message.
*
* @param[in] pMsg Pointer to the Message [N/A]
* @param[out] pLen Length of the returned Nonce [N/A]
*
* @retval SEC_CHAR* Pointer to the Sender Nonce in the Message [SEC_CHAR*|N/A]
* @retval SEC_CHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the sender nonce */
PSELINKDLL SEC_CHAR*
SCEP_getSenderNonce(SCEP_MSG_S* pMsg,
                    SEC_UINT32* pLen);



/**
* @defgroup SCEP_getRecipientNonce
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_CHAR* SCEP_getRecipientNonce(SCEP_MSG_S* pMsg, SEC_UINT32* pLen);
* @endcode
*
* @par Purpose
* To fetch the recipient nonce from the given SCEP message.
* @par Description
* This function gets the recipient nonce from the SCEP message.
*
* @param[in] pMsg Pointer to the Message
* @param[out] pLen Length of the returned Nonce
*
* @retval SEC_CHAR* Pointer to Recipient Nonce in the Message [SEC_CHAR*|N/A]
* @retval SEC_CHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the recipient nonce */
PSELINKDLL SEC_CHAR*
SCEP_getRecipientNonce(SCEP_MSG_S* pMsg,
                       SEC_UINT32* pLen);


/**
* @defgroup SCEP_getTID
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_CHAR* SCEP_getTID(SCEP_MSG_S* pMsg, SEC_UINT32* pLen);
* @endcode
*
* @par Purpose
* To fetch the TID from the given SCEP Message.
* @par Description
* This function gets the transaction ID from the SCEP message.
*
* @param[in] pMsg Pointer to the Message [N/A]
* @param[out] pLen Length of the returned Transaction ID [N/A]
*
* @retval SEC_CHAR* Pointer to Transaction ID in the Message [SEC_CHAR*|N/A]
* @retval SEC_CHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the transaction ID */
PSELINKDLL SEC_CHAR*
SCEP_getTID(SCEP_MSG_S* pMsg,
                SEC_UINT32* pLen);



/**
* @defgroup SCEP_getIssuerFromCertPollReq
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_NAME_S* SCEP_getIssuerFromCertPollReq(SCEP_CERTPOLLREQ_S* pstCertPollReq);
* @endcode
*
* @par Purpose
* To fetch the Issuer name from the given SCEP Certificate Poll request structure.
* @par Description
* This function gets the Issuer from Certificate Poll Request Structure.
*
* @param[in] pstCertPollReq Cert Poll Request Pointer [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* Issuer Name [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the Issuer from Cert Poll Request Structure */
PSELINKDLL SEC_NAME_S*
SCEP_getIssuerFromCertPollReq(SCEP_CERTPOLLREQ_S* pstCertPollReq);




/**
* @defgroup SCEP_getSubjectFromCertPollReq
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_NAME_S* SCEP_getSubjectFromCertPollReq(SCEP_CERTPOLLREQ_S* pstCertPollReq);
* @endcode
*
* @par Purpose
* To fetch the Subject Name from the given SCEP Certificate Poll request structure.
* @par Description
* This function gets the Subject from Cert Poll Request Structure.
*
* @param[in] pstCertPollReq Cert Poll Request Pointer [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* Subject Name [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the Subject from Cert Poll Request Structure */
PSELINKDLL SEC_NAME_S*
SCEP_getSubjectFromCertPollReq(SCEP_CERTPOLLREQ_S* pstCertPollReq);




/**
* @defgroup SCEP_getSNFromCRLQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_BIGINT_S* SCEP_getSNFromCRLQuery(SCEP_CRLQUERY_S* pstCRLQuery);
* @endcode
*
* @par Purpose
* To fetch the Serial Number from the given SCEP CRL query structure.
* @par Description
* This function gets the SerialNumber from CRL Query Structure.
*
* @param[in] pstCRLQuery CRL Query Pointer [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BIGINT_S* Serial Number [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the SerialNumber from CRL Query Structure */
PSELINKDLL SEC_BIGINT_S*
SCEP_getSNFromCRLQuery(SCEP_CRLQUERY_S* pstCRLQuery);




/**
* @defgroup SCEP_getIssuerFromCRLQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_NAME_S* SCEP_getIssuerFromCRLQuery(SCEP_CRLQUERY_S* pstCRLQuery);
* @endcode
*
* @par Purpose
* To fetch the Issuer Name from the given SCEP CRL Query structure.
* @par Description
* This function gets the Issuer from CRL Query Structure.
*
* @param[in] pstCRLQuery CRL Query Pointer [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* Issuer Name [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the Issuer from CRL Query Structure */
PSELINKDLL SEC_NAME_S*
SCEP_getIssuerFromCRLQuery(SCEP_CRLQUERY_S* pstCRLQuery);




/**
* @defgroup SCEP_getIssuerFromCertQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_NAME_S* SCEP_getIssuerFromCertQuery(SCEP_CERTQUERY_S* pstCertQuery);
* @endcode
*
* @par Purpose
* To fetch the Issuer name from the givne SCEP Certificate query structure.
* @par Description
* This function gets the Issuer from Cert Query Structure.
*
* @param[in] pstCertQuery Cert Query Pointer [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* Issuer Name [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Gets the Issuer from Cert Query Structure */
PSELINKDLL SEC_NAME_S*
SCEP_getIssuerFromCertQuery(SCEP_CERTQUERY_S* pstCertQuery);




/**
* @defgroup SCEP_getSNFromCertQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_BIGINT_S* SCEP_getSNFromCertQuery(SCEP_CERTQUERY_S* pstCertQuery);
* @endcode
*
* @par Purpose
* To fetch the Serial Number from the given SCEP Certificate Query Structure.
* @par Description
* This function gets the SerialNumber from Certficate Query Structure.
*
* @param[in] pstCertQuery Cert Query Pointer [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BIGINT_S* Serial Number [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


/* Gets the SerialNumber from Cert Query Structure */
PSELINKDLL SEC_BIGINT_S*
SCEP_getSNFromCertQuery(SCEP_CERTQUERY_S* pstCertQuery);




/**
* @defgroup SCEP_freeCertReq
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeCertReq(PKCS10_REQ_S* pCertReq);
* @endcode
*
* @par Purpose
* To free the given PKCS10_REQ_S structure - the SCEP certificate request message.
* @par Description
* This function is used to free the memory allocated to the given Certifiate Request Structure.
*
* @param[in] pCertReq Pointer to the Certificate Request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Frees the given Certifiate Request Structure */
PSELINKDLL SEC_VOID
SCEP_freeCertReq(PKCS10_REQ_S* pCertReq);




/**
* @defgroup SCEP_freeCertResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeCertResp(SCEP_CERTRESP_S* pCertResp);
* @endcode
*
* @par Purpose
* To free the given SCEP_CERTRESP_S structure.
* @par Description
* This function is used to free the memory allocated to the given Certifiate Response Structure.
*
* @param[in] pCertResp Pointer to the Certificate Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


/* Frees the given Certifiate Response Structure */
PSELINKDLL SEC_VOID
SCEP_freeCertResp(SCEP_CERTRESP_S* pCertResp);




/**
* @defgroup SCEP_freeCertPollReq
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeCertPollReq(SCEP_CERTPOLLREQ_S* pCertPollReq);
* @endcode
*
* @par Purpose
* To free the given SCEP_CERTPOLLREQ_S structure.
* @par Description
* This function is used to free the memory allocated to the given CertPollReq Structure.
*
* @param[in] pCertPollReq Pointer to the CertPollRequest [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Frees the given CertPollReq Structure */
PSELINKDLL SEC_VOID
SCEP_freeCertPollReq(SCEP_CERTPOLLREQ_S* pCertPollReq);




/**
* @defgroup SCEP_freeCertQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeCertQuery(SCEP_CERTQUERY_S* pCertQuery);
* @endcode
*
* @par Purpose
* To free the given SCEP_CERTQUERY_S structure.
* @par Description
* This function is used to free the memory allocated to the given CertQuery Structure.
*
* @param[in] pCertQuery Pointer to the Cert Query [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Frees the given CertQuery Structure */
PSELINKDLL SEC_VOID
SCEP_freeCertQuery(SCEP_CERTQUERY_S* pCertQuery);




/**
* @defgroup SCEP_freeCRLQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeCRLQuery(SCEP_CRLQUERY_S* pCRLQuery);
* @endcode
*
* @par Purpose
* To free the given SCEP_CRLQUERY_S structure.
* @par Description
* This function is used to free the memory allocated to the given CRLQuery Structure.
*
* @param[in] pCRLQuery Pointer to the CRL Query [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Frees the given CRLQuery Structure */
PSELINKDLL SEC_VOID
SCEP_freeCRLQuery(SCEP_CRLQUERY_S* pCRLQuery);




/**
* @defgroup SCEP_freeHTTPContent
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeHTTPContent(SCEP_HTTPCONTENT_S* pHTTPContent);
* @endcode
*
* @par Purpose
* To free the given SCEP_HTTPCONTENT_S structure.
* @par Description
* This function is used to free the memory allocated to the given HTTPContent Structure.
*
* @param[in] pHTTPContent Pointer to HTTP Content [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Frees the given HTTPContent Structure */
PSELINKDLL SEC_VOID
SCEP_freeHTTPContent(SCEP_HTTPCONTENT_S* pHTTPContent);



/**
* @defgroup SCEP_freeCRLResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeCRLResp(SCEP_CRLRESP_S* pCRLResp);
* @endcode
*
* @par Purpose
* To free the given SCEP_CRLRESP_S structure.
* @par Description
* This function is used to free the memory allocated to the given CRLResp Structure.
*
* @param[in] pCRLResp Pointer to the CRL Response [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Frees the given CRLResp Structure */
PSELINKDLL SEC_VOID
SCEP_freeCRLResp(SCEP_CRLRESP_S* pCRLResp);



/**
* @defgroup SCEP_freeSCEPMsg
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeSCEPMsg(SCEP_MSG_S* pSCEPMessage);
* @endcode
*
* @par Purpose
* To free the given SCEP_MSG_S structure.
* @par Description
* This function is used to free the memory allocated to the given SCEPMessage Structure.
*
* @param[in] pSCEPMessage Pointer to the SCEP Message [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Frees the given SCEPMessage Structure */
PSELINKDLL SEC_VOID
SCEP_freeSCEPMsg(SCEP_MSG_S* pSCEPMessage);

/*encode functions*/



/**
* @defgroup SCEP_encodeSCEPMsg
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_encodeSCEPMsg(SCEP_MSG_S* pstSCEPMsg, SEC_UINT32* pulEncodedLen);
* @endcode
*
* @par Purpose
* To encode the given SCEP message.
* @par Description
* This function encodes the given SCEPMsg structure.
*
* @param[in] pstSCEPMsg Pointer to SCEP_MSG_S structure [N/A]
* @param[out] pulEncodedLen Encoded Buffer Length [N/A]
*
* @retval SEC_UCHAR* Encoded Buffer [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Encodes the given SCEPMsg */
PSELINKDLL SEC_UCHAR*
SCEP_encodeSCEPMsg(SCEP_MSG_S* pstSCEPMsg,
                   SEC_UINT32* pulEncodedLen);




/**
* @defgroup SCEP_encodeCertResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_encodeCertResp(SCEP_CERTRESP_S* pstCerResp, SEC_UINT32* pulEncodedLen);
* @endcode
*
* @par Purpose
* To encode the given SCEP Certificate response structure.
* @par Description
* This function encodes the given CertResp structure.
*
* @param[in] pstCerResp Pointer to the SCEP_CERTRESP_S [N/A]
* @param[out] pulEncodedLen Encoded Buffer Length [N/A]
*
* @retval SEC_UCHAR* Encoded Buffer [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/



/* Encodes the given CertResp */
PSELINKDLL SEC_UCHAR*
SCEP_encodeCertResp(SCEP_CERTRESP_S* pstCerResp,
                    SEC_UINT32* pulEncodedLen);



/**
* @defgroup SCEP_encodeCRLResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_encodeCRLResp(SCEP_CRLRESP_S* pstCRLResp, SEC_UINT32* pulEncodedLen);
* @endcode
*
* @par Purpose
* To encode the given SCEP CRL Response structure.
* @par Description
* This function encodes the given CRL Response structure.
*
* @param[in] pstCRLResp Pointer to the SCEP_CRLRESP_S [N/A]
* @param[out] pulEncodedLen Encoded Buffer Length [N/A]
*
* @retval SEC_UCHAR* Encoded Buffer [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Encodes the given CRL Response */
PSELINKDLL SEC_UCHAR*
SCEP_encodeCRLResp(SCEP_CRLRESP_S* pstCRLResp,
                   SEC_UINT32* pulEncodedLen);



/**
* @defgroup SCEP_encodeCertQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_encodeCertQuery(SCEP_CERTQUERY_S* pstCertQuery, SEC_UINT32* pulEncodedLen);
* @endcode
*
* @par Purpose
* To encode the given SCEP Certificate Query structure.
* @par Description
* This function encodes the given Cert Query structure.
*
* @param[in] pstCertQuery Pointer to SCEP_CERTQUERY_S [N/A]
* @param[out] pulEncodedLen Encoded Buffer Length [N/A]
*
* @retval SEC_UCHAR* Encoded Buffer [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Encodes the given Cert Query */
PSELINKDLL SEC_UCHAR*
SCEP_encodeCertQuery(SCEP_CERTQUERY_S* pstCertQuery,
                     SEC_UINT32* pulEncodedLen);



/**
* @defgroup SCEP_encodeHTTPContent
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_encodeHTTPContent(SCEP_HTTPCONTENT_S* pstHTTPContent, SEC_UINT32* pulEncodedLen);
* @endcode
*
* @par Purpose
* To encode the given SCEP HTTP Content structure.
* @par Description
* This function encodes the given HTTP Content structure.
*
* @param[in] pstHTTPContent Pointer to SCEP_HTTPCONTENT_S [N/A]
* @param[out] pulEncodedLen Encoded Buffer Length [N/A]
*
* @retval SEC_UCHAR* Encoded Buffer [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Encodes the given HTTP Content */
PSELINKDLL SEC_UCHAR*
SCEP_encodeHTTPContent(SCEP_HTTPCONTENT_S* pstHTTPContent,
                       SEC_UINT32* pulEncodedLen);



/**
* @defgroup SCEP_encodeCertPollReq
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_encodeCertPollReq(SCEP_CERTPOLLREQ_S *pstCertPollReq, SEC_UINT32* pulEncodedLen);
* @endcode
*
* @par Purpose
* To encode the given SCEP Certificate Poll request structure.
* @par Description
* This function encodes the given CertPollReq structure.
*
* @param[in] pstCertPollReq Pointer to SCEP_CERTPOLLREQ_S [N/A]
* @param[out] pulEncodedLen Encoded Buffer Length [N/A]
*
* @retval SEC_UCHAR* Encoded Buffer [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Encodes the given CertPollReq */
PSELINKDLL SEC_UCHAR*
SCEP_encodeCertPollReq(SCEP_CERTPOLLREQ_S *pstCertPollReq,
                       SEC_UINT32* pulEncodedLen);



/**
* @defgroup SCEP_encodeCRLQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_UCHAR* SCEP_encodeCRLQuery(SCEP_CRLQUERY_S* pstCRLQuery, SEC_UINT32* pulEncodedLen);
* @endcode
*
* @par Purpose
* To encode the given SCEP CRL Query structure.
* @par Description
* This function encodes the given CRLQuery structure.
*
* @param[in] pstCRLQuery Pointer to SCEP_CRLQUERY_S [N/A]
* @param[out] pulEncodedLen Encoded Buffer Length [N/A]
*
* @retval SEC_UCHAR* Encoded Buffer [SEC_UCHAR*|N/A]
* @retval SEC_UCHAR* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Encodes the given CRLQuery */
PSELINKDLL SEC_UCHAR*
SCEP_encodeCRLQuery(SCEP_CRLQUERY_S* pstCRLQuery,
                    SEC_UINT32* pulEncodedLen);

/*decode functions*/



/**
* @defgroup SCEP_decodeSCEPMsg
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_MSG_S* SCEP_decodeSCEPMsg(SEC_UCHAR* pcEncodedValue, SEC_UINT32 ulLength,
* SEC_UINT32* pulDecodedLen);
* @endcode
*
* @par Purpose
* To generate the decoded SCEP_MSG_S structure from the encoded SCEP message buffer.
* @par Description
* This function decodes the given encoded SCEPMsg structure.
*
* @param[in] pcEncodedValue Pointer to the encoded buffer [N/A]
* @param[in] ulLength Length of the encoded buffer [N/A]
* @param[out] pulDecodedLen Decoded Buffer Length
*
* @retval SCEP_MSG_S* Poitner to decoded SCEP_MSG_S [SCEP_MSG_S*|N/A]
* @retval SCEP_MSG_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Decodes the given encoded SCEPMsg */
PSELINKDLL SCEP_MSG_S*
SCEP_decodeSCEPMsg(SEC_UCHAR* pcEncodedValue,
                   SEC_UINT32 ulLength,
                   SEC_UINT32* pulDecodedLen);



/**
* @defgroup SCEP_decodeCertResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CERTRESP_S* SCEP_decodeCertResp(SEC_UCHAR* pcEncodedValue, SEC_UINT32 ulLength,
* SEC_UINT32* pulDecodedLen);
* @endcode
*
* @par Purpose
* To decode the SCEP_CERTRESP_S structure from the given encoded SCEP certificate response buffer.
* @par Description
* This function decodes the given encoded CertResp structure.
*
* @param[in] pcEncodedValue Pointer to the encoded buffer [N/A]
* @param[in] ulLength Length of the encoded buffer [N/A]
* @param[out] pulDecodedLen Decoded Buffer Length [N/A]
*
* @retval SCEP_CERTRESP_S* Pointer to decoded SCEP_CERTRESP_S [SCEP_CERTRESP_S*|N/A]
* @retval SCEP_CERTRESP_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Decodes the given encoded CertResp */
PSELINKDLL SCEP_CERTRESP_S*
SCEP_decodeCertResp(SEC_UCHAR* pcEncodedValue,
                    SEC_UINT32 ulLength,
                    SEC_UINT32* pulDecodedLen);



/**
* @defgroup SCEP_decodeCRLResp
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CRLRESP_S* SCEP_decodeCRLResp(SEC_UCHAR* pcEncodedValue, SEC_UINT32 ulLength,
* SEC_UINT32* pulDecodedLen);
* @endcode
*
* @par Purpose
* To generate the decoded SCEP_CRLRESP_S structure from the encoded CRL response buffer.
* @par Description
* This function decodes the given encoded CRLResp structure.
*
* @param[in] pcEncodedValue Pointer to the encoded buffer [N/A]
* @param[in] ulLength Length of the encoded buffer [N/A]
* @param[out] pulDecodedLen Decoded Buffer Length [N/A]
*
* @retval SCEP_CRLRESP_S* Pointer to decoded SCEP_CRLRESP_S [SCEP_CRLRESP_S*|N/A]
* @retval SCEP_CRLRESP_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Decodes the given encoded CRLResp */
PSELINKDLL SCEP_CRLRESP_S*
SCEP_decodeCRLResp(SEC_UCHAR* pcEncodedValue,
                   SEC_UINT32 ulLength,
                   SEC_UINT32* pulDecodedLen);



/**
* @defgroup SCEP_decodeCertQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CERTQUERY_S* SCEP_decodeCertQuery(SEC_UCHAR* pcEncodedValue, SEC_UINT32 ulLength,
* SEC_UINT32* pulDecodedLen);
* @endcode
*
* @par Purpose
* To generate the decoded SCEP_CERTQUERY_S structure from the given encoded Certificate query buffer.
* @par Description
* This function decodes the given encoded CertQuery structure.
*
* @param[in] pcEncodedValue Pointer to the encoded buffer [N/A]
* @param[in] ulLength Length of the encoded buffer [N/A]
* @param[out] pulDecodedLen Decoded Buffer Length [N/A]
*
* @retval SCEP_CERTQUERY_S* Poitner to decoded SCEP_CERTQUERY_S [SCEP_CERTQUERY_S*|N/A]
* @retval SCEP_CERTQUERY_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Decodes the given encoded CertQuery */
PSELINKDLL SCEP_CERTQUERY_S*
SCEP_decodeCertQuery(SEC_UCHAR* pcEncodedValue,
                     SEC_UINT32 ulLength,
                     SEC_UINT32* pulDecodedLen);



/**
* @defgroup SCEP_decodeHTTPContent
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_HTTPCONTENT_S* SCEP_decodeHTTPContent(SEC_UCHAR* pcEncodedValue, SEC_UINT32 ulLength,
* SEC_UINT32* pulDecodedLen);
* @endcode
*
* @par Purpose
* To generate the decoded SCEP_HTTPCONTENT_S structure from the given encoded HTTP content buffer.
* @par Description
* This function decodes the given encoded HTTPContent structure.
*
* @param[in] pcEncodedValue Pointer to the encoded buffer [N/A]
* @param[in] ulLength Length of the encoded buffer [N/A]
* @param[out] pulDecodedLen Decoded Buffer Length [N/A]
*
* @retval SCEP_HTTPCONTENT_S* Poitner to SCEP_HTTPCONTENT_S [SCEP_HTTPCONTENT_S*|N/A]
* @retval SCEP_HTTPCONTENT_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Decodes the given encoded HTTPContent */
PSELINKDLL SCEP_HTTPCONTENT_S*
SCEP_decodeHTTPContent(SEC_UCHAR* pcEncodedValue,
                       SEC_UINT32 ulLength,
                       SEC_UINT32* pulDecodedLen);



/**
* @defgroup SCEP_decodeCertPollReq
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CERTPOLLREQ_S* SCEP_decodeCertPollReq(SEC_UCHAR* pcEncodedValue, SEC_UINT32 ulLength,
* SEC_UINT32* pulDecodedLen);
* @endcode
*
* @par Purpose
* To generate the decoded SCEP_CERTPOLLREQ_S structure from the given encoded Certificate poll request buffer.
* @par Description
* This function decodes the given encoded CertPollReq structure.
*
* @param[in] pcEncodedValue Pointer to the encoded buffer [N/A]
* @param[in] ulLength Length of the encoded buffer [N/A]
* @param[out] pulDecodedLen Decoded Buffer Length [N/A]
*
* @retval SCEP_CERTPOLLREQ_S* Poitner to SCEP_CERTPOLLREQ_S [SCEP_CERTPOLLREQ_S*|N/A]
* @retval SCEP_CERTPOLLREQ_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


/* Decodes the given encoded CertPollReq */
PSELINKDLL SCEP_CERTPOLLREQ_S*
SCEP_decodeCertPollReq(SEC_UCHAR* pcEncodedValue,
                       SEC_UINT32 ulLength,
                       SEC_UINT32* pulDecodedLen);



/**
* @defgroup SCEP_decodeCRLQuery
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CRLQUERY_S* SCEP_decodeCRLQuery(SEC_UCHAR* pcEncodedValue, SEC_UINT32 ulLength,
* SEC_UINT32* pulDecodedLen);
* @endcode
*
* @par Purpose
* To generate the decoded SCEP_CRLQUERY_S structure from the given encoded CRL query buffer.
* @par Description
* This function decodes the given encoded CRLQuery structure.
*
* @param[in] pcEncodedValue Pointer to the encoded buffer [N/A]
* @param[in] ulLength Length of the encoded buffer [N/A]
* @param[out] pulDecodedLen Decoded Buffer Length [N/A]
*
* @retval SCEP_CRLQUERY_S* Poitner to decoded SCEP_CRLQUERY_S [SCEP_CRLQUERY_S*|N/A]
* @retval SCEP_CRLQUERY_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/* Decodes the given encoded CRLQuery */
PSELINKDLL SCEP_CRLQUERY_S*
SCEP_decodeCRLQuery(SEC_UCHAR* pcEncodedValue,
                    SEC_UINT32 ulLength,
                    SEC_UINT32* pulDecodedLen);


/**
* @defgroup SCEP_getCRLDistPoint
* @ingroup scepFunctions
* @par Prototype
* @code
* CRLDistributionPoints* SCEP_getCRLDistPoint(SCEP_CRLQUERY_S* pstCRLQuery);
* @endcode
*
* @par Purpose
* To fetch the CRL Distribution Point from the given CRL query structure.
* @par Description
* This function gets the CRL Distribution Points from CRL Query Structure.
*
* @param[in] pstCRLQuery CRL Query Pointer [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRLDistributionPoints* CRL Distribution Points [CRLDistributionPoints*|N/A]
* @retval CRLDistributionPoints* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

/*Gets the CRL distribution point from the CRL Query Structure*/
PSELINKDLL CRLDistributionPoints*
SCEP_getCRLDistPoint(SCEP_CRLQUERY_S* pstCRLQuery);



/**
* @defgroup SEC_dupIssuerAndSerialNumber_S
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CERTQUERY_S* SEC_dupIssuerAndSerialNumber_S(SCEP_CERTQUERY_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a SCEP_CERTQUERY_S structure.
* @par Description
* This function creates a duplicate copy of a Certificate Query
* request structure (same as SEC_ISSUER_AND_SERIAL_S structure).
*
* @param[in] pSrc Certificate query request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CERTQUERY_S* Certificate query request [SCEP_CERTQUERY_S*|N/A]
* @retval SCEP_CERTQUERY_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SCEP_CERTQUERY_S* SEC_dupIssuerAndSerialNumber_S(SCEP_CERTQUERY_S* pSrc);


/**
* @defgroup SEC_dupCertPollReq_S
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CERTPOLLREQ_S* SEC_dupCertPollReq_S(SCEP_CERTPOLLREQ_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a SCEP_CERTPOLLREQ_S structure.
* @par Description
* This function creates a duplicate copy of a Certificate Poll request structure.
*
* @param[in] pSrc Certificate poll request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CERTPOLLREQ_S* Certificate poll request [SCEP_CERTPOLLREQ_S*|N/A]
* @retval SCEP_CERTPOLLREQ_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL SCEP_CERTPOLLREQ_S* SEC_dupCertPollReq_S(SCEP_CERTPOLLREQ_S* pSrc);


/**
* @defgroup SEC_dupCRLQuery_S
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CRLQUERY_S* SEC_dupCRLQuery_S(SCEP_CRLQUERY_S* pSrc);
* @endcode
*
* @par Purpose
* To duplicate a SCEP_CRLQUERY_S structure.
* @par Description
* This function creates a duplicate copy of a CRL Query request structure.
*
* @param[in] pSrc CRL Query request [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CRLQUERY_S* CRL Query request [SCEP_CRLQUERY_S*|N/A]
* @retval SCEP_CRLQUERY_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SCEP_CRLQUERY_S* SEC_dupCRLQuery_S(SCEP_CRLQUERY_S* pSrc);


/**
* @defgroup SCEP_createCRLQuery_Ex
* @ingroup scepFunctions
* @par Prototype
* @code
* SCEP_CRLQUERY_EX_S*  SCEP_createCRLQuery_Ex(
*                                                          SEC_NAME_S* pstCAName,
*                                                          SEC_BIGINT_S* pstSerial);
* @endcode
*
* @par Purpose
* To create an SCEP CRL query message.
*
* @par Description
* This function Creates and returns an SCEP GetCRL message. The query of the CRL can only be initialized by the requester.
* The CRL may be retrieved by a simple HTTP GET. If the CA supports CRL Distribution Points [RFC5280] then the CRL MUST
* be retrieved via the mechanism specified in the CDP.
*
* @param[in] pstCAName CA's Name [N/A]
* @param[in] pstSerial serial number from a certificate within the scope of the CRL to
   be retrieved (e.g. from a certificate to be validated). [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SCEP_CRLQUERY_EX_S* Created CRL Query [SCEP_CRLQUERY_EX_S*|N/A]
* @retval SCEP_CRLQUERY_EX_S* In case of failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
* This API will create the CRL query according to the draft-nourse-scep-20
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL
SCEP_CRLQUERY_EX_S*  SCEP_createCRLQuery_Ex(
                                                          SEC_NAME_S* pstCAName,
                                                          SEC_BIGINT_S* pstSerial);

/**
* @defgroup SCEP_freeCrlQuery_EX
* @ingroup scepFunctions
* @par Prototype
* @code
* SEC_VOID SCEP_freeCrlQuery_EX(SCEP_CRLQUERY_EX_S* pstCrlQuery);
* @endcode
*
* @par Purpose
* To free the given SCEP_CRLQUERY_EX_S structure.
* @par Description
* This function is used to free the memory allocated to the given CRLQuery ex Structure.
*
* @param[in] pCRLQuery Pointer to the CRL Query [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID  This does not return any value [N/A|N/A]
*
* @par Dependency
* scep.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL 
SEC_VOID SCEP_freeCrlQuery_EX(SCEP_CRLQUERY_EX_S* pstCrlQuery);


#ifdef __cplusplus
	}
#endif

#endif /* _IPSI_SCEP_H_ */
#endif // __SEC_NO_SCEP__

