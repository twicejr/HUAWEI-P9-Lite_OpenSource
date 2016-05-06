/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

------------------------------------------------------------------------------


                              pem.h

  Project Code: SeCert
  Module Name: PEM (Privacy Enhanced Mail)
  @brief  contains the function for encoding & decoding the input to PEM format
  The list of items in this file are:
  -PEM_encode PEM function to encode the input to PEM format
  -PEM_decode PEM function to decode the input from PEM format to respective format

*/

#include "ipsi_pse_build_conf.h"
#ifndef  _SEC_PEM_H_
#define   _SEC_PEM_H_

#include "sec_sys.h"
#include "sec_list.h"
#include "ipsi_types.h"

#ifdef	 __cplusplus
extern	"C"{
#endif

/** @defgroup pem
* This section contains the pem Structures, Functions and Enums.
*/

/** @defgroup pemEnums
* @ingroup pem
* This section contains the pem Enums
*/

/** @defgroup pemStructure
* @ingroup pem
* This section contains the pem Structures.
*/

/**
* @defgroup PEM_OBJTYPE_S
* @ingroup pemStructure
* @code
* typedef struct
* {
* 	SEC_CHAR* szObjTypeName;
* 	SEC_CHAR* (*pfEncode ) (void * , SEC_UINT32 * );
* 	void* (*pfDecode ) (SEC_CHAR* , SEC_UINT32, SEC_UINT32* );
* } PEM_OBJTYPE_S;
* @endcode
*
* @datastruct szObjTypeName String describing the type of the PEM object.
* @datastruct pfEncode Function Pointer to the encoding function for the given PEM object.
* @datastruct pfDecode Function Pointer to the decoding function for the given PEM object.
*/
typedef struct
{
	SEC_CHAR* szObjTypeName; /* string describing the type of the PEM object */
    /* Function pointer to the encoding function for the given PEM object */
	SEC_CHAR* (*pfEncode ) (void * , SEC_UINT32 * );
	/* Function pointer to the decoding function for the given PEM object */
	void* (*pfDecode ) (SEC_CHAR* , SEC_UINT32, SEC_UINT32* );
} PEM_OBJTYPE_S;


/** @defgroup pemFunctions
* @ingroup pem
* This section contains the PEM Functions
*/


/**
* @defgroup pem_encodeCertList
* @ingroup pemFunctions
* @par Prototype
* @code
* SEC_CHAR* pem_encodeCertList(SEC_List_S* pstCertList);
* @endcode
*
* @par Purpose
* To encode a certificate list in PEM format.
*
* @par Description
* This function encodes the list of certificates which is passed as the input parameter.
*
* @param[in] pstCertList The list which hold X509 Certificates [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR*  PEM format encoded certificate list output [SEC_CHAR*|N/A]
* @retval SEC_CHAR* If error [SEC_NULL|N/A]
*
* @par Dependency
* pem.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* @par Memory Handling
* \n
* 1. The encoded output buffer from pem_encodeCertList function should be freed
* by calling ipsi_free function.
* \n\n
* 2. Buffer returned by pem_encodeCertList will be Null Terminated. User is expected to pass this
* buffer as-is to the decoding API. If this buffer is passed to API(s) which take buffer and buffer
* length as input, the buffer len passed should also include the null termination character.
* Passing the value returned by strlen of encoded buffer is incorrect as it doesn't include the NULL
* termination character.
*/
PSELINKDLL SEC_CHAR* pem_encodeCertList (SEC_List_S* pstCertList);





/**
* @defgroup pem_decodeCertList
* @ingroup pemFunctions
* @par Prototype
* @code
* SEC_List_S* pem_decodeCertList(SEC_CHAR* pcEncodedCertList);
* @endcode
*
* @par Purpose
* To decode an encoded PEM format certificate list.
*
* @par Description
* This function decodes the list of certificates which is encoded in PEM format and passed as the input parameter.
*
* @param[in] pcEncodedCertList PEM encoded list of certificates [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_List_S*  Returns the list which contains X509 Certificates [SEC_List_S*|N/A]
* @retval SEC_List_S* If error [SEC_NULL|N/A]
*
* @par Dependency
* pem.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* @par Memory Handling
* \n
* The decoded output which is list of certificates from
* pem_decodeCertList function should be freed by calling
* SEC_LIST_FREE with freeFunc pointer as X509_freeCert.
*/
PSELINKDLL SEC_List_S* pem_decodeCertList(SEC_CHAR* pcEncodedCertList);

/*
*	This enumeration represents various object types, The object types includes following
*	1) X509 Certificate
*	2) Certificate Revocation List (CRL)
*	3) OCSP Request message
*	4) OCSP Response message
*	5) PKCS 8 Private Key
*	6) PKCS 8 encrypted Private Key
*	7) X509 public key
*	8) PKCS7 message
*	9) PKCS10 message.
*	the object type is used to identify input / output of PEM_encode / PEM_decode.
*/
/*bright add it*/
#define MAX_PEM_OBJTYPE  12

/**
* @defgroup PEM_OBJTYPE_E
* @ingroup pemEnums
* @par Prototype
* @code
* typedef enum PEM_objtype_e
* {
*	PEM_OBJTYPE_CERT                    = 0,
*	PEM_OBJTYPE_CRL                     = 1,
*	PEM_OBJTYPE_PKCS10_REQUEST          = 2,
*	PEM_OBJTYPE_OCSP_REQUEST            = 3,
*	PEM_OBJTYPE_OCSP_RESPONSE           = 4,
*	PEM_OBJTYPE_P8_PRIVATEKEY           = 5,
*	PEM_OBJTYPE_P8_ENCRYPTED_PRIVATEKEY = 6,
*	PEM_OBJTYPE_X509_SUBJECT_PUBLICKEY  = 7,
*	PEM_OBJTYPE_PKCS7                   = 8,
*	PEM_OBJTYPE_RSA_PRIVATEKEY          = 9,
*	PEM_OBJTYPE_DSA_PRIVATEKEY          = 10,
*   PEM_OBJTYPE_ECDSA_PRIVATEKEY        = 11,
*	PEM_OBJTYPE_UNKNOWN                 = 12
* } PEM_OBJTYPE_E;
* @endcode
*
* @datastruct PEM_OBJTYPE_CERT=0 structure=X509_CERT_S
* @datastruct PEM_OBJTYPE_CRL=1 structure=X509_CRL_S
* @datastruct PEM_OBJTYPE_PKCS10_REQUEST=2 structure=PKCS10_REQ_S
* @datastruct PEM_OBJTYPE_OCSP_REQUEST=3 structure=OCSP_REQUEST_S
* @datastruct PEM_OBJTYPE_OCSP_RESPONSE=4 structure=OCSP_RESP_S
* @datastruct PEM_OBJTYPE_P8_PRIVATEKEY=5 structure=PKCS8_PRIVKEY_S
* @datastruct PEM_OBJTYPE_P8_ENCRYPTED_PRIVATEKEY=6 structure=PKCS8_ENCRYPTED_PRIVKEY_S
* @datastruct PEM_OBJTYPE_X509_SUBJECT_PUBLICKEY=7 structure=SEC_PUBKEY_INFO_S
* @datastruct PEM_OBJTYPE_PKCS7=8 structure=PKCS7_MSG_S
* @datastruct PEM_OBJTYPE_RSA_PRIVATEKEY=9 structure=RSA KEY
* @datastruct PEM_OBJTYPE_DSA_PRIVATEKEY=10 structure=DSA KEY
* @datastruct PEM_OBJTYPE_UNKNOWN=11 structure=unknown
*/
typedef enum PEM_objtype_e
{
	PEM_OBJTYPE_CERT = 0,						/* structure   = X509_CERT_S */
	PEM_OBJTYPE_CRL = 1,						/* structure   = X509_CRL_S */
	PEM_OBJTYPE_PKCS10_REQUEST = 2,				/* structure   = PKCS10_REQ_S */
	PEM_OBJTYPE_OCSP_REQUEST = 3,				/* structure   = OCSP_REQUEST_S */
	PEM_OBJTYPE_OCSP_RESPONSE = 4,				/* structure   = OCSP_RESP_S */
	PEM_OBJTYPE_P8_PRIVATEKEY = 5,				/* structure   = PKCS8_PRIVKEY_S */
	PEM_OBJTYPE_P8_ENCRYPTED_PRIVATEKEY = 6,	/* structure   = PKCS8_ENCRYPTED_PRIVKEY_S */
	PEM_OBJTYPE_X509_SUBJECT_PUBLICKEY = 7,		/* structure   = SEC_PUBKEY_INFO_S */
	PEM_OBJTYPE_PKCS7 = 8,						/* structure   = PKCS7_MSG_S */
	PEM_OBJTYPE_RSA_PRIVATEKEY = 9,             /* structure   = RSA KEY*/
	PEM_OBJTYPE_DSA_PRIVATEKEY =10,             /* structure   = DSA KEY*/
	PEM_OBJTYPE_ECDSA_PRIVATEKEY =11,             /* structure   = ECDSA KEY*/
	PEM_OBJTYPE_UNKNOWN = 12                    /* structure   = unknown*/
} PEM_OBJTYPE_E;

/*
*	Representation of different proc types (process type refer RFC 1421)
*	the input object can be encoded in 2 formats
*	1) MIC_ONLY  here integrity of data  is protected & data is encoded into base 64 format.
*	2) ENCRYPTED here integrity of data  is protected & data is encrypted.
*
*	note:  MIC =  Message integrity code
*/
/**
* @defgroup PEM_PROCTYPE_E
* @ingroup pemEnums
* @par Prototype
* @code
* typedef enum
* {
*	MIC_CLEAR =0,
*	MIC_ONLY  =1,
*	ENCRYPTED =2
* } PEM_PROCTYPE_E;
* @endcode
*
* @datastruct MIC_CLEAR=0 Integrity of data is protected and data is left unmodified. This is not supported for any of the object types.
* @datastruct MIC_ONLY=1 Here integrity of data is protected & data is encoded into base 64 format.
* @datastruct ENCRYPTED=2 Here integrity of data is protected & data is encrypted.
*/
typedef enum
{
	MIC_CLEAR=0,   /*Integrity of data is protected and data is left unmodified. This is not supported for any of the object types.*/
	MIC_ONLY=1,    /*Here integrity of data is protected & data is encoded into base 64 format.*/
	ENCRYPTED=2    /*Here integrity of data is protected & data is encrypted*/
} PEM_PROCTYPE_E;

/*
PEM encode macro for encoding certificates. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_CERT_ENCODE(pCert,enProcType,enAlgId,pEncKey,ulKeyLen)\
	PEM_encode(pCert,PEM_OBJTYPE_CERT,enProcType,enAlgId,pEncKey,ulKeyLen)


/*
PEM encode macro for encoding CRL. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_CRL_ENCODE(pCRL,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pCRL,PEM_OBJTYPE_CRL,enProcType,enAlgId,pEncKey,ulKeyLen )

/*
PEM encode macro for encoding PKCS10 request. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_PKCS10REQ_ENCODE(pP10Req,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pP10Req,PEM_OBJTYPE_PKCS10_REQUEST,enProcType,enAlgId,pEncKey,ulKeyLen )

/*
PEM encode macro for encoding OCSP Request. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_OCSPREQ_ENCODE(pOCSPReq,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pOCSPReq,PEM_OBJTYPE_OCSP_REQUEST,enProcType,enAlgId,pEncKey,ulKeyLen )

/*
PEM encode macro for encoding OCSP Response. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_OCSPRESP_ENCODE(pOCSPResp,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pOCSPResp,PEM_OBJTYPE_OCSP_RESPONSE,enProcType,enAlgId,pEncKey,ulKeyLen )

/*
PEM encode macro for encoding PKCS8 PrivateKey. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_PKCS8PRIVKEY_ENCODE(pP8PrivKey,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pP8PrivKey,PEM_OBJTYPE_P8_PRIVATEKEY,enProcType,enAlgId,pEncKey,ulKeyLen )

/*
PEM encode macro for encoding PKCS8 Encrypted private key. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_PKCS8ENCRPRIVKEY_ENCODE(pP8EncrPrivKey,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pP8EncrPrivKey,PEM_OBJTYPE_P8_ENCRYPTED_PRIVATEKEY,enProcType,enAlgId,pEncKey,ulKeyLen )

/*
PEM encode macro for encoding Public key. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_SUBPUBKEY_ENCODE(pSubPubKey,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pSubPubKey,PEM_OBJTYPE_X509_SUBJECT_PUBLICKEY,enProcType,enAlgId,pEncKey,ulKeyLen )

/*
PEM encode macro for encoding PKCS7 objects. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_PKCS7OBJ_ENCODE(pP7Obj,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode (pP7Obj,PEM_OBJTYPE_PKCS7,enProcType,enAlgId,pEncKey,ulKeyLen )

/*bright add it */
/*
PEM encode macro for encoding RSAPrivateKey objects. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_RSAPRIVKEY_ENCODE(pRSAPrivKey,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pRSAPrivKey,PEM_OBJTYPE_RSA_PRIVATEKEY,enProcType,enAlgId,pEncKey,ulKeyLen)

/*bright add it */
/*
PEM encode macro for encoding DSAPrivateKey objects. Parameters enAlgId, pEncKey, ulKeyLen can be null for proctype MIC_ONLY.
*/
#define PEM_DSAPRIVKEY_ENCODE(pRSAPrivKey,enProcType,enAlgId,pEncKey,ulKeyLen )\
	PEM_encode(pRSAPrivKey,PEM_OBJTYPE_DSA_PRIVATEKEY,enProcType,enAlgId,pEncKey,ulKeyLen)




/**
* @defgroup PEM_encode
* @ingroup pemFunctions
* @par Prototype
* @code
* SEC_CHAR*  PEM_encode (void* pObject, PEM_OBJTYPE_E enObjectType, PEM_PROCTYPE_E enProcType,
* SEC_ALGID_E enAlgId, SEC_CHAR* pEncKey, SEC_INT32 ulKeyLen);
* @endcode
*
* @par Purpose
* To encode the given data to PEM format.
*
* @par Description
* This function encodes the object in input buffer to PEM format depending on options. The object here is represented
* by any of the PEM_OBJTYPE_E type. If the proc type is MIC_ONLY then the enAlgId, pEncKey, ulKeyLen can be assigned
* to NULL. And if the proc type is ENCRYPTED then valid values for enAlgId,pEncKey, ulKeyLen have to be given.
* The PEM_encode will return the given object in PEM format. Details about PEM is documented in four RFCs:
* 1421, 1422, 1423 and 1424.
*
* @param[in] pObject The Object that has to be  encoded in PEM format.
* The object can be any one mentioned in PEM_OBJTYPE_E. Example: X509 Certificate,CRL,OCSP Request,OCSP Response.
* The Object must be the structure mentioned as per the enObjectType parameter.
* For example, it should be a certificate if enObjectType = PEM_OBJTYPE_CERT and other object
* types should be passed correctly based on the object type passed as part of PEM_OBJTYPE_E. [N/A]
* @param[in] enObjectType Object type to specify the type of pObject. For example, PEM_OBJTYPE_CERT [N/A]
* @param[in] enProcType Proc type.The process to create the PEM Message.Possible values are MIC_ONLY,ENCRYPTED [N/A]
* @param[in] enAlgId The symmetric encryption algorithm id [N/A]
* @param[in] pEncKey The password for creating symmetric encryption key [N/A]
* @param[in] ulKeyLen Length of the given password [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* On successful completion [The PEM formated output data|N/A]
* @retval SEC_CHAR* In case of error [SEC_NULL|N/A]
*
* @par Dependency
* pem.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* @par Memory Handling
* \n
* 1. The encoded output buffer from PEM_encode function should be freed
* by calling ipsi_free function.
* \n\n
* 2. Buffer returned by PEM_encode will be Null Terminated. User is expected to pass this
* buffer as-is to the decoding API. If this buffer is passed to API(s) which take buffer and buffer
* length as input, the buffer len passed should also include the null termination character.
* Passing the value returned by strlen of encoded buffer is incorrect as it doesn't include the NULL
* termination character.
*/
PSELINKDLL SEC_CHAR*  PEM_encode (void* pObject,
							   PEM_OBJTYPE_E enObjectType,
							   PEM_PROCTYPE_E enProcType,
							   SEC_ALGID_E enAlgId,
							   SEC_CHAR* pEncKey,
							   SEC_INT32 ulKeyLen
							   );


/* PEM decode macro for object type certificate (PEM_OBJTYPE_CERT ) */
#define PEM_CERT_DECODE(pucPEMtext,pEncKey, ulKeyLen )\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_CERT,pEncKey, ulKeyLen)


/* PEM decode macro for object type CRL  (PEM_OBJTYPE_CRL) */
#define PEM_CRL_DECODE(pucPEMtext,pEncKey, ulKeyLen)\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_CRL,pEncKey, ulKeyLen)

/* PEM decode macro for object type PKCS10 request (PEM_OBJTYPE_PKCS10_REQUEST)  */
#define PEM_PKCS10REQ_DECODE(pucPEMtext,pEncKey, ulKeyLen)\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_PKCS10_REQUEST,pEncKey, ulKeyLen)

/* PEM decode macro for object type OCSP request (PEM_OBJTYPE_OCSP_REQUEST)*/
#define PEM_OCSPREQ_DECODE(pucPEMtext,pEncKey, ulKeyLen)\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_OCSP_REQUEST,pEncKey, ulKeyLen)

/* PEM decode macro for object type OCSP response (PEM_OBJTYPE_OCSP_RESPONSE ) */
#define PEM_OCSPRESP_DECODE(pucPEMtext,pEncKey, ulKeyLen)\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_OCSP_RESPONSE,pEncKey, ulKeyLen)

/* PEM decode macro for object type PKCS 8 private key (PEM_OBJTYPE_P8_PRIVATEKEY)*/
#define PEM_PKCS8PRIVKEY_DECODE(pucPEMtext,pEncKey, ulKeyLen)\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_P8_PRIVATEKEY,pEncKey, ulKeyLen)

/* PEM decode  macro for object type PKCS 8 encrypted key (PEM_OBJTYPE_P8_ENCRYPTED_PRIVATEKEY)*/
#define PEM_PKCS8ENCRPRIVKEY_DECODE(pucPEMtext,pEncKey, ulKeyLen)\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_P8_ENCRYPTED_PRIVATEKEY,pEncKey, ulKeyLen)

/* PEM decode macro  for object type public key (PEM_OBJTYPE_X509_SUBJECT_PUBLICKEY)*/
#define PEM_SUBPUBKEY_DECODE(pucPEMtext,pEncKey, ulKeyLen)\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_X509_SUBJECT_PUBLICKEY,pEncKey, ulKeyLen)

/* PEM decode macro  for object type PKCS 7 (PEM_OBJTYPE_PKCS7) */
#define PEM_PKCS7OBJ_DECODE(pucPEMtext,pEncKey, ulKeyLen)\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_PKCS7,pEncKey, ulKeyLen)

/*bright add it */
/* PEM decode macro  for object type RSAPrivateKey (PEM_OBJTYPE_RSA_PRIVATEKEY) */
#define PEM_RSAPRIVKEY_DECODE(pucPEMtext,pEncKey, ulKeyLen )\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_RSA_PRIVATEKEY, pEncKey, ulKeyLen)

/*bright add it */
/* PEM decode macro  for object type DSAPrivateKey (PEM_OBJTYPE_DSA_PRIVATEKEY) */
#define PEM_DSAPRIVKEY_DECODE(pucPEMtext,pEncKey, ulKeyLen )\
	  PEM_decode (pucPEMtext, PEM_OBJTYPE_DSA_PRIVATEKEY, pEncKey, ulKeyLen)
/*bright add it */


/**
* @defgroup Check_PEMobjtype
* @ingroup pemFunctions
* @par Prototype
* @code
* PEM_OBJTYPE_E  Check_PEMobjtype(SEC_CHAR* pucPEMBuf);
* @endcode
*
* @par Purpose
* To find the type of an input PEM object.
*
* @par Description
* This function checks the input PEM object to determine its Object type( any of the values of PEM_OBJTYPE_E).
*
* @param[in] pucPEMBuf Input PEM buffer [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval PEM_OBJTYPE_E On successful completion [The output Object types.The object can be any one mentioned
* in PEM_OBJTYPE_E. For example, X509 Certificate, CRL,OCSP Request, OCSP Response and so on|N/A]
* @retval PEM_OBJTYPE_E On error [PEM_OBJTYPE_UNKNOWN|N/A]
*
* @par Dependency
* pem.h
*
* @par Note
*
* None
*
* @par Related Topics
* N/A
*/
PSELINKDLL PEM_OBJTYPE_E  Check_PEMobjtype(SEC_CHAR* pucPEMBuf);


/**
* @defgroup PEM_decode
* @ingroup pemFunctions
* @par Prototype
* @code
* void*  PEM_decode (SEC_CHAR* pucPEMBuf, PEM_OBJTYPE_E enObjectType,
* SEC_CHAR* pEncKey, SEC_INT32 ulKeyLen);
* @endcode
*
* @par Purpose
* To decode the encoded PEM object into its original object type.
*
* @par Description
* This function decodes the input PEM format to the desired object.This API will decode the PEM encoded input buffer
* (which can contain any of the following\n
* Certificate,CRL,\n
* OCSP request,\n
* OCSP response,\n
* PKCS 7, 8, 10 messages)\n
* The object type input parameter  will identify the desired output object.This API will take the input PEM
* formated data and returns the requested object and null if error in input parameters.
* Details about PEM is documented in four RFCs: 1421 , 1422 , 1423  and 1424.
*
* @param[in] pucPEMBuf Input PEM buffer [N/A]
* @param[in] enObjectType Object type to specify the type of pObject.For example,PEM_OBJTYPE_CERT [N/A]
* @param[in] pEncKey Symmetric encryption key [N/A]
* @param[in] ulKeyLen Symmetric encryption key length [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval void* On successful completion [The output Object which is PEM decoded.
* The object can be any one mentioned in PEM_OBJTYPE_E. For example, X509
* Certificate,CRL, OCSP Request,OCSP Response etc|N/A]
* @retval void* If error [SEC_NULL|N/A]
*
* @par Dependency
* pem.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
* @par Memory Handling
* \n
* The decoded output buffer from PEM_decode function should be freed
* according to the object type decoded.
* - For PEM_OBJTYPE_CERT, X509_freeCert should be used.
* - For PEM_OBJTYPE_CRL, X509CRL_free should be used.
* - For PEM_OBJTYPE_PKCS10_REQUEST, PKCS10_freeCertReq should be used.
* - For PEM_OBJTYPE_OCSP_REQUEST, OCSP_freeOCSPReq should be used.
* - For PEM_OBJTYPE_OCSP_RESPONSE, OCSP_freeOCSPResp should be used.
* - For PEM_OBJTYPE_P8_PRIVATEKEY, PKCS8_freePrivKey should be used.
* - For PEM_OBJTYPE_P8_ENCRYPTED_PRIVATEKEY, PKCS8_freeEncryptedPrivKey
*   should be used.
* - For PEM_OBJTYPE_X509_SUBJECT_PUBLICKEY, X509_freePubKeyInfo should be used.
* - For PEM_OBJTYPE_PKCS7, PKCS7_freePKCS7Msg should be used.
* - For PEM_OBJTYPE_RSA_PRIVATEKEY, CRYPT_PKEY_free should be used.
* - For PEM_OBJTYPE_DSA_PRIVATEKEY, CRYPT_PKEY_free should be used.
* - For PEM_OBJTYPE_ECDSA_PRIVATEKEY, CRYPT_PKEY_free should be used.
*/
PSELINKDLL void*  PEM_decode (SEC_CHAR* pucPEMBuf,
						  PEM_OBJTYPE_E enObjectType,
						  SEC_CHAR* pEncKey,
						  SEC_INT32 ulKeyLen
						  );

/**
* @defgroup PEM_findObjectPos
* @ingroup pemFunctions
* @par Prototype
* @code
* SEC_UINT32 PEM_findObjectPos(SEC_CHAR *pucBuf, SEC_CHAR **pos, PEM_OBJTYPE_E enObjectType);
* @endcode
*
* @par Purpose
* To find pem object position.
*
* @par Description
* This function finds position of pwm object.
* @param[in] pucBuf Input buffer [N/A]
* @param[in] pos position for pem object [N/A]
* @param[in] enObjectType pem object type [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_UINT32 If finding of pem object is successful [SEC_TRUE|N/A]
* @retval SEC_INT32 if finding of pem object is failed [SEC_FALSE ]
*
* @par Dependency
* pem.h
*
* @par Note
*
*
* @par Related Topics
* N/A
*/

PSELINKDLL SEC_UINT32 PEM_findObjectPos(SEC_CHAR *pucBuf, SEC_CHAR **pos, PEM_OBJTYPE_E enObjectType);

#ifdef	__cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _SEC_PEM_H_ */

