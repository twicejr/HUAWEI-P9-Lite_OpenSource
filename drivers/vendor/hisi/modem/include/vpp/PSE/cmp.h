/*

                Copyright 2005, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                             cmp.h

  Project Code: SeCert
   Module Name: CMP
  Date Created: 2005-07-15
        Author: Sindhu
   @brief This header file declares all the structures and methods that
                 are required to create CMP standard defined Request and
                 Response Messages

*/
#include "ipsi_pse_build_conf.h"

#ifndef _SSL_

#ifndef _IPSI_CMP_H
#define _IPSI_CMP_H

/* SeCert Headers */
#include "crmf.h"
#include "sec_crypto.h"
#include "sec_list.h"
#include "sec_error.h"
#include "pkcs10.h"
#include "x509_basictypes.h"
#include "asn-types.h"
#include "x509v3_extn.h"

#ifdef __IPSI_CMPV2__

typedef struct stSEC_List CMPV2_CERT_CONF_MSG_S;

typedef struct stSEC_List CMPV2_POLL_REQ_MSG_S;

typedef struct stSEC_List CMPV2_POLL_REP_MSG_S;

#endif /*__IPSI_CMPV2__*/

#ifdef  __cplusplus
extern "C"{
#endif

/* Supported CMP Version*/
#define CMP_VERSION_TYPE 2


/* FAILURE REASONS */
#define CMP_REASON_BADALG            0    /* Unrecognized or Unsupported Algorithm Identifier*/

#define CMP_REASON_BADMESSAGECHECK          1    /* Integrity Check Failed*/

#define CMP_REASON_BADREQUEST              2    /* Transaction not Permitted or Supported*/

#define CMP_REASON_BADTIME                  3    /* MessageTime not sufficiently close to the system time*/

#define CMP_REASON_BADCERTID              4    /* No Certificate found matching the provided criteria*/

#define CMP_REASON_BADDATAFORMAT          5    /* Data submitted with the Wrong Format*/

#define CMP_REASON_WRONGAUTHORITY          6    /* Authority indicated in the request different from the response token*/

#define CMP_REASON_INCORRECTDATA          7    /* Requester's Data Incorrect*/

#define CMP_REASON_MISSING_TIMESTAMP      8    /* Missing Time Stamp*/

#define CMP_REASON_BADPOP                  9    /* Proof of Possession Failure*/

#define CMP_REASON_CERTREVOKED            10

#define CMP_REASON_CERTCONFIRMED          11

#define CMP_REASON_WRONG_INTEGRITY        12

#define CMP_REASON_BAD_RECIPIENT_NONCE    13

#define CMP_REASON_TIME_NOT_AVAILABLE     14

#define CMP_REASON_UNACCEPTED_POLICY      15

#define CMP_REASON_UNACCEPTED_EXTENSION   16

#define CMP_REASON_ADD_INFO_NOT_AVAILABLE 17

#define CMP_REASON_BAD_SENDER_NONCE       18

#define CMP_REASON_BAD_CERTTEMPLATE       19

#define CMP_REASON_SIGNER_NOT_TRUSTED     20

#define CMP_REASON_TRANSACTION_ID_IN_USE  21

#define CMP_REASON_UNSUPPORTED_VERSION    22

#define CMP_REASON_NOT_AUTHORIZED         23

#define CMP_REASON_SYSTEM_UNAVAIL         24

#define CMP_REASON_SYSTEM_FAILURE         25

#define CMP_REASON_DUPLICATE_CERT_REQ     26




/** @defgroup cmp
* This section contains the cmp Enums, Structures, and Functions.
*/

/** @defgroup cmpEnums
* @ingroup cmp
* This section contains the cmp Enums.
*/

/** @defgroup cmpStructures
* @ingroup cmp
* This section contains the cmp Structures.
*/

/** @defgroup cmpFunctions
* @ingroup cmp
* This section contains the cmp Functions.
*/



/* Status for creating the PKIStatus structure of the Certificate Response*/
/**
* @defgroup CERT_RESP_STATUS_E
* @ingroup cmpEnums
* @par Prototype
* @code
* typedef enum enPKIStatus
* {
* CMP_STATUS_GRANTED                = 0,
* CMP_STATUS_GRANTEDWITHMODS        = 1,
* CMP_STATUS_REJECTION              = 2,
* CMP_STATUS_WAITING                = 3,
* CMP_STATUS_REVOCATIONWARNING      = 4,
* CMP_STATUS_REVOCATIONNOTIFICATION = 5,
* CMP_STATUS_KEYUPDATEWARNING       = 6,
* CMP_STATUS_INVALID                = 7
* }CERT_RESP_STATUS_E;
* @endcode
*
* @datastruct CMP_STATUS_GRANTED=0 Status Granted
* @datastruct CMP_STATUS_GRANTEDWITHMODS=1 Granted with Mods
* @datastruct CMP_STATUS_REJECTION=2 Status as more information required
* @datastruct CMP_STATUS_WAITING=3 Status as request body part has not yet been processed
* @datastruct CMP_STATUS_REVOCATIONWARNING=4 Status as warning that a revocation is imminent
* @datastruct CMP_STATUS_REVOCATIONNOTIFICATION=5 Status as notification that a revocation has occurred
* @datastruct CMP_STATUS_KEYUPDATEWARNING=6 Status as update already done
* @datastruct CMP_STATUS_INVALID=7 Invalid Status
*/
typedef enum enPKIStatus
{
    CMP_STATUS_GRANTED                = 0,        /* Status Granted*/
    CMP_STATUS_GRANTEDWITHMODS        = 1,        /* Granted with Mods*/
    CMP_STATUS_REJECTION            = 2,        /* Status as more information required*/
    CMP_STATUS_WAITING                = 3,        /* Status as request body part has not yet been processed*/
    CMP_STATUS_REVOCATIONWARNING    = 4,        /* Status as warning that a revocation is imminent*/
    CMP_STATUS_REVOCATIONNOTIFICATION = 5,        /* Status as notification that a revocation has occurred*/
    CMP_STATUS_KEYUPDATEWARNING        = 6,        /* Status as update already done*/
    CMP_STATUS_INVALID                = 7            /* Invalid Status*/
}CERT_RESP_STATUS_E;

/* Choice used in CMP_CERTTYPE_S structure*/
/**
* @defgroup CMP_CERTTYPE_E
* @ingroup cmpEnums
* @par Prototype
* @code
* typedef enum enCMP_CertType
* {
* CMP_CERTTYPE_X509         = 0,
* CMP_CERTTYPE_ENCRYPTED    = 1,
* CMP_CERTTYPE_INVALID      = 2
* } CMP_CERTTYPE_E;
* @endcode
*
* @datastruct CMP_CERTTYPE_X509=0 Choice of Certicate in CMP_CERTTYPE_S
* @datastruct CMP_CERTTYPE_ENCRYPTED=1 Choice of Encrypted Certificate in CMP_CERTTYPE_S
* @datastruct CMP_CERTTYPE_INVALID=2 Invalid Choice
*/
typedef enum enCMP_CertType
{
    CMP_CERTTYPE_X509        = 0,    /* Choice of Certicate in CMP_CERTTYPE_S */
    CMP_CERTTYPE_ENCRYPTED    = 1,    /* Choice of Encrypted Certificate in CMP_CERTTYPE_S*/
    CMP_CERTTYPE_INVALID    = 2        /* Invalid Choice*/
} CMP_CERTTYPE_E;

/**
* @defgroup CMP_PKIBODYTYPE_E
* @ingroup cmpEnums
* @par Prototype
* @code
* typedef enum enCMP_PKIBodyChoiceId
* {
* CMP_BODY_TYPE_IR      = 0,
* CMP_BODY_TYPE_IP      = 1,
* CMP_BODY_TYPE_CR      = 2,
* CMP_BODY_TYPE_CP      = 3,
* CMP_BODY_TYPE_P10CR   = 4,
* CMP_BODY_TYPE_POPDECC = 5,
* CMP_BODY_TYPE_POPDECR = 6,
* CMP_BODY_TYPE_KUR     = 7,
* CMP_BODY_TYPE_KUP     = 8,
* CMP_BODY_TYPE_KRR     = 9,
* CMP_BODY_TYPE_KRP     = 10,
* CMP_BODY_TYPE_RR      = 11,
* CMP_BODY_TYPE_RP      = 12,
* CMP_BODY_TYPE_CCR     = 13,
* CMP_BODY_TYPE_CCP     = 14,
* CMP_BODY_TYPE_CKUANN  = 15,
* CMP_BODY_TYPE_CANN    = 16,
* CMP_BODY_TYPE_RANN    = 17,
* CMP_BODY_TYPE_CRLANN  = 18,
* CMP_BODY_TYPE_CONF    = 19,
* CMP_BODY_TYPE_NESTED  = 20,
* CMP_BODY_TYPE_GENM    = 21,
* CMP_BODY_TYPE_GENP    = 22,
* CMP_BODY_TYPE_ERROR   = 23,
* CMP_BODY_TYPE_INVALID = 24
* } CMP_PKIBODYTYPE_E;
* @endcode
*
* @datastruct CMP_BODY_TYPE_IR=0 Initialization Request
* @datastruct CMP_BODY_TYPE_IP=1 Initialization Response
* @datastruct CMP_BODY_TYPE_CR=2 Certification Request
* @datastruct CMP_BODY_TYPE_CP=3 Certification Response
* @datastruct CMP_BODY_TYPE_P10CR=4 PKCS #10 Cert.Req
* @datastruct CMP_BODY_TYPE_POPDECC=5 POP Challenge
* @datastruct CMP_BODY_TYPE_POPDECR=6 POP Response
* @datastruct CMP_BODY_TYPE_KUR=7 Key Update Request
* @datastruct CMP_BODY_TYPE_KUP=8 Key Update Response
* @datastruct CMP_BODY_TYPE_KRR=9 Key Recovery Request
* @datastruct CMP_BODY_TYPE_KRP=10 Key Recovery Response
* @datastruct CMP_BODY_TYPE_RR=11 Revocation Request
* @datastruct CMP_BODY_TYPE_RP=12 Revocation Response
* @datastruct CMP_BODY_TYPE_CCR=13 Cross-Certificate Request
* @datastruct CMP_BODY_TYPE_CCP=14 Cross-Certificate Response
* @datastruct CMP_BODY_TYPE_CKUANN=15 CA Key Update Announcement
* @datastruct CMP_BODY_TYPE_CANN=16 Certificate Announcement
* @datastruct CMP_BODY_TYPE_RANN=17 Revocation Announcement
* @datastruct CMP_BODY_TYPE_CRLANN=18 CRL Announcement
* @datastruct CMP_BODY_TYPE_CONF=19 Confirmation
* @datastruct CMP_BODY_TYPE_NESTED=20 Nested Message
* @datastruct CMP_BODY_TYPE_GENM=21 General Message
* @datastruct CMP_BODY_TYPE_GENP=22 General Response
* @datastruct CMP_BODY_TYPE_ERROR=23 Error Message
* @datastruct CMP_BODY_TYPE_INVALID=24 Invalid Body Type
*/
/* Choice for creating a PKI Message Body*/

typedef enum enCMP_PKIBodyChoiceId
{
        CMP_BODY_TYPE_IR        = 0,        /* Initialization Request*/
        CMP_BODY_TYPE_IP        = 1,        /* Initialization Response*/
        CMP_BODY_TYPE_CR        = 2,        /* Certification Request*/
        CMP_BODY_TYPE_CP        = 3,        /* Certification Response*/
        CMP_BODY_TYPE_P10CR        = 4,        /* PKCS #10 Cert.Req*/
        CMP_BODY_TYPE_POPDECC    = 5,        /* POP Challenge*/
        CMP_BODY_TYPE_POPDECR    = 6,        /* POP Response*/
        CMP_BODY_TYPE_KUR        = 7,        /* Key Update Request*/
        CMP_BODY_TYPE_KUP        = 8,        /* Key Update Response*/
        CMP_BODY_TYPE_KRR        = 9,        /* Key Recovery Request*/
        CMP_BODY_TYPE_KRP        = 10,        /* Key Recovery Response*/
        CMP_BODY_TYPE_RR        = 11,        /* Revocation Request*/
        CMP_BODY_TYPE_RP        = 12,        /* Revocation Response*/
        CMP_BODY_TYPE_CCR        = 13,        /* Cross-Certificate Request*/
        CMP_BODY_TYPE_CCP        = 14,        /* Cross-Certificate Response*/
        CMP_BODY_TYPE_CKUANN    = 15,        /* CA Key Update Announcement*/
        CMP_BODY_TYPE_CANN        = 16,        /* Certificate Announcement*/
        CMP_BODY_TYPE_RANN        = 17,        /* Revocation Announcement*/
        CMP_BODY_TYPE_CRLANN    = 18,        /* CRL Announcement*/
        CMP_BODY_TYPE_CONF        = 19,        /* Confirmation*/
        CMP_BODY_TYPE_NESTED    = 20,        /* Nested Message*/
        CMP_BODY_TYPE_GENM        = 21,        /* General Message*/
        CMP_BODY_TYPE_GENP        = 22,        /* General Response*/
        CMP_BODY_TYPE_ERROR        = 23,        /* Error Message*/
#ifdef __IPSI_CMPV2__
        CMP_BODY_TYPE_CERT_CONFIRM = 24,  /* Certificate Confirmation */
        CMP_BODY_TYPE_POLLREQ        = 25,   /* Poll request*/
        CMP_BODY_TYPE_POLLREP        = 26,   /* Poll resonse */
        CMP_BODY_TYPE_INVALID    = 27        /* Invalid Body Type*/
#else
       CMP_BODY_TYPE_INVALID    = 24   /* Invalid */
#endif

} CMP_PKIBODYTYPE_E;

/* In cases where an end entity sends a protected PKI message to an RA,
    the RA may forward that message to a CA, attaching its own protection,
    the entire message sent by the end entity is nested within a new PKIMessage
    by the RA using CMP_NESTEDMSGCNT_S*/

typedef struct stCMP_PKIMessage CMP_NESTEDMSGCNT_S; /* Nested PKI Message*/


/* This structure is typically used in an environment in which
    RA verifies POP and then makes a certification request to the CA on behalf
    of the end-entity*/
/**
* @defgroup CMP_CHALLENGE_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_Challenge
* {
* SEC_ALG_IDENTIFIER_S* pstOwf;
* SEC_AsnOcts_S stWitness;
* SEC_AsnOcts_S stChallenge;
* } CMP_CHALLENGE_S;
* @endcode
*
* @datastruct pstOwf Hash Algorithm/One-Way function, (Optional).
* @datastruct stWitness Contains the result of applying the hash to a randomly-generated INTEGER.
* @datastruct stChallenge Contains the encryption under the Public Key.
*/
typedef struct stCMP_Challenge
{
    SEC_ALG_IDENTIFIER_S* pstOwf;    /* Hash Algorithm/One-Way function, (Optional)*/
    SEC_AsnOcts_S stWitness;        /* Contains the result of applying the hash to a randomly-generated INTEGER*/
    SEC_AsnOcts_S stChallenge;        /* Contains the encryption under the Public Key*/
} CMP_CHALLENGE_S;





/* This structure is used in the CMP_KEYPAIR_S of the Certificate Response
    The purpose of it is to allow a CA to return the value of a certificate*/
/**
* @defgroup CMP_CERTTYPE_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_CertType
* {
* CMP_CERTTYPE_E enType;
* union
* {
* X509_CERT_S* pstCertificate;
* CRMF_ENCRYPTED_VALUE_S* pstEncryptedCert;
* }unCertType;
* }CMP_CERTTYPE_S;
* @endcode
*
* @datastruct enType Choice to specify Certificate type.
* @datastruct pstCertificate Certificate.
* @datastruct pstEncryptedCert Encrypted Certificate Value
*/
typedef struct stCMP_CertType
{
    CMP_CERTTYPE_E enType;                            /*Choice to specify Certificate type*/
    union
    {
        X509_CERT_S* pstCertificate;                 /*Certificate*/
        CRMF_ENCRYPTED_VALUE_S* pstEncryptedCert;    /*Encrypted Certificate Value*/
    }unCertType;
}CMP_CERTTYPE_S;


/* When requesting revocation of a certificate (or several certificates),
    the CMP_REVDETAILS_S structure is used*/
/**
* @defgroup CMP_REVDETAILS_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_RevDetails
* {
* CRMF_CERT_TEMPLATE_S* pstCertDetails;
* ReasonFlags stRevocationReason;
* SEC_GeneralizedTime_S badSinceDate;
* Extensions* pCrlEntryDetails;
* } CMP_REVDETAILS_S;
* @endcode
*
* @datastruct pstCertDetails Certificate Template
* @datastruct stRevocationReason Reason Flags (Optional)
* @datastruct badSinceDate Generalized Time (Optional)
* @datastruct pCrlEntryDetails Extensions (Optional)
*/
typedef struct stCMP_RevDetails
{
    CRMF_CERT_TEMPLATE_S* pstCertDetails;    /* Certificate Template*/
    ReasonFlags stRevocationReason;            /* Reason Flags (Optional)*/
    SEC_GeneralizedTime_S badSinceDate;        /* Generalized Time (Optional)*/
    Extensions* pCrlEntryDetails;            /* Extensions (Optional)*/
} CMP_REVDETAILS_S;


/* Whenever the CA changes its key pair, it publishes the new
    certificates through this Announcement*/
/**
* @defgroup CMP_CAKEYUPDATEANN_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_CAKeyUpdAnnouncement
* {
*
* X509_CERT_S* pstOldWithNew;
* X509_CERT_S* pstNewWithOld;
* X509_CERT_S* pstNewWithNew;
* } CMP_CAKEYUPDATEANN_S;
* @endcode
*
* @datastruct pstOldWithNew Certificate containing the old CA public key signed with the new private key.
* @datastruct pstNewWithOld Certificate containing the new CA public key signed with the old private key.
* @datastruct pstNewWithNew Certificate containing the new CA public key signed with the new private key.
*/
typedef struct stCMP_CAKeyUpdAnnouncement
{

    X509_CERT_S* pstOldWithNew; /* Certificate containing the old CA public key
                                    signed with the new private key*/
    X509_CERT_S* pstNewWithOld; /* Certificate containing the new CA public key
                                    signed with the old private key*/
    X509_CERT_S* pstNewWithNew; /* Certificate containing the new CA public key
                                    signed with the new private key*/
} CMP_CAKEYUPDATEANN_S;


/* Used for creating PKI General Message or General Response or GeneralInfo in
    PKI Header for sending machine-processable additional data to the recipient*/
/**
* @defgroup CMP_INFOTYPEVAL_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_InfoTypeAndValue
* {
* SEC_AsnOid_S stInfoType;
* SEC_AsnAny_S stInfoValue;
* } CMP_INFOTYPEVAL_S;
* @endcode
*
* @datastruct stInfoType Object Identifier
* @datastruct stInfoValue InfoValue can be a Certificate,Algorithm Identifier, list of Algorithm Identifiers,
* CAKeyUpdateInfo or CRL (Optional).
*/
typedef struct stCMP_InfoTypeAndValue
{
    SEC_AsnOid_S stInfoType;    /* Object Identifier*/
    SEC_AsnAny_S stInfoValue;    /* InfoValue can be a Certificate,Algorithm Identifier.
                                        list of Algorithm Identifiers,
                                        CAKeyUpdateInfo or CRL (Optional)*/

} CMP_INFOTYPEVAL_S;


/* This structure contains some header information for addressing and
   transaction identification*/
/**
* @defgroup CMP_PKIHDR_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_PKIHeader
* {
* SEC_UINT32 ulVersion;
* SEC_GEN_NAME_S* pstSender;
* SEC_GEN_NAME_S* pstRecipient;
* SEC_GeneralizedTime_S stMessageTime;
* SEC_ALG_IDENTIFIER_S* pstProtectionAlg;
* SEC_AsnOcts_S stSenderKID;
* SEC_AsnOcts_S stRecipKID;
* SEC_AsnOcts_S stTransactionID;
* SEC_AsnOcts_S stSenderNonce;
* SEC_AsnOcts_S stRecipNonce;
* SEC_List_S* pFreeText;
* SEC_List_S* pGeneralInfo;
* } CMP_PKIHDR_S;
* @endcode
*
* @datastruct ulVersion Supported Version.
* @datastruct pstSender Identifies the Sender.
* @datastruct pstRecipient Identifies the intended recipient.
* @datastruct stMessageTime Time at which the sender created the message (Optional).
* @datastruct pstProtectionAlg Algorithm used for calculation of protection bits (Optional).
* @datastruct stSenderKID To identify specific keys used for protection (Optional).
* @datastruct stRecipKID To identify specific keys used for protection (Optional).
* @datastruct stTransactionID Identifies the Transaction.
* @datastruct stSenderNonce SenderNonce is inserted by the creator of this message and provides replay
* protection(Optional).
* @datastruct stRecipNonce Nonce previously inserted in a related message by the intended recipient of
* this message (Optional).
* @datastruct pFreeText This field may be used to send a human-readable message to the recipient (Optional).
* @datastruct pGeneralInfo List of CMP_INFOTYPEVAL_S (Optional).
*/
typedef struct stCMP_PKIHeader
{
    SEC_UINT32 ulVersion;                    /* Supported Version*/
    SEC_GEN_NAME_S* pstSender;                /* Identifies the Sender*/
    SEC_GEN_NAME_S* pstRecipient;            /* Identifies the intended recipient*/
    SEC_GeneralizedTime_S stMessageTime;    /* Time at which the sender created the message (Optional)*/
    SEC_ALG_IDENTIFIER_S* pstProtectionAlg; /* Algorithm used for calculation of protection bits (Optional)*/
    SEC_AsnOcts_S stSenderKID;                /* To identify specific keys used for protection (Optional)*/
    SEC_AsnOcts_S stRecipKID;                /* To identify specific keys used for protection (Optional)*/
    SEC_AsnOcts_S stTransactionID;            /* Identifies the Transaction*/
    SEC_AsnOcts_S stSenderNonce;            /* SenderNonce is inserted by the creator of this message and
                                                     provides replay protection(Optional)*/
    SEC_AsnOcts_S stRecipNonce;                /* Nonce previously inserted in a related message
                                                     by the intended recipient of this message (Optional)*/
    SEC_List_S* pFreeText;                    /* This field may be used to send a human-readable
                                                     message to the recipient (Optional)*/
    SEC_List_S* pGeneralInfo;                /* List of CMP_INFOTYPEVAL_S (Optional)*/
} CMP_PKIHDR_S;


/* Used in creating the Certificate Response*/
/**
* @defgroup CMP_PKISTATUS_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_PKIStatus
* {
* SEC_UINT32 ulStatus;
* SEC_List_S* pStatusString;
* SEC_AsnBits_S failInfo;
* } CMP_PKISTATUS_S;
* @endcode
*
* @datastruct ulStatus One of the values of the enum CERT_RESP_STATUS_E.
* @datastruct pStatusString StatusString containing the Error Details (Optional).
* @datastruct failInfo Failure Information (Optional).
*/
typedef struct stCMP_PKIStatus
{
    SEC_UINT32 ulStatus;                    /* One of the values of the enum CERT_RESP_STATUS_E*/
    SEC_List_S* pStatusString;                /* StatusString containing the Error Details (Optional)*/
    SEC_AsnBits_S failInfo;                    /* Failure Information (Optional)*/
}CMP_PKISTATUS_S;


/* This structure can be added to Certificate Response or Key Recovery Response
    only when the Response Status is not Rejected*/
/**
* @defgroup CMP_KEYPAIR_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_KeyPair
* {
* CMP_CERTTYPE_S* pstCert;
* CRMF_ENCRYPTED_VALUE_S* pstPrivateKey;
* CRMF_PUBLICATION_INFO_S* pstPublicationInfo;
* } CMP_KEYPAIR_S;
* @endcode
*
* @datastruct pstCert Certificate or Encrypted Certificate.
* @datastruct pstPrivateKey Encrypted PrivateKey Value  (Optional).
* @datastruct pstPublicationInfo PKI Publication Information (Optional).
*/
typedef struct stCMP_KeyPair
{
    CMP_CERTTYPE_S* pstCert;                    /* Certificate or Encrypted Certificate*/
    CRMF_ENCRYPTED_VALUE_S* pstPrivateKey;        /* Encrypted PrivateKey Value  (Optional)*/
    CRMF_PUBLICATION_INFO_S* pstPublicationInfo;/* PKI Publication Information (Optional)*/
} CMP_KEYPAIR_S;


/* When a CA has revoked, or is about to revoke, a particular
   certificate, it may issue the Revocation announcement*/
/**
* @defgroup CMP_REVOKEANN_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_RevokeAnn
* {
* SEC_UINT32 ulStatus;
* CRMF_CERT_ID_S* pstCertId;
* SEC_GeneralizedTime_S willBeRevokedAt;
* SEC_GeneralizedTime_S badSinceDate;
* Extensions* pCRLDetails;
* } CMP_REVOKEANN_S;
* @endcode
*
* @datastruct ulStatus Refer CERT_RESP_STATUS_E
* @datastruct pstCertId CertID
* @datastruct willBeRevokedAt Time at which a new entry will be added to the relevant CRLs.
* @datastruct badSinceDate Time at which the Certificate was revoked.
* @datastruct pCRLDetails List of SEC_EXTN_S including extra CRL Details like CRL Number, Reason or Location (Optional).
*/
typedef struct stCMP_RevokeAnn
{
    SEC_UINT32 ulStatus;                        /* Refer CERT_RESP_STATUS_E*/
    CRMF_CERT_ID_S* pstCertId;                    /* CertID*/
    SEC_GeneralizedTime_S willBeRevokedAt;        /* Time at which a new entry will
                                                     be added to the relevant CRLs*/
    SEC_GeneralizedTime_S badSinceDate;            /* Time at which the Certificate
                                                     was revoked*/
    Extensions* pCRLDetails;                    /* List of SEC_EXTN_S including extra CRL Details
                                                     like CRL Number, Reason or Location (Optional)*/
} CMP_REVOKEANN_S;


/* If the modified certificate is unacceptable to the requestor, an Error Message
    may be sent (with a PKIStatus of "rejection")*/
/**
* @defgroup CMP_ERRMSG_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_ErrMsg
* {
* CMP_PKISTATUS_S* pstPKIStatusInfo;
* SEC_UINT32* pulErrorCode;
* SEC_List_S* pErrorDetails;
* } CMP_ERRMSG_S;
* @endcode
*
* @datastruct pstPKIStatusInfo PKI Status Information.
* @datastruct pulErrorCode Implementation-specific error codes (Optional).
* @datastruct pErrorDetails Implementation-specific error details (Optional).
*/
typedef struct stCMP_ErrMsg
{
    CMP_PKISTATUS_S* pstPKIStatusInfo;            /* PKI Status Information */
    SEC_UINT32* pulErrorCode;                    /* Implementation-specific error codes (Optional)*/
    SEC_List_S* pErrorDetails;                    /* Implementation-specific error details (Optional)*/
} CMP_ERRMSG_S;


/* This Response is sent as part of Certificate Response Message
with either the failinfo in PKIStatus or the CertifiedKeyPair*/
/**
* @defgroup CMP_CERTRESP_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_CertResp
* {
* SEC_INT32 iCertReqId;
* CMP_PKISTATUS_S* pstStatus;
* CMP_KEYPAIR_S* pstCertifiedKeyPair;
* SEC_AsnOcts_S stRspInfo;
* } CMP_CERTRESP_S;
* @endcode
*
* @datastruct iCertReqId An integer specifying the certificate request ID.
* @datastruct pstStatus PKI Status Information.
* @datastruct pstCertifiedKeyPair Contains Encrypted Certificate and sometimes an encrypted Private Key (Optional).
* @datastruct stRspInfo Analogous to RegInfo in Certificate Request Message (Optional).
*/
typedef struct stCMP_CertResp
{
    SEC_INT32 iCertReqId;                    /* An integer specifying the certificate request ID.*/
    CMP_PKISTATUS_S* pstStatus;                /* PKI Status Information*/
    CMP_KEYPAIR_S* pstCertifiedKeyPair;        /* Contains Encrypted Certificate and
                                                 sometimes an encrypted Private Key (Optional)*/
    SEC_AsnOcts_S stRspInfo;                /* Analogous to RegInfo in Certificate
                                                 Request Message (Optional)*/
} CMP_CERTRESP_S;


/* This structure is sent in response to the Key Recovery Request made to get
    the Key History from the Requestor*/
/**
* @defgroup CMP_KEYRECOVERYRESP_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_KeyRecoveryResp
* {
* CMP_PKISTATUS_S* pstStatus;
* X509_CERT_S* pstNewSigCert;
* SEC_List_S* pCACerts;
* SEC_List_S* pKeyPairHist;
* } CMP_KEYRECOVERYRESP_S;
* @endcode
*
* @datastruct pstStatus Status updated in a CMP_PKISTATUS_S structure
* @datastruct pstNewSigCert Certificate (Optional)
* @datastruct pCACerts List of CA Certificates (Optional)
* @datastruct pKeyPairHist List of CMP_KEYPAIR_S (Optional)
*/
typedef struct stCMP_KeyRecoveryResp
{
    CMP_PKISTATUS_S* pstStatus;                /* Status updated in a CMP_PKISTATUS_S structure */
    X509_CERT_S* pstNewSigCert;                /* Certificate (Optional)*/
    SEC_List_S* pCACerts;                    /* List of CA Certificates (Optional)*/
    SEC_List_S* pKeyPairHist;                /* List of CMP_KEYPAIR_S (Optional)*/
} CMP_KEYRECOVERYRESP_S;


/* It is produced in response to the Revocation Request and it is
    sent to the Requester of the Revocation*/
/**
* @defgroup CMP_REVOKERESP_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_RevokeResp
* {
* SEC_List_S* pStatus;
* SEC_List_S* pRevCerts;
* SEC_List_S* pCRLs;
* } CMP_REVOKERESP_S;
* @endcode
*
* @datastruct pStatus List of CMP_PKISTATUS_S
* @datastruct pRevCerts CertIDs for which revocation was requested (Optional)
* @datastruct pCRLs List of resulting CRLs (Optional)
*/
typedef struct stCMP_RevokeResp
{
    SEC_List_S* pStatus;                    /* List of CMP_PKISTATUS_S*/
    SEC_List_S* pRevCerts;                    /* CertIDs for which revocation was requested (Optional)*/
    SEC_List_S* pCRLs;                        /* List of resulting CRLs (Optional)*/
} CMP_REVOKERESP_S;


/* A CertRepMessage data structure has a status value for each certificate requested,
    and optionally has a CA public key, failure information, a subject certificate,
    and an encrypted private key*/
/**
* @defgroup CMP_CERTRESPMSG_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_CertRespMsg
* {
* SEC_List_S* pCAPubs;
* SEC_List_S* pRespList;
* } CMP_CERTRESPMSG_S;
* @endcode
*
* @datastruct pCAPubs List of CA Certificates (Optional)
* @datastruct pRespList List of CMP_CERTRESP_S
*/
typedef struct stCMP_CertRespMsg
{
    SEC_List_S* pCAPubs;                    /* List of CA Certificates (Optional)*/
    SEC_List_S* pRespList;                    /* List of CMP_CERTRESP_S*/
} CMP_CERTRESPMSG_S;

/* DH Based MAC parameter*/
/**
* @defgroup CMP_DHBMPARAM_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_DHBMParameter
* {
* SEC_ALG_IDENTIFIER_S* pstOwf;
* SEC_ALG_IDENTIFIER_S* pstMAC;
* } CMP_DHBMPARAM_S;
* @endcode
*
* @datastruct pstOwf Hashing Algorithm
* @datastruct pstMAC Digest Algorithm
*/
typedef struct stCMP_DHBMParameter /* Sequence*/
{
    SEC_ALG_IDENTIFIER_S* pstOwf;    /* Hashing Algorithm*/
    SEC_ALG_IDENTIFIER_S* pstMAC;    /* Digest Algorithm*/
} CMP_DHBMPARAM_S;



/* This structure can be used to generate the Challenge using
    the randomly-generated Integer*/
/**
* @defgroup CMP_RAND_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_Rand
* {
* SEC_UINT32 ulInt;
* SEC_GEN_NAME_S* pstSender;
* } CMP_RAND_S;
* @endcode
*
* @datastruct ulInt Randomly-generated Integer
* @datastruct pstSender Sender's Name (as included in PKIHeader)
*/
typedef struct stCMP_Rand /* Sequence*/
{
    SEC_UINT32 ulInt;            /* Randomly-generated Integer*/
    SEC_GEN_NAME_S* pstSender;    /* Sender's Name (as included in PKIHeader)*/
} CMP_RAND_S;




/* One of the following is created as part of PKI Messages
    They can be  used to make Requests and Responses between the EE and CA/RA*/
/**
* @defgroup CMP_PKIBODY_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_PKIBody
* {
* CMP_PKIBODYTYPE_E enBodyType;
* union unCMP_PKIBodyMsg
* {
* CRMF_CertReqMsgList* pstIr;
* CMP_CERTRESPMSG_S* pstIp;
* CRMF_CertReqMsgList* pstCr;
* CMP_CERTRESPMSG_S* pstCp;
* PKCS10_REQ_S* pstP10cr;
* SEC_List_S* pstPopdecc;
* SEC_List_S* pstPopdecr;
* CRMF_CertReqMsgList* pstKur;
* CMP_CERTRESPMSG_S* pstKup;
* CRMF_CertReqMsgList* pstKrr;
* CMP_KEYRECOVERYRESP_S* pstKrp;
* SEC_List_S* pstRr;
* CMP_REVOKERESP_S* pstRp;
* CRMF_CertReqMsgList* pstCcr;
* CMP_CERTRESPMSG_S* pstCcp;
* CMP_CAKEYUPDATEANN_S* pstCkuann;
* X509_CERT_S* pstCann;
* CMP_REVOKEANN_S* pstRann;
* SEC_List_S* pstCrlann;
* SEC_AsnNull pstConf;
* CMP_NESTEDMSGCNT_S* pstNested;
* SEC_List_S* pstGenm;
* SEC_List_S* pstGenp;
* CMP_ERRMSG_S* pstError;
* }unBodyMsg;
* }CMP_PKIBODY_S;
* @endcode
*
* @datastruct enBodyType Choice to specify PKI Body Type
* @datastruct pstIr Initialization Request
* @datastruct pstIp Initialization Response
* @datastruct pstCr Certification Request
* @datastruct pstCp Certification Response
* @datastruct pstP10cr PKCS #10 Certificate Req
* @datastruct pstPopdecc POP Challenge
* @datastruct pstPopdecr POP Response
* @datastruct pstKur Key Update Request
* @datastruct pstKup Key Update Response
* @datastruct pstKrr Key Recovery Request
* @datastruct pstKrp Key Recovery Response
* @datastruct pstRr Revocation Request
* @datastruct pstRp Revocation Response
* @datastruct pstCcr Cross-Certificate Request
* @datastruct pstCcp Cross-Certificate Response
* @datastruct pstCkuann CA Key Update Announcement
* @datastruct pstCann Certificate Announcement
* @datastruct pstRann Revocation Announcement
* @datastruct pstCrlann CRL Announcement
* @datastruct pstConf Confirmation
* @datastruct pstNested Nested Message
* @datastruct pstGenm General Message
* @datastruct pstGenp General Response
* @datastruct pstError Error Message
*/
typedef struct stCMP_PKIBody
{
    CMP_PKIBODYTYPE_E enBodyType;        /* Choice to specify PKI Body Type*/
    union unCMP_PKIBodyMsg
    {
        CRMF_CertReqMsgList* pstIr;        /* Initialization Request*/
        CMP_CERTRESPMSG_S* pstIp;        /* Initialization Response*/
        CRMF_CertReqMsgList* pstCr;        /* Certification Request*/
        CMP_CERTRESPMSG_S* pstCp;        /* Certification Response*/
        PKCS10_REQ_S* pstP10cr;            /* PKCS #10 Certificate Req*/
        SEC_List_S* pstPopdecc;            /* POP Challenge*/
        SEC_List_S* pstPopdecr;            /* POP Response*/
        CRMF_CertReqMsgList* pstKur;    /* Key Update Request*/
        CMP_CERTRESPMSG_S* pstKup;        /* Key Update Response */
        CRMF_CertReqMsgList* pstKrr;    /* Key Recovery Request*/
        CMP_KEYRECOVERYRESP_S* pstKrp;    /* Key Recovery Response*/
        SEC_List_S* pstRr;                /* Revocation Request*/
        CMP_REVOKERESP_S* pstRp;        /* Revocation Response*/
        CRMF_CertReqMsgList* pstCcr;    /* Cross-Certificate Request*/
        CMP_CERTRESPMSG_S* pstCcp;        /* Cross-Certificate Response*/
        CMP_CAKEYUPDATEANN_S* pstCkuann;/* CA Key Update Announcement */
        X509_CERT_S* pstCann;            /* Certificate Announcement */
        CMP_REVOKEANN_S* pstRann;        /* Revocation Announcement */
        SEC_List_S* pstCrlann;            /* CRL Announcement*/
        SEC_AsnNull pstConf;            /* Confirmation*/
        CMP_NESTEDMSGCNT_S* pstNested;    /* Nested Message*/
        SEC_List_S* pstGenm;            /* General Message*/
        SEC_List_S* pstGenp;            /* General Response*/
        CMP_ERRMSG_S* pstError;            /* Error Message*/
#ifdef __IPSI_CMPV2__
        CMPV2_CERT_CONF_MSG_S *pstConfirmContent;
        CMPV2_POLL_REQ_MSG_S *pstPollReqMsg;
        CMPV2_POLL_REP_MSG_S *pstPollRepMsg;
#endif
    }unBodyMsg;

}CMP_PKIBODY_S;



/* This is the outermost structure used in the PKI Management
    This can be protected and sent across the network*/
/**
* @defgroup CMP_PKIMSG_S
* @ingroup cmpStructures
* @par Prototype
* @code
* typedef struct stCMP_PKIMessage
* {
* CMP_PKIHDR_S* pstHeader;
* CMP_PKIBODY_S* pstBody;
* SEC_AsnBits_S stProtection;
* SEC_List_S* pExtraCerts;
* } CMP_PKIMSG_S;
* @endcode
*
* @datastruct pstHeader Pointer to PKI Header structure.
* @datastruct pstBody Pointer to PKI Body structure.
* @datastruct stProtection Contains bits that protect the PKI Message (Optional)
* @datastruct pExtraCerts List of Certificates that may be useful to the recipient (Optional)
*/
typedef struct stCMP_PKIMessage /* Sequence*/
{
    CMP_PKIHDR_S* pstHeader;        /* Pointer to PKI Header structure. */
    CMP_PKIBODY_S* pstBody;            /* Pointer to PKI Body structure. */
    SEC_AsnBits_S stProtection;        /* Contains bits that protect the PKI Message (Optional)*/
    SEC_List_S* pExtraCerts;        /* List of Certificates that may be useful
                                         to the recipient (Optional)*/

} CMP_PKIMSG_S;


/* FUNCTION DECLARATIONS */




/**
* @defgroup CMP_createPKIMsg
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIMSG_S* CMP_createPKIMsg (CMP_PKIHDR_S* pstPKIHeader,
* CMP_PKIBODY_S* pstPKIBody);
* @endcode
*
* @par Purpose
* To create a PKI Message structure using PKI Body and PKI Header structures.
*
* @par Description
* Creates a PKI Message structure using PKI Body and PKI Header structures. The PKI Message can be exchanged between the
* End-Entity and CA/RA for initializing into the PKI or for sending/receiving Requests/Responses.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. Input can be provided using CMP_createPKIHdr(). [N/A]
* @param[in] pstPKIBody Pointer to PKI Body structure. Input can be provided using CMP_createPKIBody(). [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIMSG_S* Pointer to PKI Message structure. [pstPKIMessage|N/A]
* @retval CMP_PKIMSG_S* If either of the inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIMSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free the PKI message, user has to call CMP_freePKIMsg API.
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_PKIMSG_S* CMP_createPKIMsg (CMP_PKIHDR_S* pstPKIHeader,
                                CMP_PKIBODY_S* pstPKIBody);

/**
* @defgroup CMP_createPKIMsg_ex
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIMSG_S* CMP_createPKIMsg_ex (CMP_PKIHDR_S* pstPKIHeader,
* CMP_PKIBODY_S* pstPKIBody);
* @endcode
*
* @par Purpose
* To create a PKI Message structure using PKI Body and PKI Header structures.
*
* @par Description
* Creates a PKI Message structure using PKI Body and PKI Header structures. The PKI Message can be exchanged between the
* End-Entity and CA/RA for initializing into the PKI or for sending/receiving Requests/Responses.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. Input can be provided using CMP_createPKIHdr(). [N/A]
* @param[in] pstPKIBody Pointer to PKI Body structure. Input can be provided using CMP_createPKIBody(). [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIMSG_S* Pointer to PKI Message structure. [pstPKIMessage|N/A]
* @retval CMP_PKIMSG_S* If either of the inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIMSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* If the API returns Success User shouldnot free the pstBody and pstHeader
* \n
* To free the PKI message, user has to call CMP_freePKIMsg API.
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_PKIMSG_S* CMP_createPKIMsg_ex (CMP_PKIHDR_S* pstHeader,
   CMP_PKIBODY_S* pstBody);

/**
* @defgroup CMP_encodePKIMsg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UCHAR* CMP_encodePKIMsg (CMP_PKIMSG_S* pstPKIMessage,
* SEC_UINT32* pulLength);
* @endcode
*
* @par Purpose
* To encode the PKI Message into DER Format.
*
* @par Description
* This method encodes the PKI Message into DER Format.
*
* @param[in] pstPKIMessage Pointer to PKI Message structure. [N/A]
* @param[out] pulLength Length of the data Encoded. [N/A]
*
* @retval SEC_UCHAR* Pointer to the encoded PKI Message. [pucEncodedPKIMsg|N/A]
* @retval SEC_UCHAR* If either of the inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_UCHAR* If memory allocation fails. [SEC_NULL_PTR|N/A]
* @retval SEC_UCHAR* If encode fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free the output character string user has to call ipsi_free
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UCHAR* CMP_encodePKIMsg (CMP_PKIMSG_S* pstPKIMessage,
                             SEC_UINT32* pulLength);




/**
* @defgroup CMP_decodePKIMsg
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIMSG_S* CMP_decodePKIMsg (SEC_UCHAR* pucEncodedPKIMsg,
* SEC_UINT32 ulEncodedLength,
* SEC_UINT32* pulBytesDecoded);
* @endcode
*
* @par Purpose
* To decode the encoded PKI Message.
*
* @par Description
* This method can be used to decode the encoded PKI Message.
*
* @param[in] pucEncodedPKIMsg Pointer to DER encoded PKI Message. [N/A]
* @param[in] ulEncodedLength Length of the Encoded PKI Message. [N/A]
* @param[out] pulBytesDecoded Pointer to Bytes Decoded. [N/A]
*
* @retval CMP_PKIMSG_S* Pointer to CMP_PKIMSG_S structure. [pstResult|N/A]
* @retval CMP_PKIMSG_S* If either of the inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIMSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIMSG_S* If decode fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free the PKI message, user has to call CMP_freePKIMsg API.
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKIMSG_S* CMP_decodePKIMsg (SEC_UCHAR* pucEncodedPKIMsg,
                                SEC_UINT32 ulEncodedLength,
                                SEC_UINT32* pulBytesDecoded);




/**
* @defgroup CMP_genProtection
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_genProtection (CMP_PKIMSG_S* pstPKIMessage,
* SEC_UCHAR* pucPassword,
* SEC_UINT32 ulPwdLen,
* SEC_PKEY_S* pstPrivKey,
* SEC_PKEY_S* pstPubKey);
* @endcode
*
* @par Purpose
* To generate the Protection Bits to protect the PKI message.
*
* @par Description
* Generates protection to PKI Message. This method can be used to generate the Protection Bits to protect the PKI message.
* This method can be called for concealing the Message only after all the fields are added. This method extracts the
* Algorithm from the ProtectionAlg field of the PKIMessage to generate the protection.
*
* @param[in] pucPassword Pointer to Pasword required for PBMAC. [N/A]
* @param[in] ulPwdLen Length of the Password. [N/A]
* @param[in] pstPrivKey Self Private Key(DH/RSA). [N/A]
* @param[in] pstPubKey  Peer Public Key(DH/RSA). [N/A]
* @param[out] pstPKIMessage Pointer to CMP_PKIMSG_S structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If PKIMessage encoding fails. [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Error Code returned by CRYPT_sign(). [N/A|N/A]
* @retval SEC_UINT32 Error Code returned by CRYPT_hmac(). [N/A|N/A]
* @retval SEC_UINT32 Error Code returned by CRYPT_digest(). [N/A|N/A]
* @retval SEC_UINT32 Error Code returned by CRYPT_computeDHKey(). [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_genProtection (CMP_PKIMSG_S* pstPKIMessage,
                              SEC_UCHAR* pucPassword,
                              SEC_UINT32 ulPwdLen,
                              SEC_PKEY_S* pstPrivKey,
                              SEC_PKEY_S* pstPubKey);





/**
* @defgroup CMP_addExtraCerts
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addExtraCerts (CMP_PKIMSG_S* pstPKIMessage,
* SEC_List_S* pExtraCerts);
* @endcode
*
* @par Purpose
* To add a list of extra certificates to PKI Message.
*
* @par Description
* Adds a list of extra certificates to PKI Message. The extraCerts field can contain certificates that may be useful to
* the recipient.
*
* @param[in] pExtraCerts Pointer to List of Certificates. [N/A]
* @param[out] pstPKIMessage Pointer to PKI Message structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addExtraCerts (CMP_PKIMSG_S* pstPKIMessage,
                              SEC_List_S* pExtraCerts);




/**
* @defgroup CMP_createPKIHdr
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIHDR_S* CMP_createPKIHdr (SEC_UINT32 ulPvno,
* SEC_GEN_NAME_S* pstSender,
* SEC_GEN_NAME_S* pstRecipient);
* @endcode
*
* @par Purpose
* To create a PKI Header structure.
*
* @par Description
* Creates a PKI Header structure. All PKI messages require some Header Information for addressing and transaction
* identification. It requires a Version No, GeneralName which identifies the sender and the intended recipient.
*
* @param[in] ulPvno PKI Version No. Should be CMP_VERSION_TYPE (2). [N/A]
* @param[in] pstSender Pointer to General Name identifying the Sender. [N/A]
* @param[in] pstRecipient Pointer to General Name identifying the intended recipient. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIHDR_S* Pointer to PKIHeader structure. [pstPKIHeader|N/A]
* @retval CMP_PKIHDR_S* If either of the inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIHDR_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free the PKI Header, user has to call CMP_freePKIHdr.
*
* N/A
*
* @par Related Topics
* N/A
*
* 
*/


PSELINKDLL CMP_PKIHDR_S* CMP_createPKIHdr (SEC_UINT32 ulPvno,
                                SEC_GEN_NAME_S* pstSender,
                                SEC_GEN_NAME_S* pstRecipient);




/**
* @defgroup CMP_setMsgTime
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_setMsgTime (CMP_PKIHDR_S* pstPKIHeader,
* DATETIME_S* pMessageTime);
* @endcode
*
* @par Purpose
* To add Message Time value at which the sender created the PKIMessage.
*
* @par Description
* Adds Message Time value at which the sender created the PKIMessage.
*
* @param[in] pMessageTime Message Time. [N/A]
* @param[out] pstPKIHeader Pointer to PKIHeader structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute fields of DATETIME_S are not considered in this function.
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_setMsgTime (CMP_PKIHDR_S* pstPKIHeader,
                           DATETIME_S* pMessageTime);




/**
* @defgroup CMP_setProtectionAlg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_setProtectionAlg (CMP_PKIHDR_S* pstPKIHeader,
* SEC_UINT32 ulProtAlg);
* @endcode
*
* @par Purpose
* To add the Protection Algorithm to an already created PKI Header structure.
*
* @par Description
* Adds the Protection Algorithm to an already created PKI Header structure. This API is used to extract the Algorithm used
* to protect the PKIMessage in CMP_genProtection().
*
* @param[in] ulProtAlg Protection algorithm. Can be a Hash/Digest Algorithm or CID_DHBASEDMAC. [N/A]
* @param[out] pstPKIHeader Pointer to PKIHeader structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_setProtectionAlg (CMP_PKIHDR_S* pstPKIHeader,
                                 SEC_UINT32 ulProtAlg);




/**
* @defgroup CMP_checkProtection
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_checkProtection (CMP_PKIMSG_S* pstPKIMessage,
* SEC_UCHAR* pucPassword,
* SEC_UINT32 ulPwdLen,
* SEC_PKEY_S* pstPrivKey,
* SEC_PKEY_S* pstPubKey);
* @endcode
*
* @par Purpose
* To verify the Protection added in the PKI Message.
*
* @par Description
* Verifies the Protection added in the PKI Message. This checking method can be used by the RA before sending it to CA
* to verify against the generated Sign or MAC Protection bits.
*
* @param[in] pucPassword Pointer to Pasword required for PBMAC [N/A]
* @param[in] ulPwdLen Length of the Password. [N/A]
* @param[in] pstPrivKey Self Private Key. [N/A]
* @param[in] pstPubKey Peer Public Key. [N/A]
* @param[out] pstPKIMessage Pointer to CMP_PKIMSG_S structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If PKIMessage encoding fails. [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 If SEC_MEM_CMP() fails. [SEC_ERR|N/A]
* @retval SEC_UINT32 CRYPT_verify() fails. [Error Code returned by CRYPT_verify()|N/A]
* @retval SEC_UINT32 CRYPT_hmac() fails. [Error Code returned by CRYPT_hmac()|N/A]
* @retval SEC_UINT32 CRYPT_digest() fails. [Error Code returned by CRYPT_digest()|N/A]
* @retval SEC_UINT32 CRYPT_computeDHKey() fails. [Error Code returned by CRYPT_computeDHKey()|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_checkProtection (CMP_PKIMSG_S* pstPKIMessage,
                                SEC_UCHAR* pucPassword,
                                SEC_UINT32 ulPwdLen,
                                SEC_PKEY_S* pstPrivKey,
                                SEC_PKEY_S* pstPubKey);




/**
* @defgroup CMP_setKIDs
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_setKIDs (CMP_PKIHDR_S* pstPKIHeader,
* SEC_CHAR* pcSenderKID,
* SEC_UINT32 ulLenSenderKID,
* SEC_CHAR* pcRecipKID,
* SEC_UINT32 ulLenRecipKID);
* @endcode
*
* @par Purpose
* To add Sender and Recipient KIDs to the created PKI Header structure.
*
* @par Description
* Adds Sender and Recipient KIDs to the created PKI Header structure. KIDs are used to identify specific keys used for
* protection.
*
* @param[in] pcSenderKID Pointer to SenderKID. [N/A]
* @param[in] ulLenSenderKID Length of the SenderKID. [N/A]
* @param[in] pcRecipKID Pointer to RecipientKID. [N/A]
* @param[in] ulLenRecipKID Length of the RecipientKID. [N/A]
* @param[out] pstPKIHeader Pointer to PKI Header structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CMP_setKIDs (CMP_PKIHDR_S* pstPKIHeader,
                        SEC_CHAR* pcSenderKID,
                        SEC_UINT32 ulLenSenderKID,
                        SEC_CHAR* pcRecipKID,
                        SEC_UINT32 ulLenRecipKID);




/**
* @defgroup CMP_setTID
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_setTID (CMP_PKIHDR_S* pstPKIHeader,
* SEC_CHAR* pcTransID,
* SEC_UINT32 ulLenTransID);
* @endcode
*
* @par Purpose
* To add a Transaction Identifier to the created PKIHeader structure.
*
* @par Description
* Adds a Transaction Identifier to the created PKIHeader structure. TID identifies the transaction will be the same in
* corresponding request, response, and confirmation messages.
*
* @param[in] pcTransID Pointer to TID. [N/A]
* @param[in] ulLenTransID Length of the TID. [N/A]
* @param[out] pstPKIHeader Pointer to PKI Header structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_setTID (CMP_PKIHDR_S* pstPKIHeader,
                       SEC_CHAR* pcTransID,
                       SEC_UINT32 ulLenTransID);




/**
* @defgroup CMP_setNonces
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_setNonces (CMP_PKIHDR_S* pstPKIHeader,
* SEC_CHAR* pcSndrNonce,
* SEC_UINT32 ulLenSndrNonce,
* SEC_CHAR* pcRecipNonce,
* SEC_UINT32 ulLenRecipNonce);
* @endcode
*
* @par Purpose
* To add Sender and Recip Nonces to a PKIHeader structure that has been created.
*
* @par Description
* Adds Sender and Recip Nonces to a PKIHeader structure that has been created. Nonces are used to provide replay
* protection. SenderNonce is inserted by the creator of this message. RecipNonce is a nonce previously inserted in
* a related message by the intended recipient of this message.
*
* @param[in] pcSndrNonce Pointer to Sender Nonce. [N/A]
* @param[in] ulLenSndrNonce Length of the Sender Nonce. [N/A]
* @param[in] pcRecipNonce Pointer to Recipient Nonce. [N/A]
* @param[in] ulLenRecipNonce Length of the Recipient Nonce. [N/A]
* @param[out] pstPKIHeader Pointer to PKI Header structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_setNonces (CMP_PKIHDR_S* pstPKIHeader,
                          SEC_CHAR* pcSndrNonce,
                          SEC_UINT32 ulLenSndrNonce,
                          SEC_CHAR* pcRecipNonce,
                          SEC_UINT32 ulLenRecipNonce);




/**
* @defgroup CMP_addFreeText
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addFreeText (CMP_PKIHDR_S* pstPKIHeader,
* SEC_List_S* pPKIFreeText);
* @endcode
*
* @par Purpose
* To add free text which is a list of UTF8 Strings to the PKI Header structure.
*
* @par Description
* Adds free text which is a list of UTF8 Strings to the PKI Header structure. This may be used to indicate
* context-specific instructions.
*
* @param[in] pPKIFreeText Pointer to PKI Free Text list. [N/A]
* @param[out] pstPKIHeader Pointer to PKI Header structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addFreeText (CMP_PKIHDR_S* pstPKIHeader,
                            SEC_List_S* pPKIFreeText);




/**
* @defgroup CMP_addGenInfo
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addGenInfo (CMP_PKIHDR_S* pstPKIHeader,
* CMP_INFOTYPEVAL_S* pstGeneralInfo);
* @endcode
*
* @par Purpose
* To add GenInfo to PKI Header structure.
*
* @par Description
* Adds GenInfo to PKI Header structure. This may be used to convey context-specific information. The General Info field
* may be used to send machine-processable additional data to the recipient.
*
* @param[in] pstGeneralInfo Pointer to General information, list of Information Type, and Value. [N/A]
* @param[out] pstPKIHeader Pointer to PKI Header structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If List memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If adding pstGeneralInfo onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addGenInfo (CMP_PKIHDR_S* pstPKIHeader,
                           CMP_INFOTYPEVAL_S* pstGeneralInfo);




/**
* @defgroup CMP_createPKIBody
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIBODY_S* CMP_createPKIBody (CMP_PKIBODYTYPE_E enBodyType,
* SEC_VOID* pstBodyMessage);
* @endcode
*
* @par Purpose
* To create a PKI Body structure.
*
* @par Description
* Creates a PKI Body structure. The PKIBody contains message-specific information (Requests / Responses / Error Message
* / Announcements) which is added to the PKIMessage and used by EE and CA/RA.
*
* @param[in] pstBodyMessage Pointer to MessageType in PKIBody. [N/A]
* @param[in] enBodyType Type of Message in the PKIBody (One of the structures from the unBodyMsg of CMP_PKIBODY_S). [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIBODY_S* Pointer to CMP_PKIBODY_S structure. [pstPKIBody|N/A]
* @retval CMP_PKIBODY_S* If either of the inputs are invalid. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIBODY_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free the PKI body, user has to call CMP_freePKIBody.
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKIBODY_S* CMP_createPKIBody (CMP_PKIBODYTYPE_E enBodyType,
                                  SEC_VOID* pstBodyMessage);


/**
* @defgroup CMP_createPKIBody_ex
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIBODY_S* CMP_createPKIBody_ex (CMP_PKIBODYTYPE_E enBodyType,
* SEC_VOID* pstBodyMessage);
* @endcode
*
* @par Purpose
* To create a PKI Body structure.
*
* @par Description
* Creates a PKI Body structure. The PKIBody contains message-specific information (Requests / Responses / Error Message
* / Announcements) which is added to the PKIMessage and used by EE and CA/RA.
*
* @param[in] pstBodyMessage Pointer to MessageType in PKIBody. [N/A]
* @param[in] enBodyType Type of Message in the PKIBody (One of the structures from the unBodyMsg of CMP_PKIBODY_S). [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIBODY_S* Pointer to CMP_PKIBODY_S structure. [pstPKIBody|N/A]
* @retval CMP_PKIBODY_S* If either of the inputs are invalid. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIBODY_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
* 
* @par Note
* User should not free the pstBodyMessage if the API returns Success.
* To free the PKI body, user has to call CMP_freePKIBody.
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKIBODY_S* CMP_createPKIBody_ex (CMP_PKIBODYTYPE_E enBodyType,
                                  SEC_VOID* pstBodyMessage);


/**
* @defgroup CMP_getPKIHdr
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIHDR_S* CMP_getPKIHdr (CMP_PKIMSG_S* pstPKIMessage);
* @endcode
*
* @par Purpose
* To get the PKI Header from the PKI Message structure.
*
* @par Description
* Gets the PKI Header from the PKI Message structure.
*
* @param[in] pstPKIMessage Pointer to PKI Message structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIHDR_S* Pointer to CMP_PKIHDR_S structure. [pstPKIHeader|N/A]
* @retval CMP_PKIHDR_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKIHDR_S* CMP_getPKIHdr (CMP_PKIMSG_S* pstPKIMessage);




/**
* @defgroup CMP_getPKIBody
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIBODY_S* CMP_getPKIBody (CMP_PKIMSG_S* pstPKIMessage);
* @endcode
*
* @par Purpose
* To get the PKI Body from PKI Message structure.
*
* @par Description
* Gets the PKI Body from PKI Message structure.
*
* @param[in] pstPKIMessage Pointer to PKI Message structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIBODY_S* Pointer to CMP_PKIBODY_S structure. [pstPKIBody|N/A]
* @retval CMP_PKIBODY_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKIBODY_S* CMP_getPKIBody (CMP_PKIMSG_S* pstPKIMessage);




/**
* @defgroup CMP_getExtraCerts
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_getExtraCerts (CMP_PKIMSG_S* pstPKIMessage);
* @endcode
*
* @par Purpose
* To get any extra Certificates from the PKI Message Structure.
*
* @par Description
* Gets any extra Certificates from the PKI Message Structure. The extraCerts field can contain certificates that may be
* useful to the recipient. For example, this can be used by a CA or RA to present an end entity with certificates that it
* needs to verify its own new certificate.
*
* @param[in] pstPKIMessage Pointer to PKI Message structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* List of Extra Certificates. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_List_S*|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_List_S* CMP_getExtraCerts (CMP_PKIMSG_S* pstPKIMessage);



/**
* @defgroup CMP_getVersionFromPKIHdr
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_getVersionFromPKIHdr (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get the PKI Version No.
*
* @par Description
* Gets the PKI Version No. field from the PKI Header structure.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 PKI Version Number(Integer). [CMP_VERSION_TYPE|N/A]
* @retval SEC_UINT32 If the input is NULL. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_getVersionFromPKIHdr (CMP_PKIHDR_S* pstPKIHeader);



/**
* @defgroup CMP_getSender
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_GEN_NAME_S* CMP_getSender (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get the SenderName from the PKI Header structure.
*
* @par Description
* Gets the SenderName from the PKI Header structure.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_GEN_NAME_S* General Name of the Sender. [pstSenderName|N/A]
* @retval SEC_GEN_NAME_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_GEN_NAME_S* CMP_getSender (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getRecipient
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_GEN_NAME_S* CMP_getRecipient (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get the Recipient Name from the PKI Header structure.
*
* @par Description
* Gets the Recipient Name from the PKI Header structure.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_GEN_NAME_S* General Name of the Recipient. [pstRecipientName|N/A]
* @retval SEC_GEN_NAME_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_GEN_NAME_S* CMP_getRecipient (CMP_PKIHDR_S* pstPKIHeader);



/**
* @defgroup CMP_extractMsgTime
* @ingroup cmpFunctions
* @par Prototype
* @code
* DATETIME_S* CMP_extractMsgTime (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To extract PKIMessage Created Time.
*
* @par Description
* Extracts PKIMessage Created Time.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* Message Time. [DATETIME_S*|N/A]
* @retval DATETIME_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
* @retval DATETIME_S* If Generalized Time to DateTime Conversion Fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* 1. Memory has to be de-allocated using ipsi_free function after the usage of 
*     Message created Time\n
* 2. The ucUTCSign,ucUTCHour,ucUTCMinute fields of DATETIME_S are not considered in this function.
*
* @par Related Topics
* N/A
*/


PSELINKDLL DATETIME_S* CMP_extractMsgTime (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getProtectionAlg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_getProtectionAlg (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get Protection Algorithm value.
*
* @par Description
* Gets Protection Algorithm value.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 PKI Message Protection Algorithm Identifier. [N/A|N/A]
* @retval SEC_UINT32 If the Input is NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If Invalid Algorithm. [CID_UNKNOWN|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_getProtectionAlg (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getSenderKID
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* CMP_getSenderKID (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get Sender KID.
*
* @par Description
* Gets Sender KID.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Sender KID. [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnOcts_S* CMP_getSenderKID (CMP_PKIHDR_S* pstPKIHeader);



/**
* @defgroup CMP_getRecipientKID
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* CMP_getRecipientKID (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get Recipient KID.
*
* @par Description
* Gets Recipient KID.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Recipient KID. [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnOcts_S* CMP_getRecipientKID (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getTID
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* CMP_getTID (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get the Transaction ID value.
*
* @par Description
* Gets the Transaction ID value.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Transaction ID [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnOcts_S* CMP_getTID (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getSenderNonce
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* CMP_getSenderNonce (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get the Sender Nonce from PKI Header.
*
* @par Description
* Gets the Sender Nonce from PKI Header.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* SenderNonce - Nonce and its length. [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnOcts_S* CMP_getSenderNonce (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getRecipientNonce
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* CMP_getRecipientNonce (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get the Recipient Nonce from PKI Header.
*
* @par Description
* Gets the Recipient Nonce from PKI Header.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* RecipNonce - Nonce and its length. [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnOcts_S* CMP_getRecipientNonce (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getFreeText
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_getFreeText (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get FreeText from PKI Header structure.
*
* @par Description
* Gets FreeText from PKI Header structure. It indicates the desired language for replies.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to FreeText. [pPKIFreeText|N/A]
* @retval SEC_List_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_List_S* CMP_getFreeText (CMP_PKIHDR_S* pstPKIHeader);



/**
* @defgroup CMP_getFirstGenInfo
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_INFOTYPEVAL_S* CMP_getFirstGenInfo (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get the First General Information from PKI Header structure.
*
* @par Description
* Gets the First General Information from PKI Header structure.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_INFOTYPEVAL_S* Pointer to CMP_INFOTYPEVAL_S. [pstInfoTypeAndVal|N/A]
* @retval CMP_INFOTYPEVAL_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_INFOTYPEVAL_S* CMP_getFirstGenInfo (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getNextGenInfo
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_INFOTYPEVAL_S* CMP_getNextGenInfo (CMP_PKIHDR_S* pstPKIHeader);
* @endcode
*
* @par Purpose
* To get General information from PKI Header structure.
*
* @par Description
* Gets General information from PKI Header structure.
*
* @param[in] pstPKIHeader Pointer to PKI Header structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_INFOTYPEVAL_S* Pointer to CMP_INFOTYPEVAL_S. [pstInfoTypeAndVal|N/A]
* @retval CMP_INFOTYPEVAL_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_INFOTYPEVAL_S* CMP_getNextGenInfo (CMP_PKIHDR_S* pstPKIHeader);




/**
* @defgroup CMP_getPKIBodyType
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIBODYTYPE_E CMP_getPKIBodyType (CMP_PKIBODY_S* pstPKIBody);
* @endcode
*
* @par Purpose
* To get the Message type from the PKI Body.
*
* @par Description
* Gets the Message type from the PKI Body.
*
* @param[in] pstPKIBody Pointer to PKI Body structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIBODYTYPE_E Type of Message in PKIBody. [N/A|N/A]
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKIBODYTYPE_E CMP_getPKIBodyType (CMP_PKIBODY_S* pstPKIBody);




/**
* @defgroup CMP_createPKIStatus
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKISTATUS_S* CMP_createPKIStatus (SEC_UINT32 ulStatus,
* SEC_List_S* pStatusString,
* SEC_AsnBits_S* pPKIFailureInfo);
* @endcode
*
* @par Purpose
* To create a PKI Status Info structure.
*
* @par Description
* Creates a PKI Status Info structure with status granted/rejected. The PKIStatus can be provided as input for the
* Certificate Responses.
*
* @param[in] ulStatus PKIStatus within the range of CERT_RESP_STATUS_E. [N/A]
* @param[in] pStatusString Pointer to List which can be added when Status is not GRANTED/GRANTEDWITHMODS (Optional). [N/A]
* @param[in] pPKIFailureInfo Pointer to Failure Information which can be added for REJECTED Status (Optional). [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKISTATUS_S* Pointer to CMP_PKISTATUS_S structure. [pstPKIStatInfo|N/A]
* @retval CMP_PKISTATUS_S* If any of the Inputs are Invalid. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free the PKI status, user has to call CMP_freePKIStatusInfo.
*
* N/A
*
* @par Related Topics
* N/A
*
* 
*/


PSELINKDLL CMP_PKISTATUS_S* CMP_createPKIStatus (SEC_UINT32 ulStatus,
                                        SEC_List_S* pStatusString,
                                        SEC_AsnBits_S* pPKIFailureInfo);




/**
* @defgroup CMP_createCertRespMsg
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CERTRESPMSG_S* CMP_createCertRespMsg (X509_CERT_S* pstCACert,
* CMP_CERTRESP_S* pstCertResp);
* @endcode
*
* @par Purpose
* To create a CMP_CERTRESPMSG_S structure.
*
* @par Description
* Creates a CMP_CERTRESPMSG_S structure. This method can be used to form Initialization, Cross-certificate, Certificate,
* and Key Update Response Message by the CA in response to the Request.
*
* @param[in] pstCACert Pointer to a CA Certificate (Optional). [N/A]
* @param[in] pstCertResp Pointer to CMP_CERTRESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CERTRESPMSG_S* Pointer to CMP_CERTRESPMSG_S structure. [pstCertRepMsg|N/A]
* @retval CMP_CERTRESPMSG_S* If any of the Inputs are Invalid. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*  To free the Cert Resp Msg, user has to call CMP_freeCertRepMsg.
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_CERTRESPMSG_S* CMP_createCertRespMsg (X509_CERT_S* pstCACert,
                                         CMP_CERTRESP_S* pstCertResp);




/**
* @defgroup CMP_createCertResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CERTRESP_S* CMP_createCertResp (SEC_AsnOcts_S* pRegInfo,
* SEC_INT32 iCertReqID,
* CMP_PKISTATUS_S* pstPKIStatusInfo);
* @endcode
*
* @par Purpose
* To create a Certificate Response to be included in Certificate Response Message.
*
* @par Description
* Creates a Certificate Response to be included in Certificate Response Message.
*
* @param[in] pRegInfo Pointer to Registration Information which is to be extracted from the Request. [N/A]
* @param[in] iCertReqID Certificate Request ID to match the response with corresponding request. [N/A]
* @param[in] pstPKIStatusInfo Pointer to PKI Status Information. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CERTRESP_S* Pointer to CMP_CERTRESP_S structure. [pstCertResp|N/A]
* @retval CMP_CERTRESP_S* If any of the Inputs are Invalid. [SEC_NULL_PTR|N/A]
* @retval CMP_CERTRESP_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*  To free the Cert Resp, user has to call CMP_freeCertResponse.
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_CERTRESP_S* CMP_createCertResp (SEC_AsnOcts_S* pRegInfo,
                                   SEC_INT32 iCertReqID,
                                   CMP_PKISTATUS_S* pstPKIStatusInfo);




/**
* @defgroup CMP_addCert
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addCert (CMP_CERTRESPMSG_S* pstCertRepMsg,
* X509_CERT_S* pstCACert);
* @endcode
*
* @par Purpose
* To add a CA Certificate to to the Certificate Response Message.
*
* @par Description
* Adds a CA Certificate to to the Certificate Response Message.
*
* @param[in] pstCACert Pointer to X509_CERT_S structure. [N/A]
* @param[out] pstCertRepMsg Pointer to CMP_CERTRESPMSG_S structure. [N/A]
*
* @retval SEC_UINT32 Upon success. The CA certificate is added successfully. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If adding pstCACert onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addCert (CMP_CERTRESPMSG_S* pstCertRepMsg,
                        X509_CERT_S* pstCACert);




/**
* @defgroup CMP_addCertResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addCertResp (CMP_CERTRESPMSG_S* pstCertRepMsg,
* CMP_CERTRESP_S* pstCertResp);
* @endcode
*
* @par Purpose
* To add a Certificate Response to the Certificate Response Message.
*
* @par Description
* Adds a Certificate Response to the Certificate Response Message.
*
* @param[in] pstCertResp Pointer to CMP_CERTRESP_S structure.
* This parameter can be formed using CMP_createCertResp(). [N/A]
* @param[out] pstCertRepMsg Pointer to CMP_CERTRESPMSG_S structure. [N/A]
*
* @retval SEC_UINT32 Upon success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If adding pstCertResp onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addCertResp (CMP_CERTRESPMSG_S* pstCertRepMsg,
                            CMP_CERTRESP_S* pstCertResp);




/**
* @defgroup CMP_addKeyPairToResponse
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addKeyPairToResponse (CMP_KEYPAIR_S* pstCertKeyPair,
* CMP_CERTRESPMSG_S* pstCertRepMsg,
* SEC_INT32 iCertReqID);
* @endcode
*
* @par Purpose
* To add the Certified Key Pair to the Certificate Response in Certificate Response Message.
*
* @par Description
* Adds the Certified Key Pair to the Certificate Response in Certificate Response Message.
*
* @param[in] iCertReqID Index to CertResponse for which the Key Pair is to be added. [N/A]
* @param[in] pstCertKeyPair Pointer to CMP_KEYPAIR_S structure. [N/A]
* @param[out] pstCertRepMsg Pointer to CMP_CERTRESPMSG_S structure. [N/A]
*
* @retval SEC_UINT32 Upon success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL or iCertReqID is not in the Response List. [N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If iCertReqID is less than -1. [SEC_ERR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addKeyPairToResponse (CMP_KEYPAIR_S* pstCertKeyPair,
                                     CMP_CERTRESPMSG_S* pstCertRepMsg,
                                     SEC_INT32 iCertReqID);




/**
* @defgroup CMP_createKeyRecoveryResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_KEYRECOVERYRESP_S* CMP_createKeyRecoveryResp (CMP_PKISTATUS_S* pstPKIStatus);
* @endcode
*
* @par Purpose
* To create a Key Recovery Response structure.
*
* @par Description
* Creates a Key Recovery Response structure. Whenever an entity in PKI system loses its PSE, then an End Entity can request
* for the new Certificate for its new Key Pair. This method can be used to form the Key Recovery Response by the CA for
* Key Recovery Request from the End Entity.
*
* @param[in] pstPKIStatus Pointer to CMP_PKISTATUS_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_KEYRECOVERYRESP_S* Pointer to CMP_KEYRECOVERYRESP_S structure. [pstKeyRecRepCnt|N/A]
* @retval CMP_KEYRECOVERYRESP_S* If the Input is NULL or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
* 
* @par Note
* To free key recovery resp, user has to call CMP_freeKeyRecRepContent.
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_KEYRECOVERYRESP_S* CMP_createKeyRecoveryResp (CMP_PKISTATUS_S* pstPKIStatus);




/**
* @defgroup CMP_addCACert
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addCACert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt,
* X509_CERT_S* pstCACert);
* @endcode
*
* @par Purpose
* To add the CA Certificate to CMP_KEYRECOVERYRESP_S.
*
* @par Description
* Adds the CA Certificate to CMP_KEYRECOVERYRESP_S.
*
* @param[in] pstCACert Pointer to CA Certificate. [N/A]
* @param[out] pstKeyRecRepCnt Pointer to CMP_KEYRECOVERYRESP_S structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If either of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If List memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If dup memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If adding CA Certiticate onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addCACert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt,
                          X509_CERT_S* pstCACert);




/**
* @defgroup CMP_addNewCert
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addNewCert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt,
* X509_CERT_S* pstNewSignCert);
* @endcode
*
* @par Purpose
* To add Newly Signed Certificate to CMP_KEYRECOVERYRESP_S.
*
* @par Description
* Adds Newly Signed Certificate to CMP_KEYRECOVERYRESP_S.
*
* @param[in] pstNewSignCert Pointer to X509_CERT_S. [N/A]
* @param[out] pstKeyRecRepCnt Pointer to CMP_KEYRECOVERYRESP_S structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the Inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If Response status to the Request is not GRANTED or GRANTEDWITHMODS. [SEC_ERR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addNewCert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt,
                           X509_CERT_S* pstNewSignCert);




/**
* @defgroup CMP_createKeyPair
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_KEYPAIR_S* CMP_createKeyPair (SEC_UINT32 enChoice,
* X509_CERT_S* pstCert,
* SEC_BOOL bPrivKeyEncrypt,
* SEC_PKEY_S* pstPrivKey,
* SEC_UINT32 ulIntndAlg,
* SEC_UINT32 ulSymmAlg,
* SEC_PKEY_S* pstPubKey,
* SEC_UINT32 ulPubKeyAlgId,
* SEC_UINT32 ulKeyGenAlgId,
* SEC_UCHAR* pucValueHint,
* SEC_UINT32 ulValueHint);
* @endcode
*
* @par Purpose
* To create a Certified Key Pair.
*
* @par Description
* Creates a Certified Key Pair. The purpose of the KeyPair is to allow a CA to return the value of a Certificate and/or
* Private Key in an encrypted manner using the Symmetric Key while sending a Certificate Response or Key Recovery Response.
* Symmetric Key is encrypted and sent using the Public Key.
*
* @param[in] enChoice Choice for Certificate/Encrypted Certificate. [N/A]
* @param[in] pstCert Pointer to  X509_CERT_S. [N/A]
* @param[in] bPrivKeyEncrypt Boolean choice (True/False) for Private Key encryption. [N/A]
* @param[in] pstPrivKey Pointer to Private Key. [N/A]
* @param[in] ulIntndAlg Intended Algorithm Identifier. [N/A]
* @param[in] ulSymmAlg Symmetric Algorithm used to encrypt the Private Key. [N/A]
* @param[in] pstPubKey Pointer to Public Key. [N/A]
* @param[in] ulPubKeyAlgId Algorithm used to encrypt the symmetric key. [N/A]
* @param[in] ulKeyGenAlgId Algorithm used to generate symmetric key. [N/A]
* @param[in] pucValueHint Pointer to a brief description or identifier of the encValue content. [N/A]
* @param[in] ulValueHint Length of value hint. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_KEYPAIR_S* Pointer to CMP_KEYPAIR_S. [pCertKeyPair|N/A]
* @retval CMP_KEYPAIR_S* If any of the Inputs are Invalid or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*  To free key pair, user has to call CMP_freeCertifiedKeyPair.
*
* N/A
*
* @par Related Topics
* N/A
*
* 
*/


PSELINKDLL CMP_KEYPAIR_S* CMP_createKeyPair (SEC_UINT32 enChoice,
                                  X509_CERT_S* pstCert,
                                  SEC_BOOL bPrivKeyEncrypt,
                                  SEC_PKEY_S* pstPrivKey,
                                  SEC_UINT32 ulIntndAlg,
                                  SEC_UINT32 ulSymmAlg,
                                  SEC_PKEY_S* pstPubKey,
                                  SEC_UINT32 ulPubKeyAlgId,
                                  SEC_UINT32 ulKeyGenAlgId,
                                  SEC_UCHAR* pucValueHint,
                                  SEC_UINT32 ulValueHint);




/**
* @defgroup CMP_addPubInfoToKeyPair
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addPubInfoToKeyPair (CMP_KEYPAIR_S* pstCertKeyPair,
* CRMF_PUBLICATION_INFO_S* pstPubInfo);
* @endcode
*
* @par Purpose
* To add Publication Information to the Key Pair of the Certificate Response / KeyRecovery Response.
*
* @par Description
* Adds Publication Information to the Key Pair of the Certificate Response / KeyRecovery Response.
*
* @param[in] pstCertKeyPair Pointer to CMP_KEYPAIR_S structure. [N/A]
* @param[out] pstPubInfo Pointer to CRMF_PUBLICATION_INFO_S structure. [N/A]
*
* @retval SEC_UINT32 Upon Success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addPubInfoToKeyPair (CMP_KEYPAIR_S* pstCertKeyPair,
                                    CRMF_PUBLICATION_INFO_S* pstPubInfo);




/**
* @defgroup CMP_addCertKeyPairToKeyRecoveryResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addCertKeyPairToKeyRecoveryResp (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt,
* CMP_KEYPAIR_S* pstCertKeyPair);
* @endcode
*
* @par Purpose
* To add KeyPair to Key Recovery Response.
*
* @par Description
* Adds KeyPair to Key Recovery Response. The purpose of this KeyPair is to allow a CA to return the value of a
* Certificate or Private Key in the encrypted format.
*
* @param[in] pstCertKeyPair Pointer to CMP_KEYPAIR_S. This input can be provided by using CMP_createKeyPair(). [N/A]
* @param[out] pstKeyRecRepCnt Pointer to CMP_KEYRECOVERYRESP_S structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If adding pstCertKeyPair onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addCertKeyPairToKeyRecoveryResp (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt,
                                                CMP_KEYPAIR_S* pstCertKeyPair);




/**
* @defgroup CMP_getNewCert
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CERT_S* CMP_getNewCert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);
* @endcode
*
* @par Purpose
* To get the Newly Signed Certificate from CMP_KEYRECOVERYRESP_S structure.
*
* @par Description
* Gets the Newly Signed Certificate from CMP_KEYRECOVERYRESP_S structure.
*
* @param[in] pstKeyRecRepCnt Pointer to CMP_KEYRECOVERYRESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Pointer to Newly Signed Certificate. [pstCertificate|N/A]
* @retval X509_CERT_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CERT_S* CMP_getNewCert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);




/**
* @defgroup CMP_getFirstCACert
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CERT_S* CMP_getFirstCACert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);
* @endcode
*
* @par Purpose
* To get the First CA Certificate from CA Certificate list in CMP_KEYRECOVERYRESP_S structure.
*
* @par Description
* Gets the First CA Certificate from CA Certificate list in CMP_KEYRECOVERYRESP_S structure.
*
* @param[in] pstKeyRecRepCnt Pointer to CMP_KEYRECOVERYRESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Pointer to CA Certificate. [pstCertificate|N/A]
* @retval X509_CERT_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CERT_S* CMP_getFirstCACert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);




/**
* @defgroup CMP_getNextCACert
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CERT_S* CMP_getNextCACert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);
* @endcode
*
* @par Purpose
* To get the next CA Certificate from CA Certificate list in CMP_KEYRECOVERYRESP_S structure.
*
* @par Description
* Gets the next CA Certificate from CA Certificate list in CMP_KEYRECOVERYRESP_S structure.
*
* @param[in] pstKeyRecRepCnt Pointer to CMP_KEYRECOVERYRESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Pointer to CACert. [pstCertificate|N/A]
* @retval X509_CERT_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CERT_S* CMP_getNextCACert (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);




/**
* @defgroup CMP_getFirstKeyPairFromKeyRecoveryResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_KEYPAIR_S* CMP_getFirstKeyPairFromKeyRecoveryResp (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);
* @endcode
*
* @par Purpose
* To get the First Certified Key Pair from Key Pair History List in CMP_KEYRECOVERYRESP_S structure.
*
* @par Description
* Gets the First Certified Key Pair from Key Pair History List in CMP_KEYRECOVERYRESP_S structure.
*
* @param[in] pstKeyRecRepCnt Pointer to CMP_KEYRECOVERYRESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_KEYPAIR_S* Pointer to CMP_KEYPAIR_S. [pstCertKeyPair|N/A]
* @retval CMP_KEYPAIR_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_KEYPAIR_S* CMP_getFirstKeyPairFromKeyRecoveryResp (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);




/**
* @defgroup CMP_getNextKeyPairFromKeyRecoveryResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_KEYPAIR_S* CMP_getNextKeyPairFromKeyRecoveryResp (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);
* @endcode
*
* @par Purpose
* To get the next Certified Key Pair from Key Pair History List in CMP_KEYRECOVERYRESP_S structure.
*
* @par Description
* Gets the next Certified Key Pair from Key Pair History List in CMP_KEYRECOVERYRESP_S structure.
*
* @param[in] pstKeyRecRepCnt Pointer to CMP_KEYRECOVERYRESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_KEYPAIR_S* Pointer to CMP_KEYPAIR_S. [pstCertKeyPair|N/A]
* @retval CMP_KEYPAIR_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_KEYPAIR_S* CMP_getNextKeyPairFromKeyRecoveryResp (CMP_KEYRECOVERYRESP_S* pstKeyRecRepCnt);




/**
* @defgroup CMP_getPubInfo
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_PUBLICATION_INFO_S* CMP_getPubInfo (CMP_KEYPAIR_S* pstCertKeyPair);
* @endcode
*
* @par Purpose
* To get the Publication Information from CMP_KEYPAIR_S structure.
*
* @par Description
* Gets the Publication Information from CMP_KEYPAIR_S structure.
*
* @param[in] pstCertKeyPair Pointer to CMP_KEYPAIR_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_PUBLICATION_INFO_S* Pointer to CRMF_PUBLICATION_INFO_S structure. [pstPubInfo|N/A]
* @retval CRMF_PUBLICATION_INFO_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CRMF_PUBLICATION_INFO_S* CMP_getPubInfo (CMP_KEYPAIR_S* pstCertKeyPair);




/**
* @defgroup CMP_getCMPCert
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID* CMP_getCMPCert (CMP_KEYPAIR_S* pstCertKeyPair);
* @endcode
*
* @par Purpose
* To get Certificate/Encrypted Certificate from CMP_KEYPAIR_S structure.
*
* @par Description
* Gets Certificate/Encrypted Certificate from CMP_KEYPAIR_S structure.
*
* @param[in] pstCertKeyPair Pointer to CMP_KEYPAIR_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Pointer to Certificate or Encrypted Certificate. [SEC_VOID*|N/A]
* @retval SEC_VOID* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID* CMP_getCMPCert (CMP_KEYPAIR_S* pstCertKeyPair);




/**
* @defgroup CMP_getPrivateKey
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_ENCRYPTED_VALUE_S* CMP_getPrivateKey (CMP_KEYPAIR_S* pstCertKeyPair);
* @endcode
*
* @par Purpose
* To get the Encrypted Private Key structure pointer from CMP_KEYPAIR_S structure.
*
* @par Description
* Gets the Encrypted Private Key structure pointer from CMP_KEYPAIR_S structure.
*
* @param[in] pstCertKeyPair Pointer to CMP_KEYPAIR_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_ENCRYPTED_VALUE_S* Pointer to CRMF_ENCRYPTED_VALUE_S structure. [pstPrivateKey|N/A]
* @retval CRMF_ENCRYPTED_VALUE_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CRMF_ENCRYPTED_VALUE_S* CMP_getPrivateKey (CMP_KEYPAIR_S* pstCertKeyPair);




/**
* @defgroup CMP_getEncryptedValue
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* CMP_getEncryptedValue (CRMF_ENCRYPTED_VALUE_S* pstEncValue);
* @endcode
*
* @par Purpose
* To get the Encrypted Value of the Private Key in CRMF_ENCRYPTED_VALUE_S structure.
*
* @par Description
* Gets the Encrypted Value of the Private Key in CRMF_ENCRYPTED_VALUE_S structure.
*
* @param[in] pstEncValue Pointer to CRMF_ENCRYPTED_VALUE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBits_S* Encrypted Value. [SEC_AsnBits_S*|N/A]
* @retval SEC_AsnBits_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnBits_S* CMP_getEncryptedValue (CRMF_ENCRYPTED_VALUE_S* pstEncValue);




/**
* @defgroup CMP_getEncryptedSymmKey
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* CMP_getEncryptedSymmKey (CRMF_ENCRYPTED_VALUE_S* pstEncValue);
* @endcode
*
* @par Purpose
* To  Get the encrypted Symmetric Key from CRMF_ENCRYPTED_VALUE_S structure.
*
* @par Description
* Gets the encrypted Symmetric Key from CRMF_ENCRYPTED_VALUE_S structure.
*
* @param[in] pstEncValue Pointer to CRMF_ENCRYPTED_VALUE_Ss structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBits_S* Encrypted Symmetric Key and its length. Pointer to SEC_AsnBits_S. [SEC_AsnBits_S*|N/A]
* @retval SEC_AsnBits_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnBits_S* CMP_getEncryptedSymmKey (CRMF_ENCRYPTED_VALUE_S* pstEncValue);



/**
* @defgroup CMP_getIntendedAlg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S* CMP_getIntendedAlg (CRMF_ENCRYPTED_VALUE_S* pstEncValue);
* @endcode
*
* @par Purpose
* To get the Intended Algorithm Identifier for which the value will be used from CRMF_ENCRYPTED_VALUE_S structure.
*
* @par Description
* Gets the Intended Algorithm Identifier for which the value will be used from CRMF_ENCRYPTED_VALUE_S structure.
*
* @param[in] pstEncValue Pointer to CRMF_ENCRYPTED_VALUE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ALG_IDENTIFIER_S* Intended Algorithm Identifier. [SEC_ALG_IDENTIFIER_S*|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_ALG_IDENTIFIER_S* CMP_getIntendedAlg (CRMF_ENCRYPTED_VALUE_S* pstEncValue);




/**
* @defgroup CMP_getSymmAlg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S* CMP_getSymmAlg (CRMF_ENCRYPTED_VALUE_S* pstEncValue);
* @endcode
*
* @par Purpose
* To get the Algorithm Identifier for Symmetric Key.
*
* @par Description
* Gets the Algorithm Identifier for Symmetric Key.
*
* @param[in] pstEncValue Pointer to CRMF_ENCRYPTED_VALUE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ALG_IDENTIFIER_S* Symmetric Key Algorithm Identifier which has been used
* to generate the Symmetric Key. [SEC_ALG_IDENTIFIER_S*|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_ALG_IDENTIFIER_S* CMP_getSymmAlg (CRMF_ENCRYPTED_VALUE_S* pstEncValue);




/**
* @defgroup CMP_getKeyAlgID
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S* CMP_getKeyAlgID (CRMF_ENCRYPTED_VALUE_S* pstEncValue);
* @endcode
*
* @par Purpose
* To get the Key Algorithm Identifier used to encrypt the symmetric key.
*
* @par Description
* Gets the Key Algorithm Identifier used to encrypt the symmetric key.
*
* @param[in] pstEncValue Pointer to CRMF_ENCRYPTED_VALUE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ALG_IDENTIFIER_S* Key Algorithm which has been used to encrypt the Symmetric Key. [SEC_ALG_IDENTIFIER_S*|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_ALG_IDENTIFIER_S* CMP_getKeyAlgID (CRMF_ENCRYPTED_VALUE_S* pstEncValue);




/**
* @defgroup CMP_getValueHint
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* CMP_getValueHint (CRMF_ENCRYPTED_VALUE_S* pstEncValue);
* @endcode
*
* @par Purpose
* To get the hint value in  CRMF_ENCRYPTED_VALUE_S.
*
* @par Description
* Gets the hint value in  CRMF_ENCRYPTED_VALUE_S. It gives a brief description or identifier of the encValue content.
*
* @param[in] pstEncValue Pointer to CRMF_ENCRYPTED_VALUE_Ss structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Value Hint. Pointer to SEC_AsnOcts_S. [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If the Input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnOcts_S* CMP_getValueHint (CRMF_ENCRYPTED_VALUE_S* pstEncValue);




/**
* @defgroup CMP_createRevocationReq
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_createRevocationReq (SEC_VOID);
* @endcode
*
* @par Purpose
* To create a Revocation Request List for the PKI Message to which Revocation Details can be added.
*
* @par Description
* Creates a Revocation Request List for the PKI Message to which Revocation Details can be added.
*
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to Revocation Request Content structure. [pRevReqContent|N/A]
* @retval SEC_List_S* If memory allocation fails to create the List. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free Revocation request list, user has to call CMP_freeRevReqContent.
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_List_S* CMP_createRevocationReq (SEC_VOID);



/**
* @defgroup CMP_createRevocationDetail
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_REVDETAILS_S* CMP_createRevocationDetail (X509_CERT_S* pstCertificate,
* SEC_AsnBits_S* pstRevRsn,
* DATETIME_S* pstBadSinceDate);
* @endcode
*
* @par Purpose
* To create a Revocation Detail structure.
*
* @par Description
* Creates a Revocation Detail structure. When revocation of a certificate (or several certificates) is requested,
* the following method can be used to create a revocation detail structure.
*
* @param[in] pstCertificate Pointer to X509_CERT_S structure. Allows requester to specify as much as they can about
* the certificate for which revocation is requested. [N/A]
* @param[in] pstRevRsn Pointer to the reason that revocation is requested (X509 Reason Flags). [N/A]
* @param[in] pstBadSinceDate Pointer to DATETIME_S and indicates best knowledge of sender. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_REVDETAILS_S* Pointer to CMP_REVDETAILS_S structure. [pstRevDetail|N/A]
* @retval CMP_REVDETAILS_S* If either of the Inputs are Invalid or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free Revocation details, user has to call CMP_freeRevDetails.
* \n
*
* The ucUTCSign,ucUTCHour,ucUTCMinute fields of DATETIME_S are not considered in this function.
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_REVDETAILS_S* CMP_createRevocationDetail (X509_CERT_S* pstCertificate,
                                              SEC_AsnBits_S* pstRevRsn,
                                              DATETIME_S* pstBadSinceDate);




/**
* @defgroup CMP_addExtns
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addExtns (CMP_REVDETAILS_S* pstRevDetails,
* Extensions* pCRLEntryDetails);
* @endcode
*
* @par Purpose
* To add CRL Extensions to the Revocation Details which is Optional.
*
* @par Description
* Adds CRL Extensions to the Revocation Details which is Optional.
*
* @param[in] pCRLEntryDetails Pointer to CRL Extensions. [N/A]
* @param[out] pstRevDetails Pointer to Revocation Detail structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addExtns (CMP_REVDETAILS_S* pstRevDetails,
                         Extensions* pCRLEntryDetails);




/**
* @defgroup CMP_addRevDetail
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addRevDetail (CMP_REVDETAILS_S* pstRevDetails,
* SEC_List_S* pRevReqContent);
* @endcode
*
* @par Purpose
* To add Revocation detail structure to the Revocation Request List.
*
* @par Description
* Adds Revocation detail structure to the Revocation Request List. Revocation Details
* are sent by the requester for a Revocation Request.
*
* @param[in] pstRevDetails Pointer to Revocation Detail structure. [N/A]
* @param[out] pRevReqContent Pointer to Revocation Request. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If adding pstRevDetails onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addRevDetail (CMP_REVDETAILS_S* pstRevDetails,
                             SEC_List_S* pRevReqContent);



/**
* @defgroup CMP_getCertDetail
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_CERT_TEMPLATE_S* CMP_getCertDetail (CMP_REVDETAILS_S* pstRevDetails);
* @endcode
*
* @par Purpose
* To get the Certificate Template from a Revocation detail of the Revocation Request.
*
* @par Description
* Gets the Certificate Template from a Revocation detail of the Revocation Request.
*
* @param[in] pstRevDetails Pointer to CMP_REVDETAILS_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_TEMPLATE_S* Pointer to CRMF_CERT_TEMPLATE_S structure. [pCertDetails|N/A]
* @retval CRMF_CERT_TEMPLATE_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
* To free CRMF cert template, user has to call CRMF_freeCertTemplate.
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CRMF_CERT_TEMPLATE_S* CMP_getCertDetail (CMP_REVDETAILS_S* pstRevDetails);




/**
* @defgroup CMP_getRevocationReason
* @ingroup cmpFunctions
* @par Prototype
* @code
* ReasonFlags* CMP_getRevocationReason (CMP_REVDETAILS_S* pstRevDetails);
* @endcode
*
* @par Purpose
* To get the Revocation Reason from CMP_REVDETAILS_S structure.
*
* @par Description
* Gets the Revocation Reason from CMP_REVDETAILS_S structure.
*
* @param[in] pstRevDetails Pointer to CMP_REVDETAILS_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval ReasonFlags* Pointer to Reason Flags - SEC_AsnBits_S [ReasonFlags*|N/A]
* @retval ReasonFlags* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL ReasonFlags* CMP_getRevocationReason (CMP_REVDETAILS_S* pstRevDetails);



/**
* @defgroup CMP_extractBadTime
* @ingroup cmpFunctions
* @par Prototype
* @code
* DATETIME_S* CMP_extractBadTime (CMP_REVDETAILS_S* pstRevDetails);
* @endcode
*
* @par Purpose
* To Extract the Bad Time from the Revocation detail structure.
*
* @par Description
* Extracts the Bad Time from the Revocation detail structure.
*
* @param[in] pstRevDetails Pointer to CMP_REVDETAILS_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* Pointer to DATETIME_S structure. [DATETIME_S*|N/A]
* @retval DATETIME_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval DATETIME_S* If Generalized Time to DateTime Conversion Fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* Memory has to be de-allocated after the usage of BadSinceDate field.
*
* @par Related Topics
* N/A
*/


PSELINKDLL DATETIME_S* CMP_extractBadTime (CMP_REVDETAILS_S* pstRevDetails);



/**
* @defgroup CMP_getVerFromCertTemplate
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_INT32* CMP_getVerFromCertTemplate (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Version from the Certificate Template.
*
* @par Description
* Gets the Version from the Certificate Template. Version can be of type V1, V2 and V3 supported by X509.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32* Pointer to Version of the Certificate Template. [SEC_INT32*|N/A]
* @retval SEC_INT32* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_INT32* CMP_getVerFromCertTemplate (CRMF_CERT_TEMPLATE_S* pstCertDetails);



/**
* @defgroup CMP_getSN
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_BIGINT_S* CMP_getSN (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Serial Number from the Certificate Template.
*
* @par Description
* Gets the Serial Number from the Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_BIGINT_S* Big Num (Certificate Serial Number). [SEC_BIGINT_S*|N/A]
* @retval SEC_BIGINT_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_BIGINT_S* CMP_getSN (CRMF_CERT_TEMPLATE_S* pstCertDetails);




/**
* @defgroup CMP_getSignAlg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_ALG_IDENTIFIER_S* CMP_getSignAlg (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Signing Algorithm from the Certificate Template.
*
* @par Description
* Gets the Signing Algorithm from the Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ALG_IDENTIFIER_S* Algorithm Identifier. [SEC_ALG_IDENTIFIER_S*|N/A]
* @retval SEC_ALG_IDENTIFIER_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_ALG_IDENTIFIER_S* CMP_getSignAlg (CRMF_CERT_TEMPLATE_S* pstCertDetails);




/**
* @defgroup CMP_getIssuer
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_NAME_S* CMP_getIssuer (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Issuer Name from Certificate Template.
*
* @par Description
* Gets the Issuer Name from Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* Pointer to Issuer Name. [SEC_NAME_S*|N/A]
* @retval SEC_NAME_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_NAME_S* CMP_getIssuer (CRMF_CERT_TEMPLATE_S* pstCertDetails);



/**
* @defgroup CMP_getValidity
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_OPT_VALIDITY_S* CMP_getValidity (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Validity from the Certificate Template.
*
* @par Description
* Gets the Validity from the Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_OPT_VALIDITY_S* Pointer to CRMF_OPT_VALIDITY_S. [CRMF_OPT_VALIDITY_S*|N/A]
* @retval CRMF_OPT_VALIDITY_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CRMF_OPT_VALIDITY_S* CMP_getValidity (CRMF_CERT_TEMPLATE_S* pstCertDetails);




/**
* @defgroup CMP_getSubject
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_NAME_S* CMP_getSubject (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Subject Name from the Certificate Template.
*
* @par Description
* Gets the Subject Name from the Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_NAME_S* Pointer to Subject Name. [pstPublicKeyInfo|N/A]
* @retval SEC_NAME_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_NAME_S* CMP_getSubject (CRMF_CERT_TEMPLATE_S* pstCertDetails);



/**
* @defgroup CMP_getPubKeyInfo
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_PUBKEY_INFO_S* CMP_getPubKeyInfo (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Encoded Public Key from the Certificate Template.
*
* @par Description
* Gets the Encoded Public Key from the Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_PUBKEY_INFO_S* Pointer to SEC_PUBKEY_INFO_S. [SEC_PUBKEY_INFO_S*|N/A]
* @retval SEC_PUBKEY_INFO_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_PUBKEY_INFO_S* CMP_getPubKeyInfo (CRMF_CERT_TEMPLATE_S* pstCertDetails);




/**
* @defgroup CMP_getIssuerID
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* CMP_getIssuerID (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Issuer ID from the Certificate Template.
*
* @par Description
* Gets the Issuer ID from the Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBits_S* Pointer to Issuer ID. [SEC_AsnBits_S*|N/A]
* @retval SEC_AsnBits_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnBits_S* CMP_getIssuerID (CRMF_CERT_TEMPLATE_S* pstCertDetails);



/**
* @defgroup CMP_getSubjectID
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* CMP_getSubjectID (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Subject ID from the Certificate Template.
*
* @par Description
* Gets the Subject ID from the Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBits_S* Pointer to Subject ID. [SEC_AsnBits_S*|N/A]
* @retval SEC_AsnBits_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnBits_S* CMP_getSubjectID (CRMF_CERT_TEMPLATE_S* pstCertDetails);



/**
* @defgroup CMP_getExtnsFromCertDetail
* @ingroup cmpFunctions
* @par Prototype
* @code
* Extensions* CMP_getExtnsFromCertDetail (CRMF_CERT_TEMPLATE_S* pstCertDetails);
* @endcode
*
* @par Purpose
* To get the Extension List from the Certificate Template.
*
* @par Description
* Gets the Extension List from the Certificate Template.
*
* @param[in] pstCertDetails Pointer to CRMF_CERT_TEMPLATE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Extensions* Pointer to Extension List. [Extensions*|N/A]
* @retval Extensions* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL Extensions* CMP_getExtnsFromCertDetail (CRMF_CERT_TEMPLATE_S* pstCertDetails);




/**
* @defgroup CMP_createRevocationResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_REVOKERESP_S* CMP_createRevocationResp (CMP_PKISTATUS_S* pstPKIStatus,
* CRMF_CERT_ID_S* pstRevCerts,
* X509_CRL_S* pstCRL);
* @endcode
*
* @par Purpose
* To create a Revocation Response.
*
* @par Description
* Creates a Revocation Response. It is produced in response to the Revocation Request and is sent to the
* Requester of the Revocation.
*
* @param[in] pstPKIStatus Pointer to CMP_PKISTATUS_S. [N/A]
* @param[in] pstRevCerts Pointer to CRMF_CERT_ID_S. [N/A]
* @param[in] pstCRL Pointer to X509_CRL_S. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_REVOKERESP_S* Pointer to CMP_REVOKERESP_S structure. [pstRevRepContent|N/A]
* @retval CMP_REVOKERESP_S* If any of the inputs are Invalid or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_REVOKERESP_S* CMP_createRevocationResp (CMP_PKISTATUS_S* pstPKIStatus,
                                            CRMF_CERT_ID_S* pstRevCerts,
                                            X509_CRL_S* pstCRL);




/**
* @defgroup CMP_addStatusToRevocationResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addStatusToRevocationResp (CMP_REVOKERESP_S* pstRevRepContent,
* CMP_PKISTATUS_S* pstPKIStatusInfo);
* @endcode
*
* @par Purpose
* To add the PKI Status Information to the Revocation Response structure.
*
* @par Description
* Adds the PKI Status Information to the Revocation Response structure. Status Information comprises of a Status
* as in CERT_RESP_STATUS_E, Status String with Error details, and Failure Information if any.
*
* @param[in] pstPKIStatusInfo Pointer to CMP_PKISTATUS_S structure. [N/A]
* @param[out] pstRevRepContent Pointer to CMP_REVOKERESP_S structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If adding pstPKIStatusInfo onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addStatusToRevocationResp (CMP_REVOKERESP_S* pstRevRepContent,
                                          CMP_PKISTATUS_S* pstPKIStatusInfo);




/**
* @defgroup CMP_createCertID
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_CERT_ID_S* CMP_createCertID (CMP_REVDETAILS_S *pstRevDetails,
* SEC_GEN_NAME_S* pstIssuer);
* @endcode
*
* @par Purpose
* To create a Certificate ID structure in order to identify particular certificates.
*
* @par Description
* Creates a Certificate ID structure in order to identify particular certificates. This CertID is used in forming the
* Revocation Detail structure.
*
* @param[in] pstRevDetails Pointer to CMP_REVDETAILS_S structure. [N/A]
* @param[in] pstIssuer Issuer Name. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_ID_S* Pointer to CRMF_CERT_ID_S structure. [pstCertID|N/A]
* @retval CRMF_CERT_ID_S* If either of the inputs are NULL or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CRMF_CERT_ID_S* CMP_createCertID (CMP_REVDETAILS_S *pstRevDetails,
                                  SEC_GEN_NAME_S* pstIssuer);




/**
* @defgroup CMP_addCertID
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addCertID (CMP_REVOKERESP_S* pstRevRepContent,
* CRMF_CERT_ID_S* pstCertID);
* @endcode
*
* @par Purpose
* To add a single Certificate ID to the Revocation Response structure.
*
* @par Description
* Adds a single Certificate ID to the Revocation Response structure.
*
* @param[in] pstCertID Pointer to CRMF_CERT_ID_S structure. [N/A]
* @param[out] pstRevRepContent Pointer to CMP_REVOKERESP_S structure. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If adding pstCertID onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addCertID (CMP_REVOKERESP_S* pstRevRepContent,
                          CRMF_CERT_ID_S* pstCertID);




/**
* @defgroup CMP_addCRL
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addCRL (CMP_REVOKERESP_S* pRevRepContent,
* X509_CRL_S* pstCRL);
* @endcode
*
* @par Purpose
* To add a single CRL to the Revocation Response structure.
*
* @par Description
* Adds a single CRL to the Revocation Response structure.
*
* @param[in] pRevRepContent Pointer to CMP_REVOKERESP_S structure. [N/A]
* @param[in] pstCRL Pointer to X509_CRL_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If adding pstCRL onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addCRL (CMP_REVOKERESP_S* pRevRepContent,
                       X509_CRL_S* pstCRL);




/**
* @defgroup CMP_getFirstStatus
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKISTATUS_S* CMP_getFirstStatus (CMP_REVOKERESP_S* pstRevRepCnt);
* @endcode
*
* @par Purpose
* To get the first PKI Status from the list in CMP_REVOKERESP_S structure.
*
* @par Description
* Gets the first PKI Status from the list in CMP_REVOKERESP_S structure.
*
* @param[in] pstRevRepCnt Pointer to CMP_REVOKERESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKISTATUS_S* Pointer to CMP_PKISTATUS_S structure. [pstStatus|N/A]
* @retval CMP_PKISTATUS_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKISTATUS_S* CMP_getFirstStatus (CMP_REVOKERESP_S* pstRevRepCnt);




/**
* @defgroup CMP_getNextStatus
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKISTATUS_S* CMP_getNextStatus (CMP_REVOKERESP_S* pstRevRepCnt);
* @endcode
*
* @par Purpose
* To get the next PKI Status from the list in CMP_REVOKERESP_S structure.
*
* @par Description
* Gets the next PKI Status from the list in CMP_REVOKERESP_S structure.
*
* @param[in] pstRevRepCnt Pointer to CMP_REVOKERESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKISTATUS_S* Pointer to CMP_PKISTATUS_S structure. [pstStatus|N/A]
* @retval CMP_PKISTATUS_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKISTATUS_S* CMP_getNextStatus (CMP_REVOKERESP_S* pstRevRepCnt);




/**
* @defgroup CMP_getFirstCertID
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_CERT_ID_S* CMP_getFirstCertID (CMP_REVOKERESP_S* pstRevRepCnt);
* @endcode
*
* @par Purpose
* To get the First Certificate ID structure from the list in CMP_REVOKERESP_S structure.
*
* @par Description
* Gets the First Certificate ID structure from the list in CMP_REVOKERESP_S structure.
*
* @param[in] pstRevRepCnt Pointer to CMP_REVOKERESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_ID_S* Pointer to CRMF_CERT_ID_S structure. [pstCertID|N/A]
* @retval CRMF_CERT_ID_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CRMF_CERT_ID_S* CMP_getFirstCertID (CMP_REVOKERESP_S* pstRevRepCnt);




/**
* @defgroup CMP_getNextCertID
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_CERT_ID_S* CMP_getNextCertID (CMP_REVOKERESP_S* pstRevRepCnt);
* @endcode
*
* @par Purpose
* To get the Next Certificate ID structure from the list in CMP_REVOKERESP_S structure.
*
* @par Description
* Gets the Next Certificate ID structure from the list in CMP_REVOKERESP_S structure.
*
* @param[in] pstRevRepCnt Pointer to CMP_REVOKERESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_ID_S* Pointer to CRMF_CERT_ID_S structure. [pstCertID|N/A]
* @retval CRMF_CERT_ID_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CRMF_CERT_ID_S* CMP_getNextCertID (CMP_REVOKERESP_S* pstRevRepCnt);




/**
* @defgroup CMP_getFirstCRL
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CRL_S* CMP_getFirstCRL (CMP_REVOKERESP_S* pstRevRepCnt);
* @endcode
*
* @par Purpose
* To get the First CRL from the list in CMP_REVOKERESP_S structure.
*
* @par Description
* Gets the First CRL from the list in CMP_REVOKERESP_S structure.
*
* @param[in] pstRevRepCnt Pointer to CMP_REVOKERESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CRL_S* Pointer to X509_CRL_S structure. [pstCRL|N/A]
* @retval X509_CRL_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CRL_S* CMP_getFirstCRL (CMP_REVOKERESP_S* pstRevRepCnt);




/**
* @defgroup CMP_getNextCRL
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CRL_S* CMP_getNextCRL (CMP_REVOKERESP_S* pstRevRepCnt);
* @endcode
*
* @par Purpose
* To get the next CRL from the list in CMP_REVOKERESP_S structure.
*
* @par Description
* Gets the next CRL from the list in CMP_REVOKERESP_S structure.
*
* @param[in] pstRevRepCnt Pointer to CMP_REVOKERESP_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CRL_S* Pointer to X509_CRL_S structure. [pstCRL|N/A]
* @retval X509_CRL_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_CRL_S* CMP_getNextCRL (CMP_REVOKERESP_S* pstRevRepCnt);




/**
* @defgroup CMP_createCAKeyUpdateAnn
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CAKEYUPDATEANN_S* CMP_createCAKeyUpdateAnn (X509_CERT_S* pstOldwithNew,
* X509_CERT_S* pstNewwithOld,
* X509_CERT_S* pstNewwithNew);
* @endcode
*
* @par Purpose
* To create a CA Key Update Announcement structure.
*
* @par Description
* Creates a CA Key Update Announcement structure. Whenever the CA changes its key pair, it publishes the new certificates
* through this Announcement.
*
* @param[in] pstOldwithNew Pointer to Certificate containing the old CA public key signed with the new private key. [N/A]
* @param[in] pstNewwithOld Pointer to Certificate containing the new CA public key signed with the old private key. [N/A]
* @param[in] pstNewwithNew Pointer to Certificate containing the new CA public key signed with the new private key. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CAKEYUPDATEANN_S* Pointer to CMP_CAKEYUPDATEANN_S structure. [pstCAKeyUpdAnnCnt|N/A]
* @retval CMP_CAKEYUPDATEANN_S* If any of the inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_CAKEYUPDATEANN_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_CAKEYUPDATEANN_S* CMP_createCAKeyUpdateAnn (X509_CERT_S* pstOldwithNew,
                                                X509_CERT_S* pstNewwithOld,
                                                X509_CERT_S* pstNewwithNew);




/**
* @defgroup CMP_getOldWithNewCert
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CERT_S* CMP_getOldWithNewCert (CMP_CAKEYUPDATEANN_S* pstCAKeyUpdAnnCnt);
* @endcode
*
* @par Purpose
* To get the Certificate containing the old CA public key signed with the new private key from CA Key Update Announcement
* structure.
*
* @par Description
* Gets the Certificate containing the old CA public key signed with the new private key from CA Key Update Announcement
* structure.
*
* @param[in] pstCAKeyUpdAnnCnt Pointer to CMP_CAKEYUPDATEANN_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Pointer to X509_CERT_S structure. [pstOldwithNew|N/A]
* @retval X509_CERT_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CERT_S* CMP_getOldWithNewCert (CMP_CAKEYUPDATEANN_S* pstCAKeyUpdAnnCnt);




/**
* @defgroup CMP_getNewWithOldCert
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CERT_S* CMP_getNewWithOldCert (CMP_CAKEYUPDATEANN_S* pstCAKeyUpdAnnCnt);
* @endcode
*
* @par Purpose
* To get the Certificate containing the new CA public key signed with the old private key from CA Key Update
* Announcement structure.
*
* @par Description
* Gets the Certificate containing the new CA public key signed with the old private key from CA Key Update
* Announcement structure.
*
* @param[in] pstCAKeyUpdAnnCnt Pointer to CMP_CAKEYUPDATEANN_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Pointer to X509_CERT_S structure. [pstNewwithOld|N/A]
* @retval X509_CERT_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CERT_S* CMP_getNewWithOldCert (CMP_CAKEYUPDATEANN_S* pstCAKeyUpdAnnCnt);




/**
* @defgroup CMP_getNewWithNewCert
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CERT_S* CMP_getNewWithNewCert (CMP_CAKEYUPDATEANN_S* pstCAKeyUpdAnnCnt);
* @endcode
*
* @par Purpose
* To get the Certificate containing the new CA public key signed with the new private key from CA Key Update
* Announcement structure.
*
* @par Description
* Gets the Certificate containing the new CA public key signed with the new private key from CA Key Update
* Announcement structure.
*
* @param[in] pstCAKeyUpdAnnCnt Pointer to CMP_CAKEYUPDATEANN_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CERT_S* Pointer to X509_CERT_S structure. [pstNewwithNew|N/A]
* @retval X509_CERT_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CERT_S* CMP_getNewWithNewCert (CMP_CAKEYUPDATEANN_S* pstCAKeyUpdAnnCnt);




/**
* @defgroup CMP_createRevocationAnnounce
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_REVOKEANN_S* CMP_createRevocationAnnounce (SEC_UINT32 ulPKIstatus,
* CRMF_CERT_ID_S* pstCertID,
* DATETIME_S* pstWillBeRevokedAt,
* DATETIME_S* pstBadSinceDate,
* Extensions* pCRLDetails);
* @endcode
*
* @par Purpose
* To create a Revocation Announcement Content.
*
* @par Description
* Creates a Revocation Announcement Content. When a CA has revoked, or is about to revoke a particular certificate,
* it may issue the Revocation announcement of this (possibly upcoming) event.
*
* @param[in] ulPKIstatus Any of the values of the enum CERT_RESP_STATUS_E [N/A]
* @param[in] pstCertID Pointer to CRMF_CERT_ID_S structure. [N/A]
* @param[in] pstWillBeRevokedAt Pointer to DATETIME_S structure. [N/A]
* @param[in] pstBadSinceDate Pointer to DATETIME_S structure. [N/A]
* @param[in] pCRLDetails Pointer to Extensions. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_REVOKEANN_S* Pointer to CMP_REVOKEANN_S structure. [CMP_REVOKEANN_S*|N/A]
* @retval CMP_REVOKEANN_S* If any of the inputs are Invalid. [SEC_NULL_PTR|N/A]
* @retval CMP_REVOKEANN_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* The ucUTCSign,ucUTCHour,ucUTCMinute fields of DATETIME_S are not considered in this function.
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_REVOKEANN_S* CMP_createRevocationAnnounce (SEC_UINT32 ulPKIstatus,
                                               CRMF_CERT_ID_S* pstCertID,
                                               DATETIME_S* pstWillBeRevokedAt,
                                               DATETIME_S* pstBadSinceDate,
                                               Extensions* pCRLDetails);




/**
* @defgroup CMP_getStatus
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_getStatus (CMP_REVOKEANN_S* pstRann);
* @endcode
*
* @par Purpose
* To get the PKI Status (CERT_RESP_STATUS_E) from Revocation Announcement.
*
* @par Description
* Gets the PKI Status (CERT_RESP_STATUS_E) from Revocation Announcement.
*
* @param[in] pstRann Pointer to CMP_REVOKEANN_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Valid Certificate Response Status between 0 & 6. [N/A|N/A]
* @retval SEC_UINT32 If input is NULL. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CMP_getStatus (CMP_REVOKEANN_S* pstRann);




/**
* @defgroup CMP_getCertID
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_CERT_ID_S* CMP_getCertID (CMP_REVOKEANN_S* pstRann);
* @endcode
*
* @par Purpose
* To get the Certificate ID from Revocation Announcements.
*
* @par Description
* Gets the Certificate ID from Revocation Announcements.
*
* @param[in] pstRann Pointer to CMP_REVOKEANN_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_ID_S* Pointer to CRMF_CERT_ID_S. [CRMF_CERT_ID_S*|N/A]
* @retval CRMF_CERT_ID_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CRMF_CERT_ID_S* CMP_getCertID (CMP_REVOKEANN_S* pstRann);



/**
* @defgroup CMP_extractRevocationTime
* @ingroup cmpFunctions
* @par Prototype
* @code
* DATETIME_S* CMP_extractRevocationTime (CMP_REVOKEANN_S* pstRann);
* @endcode
*
* @par Purpose
* To Extract the Time at which a new entry will be added to the relevant CRLs from Revocation Announcement.
*
* @par Description
* Extracts the Time at which a new entry will be added to the relevant CRLs from Revocation Announcement.
*
* @param[in] pstRann Pointer to CMP_REVOKEANN_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* Pointer to DATETIME_S structure. [pstDateTime|N/A]
* @retval DATETIME_S* If input is NULL. [SEC_NULL_PTR|N/A]
* @retval DATETIME_S* If Generalized Time to DateTime Conversion Fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* Memory has to be de-allocated after the usage of RevocationTime field.
*
* @par Related Topics
* N/A
*/


PSELINKDLL DATETIME_S* CMP_extractRevocationTime (CMP_REVOKEANN_S* pstRann);



/**
* @defgroup CMP_extractBadDate
* @ingroup cmpFunctions
* @par Prototype
* @code
* DATETIME_S* CMP_extractBadDate (CMP_REVOKEANN_S* pstRann);
* @endcode
*
* @par Purpose
* To Extract the Time at which the Certificate was revoked from Revocation Announcement Content.
*
* @par Description
* Extracts the Time at which the Certificate was revoked from Revocation Announcement Content.
*
* @param[in] pstRann Pointer to CMP_REVOKEANN_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval DATETIME_S* Pointer to DATETIME_S structure. [pstDateTime|N/A]
* @retval DATETIME_S* If input is NULL. [SEC_NULL_PTR|N/A]
* @retval DATETIME_S* If Generalized Time to DateTime Conversion Fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* Memory has to be de-allocated after the usage of Bad Date field.
*
* @par Related Topics
* N/A
*/


PSELINKDLL DATETIME_S* CMP_extractBadDate (CMP_REVOKEANN_S* pstRann);



/**
* @defgroup CMP_getExtnsFromRevocationAnnounce
* @ingroup cmpFunctions
* @par Prototype
* @code
* Extensions* CMP_getExtnsFromRevocationAnnounce (CMP_REVOKEANN_S* pstRann);
* @endcode
*
* @par Purpose
* To get the Extensions from Revocation Announcement Content.
*
* @par Description
* Gets the Extensions from Revocation Announcement Content.
*
* @param[in] pstRann Pointer to CMP_REVOKEANN_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval Extensions* Pointer to SEC_EXTN_S List. [Extensions*|N/A]
* @retval Extensions* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL Extensions* CMP_getExtnsFromRevocationAnnounce (CMP_REVOKEANN_S* pstRann);



/**
* @defgroup CMP_createCRLAnnounce
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_createCRLAnnounce (X509_CRL_S* pstCRL);
* @endcode
*
* @par Purpose
* To create a CRL Announcement Content List.
*
* @par Description
* Creates a CRL Announcement Content List. When a CA issues a new CRL (or set of CRLs) this method can be used to
* announce this event.
*
* @param[in] pstCRL Pointer to X509_CRL_S structure. [N/A]
* @param[out] N/A N/A [N/A
*
* @retval SEC_List_S* Pointer to CRL Announcement List. [pCRLAnnCnt|N/A]
* @retval SEC_List_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* CMP_createCRLAnnounce (X509_CRL_S* pstCRL);



/**
* @defgroup CMP_addCertList
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addCertList (SEC_List_S* pstCRLAnnCnt,
* X509_CRL_S* pstCRL);
* @endcode
*
* @par Purpose
* To add a CRL to CRL Announcement List.
*
* @par Description
* Adds a CRL to CRL Announcement List.
*
* @param[in] pstCRL Pointer to X509_CRL_S structure. [N/A]
* @param[out] pstCRLAnnCnt Pointer to CRL Announcement List. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If adding X509_CRL_S onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addCertList (SEC_List_S* pstCRLAnnCnt,
                            X509_CRL_S* pstCRL);




/**
* @defgroup CMP_getFirstCertList
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CRL_S* CMP_getFirstCertList (SEC_List_S* pstCRLAnnCnt);
* @endcode
*
* @par Purpose
* To get first CRL from CRL Announcement Content List.
*
* @par Description
* Gets first CRL from CRL Announcement Content List.
*
* @param[in] pstCRLAnnCnt Pointer to SEC_List_S. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CRL_S* Pointer to X509_CRL_S structure. [pstCertList|N/A]
* @retval X509_CRL_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL X509_CRL_S* CMP_getFirstCertList (SEC_List_S* pstCRLAnnCnt);



/**
* @defgroup CMP_getNextCertList
* @ingroup cmpFunctions
* @par Prototype
* @code
* X509_CRL_S* CMP_getNextCertList (SEC_List_S* pstCRLAnnCnt);
* @endcode
*
* @par Purpose
* To get a CRL from CRL Announcement List.
*
* @par Description
* Gets a CRL from CRL Announcement List.
*
* @param[in] pstCRLAnnCnt Pointer to SEC_List_S. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval X509_CRL_S* Pointer to X509_CRL_S structure. [pstCertList|N/A]
* @retval X509_CRL_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL X509_CRL_S* CMP_getNextCertList (SEC_List_S* pstCRLAnnCnt);



/**
* @defgroup CMP_createChallenge
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CHALLENGE_S* CMP_createChallenge (CMP_PKIHDR_S* pstPKIHdr,
* SEC_UINT32 ulAlgID,
* SEC_UINT32 ulOWFAlgID,
* SEC_UINT32 ulChallLen,
* SEC_BOOL   bFirstChall,
* SEC_UCHAR* pucSymmKey,
* SEC_UINT32 ulSymmKeyLen,
* SEC_UCHAR* pucInitVect,
* SEC_UINT32 ulInitVectLen);
* @endcode
*
* @par Purpose
* To create CMP_CHALLENGE_S structure.
*
* @par Description
* Creates CMP_CHALLENGE_S structure.This method can be used in case of encryption keys, where in the end entity can be
* required to decrypt a value in order to prove the possession of Private Key and is achieved by RA/CA issuing a random
* challenge.
*
* @param[in] pstPKIHdr Pointer to CMP_PKIHDR_S structure. [N/A]
* @param[in] ulAlgID Symmetric Algorithm for encryption. [N/A]
* @param[in] ulOWFAlgID Hash Algorithm. [N/A]
* @param[in] ulChallLen Length of the Challenge required. [N/A]
* @param[in] bFirstChall Boolean (True/False),MUST be present in the first Challenge and optional otherwise. User can
* send a negative value if not intended to be sent. [N/A]
* @param[in] pucSymmKey Symmetric Key for encryption. [N/A]
* @param[in] ulSymmKeyLen Length of the Symmetric Key. [N/A]
* @param[in] pucInitVect InitVector required for encryption in case of CBC mode SymmAlg. [N/A]
* @param[in] ulInitVectLen Length of the InitVector. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CHALLENGE_S* Pointer to CMP_CHALLENGE_S structure. [pstChallenge|N/A]
* @retval CMP_CHALLENGE_S* If any of the inputs are Invalid or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
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

PSELINKDLL CMP_CHALLENGE_S* CMP_createChallenge (CMP_PKIHDR_S* pstPKIHdr,
                                      SEC_UINT32 ulAlgID,
                                      SEC_UINT32 ulOWFAlgID,
                                      SEC_UINT32 ulChallLen,
                                      SEC_BOOL   bFirstChall,
                                      SEC_UCHAR* pucSymmKey,
                                      SEC_UINT32 ulSymmKeyLen,
                                      SEC_UCHAR* pucInitVect,
                                      SEC_UINT32 ulInitVectLen);




/**
* @defgroup CMP_createPOPDecryptKeyChallenge
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_createPOPDecryptKeyChallenge (CMP_CHALLENGE_S* pstChall);
* @endcode
*
* @par Purpose
* To create a POP DecryptKey Challenge List.
*
* @par Description
* Creates a POP DecryptKey Challenge List. The CA/RA calls this API to generate Challenge when an end entity is
* required to provide the proof of possession by decrypting the generated challenge sent by CA/RA.
*
* @param[in] pstChall Pointer to CMP_CHALLENGE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to POPODecKeyChallCnt List. [pPOPDecKeyChallCnt|N/A]
* @retval SEC_List_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
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


PSELINKDLL SEC_List_S* CMP_createPOPDecryptKeyChallenge (CMP_CHALLENGE_S* pstChall);




/**
* @defgroup CMP_addChallenge
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addChallenge (SEC_List_S* pPOPODecKeyChallCnt,
* CMP_CHALLENGE_S* pstChall);
* @endcode
*
* @par Purpose
* To add a Challenge to POP DecryptKeyChallengeCnt List.
*
* @par Description
* Adds a Challenge to POP DecryptKeyChallengeCnt List. Challenge can be added in order to prove the possession of Private
* Key with one Challenge per encryption key certification request.
*
* @param[in] pstChall Pointer to CMP_CHALLENGE_S structure. [N/A]
* @param[out] pPOPODecKeyChallCnt Pointer to CMP_POPODecKeyChallCnt List. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addChallenge (SEC_List_S* pPOPODecKeyChallCnt,
                             CMP_CHALLENGE_S* pstChall);



/**
* @defgroup CMP_verifyChallenge
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_verifyChallenge ( SEC_UINT32 ulChallengeIndex,
* SEC_List_S* pPOPODecKeyChallCnt,
* SEC_GEN_NAME_S* pSenderName,
* SEC_UINT32 ulAlgID,
* SEC_UCHAR* pucSymmKey,
* SEC_UINT32 ulSymmKeyLen,
* SEC_UCHAR* pucInitVect,
* SEC_UINT32 ulInitVectLen);
* @endcode
*
* @par Purpose
* To verify the Challenge.
*
* @par Description
* This method can be used to verify the Challenge. This can be used for verifying the Challenge in case the EE and CA/RA
* share the Secret Key (Symmetric Key).
*
* @param[in] ulChallengeIndex Index to extract CMP_CHALLENGE_S structure. [N/A]
* @param[in] pPOPODecKeyChallCnt Pointer to a list of Key Challenge structures(CMP_CHALLENGE_S). [N/A]
* @param[in] pSenderName Pointer to SEC_GEN_NAME_S structure. [N/A]
* @param[in] ulAlgID Algorithm for decryption. [N/A]
* @param[in] pucSymmKey Symmetric Key for decryption. [N/A]
* @param[in] ulSymmKeyLen Length of the Symmetric Key. [N/A]
* @param[in] pucInitVect Initialization Vector. [N/A]
* @param[in] ulInitVectLen Length of Initialization Vector required in case of CBC mode Algorithims. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 In case of memcmp failure. [SEC_ERR|N/A]
* @retval SEC_UINT32 In case of memory allocation failure. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 Error Code returned by CRYPT_digest(). [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_verifyChallenge ( SEC_UINT32 ulChallengeIndex,
                                 SEC_List_S* pPOPODecKeyChallCnt,
                                 SEC_GEN_NAME_S* pSenderName,
                                 SEC_UINT32 ulAlgID,
                                 SEC_UCHAR* pucSymmKey,
                                 SEC_UINT32 ulSymmKeyLen,
                                 SEC_UCHAR* pucInitVect,
                                 SEC_UINT32 ulInitVectLen);




/**
* @defgroup CMP_getFirstChallenge
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CHALLENGE_S* CMP_getFirstChallenge (SEC_List_S* pPOPODecKeyChallCnt);
* @endcode
*
* @par Purpose
* To get the first Challenge from POPODecKeyChallContent List.
*
* @par Description
* Gets the first Challenge from POPODecKeyChallContent List.
*
* @param[in] pPOPDecKeyChallCnt Pointer to POPODecKeyChallContent List. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CHALLENGE_S* Pointer to CMP_CHALLENGE_S structure. [pstChallenge|N/A]
* @retval CMP_CHALLENGE_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_CHALLENGE_S* CMP_getFirstChallenge (SEC_List_S* pPOPODecKeyChallCnt);



/**
* @defgroup CMP_getNextChallenge
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CHALLENGE_S* CMP_getNextChallenge (SEC_List_S* pPOPODecKeyChallCnt);
* @endcode
*
* @par Purpose
* To get the next Challenge from POPODecKeyChallContent List.
*
* @par Description
* Gets the next Challenge from POPODecKeyChallContent List.
*
* @param[in] pPOPDecKeyChallCnt Pointer to POPODecKeyChallContent List. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CHALLENGE_S* Pointer to CMP_CHALLENGE_S structure. [pstChallenge|N/A]
* @retval CMP_CHALLENGE_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_CHALLENGE_S* CMP_getNextChallenge (SEC_List_S* pPOPODecKeyChallCnt);




/**
* @defgroup CMP_getChallengeVal
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_RAND_S* CMP_getChallengeVal (CMP_CHALLENGE_S* pstChall,
* SEC_UINT32 ulAlgID,
* const SEC_UCHAR * pucSymmKey,
* SEC_UINT32 ulSymmKeyLen,
* const SEC_UCHAR * pucInitVect,
* SEC_UINT32 ulInitVectLen);
* @endcode
*
* @par Purpose
* To get the randomly generated Challenge Value from CMP_CHALLENGE_S structure.
*
* @par Description
* Gets the randomly generated Challenge Value from CMP_CHALLENGE_S structure.
*
* @param[in] pstChall Pointer to CMP_CHALLENGE_S structure. [N/A]
* @param[in] ulAlgID Algorithm for decryption. [N/A]
* @param[in] pucSymmKey Symmetric Key for decryption. [N/A]
* @param[in] ulSymmKeyLen Length of the Symmetric Key. [N/A]
* @param[in] pucInitVect Initialization Vector. [N/A]
* @param[in] ulInitVectLen Length of Initialization Vector required in case of CBC mode Algorithims. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_RAND_S* Decrypted Challenge Value. [CMP_RAND_S*|N/A]
* @retval CMP_RAND_S* If input is NULL or memory allocation fails. [SEC_NULL_PTR|N/A]
* @retval CMP_RAND_S* If decryption fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_RAND_S* CMP_getChallengeVal (CMP_CHALLENGE_S* pstChall,
                                 SEC_UINT32 ulAlgID,
                                 const SEC_UCHAR * pucSymmKey,
                                 SEC_UINT32 ulSymmKeyLen,
                                 const SEC_UCHAR * pucInitVect,
                                 SEC_UINT32 ulInitVectLen);




/**
* @defgroup CMP_getWitness
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* CMP_getWitness (CMP_CHALLENGE_S* pstChall);
* @endcode
*
* @par Purpose
* To Extract witness from CMP_CHALLENGE_S structure.
*
* @par Description
* Extracts witness from CMP_CHALLENGE_S structure.
*
* @param[in] pstChall Pointer to CMP_CHALLENGE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* WitNess, pointer to SEC_AsnOcts_S. [SEC_AsnOcts_S*|N/A]
* @retval SEC_AsnOcts_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnOcts_S* CMP_getWitness (CMP_CHALLENGE_S* pstChall);



/**
* @defgroup CMP_getOWF
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_getOWF (CMP_CHALLENGE_S* pstChall);
* @endcode
*
* @par Purpose
* To get the OWF(One Way Function) from CMP_CHALLENGE_S structure.
*
* @par Description
* Gets the OWF(One Way Function) from CMP_CHALLENGE_S structure.
*
* @param[in] pstChall Pointer to CMP_CHALLENGE_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Valid Digest Algorithm. [N/A|N/A]
* @retval SEC_UINT32 If input is NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If not a valid Algorithm. [CID_UNKNOWN|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_getOWF (CMP_CHALLENGE_S* pstChall);




/**
* @defgroup CMP_getRand
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_getRand (CMP_RAND_S* pstRand);
* @endcode
*
* @par Purpose
* To get the Random Integer.
*
* @par Description
* Gets the Random Integer.
*
* @param[in] pstRand Pointer to CMP_RAND_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Random Integer. [N/A|N/A]
* @retval SEC_UINT32 If the input is NULL. [SEC_ERR_INVALID_ARG|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_getRand (CMP_RAND_S* pstRand);



/**
* @defgroup CMP_createPOPDecryptKeyResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_createPOPDecryptKeyResp (SEC_UINT32 ulRandInt);
* @endcode
*
* @par Purpose
* To create a POP DecryptKey Response List.
*
* @par Description
* Creates a POP DecryptKey Response List. The retrieved Integer from the POP Challenge is returned to the Sender of the
* corresponding Challenge. There must be one Integer per encryption key certification request.
*
* @param[in] ulRandInt Randomly Generated Integer. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to POP Challenge Response List. [SEC_List_S*|N/A]
* @retval SEC_List_S* If inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
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


PSELINKDLL SEC_List_S* CMP_createPOPDecryptKeyResp (SEC_UINT32 ulRandInt);




/**
* @defgroup CMP_addRandom
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addRandom (SEC_List_S* pPOPODecKeyRespCnt,
* SEC_UINT32 ulRandInt);
* @endcode
*
* @par Purpose
* To add the retrieved Random Integer from the POP Challenge to the POP Decrypt Response List.
*
* @par Description
* Adds the retrieved Random Integer from the POP Challenge to the POP Decrypt Response List.
*
* @param[in] ulRandInt Randomly Generated Integer. [N/A]
* @param[out] pPOPODecKeyRespCnt Pointer to CMP_POPODecKeyRespCnt structure. [N/A]
*
* @retval SEC_UINT32 Upon success. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If adding ulRandInt onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CMP_addRandom (SEC_List_S* pPOPODecKeyRespCnt,
                          SEC_UINT32 ulRandInt);




/**
* @defgroup CMP_createInfoTypeAndValue
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_INFOTYPEVAL_S* CMP_createInfoTypeAndValue (SEC_UINT32 ulInfoID,
* SEC_VOID* pstInfoValue);
* @endcode
*
* @par Purpose
* To create a Information Type and Value Structure.
*
* @par Description
* Creates a Information Type and Value Structure. This can be used to create a General Message or a General Response.
*
* @param[in] ulInfoID InfoType can be any of the following types\n
* CID_CAPROTENCCERT (pstInfoValue - Pointer to X509_CERT_S)\n
* CID_SIGNKEYPAIRTYPES (pstInfoValue - Pointer to List of Algo Identifiers)\n
* CID_ENCKEYPAIRTYPES (pstInfoValue - Pointer to List of Algo Identifiers)\n
* CID_PREFERREDSYMMALG (pstInfoValue - Pointer to SEC_ALG_IDENTIFIER_S)\n
* CID_CAKEYUPDATEINFO (pstInfoValue - Pointer to CMP_CAKEYUPDATEANN_S)\n
* CID_CURRENTCRL (pstInfoValue - Pointer to X509_CRL_S) [N/A]
* @param[in] pstInfoValue Pointer to InfoVal. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_INFOTYPEVAL_S* Pointer to CMP_INFOTYPEVAL_S structure. [pstInfoTypeAndValue|N/A]
* @retval CMP_INFOTYPEVAL_S* If input parameters are NULL or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
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


PSELINKDLL CMP_INFOTYPEVAL_S* CMP_createInfoTypeAndValue (SEC_UINT32 ulInfoID,
                                               SEC_VOID* pstInfoValue);




/**
* @defgroup CMP_createGenMsg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_createGenMsg (CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);
* @endcode
*
* @par Purpose
* To create a General Message List.
*
* @par Description
* Creates a General Message List. The end entity sends general message to the PKI requesting details which will be
* required for later PKI management operations.
*
* @param[in] pstInfoTypeAndVal Pointer to CMP_INFOTYPEVAL_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to General Message List. [pGenMsgCnt|N/A]
* @retval SEC_List_S* If input parameter is NULL or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_List_S* CMP_createGenMsg (CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);




/**
* @defgroup CMP_createGenResp
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_createGenResp (CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);
* @endcode
*
* @par Purpose
* To create a General Response List.
*
* @par Description
* Creates a General Response List. RA/CA responds with General Response for the General Message sent by the EE.
*
* @param[in] pstInfoTypeAndVal Pointer to CMP_INFOTYPEVAL_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to General Response List. [pGenRepCnt|N/A]
* @retval SEC_List_S* If input parameter is NULL or memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_List_S* CMP_createGenResp (CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);




/**
* @defgroup CMP_addInfoTypeAndValue
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32 CMP_addInfoTypeAndValue (SEC_List_S* pList,
* CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);
* @endcode
*
* @par Purpose
* To add the CMP_INFOTYPEVAL_S structure.
*
* @par Description
* Adds the CMP_INFOTYPEVAL_S structure. Input List is a General Message List or a General Response List.
*
* @param[in] pstInfoTypeAndVal Pointer to CMP_INFOTYPEVAL_S structure. [N/A]
* @param[out] pList Pointer to List. [N/A]
*
* @retval SEC_UINT32 Upon successful completion. [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If inputs are NULL. [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails. [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If adding InfoTypeAndVal onto the List fails. [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CMP_addInfoTypeAndValue (SEC_List_S* pList,
                                    CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);




/**
* @defgroup CMP_getFirstInfoTypeAndValue
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_INFOTYPEVAL_S* CMP_getFirstInfoTypeAndValue (SEC_List_S* pList);
* @endcode
*
* @par Purpose
* To get the First CMP_INFOTYPEVAL_S structure from GenMsgCnt List or GenRepCnt List.
*
* @par Description
* Gets the First CMP_INFOTYPEVAL_S structure from GenMsgCnt List or GenRepCnt List.
*
* @param[in] pList Pointer to List. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_INFOTYPEVAL_S* Pointer to CMP_INFOTYPEVAL_S structure. [pstInfoTypeAndVal|N/A]
* @retval CMP_INFOTYPEVAL_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_INFOTYPEVAL_S* CMP_getFirstInfoTypeAndValue (SEC_List_S* pList);



/**
* @defgroup CMP_getNextInfoTypeAndValue
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_INFOTYPEVAL_S* CMP_getNextInfoTypeAndValue (SEC_List_S* pList);
* @endcode
*
* @par Purpose
* To get the next CMP_INFOTYPEVAL_S structure from GenMsgCnt List or GenRepCnt List.
*
* @par Description
* Gets the next CMP_INFOTYPEVAL_S structure from GenMsgCnt List or GenRepCnt List.
*
* @param[in] pList Pointer to List. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_INFOTYPEVAL_S* Pointer to CMP_INFOTYPEVAL_S structure. [pstInfoTypeAndVal|N/A]
* @retval CMP_INFOTYPEVAL_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_INFOTYPEVAL_S* CMP_getNextInfoTypeAndValue (SEC_List_S* pList);




/**
* @defgroup CMP_getInfoType
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_AsnOcts_S* CMP_getInfoType (CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);
* @endcode
*
* @par Purpose
* To get the Information Type from CMP_INFOTYPEVAL_S structure.
*
* @par Description
* Gets the Information Type from CMP_INFOTYPEVAL_S structure.
*
* @param[in] pstInfoTypeAndVal Pointer to CMP_INFOTYPEVAL_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnOcts_S* Pointer to SEC_AsnOcts_S. [InfoType|N/A]
* @retval SEC_AsnOcts_S* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_AsnOcts_S* CMP_getInfoType (CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);




/**
* @defgroup CMP_getInfoVal
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID* CMP_getInfoVal (CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);
* @endcode
*
* @par Purpose
* To get Information Value from CMP_INFOTYPEVAL_S structure.
*
* @par Description
* Gets Information Value from CMP_INFOTYPEVAL_S structure.
*
* @param[in] pstInfoTypeAndVal Pointer to CMP_INFOTYPEVAL_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Pointer to InfoValue (Refer to CMP_createInfoTypeAndValue()). [InfoVal|N/A]
* @retval SEC_VOID* If the input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID* CMP_getInfoVal (CMP_INFOTYPEVAL_S* pstInfoTypeAndVal);




/**
* @defgroup CMP_createErrMsg
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_ERRMSG_S* CMP_createErrMsg (CMP_PKISTATUS_S* pstPKIStatus,
* SEC_List_S* pErrDetails,
* SEC_UINT32* pulErrCode);
* @endcode
*
* @par Purpose
* To create a CMP_ERRMSG_S structure.
*
* @par Description
* This method is used to create a CMP_ERRMSG_S structure. Even if the originator completely specifies the contents of
* a certificate it requires, a CA is free to modify fields within the certificate actually issued. If the modified
* certificate is unacceptable to the requester, an Error Message can be sent.
*
* @param[in] pstPKIStatus Pointer to CMP_PKISTATUS_S structure. [N/A]
* @param[in] pErrDetails Pointer to List of ErrorDetails (List Of Octet Strings). [N/A]
* @param[in] pulErrCode Pointer to Error Code as given in FAILURE REASONS. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_ERRMSG_S* Pointer to CMP_ERRMSG_S structure. [pstErrMsgCnt|N/A]
* @retval CMP_ERRMSG_S* If any of the inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_ERRMSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
* @retval CMP_ERRMSG_S* If ulStatus in PKIStatus is not "REJECTION". [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_ERRMSG_S* CMP_createErrMsg (CMP_PKISTATUS_S* pstPKIStatus,
                                SEC_List_S* pErrDetails,
                                SEC_UINT32* pulErrCode);




/**
* @defgroup CMP_getErrCode
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UINT32* CMP_getErrCode (CMP_ERRMSG_S* pstErrMsgCnt);
* @endcode
*
* @par Purpose
* To get Error Code from CMP_ERRMSG_S.
*
* @par Description
* Gets Error Code from CMP_ERRMSG_S.
*
* @param[in] pstErrMsgCnt Pointer to CMP_ERRMSG_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32* Pointer to (unsigned long) ErrorCode. [SEC_UINT32*|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32* CMP_getErrCode (CMP_ERRMSG_S* pstErrMsgCnt);




/**
* @defgroup CMP_getErrDetails
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* CMP_getErrDetails (CMP_ERRMSG_S* pstErrMsgCnt);
* @endcode
*
* @par Purpose
* To get Error details from Error Message.
*
* @par Description
* Gets Error details from Error Message.
*
* @param[in] pstErrMsgCnt Pointer to CMP_ERRMSG_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to Error Detail List. [SEC_List_S*|N/A]
* @retval SEC_List_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_List_S* CMP_getErrDetails (CMP_ERRMSG_S* pstErrMsgCnt);




/**
* @defgroup CMP_getPKIStatusInfo
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKISTATUS_S* CMP_getPKIStatusInfo (CMP_ERRMSG_S* pstErrMsgCnt);
* @endcode
*
* @par Purpose
* To get PKI Status from Error Message.
*
* @par Description
* Gets PKI Status from Error Message.
*
* @param[in] pstErrMsgCnt Pointer to CMP_ERRMSG_S structure. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKISTATUS_S* Pointer to CMP_PKISTATUS_S structure. [pPKIStatusinfo|N/A]
* @retval CMP_PKISTATUS_S* If input is NULL. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_PKISTATUS_S* CMP_getPKIStatusInfo (CMP_ERRMSG_S* pstErrMsgCnt);




/**
* @defgroup CMP_freePKIMsg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freePKIMsg (CMP_PKIMSG_S* pstPKIMsg);
* @endcode
*
* @par Purpose
* To free the PKI Message structure.
*
* @par Description
* This function is used to free the PKI Message structure.
*
* @param[in] pstPKIMsg Pointer to CMP_PKIMSG_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freePKIMsg (CMP_PKIMSG_S* pstPKIMsg);




/**
* @defgroup CMP_freePKIHdr
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freePKIHdr (CMP_PKIHDR_S* pstPKIHdr);
* @endcode
*
* @par Purpose
* To free the PKI Header structure.
*
* @par Description
* This function is used to free the PKI Header structure.
*
* @param[in] pstPKIHdr Pointer to CMP_PKIHDR_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freePKIHdr (CMP_PKIHDR_S* pstPKIHdr);




/**
* @defgroup CMP_freePKIBody
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freePKIBody (CMP_PKIBODY_S* pstPKIBody);
* @endcode
*
* @par Purpose
* To free the PKI Body structure.
*
* @par Description
* This function is used to free the PKI Body structure.
*
* @param[in] pstPKIBody Pointer to CMP_PKIBODY_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freePKIBody (CMP_PKIBODY_S* pstPKIBody);




/**
* @defgroup CMP_freeCertRepMsg
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeCertRepMsg (CMP_CERTRESPMSG_S* pstCertRepMessage);
* @endcode
*
* @par Purpose
* To free the Certificate Response Message.
*
* @par Description
* This function is used to free the Certificate Response Message.
*
* @param[in] pstCertRepMessage Pointer to CMP_CERTRESPMSG_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeCertRepMsg (CMP_CERTRESPMSG_S* pstCertRepMessage);




/**
* @defgroup CMP_freeRevReqContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeRevReqContent(SEC_List_S* pRevReqContent);
* @endcode
*
* @par Purpose
* To free the Revocation Request List.
*
* @par Description
* This function is used to free the Revocation Request List.
*
* @param[in] pRevReqContent Pointer to Revocation Request List to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeRevReqContent(SEC_List_S* pRevReqContent);




/**
* @defgroup CMP_freeRevRepContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeRevRepContent (CMP_REVOKERESP_S* pstRevRepContent);
* @endcode
*
* @par Purpose
* To free the CMP_REVOKERESP_S structure.
*
* @par Description
* This function is used to free the CMP_REVOKERESP_S structure.
*
* @param[in] pstRevRepContent Pointer to CMP_REVOKERESP_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeRevRepContent (CMP_REVOKERESP_S* pstRevRepContent);




/**
* @defgroup CMP_freeKeyRecRepContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeKeyRecRepContent(CMP_KEYRECOVERYRESP_S* pstKeyRecRepContent);
* @endcode
*
* @par Purpose
* To free the Key Recovery Response structure.
*
* @par Description
* This function is used to free the Key Recovery Response structure.
*
* @param[in] pstKeyRecRepContent Pointer to CMP_KEYRECOVERYRESP_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeKeyRecRepContent(CMP_KEYRECOVERYRESP_S* pstKeyRecRepContent);




/**
* @defgroup CMP_freeCAKeyUpdAnnCnt
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeCAKeyUpdAnnCnt (CMP_CAKEYUPDATEANN_S* pstCAKeyUpdAnnounce);
* @endcode
*
* @par Purpose
* To free the CMP_CAKEYUPDATEANN_S structure.
*
* @par Description
* This function is used to free the CMP_CAKEYUPDATEANN_S structure.
*
* @param[in] pstCAKeyUpdAnnounce Pointer to CMP_CAKEYUPDATEANN_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeCAKeyUpdAnnCnt (CMP_CAKEYUPDATEANN_S* pstCAKeyUpdAnnounce);




/**
* @defgroup CMP_freeCRLAnnContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeCRLAnnContent (SEC_List_S* pCRLAnnounce);
* @endcode
*
* @par Purpose
* To free the CMP_CRLAnnCnt List.
*
* @par Description
* This function is used to free the CMP_CRLAnnCnt List.
*
* @param[in] pCRLAnnounce Pointer to X509_CRL_S List to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeCRLAnnContent (SEC_List_S* pCRLAnnounce);




/**
* @defgroup CMP_freeCertTemplate
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeCertTemplate (CRMF_CERT_TEMPLATE_S* pstCertTemplate);
* @endcode
*
* @par Purpose
* To free CRMF_CERT_TEMPLATE_S structure.
*
* @par Description
* This function is used to free CRMF_CERT_TEMPLATE_S structure.
*
* @param[in] pstCertTemplate Pointer to CRMF_CERT_TEMPLATE_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeCertTemplate (CRMF_CERT_TEMPLATE_S* pstCertTemplate);




/**
* @defgroup CMP_freePOPODecKeyChallCnt
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freePOPODecKeyChallCnt (SEC_List_S* pPOPODecKeyChallCnt);
* @endcode
*
* @par Purpose
* To free the CMP_POPODecKeyChallCnt List.
*
* @par Description
* This function is used to free the CMP_POPODecKeyChallCnt List.
*
* @param[in] pPOPODecKeyChallCnt Pointer to the list of CMP_CHALLENGE_S structures, which is to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freePOPODecKeyChallCnt (SEC_List_S* pPOPODecKeyChallCnt);




/**
* @defgroup CMP_freeRevAnnCnt
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeRevAnnCnt(CMP_REVOKEANN_S* pstRann);
* @endcode
*
* @par Purpose
* To free the CMP_REVOKEANN_S Structure.
*
* @par Description
* This function is used to free the CMP_REVOKEANN_S Structure.
*
* @param[in] pstRann Pointer to CMP_REVOKEANN_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeRevAnnCnt(CMP_REVOKEANN_S* pstRann);




/**
* @defgroup CMP_freePOPODecKeyRespCnt
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freePOPODecKeyRespCnt (SEC_List_S* pPOPODecKeyRespCnt);
* @endcode
*
* @par Purpose
* To free the CMP_POPODecKeyRespCnt List.
*
* @par Description
* This function is used to free the CMP_POPODecKeyRespCnt List.
*
* @param[in] pPOPODecKeyRespCnt Pointer to CMP_POPODecKeyRespCnt structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freePOPODecKeyRespCnt (SEC_List_S* pPOPODecKeyRespCnt);




/**
* @defgroup CMP_freeErrMsgCnt
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeErrMsgCnt (CMP_ERRMSG_S* pstErrMsgCnt);
* @endcode
*
* @par Purpose
* To free the CMP_ERRMSG_S structure.
*
* @par Description
* This function is used to free the CMP_ERRMSG_S structure.
*
* @param[in] pstErrMsgCnt Pointer to CMP_ERRMSG_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeErrMsgCnt (CMP_ERRMSG_S* pstErrMsgCnt);




/**
* @defgroup CMP_freeGenMsgCnt
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeGenMsgCnt (SEC_List_S* pGenMsgCnt);
* @endcode
*
* @par Purpose
* To free the General Message list.
*
* @par Description
* This function is used to free the General Message list.
*
* @param[in] pGenMsgCnt Pointer to CMP_GenMsgCnt List to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeGenMsgCnt (SEC_List_S* pGenMsgCnt);




/**
* @defgroup CMP_freeGenRepCnt
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeGenRepCnt (SEC_List_S* pGenRepCnt);
* @endcode
*
* @par Purpose
* To free the CMP_GenRepCnt List.
*
* @par Description
* This function is used to free the CMP_GenRepCnt List.
*
* @param[in] pGenRepCnt Pointer to CMP_GenRepCnt structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeGenRepCnt (SEC_List_S* pGenRepCnt);



/**
* @defgroup CMP_freeRevDetails
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeRevDetails (CMP_REVDETAILS_S* pstRevDetails);
* @endcode
*
* @par Purpose
* To free the CMP_REVDETAILS_S structure.
*
* @par Description
* This function is used to free the CMP_REVDETAILS_S structure.
*
* @param[in] pstRevDetails Pointer to CMP_REVDETAILS_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeRevDetails (CMP_REVDETAILS_S* pstRevDetails);



/**
* @defgroup CMP_freeCertifiedKeyPair
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeCertifiedKeyPair (CMP_KEYPAIR_S* pstCertifiedKeyPair);
* @endcode
*
* @par Purpose
* To free the CMP_KEYPAIR_S structure.
*
* @par Description
* This function is used to free the CMP_KEYPAIR_S structure.
*
* @param[in] pstCertifiedKeyPair Pointer to CMP_KEYPAIR_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeCertifiedKeyPair (CMP_KEYPAIR_S* pstCertifiedKeyPair);



/**
* @defgroup CMP_freeChallenge
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeChallenge (CMP_CHALLENGE_S* pstChallenge);
* @endcode
*
* @par Purpose
* To free the CMP_CHALLENGE_S structure.
*
* @par Description
* This function is used to free the CMP_CHALLENGE_S structure.
*
* @param[in] pstChallenge Pointer to CMP_CHALLENGE_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeChallenge (CMP_CHALLENGE_S* pstChallenge);



/**
* @defgroup CMP_freePKIFreeText
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freePKIFreeText (SEC_List_S* pPKIFreeText);
* @endcode
*
* @par Purpose
* To free the List.
*
* @par Description
* This function is used to free the List.
*
* @param[in] pPKIFreeText Pointer to the list of SEC_AsnOcts_S structures which is to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freePKIFreeText (SEC_List_S* pPKIFreeText);



/**
* @defgroup CMP_freePKIStatusInfo
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freePKIStatusInfo (CMP_PKISTATUS_S* pstPKIStatusInfo);
* @endcode
*
* @par Purpose
* To free the CMP_PKISTATUS_S structure.
*
* @par Description
* This function is used to free the CMP_PKISTATUS_S structure.
*
* @param[in] pstPKIStatusInfo Pointer to CMP_PKISTATUS_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freePKIStatusInfo (CMP_PKISTATUS_S* pstPKIStatusInfo);



/**
* @defgroup CMP_freeCertResponse
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeCertResponse (CMP_CERTRESP_S* pstCertResponse);
* @endcode
*
* @par Purpose
* To free the CMP_CERTRESP_S structure.
*
* @par Description
* This function is used to free the CMP_CERTRESP_S structure.
*
* @param[in] pstCertResponse Pointer to CMP_CERTRESP_S to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeCertResponse (CMP_CERTRESP_S* pstCertResponse);



/**
* @defgroup CMP_freeCertResponse_ex
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeCertResponse_ex (CMP_CERTRESP_S* pstCertResponse);
* @endcode
*
* @par Purpose
* To free the CMP_CERTRESP_S structure.
*
* @par Description
* This function is used to free the CMP_CERTRESP_S structure.
*
* @param[in] pstCertResponse Pointer to CMP_CERTRESP_S to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL  SEC_VOID CMP_freeCertResponse_ex (CMP_CERTRESP_S* pstCertResponse);

/**
* @defgroup CMP_freeInfoTypeAndValue
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_VOID CMP_freeInfoTypeAndValue (CMP_INFOTYPEVAL_S *pstInfoTypeAndVal);
* @endcode
*
* @par Purpose
* To free the CMP_INFOTYPEVAL_S structure.
*
* @par Description
* This function is used to free the CMP_INFOTYPEVAL_S structure.
*
* @param[in] pstInfoTypeAndVal Pointer to CMP_INFOTYPEVAL_S structure to be freed. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_VOID CMP_freeInfoTypeAndValue (CMP_INFOTYPEVAL_S *pstInfoTypeAndVal);




/**
* @defgroup CMP_encodeRand
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_UCHAR* CMP_encodeRand (CMP_RAND_S* pstRand,
* SEC_UINT32* pulLength);
* @endcode
*
* @par Purpose
* To encode the Rand structure into DER Format.
*
* @par Description
* This method encodes the Rand structure into DER Format.
*
* @param[in] pstRand Pointer to CMP_RAND_S structure. [N/A]
* @param[out] pulLength Length of the data Encoded. [N/A]
*
* @retval SEC_UCHAR* Pointer to Encoded Rand. [pucEncodedRand|N/A]
* @retval SEC_UCHAR* If memory allocation fails. [SEC_NULL_PTR|N/A]
* @retval SEC_UCHAR* If encode fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UCHAR* CMP_encodeRand (CMP_RAND_S* pstRand,
                           SEC_UINT32* pulLength);




/**
* @defgroup CMP_decodeRand
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_RAND_S* CMP_decodeRand (SEC_UCHAR* pucEncodedRand,
* SEC_UINT32 ulEncodedRandLength,
* SEC_UINT32* pulBytesDecoded);
* @endcode
*
* @par Purpose
* To decode the encoded CMP_RAND_S structure.
*
* @par Description
* This method can be used to decode the encoded CMP_RAND_S structure.
*
* @param[in] pucEncodedRand Pointer to DER encoded Rand. [N/A]
* @param[in] ulEncodedLength Length of the Encoded Rand. [N/A]
* @param[out] pulBytesDecoded Pointer to Bytes Decoded. [N/A]
*
* @retval CMP_RAND_S* Pointer to CMP_RAND_S structure. [pstResult|N/A]
* @retval CMP_RAND_S* If either of the inputs are NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_RAND_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
* @retval CMP_RAND_S* If decode fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_RAND_S* CMP_decodeRand (SEC_UCHAR* pucEncodedRand,
                            SEC_UINT32 ulEncodedRandLength,
                            SEC_UINT32* pulBytesDecoded);




/**
* @defgroup SEC_dupRevRepContentSeqOf2
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupRevRepContentSeqOf2 (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* This method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/



PSELINKDLL SEC_List_S* SEC_dupRevRepContentSeqOf2 (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupRevRepContentSeqOf1
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupRevRepContentSeqOf1 (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_List_S* SEC_dupRevRepContentSeqOf1 (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupKeyRecRepContentSeqOf
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupKeyRecRepContentSeqOf (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupKeyRecRepContentSeqOf (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupCertRepMessageSeqOf
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupCertRepMessageSeqOf (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupCertRepMessageSeqOf (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupPKIMessageSeqOf
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupPKIMessageSeqOf (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupPKIMessageSeqOf (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupPKIFreeText
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupPKIFreeText (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupPKIFreeText (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupPBMParameter
* @ingroup cmpFunctions
* @par Prototype
* @code
* CRMF_PBM_PARAM_S* SEC_dupPBMParameter (CRMF_PBM_PARAM_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_PBM_PARAM_S* Pointer to destination. [CRMF_PBM_PARAM_S*|N/A]
* @retval CRMF_PBM_PARAM_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CRMF_PBM_PARAM_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_PBM_PARAM_S* SEC_dupPBMParameter (CRMF_PBM_PARAM_S* pSrc);

/**
* @defgroup SEC_dupDHBMParameter
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_DHBMPARAM_S* SEC_dupDHBMParameter (CMP_DHBMPARAM_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_DHBMPARAM_S* Pointer to destination. [CMP_DHBMPARAM_S*|N/A]
* @retval CMP_DHBMPARAM_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_DHBMPARAM_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_DHBMPARAM_S* SEC_dupDHBMParameter (CMP_DHBMPARAM_S* pSrc);

/**
* @defgroup SEC_dupChallenge
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CHALLENGE_S* SEC_dupChallenge (CMP_CHALLENGE_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CHALLENGE_S* Pointer to destination. [CMP_CHALLENGE_S*|N/A]
* @retval CMP_CHALLENGE_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_CHALLENGE_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_CHALLENGE_S* SEC_dupChallenge (CMP_CHALLENGE_S* pSrc);

/**
* @defgroup SEC_dupPOPODecKeyRespContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupPOPODecKeyRespContent (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupPOPODecKeyRespContent (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupCertOrEncCert
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CERTTYPE_S* SEC_dupCertOrEncCert (CMP_CERTTYPE_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CERTTYPE_S* Pointer to destination. [CMP_CERTTYPE_S*|N/A]
* @retval CMP_CERTTYPE_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_CERTTYPE_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_CERTTYPE_S* SEC_dupCertOrEncCert (CMP_CERTTYPE_S* pSrc);

/**
* @defgroup SEC_dupRevDetails
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_REVDETAILS_S* SEC_dupRevDetails (CMP_REVDETAILS_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_REVDETAILS_S* Pointer to destination. [CMP_REVDETAILS_S*|N/A]
* @retval CMP_REVDETAILS_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_REVDETAILS_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_REVDETAILS_S* SEC_dupRevDetails (CMP_REVDETAILS_S* pSrc);

/**
* @defgroup SEC_dupCAKeyUpdAnnContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CAKEYUPDATEANN_S* SEC_dupCAKeyUpdAnnContent (CMP_CAKEYUPDATEANN_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CAKEYUPDATEANN_S* Pointer to destination. [CAKEYUPDATEANN_S*|N/A]
* @retval CMP_CAKEYUPDATEANN_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_CAKEYUPDATEANN_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_CAKEYUPDATEANN_S* SEC_dupCAKeyUpdAnnContent (CMP_CAKEYUPDATEANN_S* pSrc);

/**
* @defgroup SEC_dupCRLAnnContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupCRLAnnContent (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupCRLAnnContent (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupInfoTypeAndValue
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_INFOTYPEVAL_S* SEC_dupInfoTypeAndValue (CMP_INFOTYPEVAL_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_INFOTYPEVAL_S* Pointer to destination. [CMP_INFOTYPEVAL_S*|N/A]
* @retval CMP_INFOTYPEVAL_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_NULL_PTR If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_INFOTYPEVAL_S* SEC_dupInfoTypeAndValue (CMP_INFOTYPEVAL_S* pSrc);

/**
* @defgroup SEC_dupPKIHeaderSeqOf
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupPKIHeaderSeqOf (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupPKIHeaderSeqOf (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupPKIHeader
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIHDR_S* SEC_dupPKIHeader (CMP_PKIHDR_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIHDR_S* Pointer to destination. [CMP_PKIHDR_S*|N/A]
* @retval CMP_PKIHDR_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIHDR_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_PKIHDR_S* SEC_dupPKIHeader (CMP_PKIHDR_S* pSrc);

/**
* @defgroup SEC_dupPKIStatusInfo
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKISTATUS_S* SEC_dupPKIStatusInfo (CMP_PKISTATUS_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKISTATUS_S* Pointer to destination. [CMP_PKISTATUS_S*|N/A]
* @retval CMP_PKISTATUS_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_PKISTATUS_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_PKISTATUS_S* SEC_dupPKIStatusInfo (CMP_PKISTATUS_S* pSrc);

/**
* @defgroup SEC_dupPOPODecKeyChallContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupPOPODecKeyChallContent (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupPOPODecKeyChallContent (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupCertifiedKeyPair
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_KEYPAIR_S* SEC_dupCertifiedKeyPair (CMP_KEYPAIR_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_KEYPAIR_S* Pointer to destination. [CMP_KEYPAIR_S*|N/A]
* @retval CMP_KEYPAIR_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_KEYPAIR_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_KEYPAIR_S* SEC_dupCertifiedKeyPair (CMP_KEYPAIR_S* pSrc);

/**
* @defgroup SEC_dupRevReqContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupRevReqContent(SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupRevReqContent(SEC_List_S* pSrc);

/**
* @defgroup SEC_dupRevAnnContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_REVOKEANN_S* SEC_dupRevAnnContent (CMP_REVOKEANN_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_REVOKEANN_S* Pointer to destination. [CMP_REVOKEANN_S*|N/A]
* @retval CMP_REVOKEANN_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_REVOKEANN_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_REVOKEANN_S* SEC_dupRevAnnContent (CMP_REVOKEANN_S* pSrc);

/**
* @defgroup SEC_dupGenMsgContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupGenMsgContent(SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupGenMsgContent(SEC_List_S* pSrc);

/**
* @defgroup SEC_dupGenRepContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupGenRepContent(SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupGenRepContent(SEC_List_S* pSrc);

/**
* @defgroup SEC_dupErrorMsgContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_ERRMSG_S* SEC_dupErrorMsgContent (CMP_ERRMSG_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_ERRMSG_S* Pointer to destination. [CMP_ERRMSG_S*|N/A]
* @retval CMP_ERRMSG_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_ERRMSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_ERRMSG_S* SEC_dupErrorMsgContent (CMP_ERRMSG_S* pSrc);

/**
* @defgroup SEC_dupRevRepContentSeqOf
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupRevRepContentSeqOf (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupRevRepContentSeqOf (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupKeyRecRepContentSeqOf1
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupKeyRecRepContentSeqOf1 (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupKeyRecRepContentSeqOf1 (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupCertResponse
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CERTRESP_S* SEC_dupCertResponse (CMP_CERTRESP_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CERTRESP_S* Pointer to destination. [CMP_CERTRESP_S*|N/A]
* @retval CMP_CERTRESP_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_CERTRESP_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_CERTRESP_S* SEC_dupCertResponse (CMP_CERTRESP_S* pSrc);

/**
* @defgroup SEC_dupKeyRecRepContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_KEYRECOVERYRESP_S* SEC_dupKeyRecRepContent (CMP_KEYRECOVERYRESP_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_KEYRECOVERYRESP_S* Pointer to destination. [CMP_KEYRECOVERYRESP_S*|N/A]
* @retval CMP_KEYRECOVERYRESP_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_KEYRECOVERYRESP_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_KEYRECOVERYRESP_S* SEC_dupKeyRecRepContent (CMP_KEYRECOVERYRESP_S* pSrc);

/**
* @defgroup SEC_dupRevRepContent
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_REVOKERESP_S* SEC_dupRevRepContent (CMP_REVOKERESP_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_REVOKERESP_S* Pointer to destination. [CMP_REVOKERESP_S*|N/A]
* @retval CMP_REVOKERESP_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_REVOKERESP_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL CMP_REVOKERESP_S* SEC_dupRevRepContent (CMP_REVOKERESP_S* pSrc);

/**
* @defgroup SEC_dupCertRepMessageSeqOf1
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupCertRepMessageSeqOf1 (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupCertRepMessageSeqOf1 (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupCertRepMessage
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_CERTRESPMSG_S* SEC_dupCertRepMessage (CMP_CERTRESPMSG_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_CERTRESPMSG_S* Pointer to destination. [CMP_CERTRESPMSG_S*|N/A]
* @retval CMP_CERTRESPMSG_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_CERTRESPMSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_CERTRESPMSG_S* SEC_dupCertRepMessage (CMP_CERTRESPMSG_S* pSrc);

/**
* @defgroup SEC_dupPKIMessage
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIMSG_S* SEC_dupPKIMessage (CMP_PKIMSG_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIMSG_S* Pointer to destination. [CMP_PKIMSG_S*|N/A]
* @retval CMP_PKIMSG_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIMSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_PKIMSG_S* SEC_dupPKIMessage (CMP_PKIMSG_S* pSrc);

/**
* @defgroup SEC_dupPKIBody
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_PKIBODY_S* SEC_dupPKIBody (CMP_PKIBODY_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_PKIBODY_S* Pointer to destination. [CMP_PKIBODY_S*|N/A]
* @retval CMP_PKIBODY_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_PKIBODY_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_PKIBODY_S* SEC_dupPKIBody (CMP_PKIBODY_S* pSrc);


#ifdef __IPSI_CMPV2__

/**
* @defgroup SEC_dupCertConfMessage
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMPV2_CERT_CONF_MSG_S* SEC_dupCertConfMessage(CMPV2_CERT_CONF_MSG_S* pstConfMsg);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pstConfMsg Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMPV2_CERT_CONF_MSG_S* Pointer to destination. [CMPV2_CERT_CONF_MSG_S*|N/A]
* @retval CMPV2_CERT_CONF_MSG_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMPV2_CERT_CONF_MSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL CMPV2_CERT_CONF_MSG_S* SEC_dupCertConfMessage(
    CMPV2_CERT_CONF_MSG_S* pstConfMsg);


/**
* @defgroup SEC_dupPollReqMessage
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMPV2_POLL_REQ_MSG_S* SEC_dupPollReqMessage (CMPV2_POLL_REQ_MSG_S* pstPollReqMsg);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pstPollReqMsg Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMPV2_POLL_REQ_MSG_S* Pointer to destination. [CMPV2_POLL_REQ_MSG_S*|N/A]
* @retval CMPV2_POLL_REQ_MSG_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMPV2_POLL_REQ_MSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL CMPV2_POLL_REQ_MSG_S* SEC_dupPollReqMessage (
              CMPV2_POLL_REQ_MSG_S* pstPollReqMsg);

/**
* @defgroup SEC_dupPollRepMessage
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMPV2_POLL_REP_MSG_S* SEC_dupPollRepMessage (CMPV2_POLL_REP_MSG_S* pstPollRepMsg);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pstPollRepMsg Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMPV2_POLL_REP_MSG_S* Pointer to destination. [CMPV2_POLL_REP_MSG_S*|N/A]
* @retval CMPV2_POLL_REP_MSG_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMPV2_POLL_REP_MSG_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
PSELINKDLL CMPV2_POLL_REP_MSG_S* SEC_dupPollRepMessage (
              CMPV2_POLL_REP_MSG_S* pstPollRepMsg);
#endif

/**
* @defgroup SEC_dupEncKeyPairTypes
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupEncKeyPairTypes (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupEncKeyPairTypes (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupSignKeyPairTypes
* @ingroup cmpFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupSignKeyPairTypes (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination. [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupSignKeyPairTypes (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupRand
* @ingroup cmpFunctions
* @par Prototype
* @code
* CMP_RAND_S* SEC_dupRand (CMP_RAND_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to a destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer internally allocating memory.
*
* @param[in] pSrc Pointer to source. [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CMP_RAND_S* Pointer to destination. [CMP_RAND_S*|N/A]
* @retval CMP_RAND_S* If the input is NULL. [SEC_NULL_PTR|N/A]
* @retval CMP_RAND_S* If memory allocation fails. [SEC_NULL_PTR|N/A]
*
* @par Dependency
* cmp.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CMP_RAND_S* SEC_dupRand (CMP_RAND_S* pSrc);


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_CMP_H */

#endif /* _SSL_ */

