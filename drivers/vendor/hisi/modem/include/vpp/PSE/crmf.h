/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

------------------------------------------------------------------------------

                              crmf.h

  Project Code: SeCert
   Module Name: CRMF
  Date Created: 2005-07-05
        Author: Sindhu
   @brief This header file declares all the structures and methods that
                are required to create CRMF standard defined Request Messages

*/

//lint -e652
#include "ipsi_pse_build_conf.h"

#ifndef _SSL_
#ifndef _IPSI_CRMF_H_
#define _IPSI_CRMF_H_


/* SeCert Headers */

#include "sec_sys.h"
#include "asn-types.h"
#include "sec_list.h"
#include "sec_error.h"
#include "sec_crypto.h"
#include "pkcs7.h"
#include "x509_basictypes.h"
#include "x509v3_extn.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Publication Method in CRMF_SINGLE_PUBINFO_S*/
#define DONTCARE    0    /* If the DontCare method is chosen, or if the
                            PKIPublicationInfo control is omitted from the request,
                            the requester indicates that the PKI may publish the
                            certificate using whatever means it chooses*/

#define X500        1    /* If the requester wishes the certificate to appear
                            in at least some locations but wishes to enable the
                            CA to make the certificate available in other repositories,
                            set two values of SinglePubInfo for pubInfos:
                            one with x500, web or ldap value and one with dontCare*/
#define WEB            2

/* IPSI_LDAP_SYMBOL_RESOLUTION - macro needs to be defined in user makefile, if user gets symbol */
/* conflict error for below LDAP macro with some other component header file. And also in user's code */
/* IPSI_LDAP macro needs to be used not LDAP macro. */
/* If IPSI_LDAP_SYMBOL_RESOLUTION macro is not used in user makefile, then either LDAP or IPSI_LDAP */
/* macro can be used. But its recommended to use IPSI_LDAP macro. */

#ifndef IPSI_LDAP_SYMBOL_RESOLUTION
#define LDAP        3
#endif

#define IPSI_LDAP        3


/* Action in CRMF_PUBLICATION_INFO_S*/
#define CRMF_CERT_DONTPUBLISH        0    /* pubInfos must not be present for this option*/
#define CRMF_CERT_PUBLISH            1    /* This option allows publication of the certificate by the CA*/

/* Options for Subsequent Message in POP Private Key*/
#define CRMF_ENCRYPT_CERT            0    /* Message that resulting certificate be
                                            encrypted for the end entity*/
#define CRMF_CHALLENGE_RESP            1    /* Message that CA engage in challenge-response
                                            exchange with end entity in order to
                                            prove private key possession*/


/* PKIArchiveOptions*/
#define CRMF_PKIARCHOPT_ENCKEY_ENCRYPTEDVAL      0    /* Option for encrypted Private Key*/
#define CRMF_PKIARCHOPT_ENCKEY_ENVELOPEDDATA     1    /* Option for Enveloped Data of Private Key*/
#define CRMF_PKIARCHOPT_KEYGENPARAMETERS         2    /* Option for parameters which re-generates the Private Key*/
#define CRMF_PKIARCHOPT_ARCHIVEREMGENPRIVKEY     3    /* Option (True/False) whether sender wishes receiver
                                                        to archive the privatekey*/

/** @defgroup crmf
* This section contains the crmf Enums, Structures and Functions */

/** @defgroup crmfEnums
* @ingroup crmf
* This section contains the crmf Enums
*/

/** @defgroup crmfStructures
* @ingroup crmf
* This section contains the crmf Structures
*/

/** @defgroup crmfFunctions
* @ingroup crmf
* This section contains the crmf Functions
*/

/* OptionalValidity Structure is used in Certificate Template of the Request*/
/**
* @defgroup CRMF_OPT_VALIDITY_S
* @ingroup crmfStructures
* @par Prototype
* @code
* typedef struct stCRMF_OptionalValidity
* {
*   SEC_TIME_S* pstNotBefore;
*   SEC_TIME_S* pstNotAfter;
* } CRMF_OPT_VALIDITY_S;
* @endcode
*
* @datastruct pstNotBefore Validity in terms of Time before which the Cetificate is not valid (Optional).
* @datastruct pstNotAfter Validity in terms of Time after which the Cetificate is not valid (Optional).
*/
typedef struct stCRMF_OptionalValidity
{
     SEC_TIME_S* pstNotBefore;    /*    Validity in terms of Time before which the
                                        Cetificate is not valid (Optional)*/
     SEC_TIME_S* pstNotAfter;    /*    Validity in terms of Time after which the
                                        Cetificate is not valid (Optional)*/
} CRMF_OPT_VALIDITY_S;


/* Used in SigningKey Proof of Possession*/
/**
* @defgroup CRMF_PKMAC_S
* @ingroup crmfStructures
* @par Prototype
* @code
* typedef struct stCRMF_PKMACValue
* {
*    SEC_ALG_IDENTIFIER_S* pstAlgId;
*    SEC_AsnBits_S value;
* } CRMF_PKMAC_S;
* @endcode
*
* @datastruct pstAlgId PasswordBasedMac with PBMParameter.
* @datastruct value Contains a password-based MAC on the DER-encoded value of publicKey.
*/
typedef struct stCRMF_PKMACValue
{
    SEC_ALG_IDENTIFIER_S* pstAlgId;        /* PasswordBasedMac with PBMParameter*/
    SEC_AsnBits_S value;                /* Contains a password-based MAC on the
                                             DER-encoded value of publicKey*/
} CRMF_PKMAC_S;


/* Used in Encrypting Certificate or Private Key*/
/**
* @defgroup CRMF_ENCRYPTED_VALUE_S
* @ingroup crmfStructures
* @par Prototype
* @code
* typedef struct stCRMF_EncryptedValue
* {
*    SEC_ALG_IDENTIFIER_S* pstIntendedAlg;
*    SEC_ALG_IDENTIFIER_S* pstSymmAlg;
*    SEC_AsnBits_S encSymmKey;
*    SEC_ALG_IDENTIFIER_S* pstKeyAlg;
*    SEC_AsnOcts_S valueHint;
*    SEC_AsnBits_S encValue;
* } CRMF_ENCRYPTED_VALUE_S;
* @endcode
*
* @datastruct pstIntendedAlg Algorithm for which the value will be used (Optional).
* @datastruct pstSymmAlg Symmetric Algorithm used to encrypt the value (Optional).
* @datastruct encSymmKey Encrypted Symmetric Key (Optional).
* @datastruct pstKeyAlg Algorithm to encrypt the Symmetric Key (Optional)
* @datastruct valueHint A brief description or identifier of the encValue content (Optional).
* @datastruct encValue Encrypted Value, can be a Certificate or Private Key.
*/
typedef struct stCRMF_EncryptedValue
{
    SEC_ALG_IDENTIFIER_S* pstIntendedAlg;    /*  Algorithm for which the value will be used (Optional)*/
    SEC_ALG_IDENTIFIER_S* pstSymmAlg;        /*  Symmetric Algorithm used to encrypt the value (Optional)*/
    SEC_AsnBits_S encSymmKey;                /*  Encrypted Symmetric Key (Optional)*/
    SEC_ALG_IDENTIFIER_S* pstKeyAlg;        /*  Algorithm to encrypt the Symmetric Key (Optional)*/
    SEC_AsnOcts_S valueHint;                /*  a brief description or identifier
                                                  of the encValue content (Optional)*/
    SEC_AsnBits_S encValue;                    /*  Encrypted Value, Can be a Certificate
                                                  or Private Key*/
} CRMF_ENCRYPTED_VALUE_S;


/* In order to identify particular certificates the CertId data
   structure is used*/
/**
* @defgroup CRMF_CERT_ID_S
* @ingroup crmfStructures
* @par Prototype
* @code
* typedef struct stCRMF_CertId
* {
*    SEC_GEN_NAME_S* pstIssuer;
*    SEC_BIGINT_S serialNumber;
* } CRMF_CERT_ID_S;
* @endcode
*
* @datastruct pstIssuer Certificate Issuer Name.
* @datastruct serialNumber Certificate Serial Number.
*/
typedef struct stCRMF_CertId
{
    SEC_GEN_NAME_S* pstIssuer;    /* Certificate Issuer Name*/
    SEC_BIGINT_S serialNumber;    /* Certificate Serial Number*/
} CRMF_CERT_ID_S;

/* Request Type used in creating the Certificate Template*/
/**
* @defgroup CRMF_REQMSG_TYPE_E
* @ingroup crmfEnums
* @par Prototype
* @code
* typedef enum enCRMF_ReqMsgType
* {
*   CRMF_INIT       = 0,
*   CRMF_CERT       = 1,
*   CRMF_CROSSCERT  = 2,
*   CRMF_KEYUPD     = 3,
*   CRMF_KEYREC     = 4,
*   CRMF_INVALID    = 5
* } CRMF_REQMSG_TYPE_E;
* @endcode
*
* @datastruct CRMF_INIT=0 Initialization Request.
* @datastruct CRMF_CERT=1 Certificate Request.
* @datastruct CRMF_CROSSCERT=2 Cross-Certification Request.
* @datastruct CRMF_KEYUPD=3 Key Update Request.
* @datastruct CRMF_KEYREC=4 Key Recovery Request.
* @datastruct CRMF_INVALID=5 Invalid Message Type.
*/
typedef enum enCRMF_ReqMsgType
{
    CRMF_INIT        = 0,    /* Initialization Request*/
    CRMF_CERT        = 1,    /* Certificate Request*/
    CRMF_CROSSCERT    = 2,    /* Cross-Certification Request*/
    CRMF_KEYUPD        = 3,    /* Key Update Request*/
    CRMF_KEYREC        = 4,    /* Key Recovery Request*/
    CRMF_INVALID    = 5        /* Invalid Message Type*/
} CRMF_REQMSG_TYPE_E;


/* Selected fields of Cert to be issued using this data structure*/
/**
* @defgroup CRMF_CERT_TEMPLATE_S
* @ingroup crmfStructures
* @par Prototype
* @code
* typedef struct stCRMF_CertTemplate
* {
*    SEC_AsnInt* pstVersion;
*    SEC_BIGINT_S serialNumber;
*    SEC_ALG_IDENTIFIER_S* pstSigningAlg;
*    SEC_NAME_S* pstIssuer;
*    CRMF_OPT_VALIDITY_S* pstValidity;
*    SEC_NAME_S* pstSubject;
*    SEC_PUBKEY_INFO_S* pstPublicKey;
*    SEC_AsnBits_S issuerUID;
*    SEC_AsnBits_S subjectUID;
*    Extensions* extensions;
* } CRMF_CERT_TEMPLATE_S;
* @endcode
*
* @datastruct pstVersion Certificate Version (Optional).
* @datastruct serialNumber Certificate Serial Number (Optional).
* @datastruct pstSigningAlg Signing Algorithm for the Certificate (Optional).
* @datastruct pstIssuer Issuer Name (Optional).
* @datastruct pstValidity Certificate Validity (Optional).
* @datastruct pstSubject Subject Name (Optional).
* @datastruct pstPublicKey Encoded Public Key (Optional)
* @datastruct issuerUID Issuer Identifier (Optional).
* @datastruct subjectUID Subject Identifier (Optional).
* @datastruct extensions List of Extensions (Optional).
*/
typedef struct stCRMF_CertTemplate
{
    SEC_AsnInt* pstVersion;                        /* Certificate Version (Optional)*/
    SEC_BIGINT_S serialNumber;                    /* Certificate Serial Number (Optional)*/
    SEC_ALG_IDENTIFIER_S* pstSigningAlg;        /* Signing Algorithm for the Certificate (Optional)*/
    SEC_NAME_S* pstIssuer;                        /* Issuer Name (Optional)*/
    CRMF_OPT_VALIDITY_S* pstValidity;            /* Certificate Validity (Optional)*/
    SEC_NAME_S* pstSubject;                        /* Subject Name (Optional)*/
    SEC_PUBKEY_INFO_S* pstPublicKey;            /* Encoded Public Key (Optional)*/
    SEC_AsnBits_S issuerUID;                    /* Issuer Identifier (Optional)*/
    SEC_AsnBits_S subjectUID;                    /* Subject Identifier (Optional)*/
    Extensions* extensions;                        /* List of Extensions (Optional)*/
    CRMF_REQMSG_TYPE_E enReqMsgType;
} CRMF_CERT_TEMPLATE_S;


/* List of Attributes affecting issuance */
typedef SEC_List_S CRMF_ControlsLst;            /* List of Controls that can be added onto Cert Request of the
                                                    Certificate Request Message*/


/* Choice for Type of Signing Key Input for Proof of Possession
    Can be either Sender Name or PublicKeyMAC*/

/**
* @defgroup CRMF_POPOSIGNING_KEY_TYPE_E
* @ingroup crmfEnums
* @par Prototype
* @code
* typedef enum enCRMF_POPOSigningKeyInputChoice
* {
*   POPOSIGNINGKEYINPUTCHOICE_SENDER       = 0,
*   POPOSIGNINGKEYINPUTCHOICE_PUBLICKEYMAC = 1,
*   POPOSIGNINGKEYINPUTCHOICE_INVALID      = 2
* } CRMF_POPOSIGNING_KEY_TYPE_E;
* @endcode
*
* @datastruct POPOSIGNINGKEYINPUTCHOICE_SENDER=0 Used only if an authenticated identity.
* has been established for the sender.
* @datastruct POPOSIGNINGKEYINPUTCHOICE_PUBLICKEYMAC=1 Used if no authenticated GeneralName.
* currently exists for the sender.
* @datastruct POPOSIGNINGKEYINPUTCHOICE_INVALID=2 Invalid Option.
*/
typedef enum enCRMF_POPOSigningKeyInputChoice
{
    POPOSIGNINGKEYINPUTCHOICE_SENDER        = 0,    /* Used only if an authenticated identity
                                                        has been established for the sender*/
    POPOSIGNINGKEYINPUTCHOICE_PUBLICKEYMAC    = 1,    /* Used if no authenticated GeneralName
                                                        currently exists for the sender*/
    /*enum value is 2 is unused*/

    /* Sender places its subject name and public key in the certificate template.
        In this case POP will be calucalated over the DER encoded certReqMsg*/
    POPOSIGNINGKEYINPUTCHOICE_CERTTEMPLATE        = 3,
    POPOSIGNINGKEYINPUTCHOICE_INVALID        = 4        /* Invalid Option*/
} CRMF_POPOSIGNING_KEY_TYPE_E;



/* Signing Key Input for Proof of Possession*/
/**
* @defgroup CRMF_POPOSIGNING_KEY_TYPE_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_POPOSigningKeyInputChoice
* {
*    CRMF_POPOSIGNING_KEY_TYPE_E enPOPSigningChoiceId;
*    union unCRMF_POPOSigningKeyInputChoice
*    {
*        SEC_GEN_NAME_S* sender;
*        CRMF_PKMAC_S* publicKeyMAC;
*    } unPOPSigningChoiceVal;
*
* } CRMF_POPOSIGNING_KEY_TYPE_S;
* @endcode
*
* @datastruct enPOPSigningChoiceId Choice - Sender Name/PublicKeyMAC.
* @datastruct sender General Name.
* @datastruct publicKeyMAC publicKeyMAC contains a password-based MAC on the DER-encoded value of publicKey.
*/
typedef struct stCRMF_POPOSigningKeyInputChoice
{
   CRMF_POPOSIGNING_KEY_TYPE_E enPOPSigningChoiceId;    /* Choice - Sender Name/PublicKeyMAC*/
   union unCRMF_POPOSigningKeyInputChoice
   {
        SEC_GEN_NAME_S* sender;            /* General Name*/
        CRMF_PKMAC_S* publicKeyMAC;        /* publicKeyMAC contains a password-based MAC
                                                on the DER-encoded value of publicKey*/
    } unPOPSigningChoiceVal;

} CRMF_POPOSIGNING_KEY_TYPE_S;

/* This structure can be used if the CertReqMsg, CertReq CertTemplate does not contain
    the subject and publicKey values*/
/**
* @defgroup CRMF_POPOSIGNING_KEYIN_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_POPOSigningKeyInput
* {
*     CRMF_POPOSIGNING_KEY_TYPE_S* pstAuthInfo;
*     SEC_PUBKEY_INFO_S* pstPublicKey;
* } CRMF_POPOSIGNING_KEYIN_S;
* @endcode
*
* @datastruct pstAuthInfo Signing Key Input.
* @datastruct pstPublicKey Encoded Public Key.
*/
typedef struct stCRMF_POPOSigningKeyInput
{
     CRMF_POPOSIGNING_KEY_TYPE_S* pstAuthInfo;    /* Signing Key Input*/
     SEC_PUBKEY_INFO_S* pstPublicKey;            /* Encoded Public Key*/
} CRMF_POPOSIGNING_KEYIN_S;


/* This structure can be used to Prove the Possession using Signature*/
/**
* @defgroup CRMF_POPOSIGNING_KEY_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_POPOSigningKey
* {
*    CRMF_POPOSIGNING_KEYIN_S* pstPOPOSKInput;
*    SEC_ALG_IDENTIFIER_S* pstAlgorithmIdentifier;
*    SEC_AsnBits_S signature;
* } CRMF_POPOSIGNING_KEY_S;
* @endcode
*
* @datastruct pstPOPOSKInput Signing Key Input (Optional).
* @datastruct pstAlgorithmIdentifier Algorithm for Signing POP SigningKeyInput or the Cert Request in the Certificate Request Message.
* @datastruct signature Signature on DER-encoded value of POPSigningKeyInput or CertReqMsg certReq.
*/
typedef struct stCRMF_POPOSigningKey
{
    CRMF_POPOSIGNING_KEYIN_S* pstPOPOSKInput;        /* Signing Key Input (Optional)*/
    SEC_ALG_IDENTIFIER_S* pstAlgorithmIdentifier;    /* Algorithm for Signing POP SigningKeyInput
                                                            or the Cert Request in the Certificate Request Message*/
    SEC_AsnBits_S signature;                        /* Signature on DER-encoded value of
                                                        POPSigningKeyInput or CertReqMsg certReq*/
} CRMF_POPOSIGNING_KEY_S;


/* Type of Proof Of Possession using Private Key*/
/**
* @defgroup CRMF_POPOPRIV_KEY_E
* @ingroup crmfEnums
* @par Prototype
* @code
* typedef enum enCRMF_POPOPrivKey
* {
*   POPOPRIVKEY_THISMESSAGE       = 0,
*   POPOPRIVKEY_SUBSEQUENTMESSAGE = 1,
*   POPOPRIVKEY_DHMAC             = 2,
*   POPOPRIVKEY_INVALID           = 3
* } CRMF_POPOPRIV_KEY_E;
* @endcode
*
* @datastruct POPOPRIVKEY_THISMESSAGE= 0 Choice of proving the possession in the current message.
* @datastruct POPOPRIVKEY_SUBSEQUENTMESSAGE= 1 Choice of proving the possession in a subsequent message.
* @datastruct POPOPRIVKEY_DHMAC= 2 Choice of proving the possession in the current message using DH Keys.
* @datastruct POPOPRIVKEY_INVALID= 3 Invalid Option.
*/
typedef enum enCRMF_POPOPrivKey
{
    POPOPRIVKEY_THISMESSAGE            = 0,    /* Choice of proving the possession in the current message*/
    POPOPRIVKEY_SUBSEQUENTMESSAGE    = 1,    /* Choice of proving the possession in a subsequent message*/
    POPOPRIVKEY_DHMAC                = 2,    /* Choice of proving the possession in
                                                    the current message using DH Keys*/
    POPOPRIVKEY_INVALID                = 3        /* Invalid Option*/
} CRMF_POPOPRIV_KEY_E;


/* This structure can be used to Prove the Possession for
    Encipherment Keys / KeyAgreement Keys*/
/**
* @defgroup CRMF_POPOPRIV_KEY_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_POPOPrivKey
* {
*   CRMF_POPOPRIV_KEY_E enPOPPrivKeyChoiceId;
*    union unCRMF_POPOPrivKey
*     {
*        SEC_AsnBits_S* pstThisMsg;
*        SEC_UINT32     subsequentMsg;
*        SEC_AsnBits_S* pstDHMAC;
*     } unPOPPrivKeyChoiceVal;
* } CRMF_POPOPRIV_KEY_S;
* @endcode
*
* @datastruct enPOPPrivKeyChoiceId choice - type as in CRMF_POPOPRIV_KEY_E.
* @datastruct pstThisMsg Contains Encrypted private Key.
* @datastruct subsequentMsg CRMF_ENCRYPT_CERT / CRMF_CHALLENGE_RESP.
* @datastruct pstDHMAC Contains the MAC formed over the DER-encoded value of the certReq parameter in CertReqMsg.
*/
typedef struct stCRMF_POPOPrivKey
{
    CRMF_POPOPRIV_KEY_E enPOPPrivKeyChoiceId;    /* choice - type as in CRMF_POPOPRIV_KEY_E*/
    union unCRMF_POPOPrivKey
    {
        SEC_AsnBits_S*        pstThisMsg;     /* Contains Encrypted private Key*/
        SEC_UINT32          subsequentMsg;  /* CRMF_ENCRYPT_CERT / CRMF_CHALLENGE_RESP*/
        SEC_AsnBits_S*      pstDHMAC;       /* Contains the MAC formed over the
                                                    DER-encoded value of the
                                                    certReq parameter in CertReqMsg*/
    }unPOPPrivKeyChoiceVal;

} CRMF_POPOPRIV_KEY_S;

/* This structure can be used to send the publication Method*/
/**
* @defgroup CRMF_SINGLE_PUBINFO_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_SinglePubInfo
* {
*    SEC_UINT32 pubMethod;
*   SEC_GEN_NAME_S* pstPubLocation;
* } CRMF_SINGLE_PUBINFO_S;
* @endcode
*
* @datastruct pubMethod Publication Method.
* @datastruct pstPubLocation General Name indicating where the requester would like the certificate to be found (Optional).
*/
typedef struct stCRMF_SinglePubInfo
{
    SEC_UINT32 pubMethod;                /* Publication Method*/
    SEC_GEN_NAME_S* pstPubLocation;        /* General Name indicating where the requester
                                             would like the certificate to be found (Optional)*/
} CRMF_SINGLE_PUBINFO_S;


/* List Of CRMF_SINGLE_PUBINFO_S*/
typedef SEC_List_S CRMF_PublicationInfoList;

/* This structure can be used by subscribers to control
    the Publication Information*/
/**
* @defgroup CRMF_PUBLICATION_INFO_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_PKIPublicationInfo
* {
*    SEC_UINT32 action;
*    CRMF_PublicationInfoList* pstPubInfos;
* } CRMF_PUBLICATION_INFO_S;
* @endcode
*
* @datastruct action CRMF_CERT_DONTPUBLISH / CRMF_CERT_PUBLISH.
* @datastruct pstPubInfos List of Single Publication Information (Optional).
*/
typedef struct stCRMF_PKIPublicationInfo
{
    SEC_UINT32 action;                        /* CRMF_CERT_DONTPUBLISH / CRMF_CERT_PUBLISH*/
    CRMF_PublicationInfoList* pstPubInfos;    /* List of Single Publication Information (Optional)*/
} CRMF_PUBLICATION_INFO_S;


/* Option for creating an Encrypted Key for PKIArchiveOptions in Controls field
    of the Certificate Request Message*/
/**
* @defgroup CRMF_ENCRYPTED_KEY_E
* @ingroup crmfEnums
* @par Prototype
* @code
* typedef enum enCRMF_EncryptedKey
* {
*    ENCRYPTED_KEY_ENCRYPTEDVALUE,
*    ENCRYPTED_KEY_ENVELOPEDDATA,
*    ENCRYPTED_KEY_INVALID
* } CRMF_ENCRYPTED_KEY_E;
* @endcode
*
* @datastruct ENCRYPTED_KEY_ENCRYPTEDVALUE Choice of Encrypted Value.
* @datastruct ENCRYPTED_KEY_ENVELOPEDDATA Choice of Enveloped Data.
* @datastruct ENCRYPTED_KEY_INVALID Invalid Option.
*/
typedef enum enCRMF_EncryptedKey
{
    ENCRYPTED_KEY_ENCRYPTEDVALUE,   /* Choice of Encrypted Value*/
    ENCRYPTED_KEY_ENVELOPEDDATA,    /* Choice of Enveloped Data*/
    ENCRYPTED_KEY_INVALID           /* Invalid Option */
} CRMF_ENCRYPTED_KEY_E;


/* This structure can be used to create the Encrypted Key for PKIArchive Options*/
/**
* @defgroup CRMF_ENCRYPTED_KEY_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_EncryptedKey
* {
*   CRMF_ENCRYPTED_KEY_E enEncryptKeyChoiceId;
*    union unCRMF_EncryptedKey
*     {
*        CRMF_ENCRYPTED_VALUE_S* pstEncryptedValue;
*        PKCS7_ENVELOPED_S* pstEnvelopedData;
*     } unEncryptKeyChoiceVal;
* } CRMF_ENCRYPTED_KEY_S;
* @endcode
*
* @datastruct enEncryptKeyChoiceId Choice as in CRMF_ENCRYPTED_KEY_E.
* @datastruct pstEncryptedValue Contains Encrypted Value of the Private Key.
* @datastruct pstEnvelopedData Encrypted Private Key is placed in EnvelopedData.
*/
typedef struct stCRMF_EncryptedKey
{
    CRMF_ENCRYPTED_KEY_E enEncryptKeyChoiceId;        /* Choice as in CRMF_ENCRYPTED_KEY_E*/
    union unCRMF_EncryptedKey
    {
        CRMF_ENCRYPTED_VALUE_S* pstEncryptedValue;    /* Contains Encrypted Value of the Private Key */
        PKCS7_ENVELOPED_S* pstEnvelopedData;        /* Encrypted Private Key is placed in EnvelopedData */
    }unEncryptKeyChoiceVal;

} CRMF_ENCRYPTED_KEY_S;


/* Structure to be used to create Certificate Response and is part of the
    Certificate Response Message */
/**
* @defgroup CRMF_CERT_REQ_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_CertRequest
* {
*    SEC_INT32 iCertReqId;
*    CRMF_CERT_TEMPLATE_S* pstCertTemplate;
*    CRMF_ControlsLst* pControlsList;
* } CRMF_CERT_REQ_S;
* @endcode
*
* @datastruct iCertReqId Request Identifier.
* @datastruct pstCertTemplate Template of Certificate content.
* @datastruct pControlsList Attributes required for processing of Request (Optional).
*/
typedef struct stCRMF_CertRequest
{
    SEC_INT32 iCertReqId;                            /* Request Identifier*/
    CRMF_CERT_TEMPLATE_S* pstCertTemplate;            /* Template of Certificate content*/
    CRMF_ControlsLst* pControlsList;                /* Attributes required for processing of Request (Optional)*/
} CRMF_CERT_REQ_S;


/* In order to prevent certain attacks and to allow a CA/RA to properly
    check the validity of the binding between an end entity and a key pair,
    the following structure can be used*/
/**
* @defgroup CRMF_POP_E
* @ingroup crmfEnums
* @par Prototype
* @code
* typedef enum enCRMF_ProofOfPossession
* {
*    PROOFOFPOSSESSION_RAVERIFIED      = 0,
*    PROOFOFPOSSESSION_SIGNATURE       = 1,
*    PROOFOFPOSSESSION_KEYENCIPHERMENT = 2,
*    PROOFOFPOSSESSION_KEYAGREEMENT    = 3,
*    PROOFOFPOSSESSION_INVALID         = 4
* }CRMF_POP_E;
* @endcode
*
* @datastruct PROOFOFPOSSESSION_RAVERIFIED=0 Option where in RA has already verified POP.
* @datastruct PROOFOFPOSSESSION_SIGNATURE=1 Option for Signature.
* @datastruct PROOFOFPOSSESSION_KEYENCIPHERMENT=2 Option for Private Key Encryption.
* @datastruct PROOFOFPOSSESSION_KEYAGREEMENT=3 Option for Private Key Encryption.
* @datastruct PROOFOFPOSSESSION_INVALID=4 Invalid Option.
*/
typedef enum enCRMF_ProofOfPossession
{
    PROOFOFPOSSESSION_RAVERIFIED        = 0,    /* Option where in RA has already verified POP*/
    PROOFOFPOSSESSION_SIGNATURE            = 1,    /* Option for Signature*/
    PROOFOFPOSSESSION_KEYENCIPHERMENT    = 2,    /* Option for Private Key Encryption*/
    PROOFOFPOSSESSION_KEYAGREEMENT        = 3,    /* Option for Private Key Encryption*/
    PROOFOFPOSSESSION_INVALID            = 4        /* Invalid Option*/
}CRMF_POP_E;


/* CA/RA is free to choose how to enforce Proof Of Possession using
    one of the following options*/
/**
* @defgroup CRMF_POP_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_ProofOfPossession
* {
*  CRMF_POP_E enPOPOChoiceId;
*  union unCRMF_ProofOfPossession
*  {
*   SEC_CHAR                raVerified;
*   CRMF_POPOSIGNING_KEY_S* pstSignature;
*   CRMF_POPOPRIV_KEY_S*    pstKeyEncipherment;
*   CRMF_POPOPRIV_KEY_S*    pstKeyAgreement;
*  } unPOPOChoiceVal;
* } CRMF_POP_S;
* @endcode
*
* @datastruct enPOPOChoiceId Choice as in CRMF_POP_E.
* @datastruct raVerified AsnNull Value - used if the RA has already verified that the requester is in possession of the private key.
* @datastruct pstSignature Signature on the POP SigningKey Input.
* @datastruct pstKeyEncipherment Private Key Encryption.
* @datastruct pstKeyAgreement Private Key Encryption with DH Keys.
* @datastruct unPOPOChoiceVal Options to enforce proof of possession.
*/
typedef struct stCRMF_ProofOfPossession
{
    CRMF_POP_E enPOPOChoiceId;                        /* choice as in CRMF_POP_E*/
    union unCRMF_ProofOfPossession
    {
        SEC_CHAR raVerified;                        /*  AsnNull Value - used if the RA has already verified
                                                            that the requester is in possession of the private key*/
        CRMF_POPOSIGNING_KEY_S* pstSignature;        /*  Signature on the POP SigningKey Input*/
        CRMF_POPOPRIV_KEY_S*    pstKeyEncipherment;    /*  Private Key Encryption*/
        CRMF_POPOPRIV_KEY_S*    pstKeyAgreement;    /*  Private Key Encryption with DH Keys*/
    }unPOPOChoiceVal;                                /*  Options to enforce proof of possession*/

} CRMF_POP_S;


/* List of Certificate Request Messages which is set in the PKI Body
    to make Initialization / Certificate / Key Update / Key Recovery Requests*/
typedef SEC_List_S CRMF_CertReqMsgList;

/* This structure can be added to the Certificate Request Message List
    of the PKI Body*/
/**
* @defgroup CRMF_CERT_REQ_MSG_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_CertReqMsg
* {
*    CRMF_CERT_REQ_S* pstCertReq;
*    CRMF_POP_S*      pstPOP;
*    SEC_List_S*      pstRegInfo;
* } CRMF_CERT_REQ_MSG_S;
* @endcode
*
* @datastruct pstCertReq Certificate Request.
* @datastruct pstPOP Proof Of Possession (Optional).
* @datastruct pstRegInfo Contains supplementary information related to the context of the certification request (Optional).
*/
typedef struct stCRMF_CertReqMsg
{
    CRMF_CERT_REQ_S*    pstCertReq;        /* Certificate Request*/
    CRMF_POP_S*            pstPOP;            /* Proof Of Possession (Optional)*/
    SEC_List_S*            pstRegInfo;        /* Contains supplementary information related
                                            to the context of the certification request (Optional)*/
} CRMF_CERT_REQ_MSG_S;


/* Password Based MAC parameter*/
/**
* @defgroup CRMF_PBM_PARAM_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_PBMParameter
* {
*    SEC_AsnOcts_S         stSalt;
*    SEC_ALG_IDENTIFIER_S* pstOWF;
*    SEC_UINT32            ulIterationCount;
*    SEC_ALG_IDENTIFIER_S* pstMAC;
* } CRMF_PBM_PARAM_S;
* @endcode
*
* @datastruct stSalt Salt value used to append with the shared secret.
* @datastruct pstOWF Hashing Algorithm.
* @datastruct ulIterationCount Iteration Count.
* @datastruct pstMAC Digest Algorithm.
*/
typedef struct stCRMF_PBMParameter
{
    SEC_AsnOcts_S stSalt;            /* Salt value used to append with the shared secret*/
    SEC_ALG_IDENTIFIER_S* pstOWF;   /* Hashing Algorithm*/
    SEC_UINT32 ulIterationCount;    /* Iteration Count*/
    SEC_ALG_IDENTIFIER_S* pstMAC;   /* Digest Algorithm*/
} CRMF_PBM_PARAM_S;


/* Options to create the PKI ArchiveOptions which can
    be added as Controls of Certificate Request*/
/**
* @defgroup CRMF_ARCHIVE_OPTS_E
* @ingroup crmfEnums
* @par Prototype
* @code
* typedef enum enCRMF_PKIArchiveOptions
* {
*    PKIARCHIVEOPTIONS_ENCRYPTEDPRIVKEY     = 0,
*    PKIARCHIVEOPTIONS_KEYGENPARAMETERS     = 1,
*    PKIARCHIVEOPTIONS_ARCHIVEREMGENPRIVKEY = 2,
*    PKIARCHIVEOPTIONS_INVALID              = 3
* } CRMF_ARCHIVE_OPTS_E;
* @endcode
*
* @datastruct PKIARCHIVEOPTIONS_ENCRYPTEDPRIVKEY=0 Encrypted Key Option.
* @datastruct PKIARCHIVEOPTIONS_KEYGENPARAMETERS=1 Key Generation Parameter Option.
* @datastruct PKIARCHIVEOPTIONS_ARCHIVEREMGENPRIVKEY=2 Archiving Option.
* @datastruct PKIARCHIVEOPTIONS_INVALID=3 Invalid.
*/
typedef enum enCRMF_PKIArchiveOptions
{
    PKIARCHIVEOPTIONS_ENCRYPTEDPRIVKEY        = 0,    /* Encrypted Key Option*/
    PKIARCHIVEOPTIONS_KEYGENPARAMETERS        = 1,    /* Key Generation Parameter Option*/
    PKIARCHIVEOPTIONS_ARCHIVEREMGENPRIVKEY    = 2,    /* Archiving Option*/
    PKIARCHIVEOPTIONS_INVALID                = 3        /* Invalid*/
} CRMF_ARCHIVE_OPTS_E;

/* This Control Option enables subscribers to supply
    information needed to establish an archive of the private key
    corresponding to the public key of the certification request
    It can be added to the List in the CertRequest of the CertReqMsg*/
/**
* @defgroup CRMF_ARCHIVE_OPTS_S
* @ingroup crmfStructures
* @code
* typedef struct stCRMF_PKIArchiveOptions
* {
*  CRMF_ARCHIVE_OPTS_E    enPKIArchiveChoiceId;
*  union unCRMF_PKIArchiveOptions
*  {
*   CRMF_ENCRYPTED_KEY_S* pstEncryptedPrivKey;
*   SEC_AsnOcts_S*        keyGenParameters;
*   SEC_AsnBool           archiveRemGenPrivKey;
*  } unPKIArchiveChoiceVal;
* } CRMF_ARCHIVE_OPTS_S;
* @endcode
*
* @datastruct enPKIArchiveChoiceId Options for creating Controls of Certificate Request.
* @datastruct pstEncryptedPrivKey Encrypted Key.
* @datastruct keyGenParameters Parameters which allow the private key to be re-generated.
* @datastruct archiveRemGenPrivKey Set to TRUE if sender wishes receiver to archive the private key of a key pair which
* the receiver generates in response to this request, else set to FALSE if no archival is desired.
*/
typedef struct stCRMF_PKIArchiveOptions
{
    CRMF_ARCHIVE_OPTS_E enPKIArchiveChoiceId;        /* Options for creating Controls of Certificate Request*/
    union unCRMF_PKIArchiveOptions
    {
        CRMF_ENCRYPTED_KEY_S* pstEncryptedPrivKey;    /* Encrypted Key*/
        SEC_AsnOcts_S* keyGenParameters;            /* Parameters which allow the private key to be re-generated*/
        SEC_AsnBool archiveRemGenPrivKey;            /* Set to TRUE if sender wishes receiver to
                                                            archive the private key of a key pair which
                                                            the receiver generates in response to this request,
                                                            else set to FALSE if no archival is desired*/
    }unPKIArchiveChoiceVal;

} CRMF_ARCHIVE_OPTS_S;


typedef CRMF_CERT_ID_S OldCertId;            /* Certificate Identifier added as Controls
                                                in Certificate Request */

typedef SEC_PUBKEY_INFO_S ProtocolEncrKey;    /* Encoded Public Key Information added as Controls
                                                in Certificate Request */


/** CRMF FUNCTIONS */

/**
* @defgroup CRMF_createCertReq
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CertReqMsgList* CRMF_createCertReq (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To create a Certificate Request Message List.
*
* @par Description
* This function creates a Certificate Request Message List.
* This can be used for making Initialization, Cross-certificate, Certificate,
* Key Update and Key Recovery Requests which can further be
* communicated to a CA.
* Input to this API can be provided using CRMF_createCertReqMsg().
*
* @param[in] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CertReqMsgList* Pointer to CRMF_CertReqMsgList [pCertReqList|N/A]
* @retval CRMF_CertReqMsgList* If the input is NULL or on memory allocation failure [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CertReqMsgList* CRMF_createCertReq (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);




/**
* @defgroup CRMF_createCertReqMsg
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_REQ_MSG_S* CRMF_createCertReqMsg (SEC_INT32 iCertReqID,
* CRMF_CERT_TEMPLATE_S* pstCertTmp);
* @endcode
*
* @par Purpose
* To create a Certificate Request Message that can be added
* to the Certificate Request Message List in the PKI Message.
*
* @par Description
* This function creates a Certificate Request Message that can be added
* to the Certificate Request Message List in the PKI Message.
*
* @param[in] iCertReqID ID for matching request and reply.
* A valid Request should hold an ID greater than or equal to zero [N/A]
* @param[in] pstCertTmp Pointer to CRMF_CERT_TEMPLATE_S structure
* This input can be provided using CRMF_createCertTemplate() [N/A]
* @param[out] N/A N/A [N/A]

* @retval CRMF_CERT_REQ_MSG_S* Pointer to the CRMF_CERT_REQ_MSG_S structure [pstCertReqMsg|N/A]
* @retval CRMF_CERT_REQ_MSG_S* If either of the inputs are NULL or on memory allocation failure[SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CERT_REQ_MSG_S* CRMF_createCertReqMsg (SEC_INT32 iCertReqID,
                                            CRMF_CERT_TEMPLATE_S* pstCertTmp);




/**
* @defgroup CRMF_addCertReqMsg
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_addCertReqMsg (CRMF_CertReqMsgList* pCertReq,
* CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To add Certificate Request Message to the
* CRMF_Certificate Request Message List.
*
* @par Description
* This function adds Certificate Request Message to the
* CRMF_Certificate Request Message List.
* Depending on the Request type, only one or two Certificate
* Request Messages can be added to the List.
*
* @param[in] pCertReq Pointer to Certificate Request Message List [N/A]
* @param[in] pstCertReqMsg Pointer to the CRMF_CERT_REQ_MSG_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On successful completion [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If either of the inputs are NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If duplicatiing the request msg failed [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If the Count in the Certificate Request
* Message List is equal to 2 [SEC_ERR_EXCESS_NODES|N/A]
* @retval SEC_UINT32 If adding pstCertReqMsg into the pCertReq List fails [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_addCertReqMsg (CRMF_CertReqMsgList* pCertReq,
                               CRMF_CERT_REQ_MSG_S* pstCertReqMsg);



/**
* @defgroup CRMF_createCertTemplate
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_TEMPLATE_S* CRMF_createCertTemplate (CRMF_REQMSG_TYPE_E enReqMsgType,
* SEC_UINT32 ulVersion,
* SEC_UINT32 ulHashAlgID,
* SEC_NAME_S* pstIssuer,
* SEC_NAME_S* pstSubject,
* CRMF_OPT_VALIDITY_S* pstValidity,
* SEC_PUBKEY_INFO_S* pstPubKeyInfo,
* SEC_AsnBits_S* pstIssrUID,
* SEC_AsnBits_S* pstSubjUID,
* X509_CERT_S *pstCert);
* @endcode
*
* @par Purpose
* To create a Certificate Template
* which can be provided as input to Certificate Request Message.
*
* @par Description
* This function is used to create a Certificate Template
* which can be provided as input to Certificate Request Message.
* Selected fields of the certificate to be issued can be put into
* this Certificate template structure.
*
* @param[in] enReqMsgType (CRMF_REQMSG_TYPE_E)-Request Type [N/A]
* @param[in] ulVersion Certificate Version Number [N/A]
* @param[in] ulHashAlgID Hash Algorithm [N/A]
* @param[in] pstIssuer Issuer Name-(Pointer to SEC_NAME_S structure) [N/A]
* @param[in] pstSubject Subject Name-(Pointer to SEC_NAME_S structure) [N/A]
* @param[in] pstValidity Pointer to CRMF_OPT_VALIDITY_S structure [N/A]
* @param[in] pstPubKeyInfo Pointer to SEC_PUBKEY_INFO_S structure [N/A]
* @param[in] pstIssrUID Pointer to Issuer Unique Identifier [N/A]
* @param[in] pstSubjUID Pointer to Subject Unique Identifier [N/A]
* @param[in] pstCert Pointer to X509_CERT_S structure [N/A]
* @param[out] N/A N/A [N/A]

* @retval CRMF_CERT_TEMPLATE_S* Pointer to CRMF_CERT_TEMPLATE_S structure [pstCertTemplate|N/A]
* @retval CRMF_CERT_TEMPLATE_S* If the Input is NULL or on memory allocation fail [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
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

PSELINKDLL CRMF_CERT_TEMPLATE_S* CRMF_createCertTemplate (CRMF_REQMSG_TYPE_E enReqMsgType,
                                               SEC_UINT32 ulVersion,
                                               SEC_UINT32 ulHashAlgID,
                                               SEC_NAME_S* pstIssuer,
                                               SEC_NAME_S* pstSubject,
                                               CRMF_OPT_VALIDITY_S* pstValidity,
                                               SEC_PUBKEY_INFO_S* pstPubKeyInfo,
                                               SEC_AsnBits_S* pstIssrUID,
                                               SEC_AsnBits_S* pstSubjUID,
                                               X509_CERT_S *pstCert);



/**
* @defgroup CRMF_addExtns
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_addExtns (CRMF_CERT_TEMPLATE_S* pstCertTemplate,
* Extensions* pExtnlist);
* @endcode
*
* @par Purpose
* To add Certificate Extensions to the Certificate Template.
*
* @par Description
* This Function is used to add Certificate Extensions
* to the Certificate Template.
*
* @param[in] pExtnlist Pointer to Extensions List [N/A]
* @param[out] pstCertTemplate Pointer to CRMF_CERT_TEMPLATE_S [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the Inputs are NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_DATA_COPY_FAILED|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_addExtns (CRMF_CERT_TEMPLATE_S* pstCertTemplate,
                          Extensions* pExtnlist);



/**
* @defgroup CRMF_addControls
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_addControls (CRMF_CERT_REQ_MSG_S* pstCertReqMsg,
* SEC_ATTR_TYPE_AND_VALUE_S* pstControl);
* @endcode
*
* @par Purpose
* To add an Attribute affecting the issuance.
*
* @par Description
* This function adds an Attribute affecting the issuance.
* The generator of a Certificate Request may include one or more control
* values pertaining to the processing of the request.
* Controls can be any one of the following:\n
* 1. Registration Token Control\n
* 2. Authenticator Control\n
* 3. Publication Information Control\n
* 4. Archive Options Control\n
* 5. OldCert ID Control\n
* 6. Protocol Encryption Key Control\n
* Input to this method can be provided by calling CRMF_createAttrTypeAndValForCntrl().
*
* @param[in] pstControl Pointer to SEC_ATTR_TYPE_AND_VALUE_S structure [N/A]
* @param[in] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If inputs are NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If List mem allocation fails [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 If adding pstRegInfo onto the List fails [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_addControls (CRMF_CERT_REQ_MSG_S* pstCertReqMsg,
                             SEC_ATTR_TYPE_AND_VALUE_S* pstControl);




/**
* @defgroup CRMF_addRegInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_addRegInfo (CRMF_CERT_REQ_MSG_S* pstCertReqMsg,
* SEC_ATTR_TYPE_AND_VALUE_S* pstRegInfo);
* @endcode
*
* @par Purpose
* To add Registration Information to Certificate Request.
*
* @par Description
* This function adds Registration Information to Certificate Request.
* This information may include subscriber contact information,
* billing information or other ancillary information useful to
* fulfillment of  the certification request.
* Input to this method can be provided by calling CRMF_createAttrTypeAndValForRegInfo().

* @param[in] pstRegInfo Pointer to SEC_ATTR_TYPE_AND_VALUE_S structure [N/A]
* @param[out] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S structure [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If inputs are NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_DATA_COPY_FAILED|N/A]
* @retval SEC_UINT32 If List mem allocation fails [SEC_ERR_DATA_NOT_AVAILABLE|N/A]
* @retval SEC_UINT32 If adding pstRegInfo onto the List fails [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_addRegInfo (CRMF_CERT_REQ_MSG_S* pstCertReqMsg,
                            SEC_ATTR_TYPE_AND_VALUE_S* pstRegInfo);




/**
* @defgroup CRMF_addPOPSigningKey
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_addPOPSigningKey (SEC_UINT32 ulHashAlgID,
* SEC_PKEY_S* pstPrivateKey,
* CRMF_POPOSIGNING_KEY_TYPE_E enPOPKeyInputType,
* SEC_GEN_NAME_S* pstSender,
* SEC_UINT32 ulPBAlgID,
* SEC_UCHAR* pucPassword,
* SEC_UINT32 ulPwdLen,
* SEC_UINT32 ulOWFAlgID,
* SEC_UINT32 ulMACAlgID,
* CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To add a Signing Key for Proof of Possession.
*
* @par Description
* This function adds a Signing Key for Proof of Possession.
* This method can be used to provide Proof of Possession as SigningKey
* and the Signature is the DER-encoded value of POP Signing Key Input or
* CertRequest parameter of Certificate Request Message
* @param[in] ulHashAlgID Hashing Algorithm for Signing
* @param[in] pstPrivateKey Self Private Key
* @param[in] enPOPKeyInputType Possible Values in CRMF_POPOSIGNING_KEY_TYPE_E
* @param[in] pstSender General Name , if enPOPKeyInputType = POPOSIGNINGKEYINPUTCHOICE_SENDER
* @param[in] ulPBAlgID Password Based Algorithm for calculating PasswordBasedMAC.
* If enPOPKeyInputType is POPOSIGNINGKEYINPUTCHOICE_PUBLICKEYMAC
* then ulPBALgID should be CID_PASSWORDBASEDMAC
* @param[in] pucPassword Pointer to Password
* @param[in] ulPwdLen Length of the password
* @param[in] ulOWFAlgID Hash/OWF Algorithm to calculate to PBMparameter
* @param[in] ulMACAlgID Algorithm for deriving PKMAC value
* @param[out] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S structure
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If Input parameters are NULL or Missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 In case of memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If SEC_encodePubKey() fails.[Error Code is the same as returned from CRYPT_sign()|N/A]
*           
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_addPOPSigningKey (SEC_UINT32 ulHashAlgID,
                                  SEC_PKEY_S* pstPrivateKey,
                                  CRMF_POPOSIGNING_KEY_TYPE_E enPOPKeyInputType,
                                  SEC_GEN_NAME_S* pstSender,
                                  SEC_UINT32 ulPBAlgID,
                                  SEC_UCHAR* pucPassword,
                                  SEC_UINT32 ulPwdLen,
                                  SEC_UINT32 ulOWFAlgID,
                                  SEC_UINT32 ulMACAlgID,
                                  CRMF_CERT_REQ_MSG_S* pstCertReqMsg);




/**
* @defgroup CRMF_addPOPPrivKey
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_addPOPPrivKey (CRMF_POP_E enType,
* CRMF_POPOPRIV_KEY_E enPOPPrivType,
* SEC_PKEY_S* pstPrivateKey,
* SEC_PKEY_S* pstPublicKey,
* SEC_UINT32 uiSubsequentMsgCh,
* SEC_NAME_S* pstIssuer,
* SEC_NAME_S* pstSubject,
* SEC_AsnBits_S* pstPrivBits,
* CRMF_CERT_REQ_MSG_S* pCertReqMsg);
* @endcode
*
* @par Purpose
* To add the Private Key as Proof of Possession.
*
* @par Description
* This function adds the Private Key as Proof of Possession.
* The proof of possession field is used to demonstrate that the entity
* to be associated with the certificate is actually in possession
* of the corresponding private key. This method provides one of the way
* to prove the possession.
*
* @param[in] enType Agreement Key or Encipherment Key [N/A]
* @param[in] enPOPPrivType Can be thisMessage, Subsequent Message or DHMAC [N/A]
* @param[in] pstPrivateKey Self RSA/DH Private Key [N/A]
* @param[in] pstPublicKey Peer RSA/DH Public Key [N/A]
* @param[in] uiSubsequentMsgCh Integer specifying CRMF_ENCRYPT_CERT or CRMF_CHALLENGE_RESP [N/A]
* @param[in] pstIssuer Issuer Name to compute DHMAC in POPOPRIVKEY_DHMAC [N/A]
* @param[in] pstSubject Subject Name to compute DHMAC in POPOPRIVKEY_DHMAC [N/A]
* @param[in] pstPrivBits Encrypted Private Key for POPOPRIVKEY_THISMESSAGE
* This can be obtained by using the
* CRMF_createEncryptedPrivKey() interface [N/A]
* @param[out] pCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S structure [N/A]

* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If Input parameters are NULL or Missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 In case of memory allocation failure [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If Encode fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 Error during CRYPT_digestFinal() [Error Code returned from CRYPT_digestFinal()|N/A]
* @retval SEC_UINT32 Error during CRYPT_computeDHKey() [Error Code returned from CRYPT_computeDHKey()|N/A]
* @retval SEC_UINT32 Error during CRYPT_hmac() [Error Code returned from CRYPT_hmac()|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_addPOPPrivKey (CRMF_POP_E enType,
                               CRMF_POPOPRIV_KEY_E enPOPPrivType,
                               SEC_PKEY_S* pstPrivateKey,/* CA or EE */
                               SEC_PKEY_S* pstPublicKey,/* EE or CA */
                               SEC_UINT32 uiSubsequentMsgCh,
                               SEC_NAME_S* pstIssuer,
                               SEC_NAME_S* pstSubject,
                               SEC_AsnBits_S* pstPrivBits,
                               CRMF_CERT_REQ_MSG_S* pCertReqMsg);




/**
* @defgroup CRMF_getCertTemplate
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_TEMPLATE_S* CRMF_getCertTemplate (CRMF_CERT_REQ_MSG_S* pCertReqMsg);
* @endcode
*
* @par Purpose
* To get Certificate Template structure from Certificate Request Message.
*
* @par Description
* This function gets Certificate Template structure from Certificate Request Message.
*
* @param[in] pCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S structure from which
* the Certificate Template is Retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_TEMPLATE_S* Pointer to CRMF_CERT_TEMPLATE_S structure [pstCertTemplate|N/A]
* @retval CRMF_CERT_TEMPLATE_S* If the Input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CERT_TEMPLATE_S* CRMF_getCertTemplate (CRMF_CERT_REQ_MSG_S* pCertReqMsg);




/**
* @defgroup CRMF_getFirstCertReqMsg
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_REQ_MSG_S* CRMF_getFirstCertReqMsg (CRMF_CertReqMsgList* pstCertReqMsgList);
* @endcode
*
* @par Purpose
* To get the First Certificate Request Message from the Certificate Request List.
*
* @par Description
* This function gets the First Certificate Request Message from the Certificate Request List.
*
* @param[in] pstCertReqMsgList List from which the Certificate Request Message is retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_REQ_MSG_S* Pointer to CRMF_CERT_REQ_MSG_S  structure [pstCertReqMsg|N/A]
* @retval CRMF_CERT_REQ_MSG_S* If the input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CERT_REQ_MSG_S* CRMF_getFirstCertReqMsg (CRMF_CertReqMsgList* pstCertReqMsgList);




/**
* @defgroup CRMF_getNextCertReqMsg
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_REQ_MSG_S* CRMF_getNextCertReqMsg (CRMF_CertReqMsgList* pstCertReqMsgList);
* @endcode
*
* @par Purpose
* To get the Next Certificate Request Message from the Certificate Request List.
*
* @par Description
* This function gets the Next Certificate Request Message from the Certificate Request List.
*
* @param[in] pstCertReqMsgList List from which the Certificate Request Message is retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_REQ_MSG_S* Pointer to CRMF_CERT_REQ_MSG_S  structure [pstCertReqMsg|N/A]
* @retval CRMF_CERT_REQ_MSG_S* If the input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CERT_REQ_MSG_S* CRMF_getNextCertReqMsg (CRMF_CertReqMsgList* pstCertReqMsgList);




/**
* @defgroup CRMF_getPOP
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_POP_S* CRMF_getPOP (CRMF_CERT_REQ_MSG_S* pCertReqMsg);
* @endcode
*
* @par Purpose
* To get Proof of Possession Structure from Certificate Request Message.
*
* @par Description
* This function gets Proof of Possession Structure from Certificate Request Message.
*
* @param[in] pCertReqMsg The structure from which the POP is
* Retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_POP_S* Pointer to CRMF_POP_S structure [CRMF_POP_S*|N/A]
* @retval CRMF_POP_S* If the input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_POP_S* CRMF_getPOP (CRMF_CERT_REQ_MSG_S* pCertReqMsg);




/**
* @defgroup CRMF_getCertReqId
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_INT32 CRMF_getCertReqId (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To get Certificate Request ID from the Certificate Request structure.
*
* @par Description
* This function gets Certificate Request ID from the Certificate Request structure.
*
* @param[in] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S structure
* is retrived [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval SEC_INT32 Certificate Request ID [SEC_INT32|N/A]
* @retval SEC_INT32 If the input is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If Request ID is not specified [-1|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_INT32 CRMF_getCertReqId (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);




/**
* @defgroup CRMF_getPOPPrivKeyType
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID* CRMF_getPOPPrivKeyType (CRMF_POPOPRIV_KEY_S* pstPrivKey);
* @endcode
*
* @par Purpose
* To get Proof of Possession of Private Key from Certificate Request Message.
*
* @par Description
* This function gets Proof of Possession of Private Key from Certificate Request Message.
*
* @param[in] pstPrivKey Pointer to CRMF_POPOPRIV_KEY_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Pointer to ThisMessage, SubMessage Type or the dhMAC
* depending on the CRMF_POPOPRIV_KEY_E type [SEC_VOID*|N/A]
* @retval SEC_VOID* If the input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID* CRMF_getPOPPrivKeyType (CRMF_POPOPRIV_KEY_S* pstPrivKey);




/**
* @defgroup CRMF_getSigningKeyInput
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID* CRMF_getSigningKeyInput (CRMF_POPOSIGNING_KEY_S* pPOPOSigningKey);
* @endcode
*
* @par Purpose
* To get POPOSigningKeyInput structure from POPOSigningKey structure.
*
* @par Description
* This function gets POPOSigningKeyInput structure from POPOSigningKey structure.
*
* @param[in] pPOPOSigningKey Pointer to CRMF_POPOSIGNING_KEY_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID* Pointer Pointer to Sender Name or Public Key MAC value
* depending on the CRMF_POPOSIGNING_KEY_TYPE_E set [SEC_VOID*|N/A]
* @retval SEC_VOID* If the input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID* CRMF_getSigningKeyInput (CRMF_POPOSIGNING_KEY_S* pPOPOSigningKey);




/**
* @defgroup CRMF_getSigningKeyAlgId
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_getSigningKeyAlgId (CRMF_POPOSIGNING_KEY_S* pstPOPSigningKey);
* @endcode
*
* @par Purpose
* To get Signing Key Algorithm Identifier structure
* from POPSigningKey structure.
*
* @par Description
* This function gets Signing Key Algorithm Identifier structure
* from POPSigningKey structure.
*
* @param[in] pstPOPSigningKey Pointer to CRMF_POPOSIGNING_KEY_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 Signing Algorithm ID [ulAlgID|N/A]
* @retval SEC_UINT32 Invalid Algorithm [CID_UNKNOWN|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_getSigningKeyAlgId (CRMF_POPOSIGNING_KEY_S* pstPOPSigningKey);




/**
* @defgroup CRMF_getAuthInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_POPOSIGNING_KEY_TYPE_E CRMF_getAuthInfo (CRMF_POPOSIGNING_KEYIN_S* pstPOPSigningKeyInput);
* @endcode
*
* @par Purpose
* To get POP Signing Key Input Choice.
*
* @par Description
* This function gets POP Signing Key Input Choice.
*
* @param[in] pstPOPSigningKeyInput Pointer to CRMF_POPOSIGNING_KEYIN_S structure [N/A]
* @param[out] N/A N/A [N/A]
* @retval CRMF_POPOSIGNING_KEY_TYPE_E On success [CRMF_POPOSIGNING_KEY_TYPE_E|N/A]
* @retval CRMF_POPOSIGNING_KEY_TYPE_E On NULL or Invalid Input [POPOSIGNINGKEYINPUTCHOICE_INVALID|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_POPOSIGNING_KEY_TYPE_E CRMF_getAuthInfo (CRMF_POPOSIGNING_KEYIN_S* pstPOPSigningKeyInput);




/**
* @defgroup CRMF_getPubKeyInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_PUBKEY_INFO_S* CRMF_getPubKeyInfo (CRMF_POPOSIGNING_KEYIN_S* pPOPOSigningKeyInput);
* @endcode
*
* @par Purpose
* To get Subject Public Key Information structure from
* POP Signing Key Input structure.
*
* @par Description
* This function gets Subject Public Key Information structure from
* POP Signing Key Input structure.
*
* @param[in] pPOPOSigningKeyInput Pointer to CRMF_POPOSIGNING_KEYIN_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_PUBKEY_INFO_S* Pointer to the Key Information [SEC_PUBKEY_INFO_S*|N/A]
* @retval SEC_PUBKEY_INFO_S* If the input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_PUBKEY_INFO_S* CRMF_getPubKeyInfo (CRMF_POPOSIGNING_KEYIN_S* pPOPOSigningKeyInput);




/**
* @defgroup CRMF_getAlgId
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_getAlgId (CRMF_PKMAC_S* pPublicKeyMAC);
* @endcode
*
* @par Purpose
* To get Algorithm Identifier from
* PKMAC Value structure.
*
* @par Description
* This function gets Algorithm Identifier from
* PKMAC Value structure.
*
* @param[in] pPublicKeyMAC Pointer to CRMF_PKMAC_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_INT32 Password Based Algorithm ID [ulAlgID|N/A]
* @retval SEC_INT32 Invalid Algorithm [CID_UNKNOWN|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_getAlgId (CRMF_PKMAC_S* pPublicKeyMAC);




/**
* @defgroup CRMF_getMACValue
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* CRMF_getMACValue (CRMF_PKMAC_S* pPublicKeyMAC);
* @endcode
*
* @par Purpose
* To get MAC Value from CRMF_PKMAC_S structure.
*
* @par Description
* This function gets MAC Value from CRMF_PKMAC_S structure.
*
* @param[in] pPublicKeyMAC Pointer to CRMF_PKMAC_S structure from which the Value is retrieved [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBits_S* The Structure that holds the value [SEC_AsnBits_S*|N/A]
* @retval SEC_AsnBits_S* If the input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnBits_S* CRMF_getMACValue (CRMF_PKMAC_S* pPublicKeyMAC);




/**
* @defgroup CRMF_createSinglePubInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_SINGLE_PUBINFO_S* CRMF_createSinglePubInfo (SEC_UINT32 ulPubMethod,
* SEC_GEN_NAME_S* pstLocation);
* @endcode
*
* @par Purpose
* To create a Single Publication Info.
*
* @par Description
* This function creates a Single Publication Info.
*
* @param[in] ulPubMethod Method for publishing the Certificate
* Method can be DONTCARE, X500, WEB or LDAP [N/A]
* @param[in] pstLocation Pointer to X509_GeneralName_S structure
* The pubLocation field, if supplied, indicates where the requester
* would like the certificate to be found  (Note that the choice within
* GeneralName includes a URL and an IP address) [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_SINGLE_PUBINFO_S* Pointer to
* CRMF_SINGLE_PUBINFO_S structure [pstSinglePubInfo|N/A]
* @retval CRMF_SINGLE_PUBINFO_S* If any of the inputs are NULL or Invalid [SEC_NULL_PTR|N/A]
* @retval CRMF_SINGLE_PUBINFO_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
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

PSELINKDLL CRMF_SINGLE_PUBINFO_S* CRMF_createSinglePubInfo (SEC_UINT32 ulPubMethod,
                                                 SEC_GEN_NAME_S* pstLocation);



/**
* @defgroup CRMF_createPubInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_PUBLICATION_INFO_S* CRMF_createPubInfo (SEC_UINT32 ulAction,
* CRMF_SINGLE_PUBINFO_S* pstSinglePubInfo);
* @endcode
*
* @par Purpose
* To create a CRMF_PUBLICATION_INFO_S structure.
*
* @par Description
* This function creates a CRMF_PUBLICATION_INFO_S structure.
* This is called when the Publication Information needs to be added
* in any of these: Initialization, Certificate, Key Recovery or Key Update Response.
*
* @param[in] ulAction Integer specifying CRMF_CERT_PUBLISH or CRMF_CERT_DONTPUBLISH [N/A]
* @param[in] pstSinglePubInfo Pointer to CRMF_SINGLE_PUBINFO_S structure
* Input to this method can be provided by calling CRMF_createSinglePubInfo() [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_PUBLICATION_INFO_S* Pointer to CRMF_PUBLICATION_INFO_S structure [pstPubInfo|N/A]
* @retval CRMF_PUBLICATION_INFO_S* If any of the inputs are NULL or Invalid [SEC_NULL_PTR|N/A]
* @retval CRMF_PUBLICATION_INFO_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
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

PSELINKDLL CRMF_PUBLICATION_INFO_S* CRMF_createPubInfo (SEC_UINT32 ulAction,
                                             CRMF_SINGLE_PUBINFO_S* pstSinglePubInfo);




/**
* @defgroup CRMF_addSinglePubInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_addSinglePubinfo (CRMF_PUBLICATION_INFO_S* pstPubInfo,
* CRMF_SINGLE_PUBINFO_S* pstSinglePubInfo);
* @endcode
*
* @par Purpose
* To add a Single Publication Information structure to the list in the
* CRMF_PUBLICATION_INFO_S structure.
*
* @par Description
* This function adds a Single Publication Information structure to the list in the
* CRMF_PUBLICATION_INFO_S structure.
* If the requester wishes the certificate to appear in at least some locations
* but wishes to enable the CA to make the certificate available in other
* repositories, this method can be called.
* Input to this method can be provided by calling CRMF_createSinglePubInfo().
*
* @param[in] pstSinglePubInfo Pointer to CRMF_SINGLE_PUBINFO_S structure [N/A]
* @param[out] pstPubInfo Pointer to CRMF_PUBLICATION_INFO_S structure [N/A]
*
* @retval SEC_UINT32 On successful completion [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If inputs are NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If adding pstSinglePubInfo onto the List fails [SEC_ERR_LIST_OPERATION_FAILED|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_addSinglePubinfo (CRMF_PUBLICATION_INFO_S* pstPubInfo,
                                  CRMF_SINGLE_PUBINFO_S* pstSinglePubInfo);




/**
* @defgroup CRMF_createAttrTypeAndValForCntrl
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* CRMF_createAttrTypeAndValForCntrl (SEC_UINT32 ulAttrID,
* SEC_UINT32 ulAttrValLen,
* SEC_UCHAR* pucAttrValue,
* SEC_VOID* pComponent);
* @endcode
*
* @par Purpose
* To create the Attribute Type and Value to be added onto the Controls List
* of the Certificate Request.
*
* @par Description
* This function creates the Attribute Type and Value to be added onto the Controls List
* of the Certificate Request.
*
* @param[in] ulAttrID AttrType, can be Registration Token Control,
*                        Authenticator Control,
*                        Publication Information Control,
*                        Archive Options Control,
*                        OldCert ID Control,
*                        Protocol Encryption Key Control [N/A]
* @param[in] ulAttrValLen Length of pucAttrValue [N/A]
* @param[in] pucAttrValue Pointer to Attribute Value
*                        This parameter should not be NULL with
*                        ulAttrID - CID_REGCTRL_REGTOKEN  or
*                        CID_REGCTRL_AUTHENTICATOR [N/A]
* @param[in] pComponent Void Pointer
*                        This parameter should not be NULL when ulAttrID value is one among the following below:
*                        CID_REGCTRL_PKIPUBLICATIONINFO (Pointer of type CRMF_PUBLICATION_INFO_S)
*                        CID_REGCTRL_PKIARCHIVEOPTIONS (Pointer of type CRMF_ARCHIVE_OPTS_S)
*                        CID_REGCTRL_OLDCERTID (Pointer of type CRMF_CERT_ID_S)
*                        CID_REGCTRL_PROTOCOLENCRKEY    (Pointer of type SEC_PUBKEY_INFO_S) [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to SEC_ATTR_TYPE_AND_VALUE_S structure [pstAttrTypeAndValue|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If any of the inputs are NULL or Invalid or memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
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

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* CRMF_createAttrTypeAndValForCntrl (SEC_UINT32 ulAttrID,
                                                              SEC_UINT32 ulAttrValLen,
                                                              SEC_UCHAR* pucAttrValue,
                                                              SEC_VOID* pComponent);




/**
* @defgroup CRMF_createAttrTypeAndValForRegInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* CRMF_createAttrTypeAndValForRegInfo (SEC_UINT32 ulAttrID,
* SEC_UINT32 ulAttrValLen,
* SEC_UCHAR* pucAttrValue,
* SEC_VOID* pComponent);
* @endcode
*
* @par Purpose
* To create the Attribute Type and Value to be added onto the Registration Info
* of the Certificate Request Message.
*
* @par Description
* This function creates the Attribute Type and Value to be added onto the Registration Info
* of the Certificate Request Message.
*
* @param[in] ulAttrID AttrType, Can be Name/Value Pairs,
*                                    CertRequest [N/A]
* @param[in] ulAttrValLen Length of pucAttrValue [N/A]
* @param[in] pucAttrValue Pointer to Attribute Value
*                        This parameter should not be NULL with
*                        ulAttrID - CID_REGINFO_UTF8PAIRS [N/A]
* @param[in] pComponent Void Pointer
*                        This can take a pointer of type CRMF_CERT_REQ_S
*                        when ulAttrID value is CID_REGINFO_CERTREQ [N/A]
* @param[out] N/A N/A [N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to SEC_ATTR_TYPE_AND_VALUE_S [pstAttrTypeAndValue|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If any of the inputs are NULL or Invalid or memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
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

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* CRMF_createAttrTypeAndValForRegInfo (SEC_UINT32 ulAttrID,
                                                                SEC_UINT32 ulAttrValLen,
                                                                SEC_UCHAR* pucAttrValue,
                                                                SEC_VOID* pComponent);




/**
* @defgroup CRMF_freePKIPubInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID CRMF_freePKIPubInfo (CRMF_PUBLICATION_INFO_S* pstPubInfo);
* @endcode
*
* @par Purpose
* To free the PKI Publication Information structure.
*
* @par Description
* This function is used to free the PKI  Publication Information structure.
*
* @param[in] pstPubInfo Pointer to CRMF_PUBLICATION_INFO_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID CRMF_freePKIPubInfo (CRMF_PUBLICATION_INFO_S* pstPubInfo);




/**
* @defgroup CRMF_freeCertId
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID CRMF_freeCertId  (CRMF_CERT_ID_S* pstCertId);
* @endcode
*
* @par Purpose
* To free the Certificate identifier.
*
* @par Description
* This function is used to free the Certificate identifier.
*
* @param[in] pstCertId Pointer to CRMF_CERT_ID_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID CRMF_freeCertId  (CRMF_CERT_ID_S* pstCertId);




/**
* @defgroup CRMF_freeCertTemplate
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID CRMF_freeCertTemplate  (CRMF_CERT_TEMPLATE_S* pstCertTemplate);
* @endcode
*
* @par Purpose
* To free the Certificate Template.
*
* @par Description
* This function is used to free the Certificate Template.
*
* @param[in] pstCertTemplate Pointer to CRMF_CERT_TEMPLATE_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID CRMF_freeCertTemplate  (CRMF_CERT_TEMPLATE_S* pstCertTemplate);




/**
* @defgroup CRMF_freeOptionalValidity
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID CRMF_freeOptionalValidity (CRMF_OPT_VALIDITY_S* pstOptValidity);
* @endcode
*
* @par Purpose
* To free the Optional Validity Structure.
*
* @par Description
* This function is used to free the Optional Validity Structure.
*
* @param[in] pstOptValidity Pointer to CRMF_OPT_VALIDITY_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID CRMF_freeOptionalValidity (CRMF_OPT_VALIDITY_S* pstOptValidity);



/**
* @defgroup CRMF_freePKIArchiveOptions
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID CRMF_freePKIArchiveOptions (CRMF_ARCHIVE_OPTS_S* pstArchiveOpts);
* @endcode
*
* @par Purpose
* To free the Archive Options of Control in Certificate Request Message.
*
* @par Description
* This function is used to free the Archive Options of Control in Certificate Request Message.
*
* @param[in] pstArchiveOpts Pointer to CRMF_ARCHIVE_OPTS_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID CRMF_freePKIArchiveOptions (CRMF_ARCHIVE_OPTS_S* pstArchiveOpts);



/**
* @defgroup CRMF_freeCertReqMessages
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID CRMF_freeCertReqMessages (CRMF_CertReqMsgList* pstCertReqMsgLst);
* @endcode
*
* @par Purpose
* To free the List of Certificate Request Messages.
*
* @par Description
* This function is used to free the List of Certificate Request Messages.
*
* @param[in] pstCertReqMsgLst Pointer to CRMF_CertReqMsgList [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID CRMF_freeCertReqMessages (CRMF_CertReqMsgList* pstCertReqMsgLst);



/**
* @defgroup CRMF_freeCertReqMsg
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID CRMF_freeCertReqMsg (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To free the Certificate Request Message.
*
* @par Description
* This function is used to free the Certificate Request Message.
*
* @param[in] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID CRMF_freeCertReqMsg (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);




/**
* @defgroup CRMF_freeSinglePubInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_VOID CRMF_freeSinglePubInfo (CRMF_SINGLE_PUBINFO_S* pSinglePKIPubInfo);
* @endcode
*
* @par Purpose
* To free the SinglePubInfo.
*
* @par Description
* This function is used to free the SinglePubInfo.
*
* @param[in] pSinglePKIPubInfo Pointer to CRMF_SINGLE_PUBINFO_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_VOID CRMF_freeSinglePubInfo (CRMF_SINGLE_PUBINFO_S* pSinglePKIPubInfo);




/**
* @defgroup CRMF_getFirstRegInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* CRMF_getFirstRegInfo (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To get First Registration Information from the list in Certificate Request Message.
*
* @par Description
* This function gets First Registration Information from the list in Certificate Request Message.
*
* @param[in] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S Structure [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to SEC_ATTR_TYPE_AND_VALUE_S [pstAttrTypeAndVal|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If the Input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* CRMF_getFirstRegInfo (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);




/**
* @defgroup CRMF_getNextRegInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* CRMF_getNextRegInfo (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To get Next Registration Information from the list in Certificate Request Message.
*
* @par Description
* This function gets Next Registration Information from the list in Certificate Request Message.
*
* @param[in] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S Structure [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to SEC_ATTR_TYPE_AND_VALUE_S [pstAttrTypeAndVal|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If the Input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* CRMF_getNextRegInfo (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);




/**
* @defgroup CRMF_getFirstControls
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* CRMF_getFirstControls (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To get First Attribute from the Controls list of the  Certificate Request.
*
* @par Description
* This function gets First Attribute from the Controls list of the  Certificate Request.
*
* @param[in] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S Structure [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to SEC_ATTR_TYPE_AND_VALUE_S [pstAttrTypeAndVal|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If the Input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* CRMF_getFirstControls (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);




/**
* @defgroup CRMF_getNextControls
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* CRMF_getNextControls (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);
* @endcode
*
* @par Purpose
* To get Next Attribute from the Controls list of the  Certificate Request.
*
* @par Description
* This function gets Next Attribute from the Controls list of the  Certificate Request.
*
* @param[in] pstCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S Structure [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to SEC_ATTR_TYPE_AND_VALUE_S [pstAttrTypeAndVal|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If the Input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* CRMF_getNextControls (CRMF_CERT_REQ_MSG_S* pstCertReqMsg);




/**
* @defgroup CRMF_createIssuerUID
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* CRMF_createIssuerUID (SEC_NAME_S* pstIssuer);
* @endcode
*
* @par Purpose
* To encode the Issuer Name to get Issuer UID.
*
* @par Description
* This function encodes the Issuer Name to get Issuer UID.
*
* @param[in] pstIssuer Pointer to SEC_NAME_S structure [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBits_S* Pointer to SEC_AsnBits_S [pstEncodedIssuerName|N/A]
* @retval SEC_AsnBits_S* If the Input is NULL [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnBits_S* CRMF_createIssuerUID (SEC_NAME_S* pstIssuer);




/**
* @defgroup CRMF_createSubjectUID
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* CRMF_createSubjectUID (SEC_NAME_S* pstSubject);
* @endcode
*
* @par Purpose
* To encode the Subject Name to get SubjUID.
*
* @par Description
* This function encodes the Subject Name to get SubjUID.
*
* @param[in] pstSubject Pointer to SEC_NAME_S structure [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_AsnBits_S* Pointer to SEC_AsnBits_S [pstEncodedSubjectName|N/A]
* @retval SEC_AsnBits_S* If the Input is NULL or the memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_AsnBits_S* CRMF_createSubjectUID (SEC_NAME_S* pstSubject);


/**
* @defgroup CRMF_createEncryptedPrivKey
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_AsnBits_S* CRMF_createEncryptedPrivKey(SEC_PKEY_S* pstPrivKey,
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
* To create the Encrypted Private Key.
*
* @par Description
* This function creates the Encrypted Private Key.
* This method encodes and encrypts the Private Key using the Symmetric Key
* The output of this method is to be provided for the proving the possession
* @param[in] pstPrivKey Pointer to Self Private Key [N/A]
* @param[in] ulIntndAlg Intended Algorithm Identifier
*                        Used if EncryptedValue might be re-examined by the sending entity in the future [N/A]
* @param[in] ulSymmAlg Symmetric Algorithm used to encrypt the Private Key [N/A]
* @param[in] pstPubKey Pointer to Peer Public Key [N/A]
* @param[in] ulPubKeyAlgId Algorithm used to encrypt the symmetric key [N/A]
* @param[in] ulKeyGenAlgId Algorithm used to generate symmetric key [N/A]
* @param[in] pucValueHint Pointer to a brief description or
                                        identifier of the encValue content [N/A]
* @param[in] ulValueHint Length of value hint [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_AsnBits_S* Pointer to SEC_AsnBits_S [pPrivBits|N/A]
* @retval SEC_AsnBits_S* If any of the Inputs are Invalid or memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
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

PSELINKDLL SEC_AsnBits_S* CRMF_createEncryptedPrivKey(SEC_PKEY_S* pstPrivKey,
                                           SEC_UINT32 ulIntndAlg,
                                           SEC_UINT32 ulSymmAlg,
                                           SEC_PKEY_S* pstPubKey,
                                           SEC_UINT32 ulPubKeyAlgId,
                                           SEC_UINT32 ulKeyGenAlgId,
                                           SEC_UCHAR* pucValueHint,
                                           SEC_UINT32 ulValueHint);




/**
* @defgroup CRMF_createPKIArchiveOpts
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_ARCHIVE_OPTS_S* CRMF_createPKIArchiveOpts (SEC_UINT32 ulChoice,
* SEC_VOID* pstType);
* @endcode
*
* @par Purpose
* To create PKIArchiveOptions that can be added as part of Controls.
*
* @par Description
* This function creates PKIArchiveOptions that can be added as part of Controls.
* The PKIArchiveOptions control enables subscribers to
* supply information needed to establish an archive of the private key
* corresponding to the public key of the certification request.
*
* @param[in] ulChoice Choice can be one of the following
*                    CRMF_PKIARCHOPT_ENCKEY_ENCRYPTEDVAL
*                    CRMF_PKIARCHOPT_ENCKEY_ENVELOPEDDATA
*                    CRMF_PKIARCHOPT_KEYGENPARAMETERS
*                    CRMF_PKIARCHOPT_ARCHIVEREMGENPRIVKEY [N/A]
* @param[in] pstType SEC_VOID* depending on value of ulChoice
*                    it can be pointer to CRMF_ENCRYPTED_KEY_S or
*                    PKCS7_MSG_S or
*                    SEC_AsnOcts_S or
*                    SEC_AsnBool [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_ARCHIVE_OPTS_S* Pointer to CRMF_ARCHIVE_OPTS_S structure [pstArchiveOpts|N/A]
* @retval CRMF_ARCHIVE_OPTS_S* If any of the inputs are Invalid or memory allocation fails[SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
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

PSELINKDLL CRMF_ARCHIVE_OPTS_S* CRMF_createPKIArchiveOpts (SEC_UINT32 ulChoice,
                                                SEC_VOID* pstType);




/**
* @defgroup CRMF_verifyPOPSigningKey
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_verifyPOPSigningKey (CRMF_CERT_REQ_MSG_S* pCertReqMsg,
* SEC_PKEY_S* pPubKey);
* @endcode
*
* @par Purpose
* To verify the Proof Of Possession of the Signing Key.
*
* @par Description
* This Function is used to verify the Proof Of Possession of the Signing Key.
*
* @param[in] pCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S Structure [N/A]
* @param[in] pPubKey Public Key to verify the Sign [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If Encoding fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UNIT32 If CRYPT_verify() fails [Error Code from CRYPT_verify()|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/


PSELINKDLL SEC_UINT32 CRMF_verifyPOPSigningKey (CRMF_CERT_REQ_MSG_S* pCertReqMsg,
                                     SEC_PKEY_S* pPubKey);




/**
* @defgroup CRMF_verifyPOPPrivKey
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_UINT32 CRMF_verifyPOPPrivKey (CRMF_CERT_REQ_MSG_S* pCertReqMsg,
* SEC_NAME_S* pstIssuer,
* SEC_NAME_S* pstSubject,
* SEC_PKEY_S* pPrivKey,
* SEC_PKEY_S* pPubKey);
* @endcode
*
* @par Purpose
* To verify the Proof Of Possession done using the Private Key.
*
* @par Description
* This Function is used to verify the Proof Of Possession done using the Private Key.
* It can be used when the possession is proven in case of
* POPOPRIVKEY_DHMAC or POPOPRIVKEY_THISMESSAGE.
*
* @param[in] pCertReqMsg Pointer to CRMF_CERT_REQ_MSG_S Structure [N/A]
* @param[in] pstIssuer Issuer Name [N/A]
* @param[in] pstSubject Subject Name [N/A]
* @param[in] pPrivKey Own DH/RSA Private Key to compute the Shared secret [N/A]
* @param[in] pPubKey Peer DH/RSA Public Key to compute the Shared secret [N/A]
* @param[out] N/A N/A [N/A]

* @retval SEC_UINT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If any of the inputs are NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If memory allocation fails [SEC_ERR_MALLOC_FAIL|N/A]
* @retval SEC_UINT32 If Encoding fails [SEC_ERR_ENCODE_FAILED|N/A]
* @retval SEC_UINT32 If Decoding of Encrypted PrivateKey fails [SEC_ERR_DECODE_FAILED|N/A]
* @retval SEC_UINT32 If Verify fails [SEC_ERR_VERIFY_FAILED|N/A]
* @retval SEC_UINT32 Error during CRYPT_random() [Error Code returned from CRYPT_random()|N/A]
* @retval SEC_UINT32 Error during CRYPT_digestFinal() [Error Code returned from CRYPT_digestFinal()|N/A]
* @retval SEC_UINT32 Error during CRYPT_hmac() [Error Code returned from CRYPT_hmac()|N/A]
* @retval SEC_UINT32 Error during CRYPT_privKeyDecrypt() [Error Code returned from CRYPT_privKeyDecrypt()|N/A]
* @retval SEC_UINT32 Error during CRYPT_decrypt() [Error Code returned from CRYPT_decrypt()|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 CRMF_verifyPOPPrivKey (CRMF_CERT_REQ_MSG_S* pCertReqMsg,
                                  SEC_NAME_S* pstIssuer,
                                  SEC_NAME_S* pstSubject,
                                  SEC_PKEY_S* pPrivKey,
                                  SEC_PKEY_S* pPubKey);





/**
* @defgroup SEC_dupOptionalValidity
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_OPT_VALIDITY_S* SEC_dupOptionalValidity (CRMF_OPT_VALIDITY_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_OPT_VALIDITY_S* Pointer to destination [CRMF_OPT_VALIDITY_S*|N/A]
* @retval CRMF_OPT_VALIDITY_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_OPT_VALIDITY_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_OPT_VALIDITY_S* SEC_dupOptionalValidity (CRMF_OPT_VALIDITY_S* pSrc);

/**
* @defgroup SEC_dupCRMFAttributeTypeAndValue
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_ATTR_TYPE_AND_VALUE_S* SEC_dupCRMFAttributeTypeAndValue (SEC_ATTR_TYPE_AND_VALUE_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_ATTR_TYPE_AND_VALUE_S* Pointer to destination [SEC_ATTR_TYPE_AND_VALUE_S*|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval SEC_ATTR_TYPE_AND_VALUE_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_ATTR_TYPE_AND_VALUE_S* SEC_dupCRMFAttributeTypeAndValue (SEC_ATTR_TYPE_AND_VALUE_S* pSrc);

/**
* @defgroup SEC_dupPKMACValue
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_PKMAC_S* SEC_dupPKMACValue (CRMF_PKMAC_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_PKMAC_S* Pointer to destination [CRMF_PKMAC_S*|N/A]
* @retval CRMF_PKMAC_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_PKMAC_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_PKMAC_S* SEC_dupPKMACValue (CRMF_PKMAC_S* pSrc);

/**
* @defgroup SEC_dupEncryptedValue
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_ENCRYPTED_VALUE_S* SEC_dupEncryptedValue (CRMF_ENCRYPTED_VALUE_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_ENCRYPTED_VALUE_S* Pointer to destination [CRMF_ENCRYPTED_VALUE_S*|N/A]
* @retval CRMF_ENCRYPTED_VALUE_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_ENCRYPTED_VALUE_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_ENCRYPTED_VALUE_S* SEC_dupEncryptedValue (CRMF_ENCRYPTED_VALUE_S* pSrc);

/**
* @defgroup SEC_dupCertId
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_ID_S* SEC_dupCertId (CRMF_CERT_ID_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_CERT_ID_S* Pointer to destination [CRMF_CERT_ID_S*|N/A]
* @retval CRMF_CERT_ID_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_CERT_ID_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CERT_ID_S* SEC_dupCertId (CRMF_CERT_ID_S* pSrc);

/**
* @defgroup SEC_dupPOPOSigningKeyInputChoice
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_POPOSIGNING_KEY_TYPE_S* SEC_dupPOPOSigningKeyInputChoice (CRMF_POPOSIGNING_KEY_TYPE_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_POPOSIGNING_KEY_TYPE_S* Pointer to destination [CRMF_POPOSIGNING_KEY_TYPE_S*|N/A]
* @retval CRMF_POPOSIGNING_KEY_TYPE_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_POPOSIGNING_KEY_TYPE_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_POPOSIGNING_KEY_TYPE_S* SEC_dupPOPOSigningKeyInputChoice (CRMF_POPOSIGNING_KEY_TYPE_S* pSrc);

/**
* @defgroup SEC_dupCertReqMsgSeqOf
* @ingroup crmfFunctions
* @par Prototype
* @code
* SEC_List_S* SEC_dupCertReqMsgSeqOf (SEC_List_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S* Pointer to destination [SEC_List_S*|N/A]
* @retval SEC_List_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval SEC_List_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_List_S* SEC_dupCertReqMsgSeqOf (SEC_List_S* pSrc);

/**
* @defgroup SEC_dupCertTemplate
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_TEMPLATE_S* SEC_dupCertTemplate (CRMF_CERT_TEMPLATE_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_CERT_TEMPLATE_S* Pointer to destination [CRMF_CERT_TEMPLATE_S*|N/A]
* @retval CRMF_CERT_TEMPLATE_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_CERT_TEMPLATE_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CERT_TEMPLATE_S* SEC_dupCertTemplate (CRMF_CERT_TEMPLATE_S* pSrc);

/**
* @defgroup SEC_dupControls
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_ControlsLst* SEC_dupControls (CRMF_ControlsLst* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_ControlsLst* Pointer to destination [CRMF_ControlsLst*|N/A]
* @retval CRMF_ControlsLst* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_ControlsLst* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_ControlsLst* SEC_dupControls (CRMF_ControlsLst* pSrc);

/**
* @defgroup SEC_dupPOPOSigningKeyInput
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_POPOSIGNING_KEYIN_S* SEC_dupPOPOSigningKeyInput (CRMF_POPOSIGNING_KEYIN_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_POPOSIGNING_KEYIN_S* Pointer to destination [CRMF_POPOSIGNING_KEYIN_S*|N/A]
* @retval CRMF_POPOSIGNING_KEYIN_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_POPOSIGNING_KEYIN_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_POPOSIGNING_KEYIN_S* SEC_dupPOPOSigningKeyInput (CRMF_POPOSIGNING_KEYIN_S* pSrc);

/**
* @defgroup SEC_dupPOPOPrivKey
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_POPOPRIV_KEY_S* SEC_dupPOPOPrivKey (CRMF_POPOPRIV_KEY_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_POPOPRIV_KEY_S* Pointer to destination [CRMF_POPOPRIV_KEY_S*|N/A]
* @retval CRMF_POPOPRIV_KEY_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_POPOPRIV_KEY_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_POPOPRIV_KEY_S* SEC_dupPOPOPrivKey (CRMF_POPOPRIV_KEY_S* pSrc);

/**
* @defgroup SEC_dupSinglePubInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_SINGLE_PUBINFO_S* SEC_dupSinglePubInfo (CRMF_SINGLE_PUBINFO_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_SINGLE_PUBINFO_S* Pointer to destination [CRMF_SINGLE_PUBINFO_S*|N/A]
* @retval CRMF_SINGLE_PUBINFO_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_SINGLE_PUBINFO_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_SINGLE_PUBINFO_S* SEC_dupSinglePubInfo (CRMF_SINGLE_PUBINFO_S* pSrc);

/**
* @defgroup SEC_dupCRMF_EncryptedKey
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_ENCRYPTED_KEY_S* SEC_dupCRMF_EncryptedKey (CRMF_ENCRYPTED_KEY_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_ENCRYPTED_KEY_S* Pointer to destination [CRMF_ENCRYPTED_KEY_S*|N/A]
* @retval CRMF_ENCRYPTED_KEY_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_ENCRYPTED_KEY_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_ENCRYPTED_KEY_S* SEC_dupCRMF_EncryptedKey (CRMF_ENCRYPTED_KEY_S* pSrc);

/**
* @defgroup SEC_dupPKIPublicationInfoSeqOf
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_PublicationInfoList* SEC_dupPKIPublicationInfoSeqOf (CRMF_PublicationInfoList* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_PublicationInfoList* Pointer to destination [CRMF_PublicationInfoList*|N/A]
* @retval CRMF_PublicationInfoList* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_PublicationInfoList* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_PublicationInfoList* SEC_dupPKIPublicationInfoSeqOf (CRMF_PublicationInfoList* pSrc);

/**
* @defgroup SEC_dupCertRequest
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_REQ_S* SEC_dupCertRequest (CRMF_CERT_REQ_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_CERT_REQ_S* Pointer to destination [CRMF_CERT_REQ_S*|N/A]
* @retval CRMF_CERT_REQ_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_CERT_REQ_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CERT_REQ_S* SEC_dupCertRequest (CRMF_CERT_REQ_S* pSrc);

/**
* @defgroup SEC_dupPOPOSigningKey
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_POPOSIGNING_KEY_S* SEC_dupPOPOSigningKey (CRMF_POPOSIGNING_KEY_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_POPOSIGNING_KEY_S* Pointer to destination [CRMF_POPOSIGNING_KEY_S*|N/A]
* @retval CRMF_POPOSIGNING_KEY_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_POPOSIGNING_KEY_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_POPOSIGNING_KEY_S* SEC_dupPOPOSigningKey (CRMF_POPOSIGNING_KEY_S* pSrc);

/**
* @defgroup SEC_dupPKIPublicationInfo
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_PUBLICATION_INFO_S* SEC_dupPKIPublicationInfo (CRMF_PUBLICATION_INFO_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_PUBLICATION_INFO_S* Pointer to destination [CRMF_PUBLICATION_INFO_S*|N/A]
* @retval CRMF_PUBLICATION_INFO_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_PUBLICATION_INFO_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_PUBLICATION_INFO_S* SEC_dupPKIPublicationInfo (CRMF_PUBLICATION_INFO_S* pSrc);

/**
* @defgroup SEC_dupPKIArchiveOptions
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_ARCHIVE_OPTS_S* SEC_dupPKIArchiveOptions (CRMF_ARCHIVE_OPTS_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
* 
* @retval CRMF_ARCHIVE_OPTS_S* Pointer to destination [CRMF_ARCHIVE_OPTS_S*|N/A]
* @retval CRMF_ARCHIVE_OPTS_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_ARCHIVE_OPTS_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_ARCHIVE_OPTS_S* SEC_dupPKIArchiveOptions (CRMF_ARCHIVE_OPTS_S* pSrc);

/**
* @defgroup SEC_dupProofOfPossession
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_POP_S* SEC_dupProofOfPossession (CRMF_POP_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_POP_S* Pointer to destination [CRMF_POP_S*|N/A]
* @retval CRMF_POP_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_POP_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_POP_S* SEC_dupProofOfPossession (CRMF_POP_S* pSrc);

/**
* @defgroup SEC_dupCertReqMsg
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CERT_REQ_MSG_S* SEC_dupCertReqMsg (CRMF_CERT_REQ_MSG_S* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CERT_REQ_MSG_S* Pointer to destination [CRMF_CERT_REQ_MSG_S*|N/A]
* @retval CRMF_CERT_REQ_MSG_S* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_CERT_REQ_MSG_S* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CERT_REQ_MSG_S* SEC_dupCertReqMsg (CRMF_CERT_REQ_MSG_S* pSrc);

/**
* @defgroup SEC_dupCertReqMessages
* @ingroup crmfFunctions
* @par Prototype
* @code
* CRMF_CertReqMsgList* SEC_dupCertReqMessages (CRMF_CertReqMsgList* pSrc);
* @endcode
*
* @par Purpose
* To copy source pointer to destination pointer.
*
* @par Description
* The following method allows copying of a source pointer to a destination pointer
* internally allocating memory.
*
* @param[in] pSrc Pointer to source [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval CRMF_CertReqMsgList* Pointer to destination [CRMF_CertReqMsgList*|N/A]
* @retval CRMF_CertReqMsgList* If the input is NULL [SEC_NULL_PTR|N/A]
* @retval CRMF_CertReqMsgList* If memory allocation fails [SEC_NULL_PTR|N/A]
*
* @par Dependency
* crmf.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/

PSELINKDLL CRMF_CertReqMsgList* SEC_dupCertReqMessages (
    CRMF_CertReqMsgList* pSrc);

#ifdef __cplusplus
}
#endif

#endif /* _IPSI_CRMF_H_ */
#endif

//lint +e652



