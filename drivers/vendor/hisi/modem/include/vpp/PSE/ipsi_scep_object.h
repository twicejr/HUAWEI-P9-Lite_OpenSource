/*****************************************************************************
                                                                            
                Copyright (C), 2008, Huawei Tech. Co., Ltd.                
                            ALL RIGHTS RESERVED                             
                                                                            
------------------------------------------------------------------------------


FileName     :ipsi_scep_object.h
Author       :
Version      :1
Date         :04-06-10
Description  :
Function List: 
          History:
                    <author>   <date>          <desc>
----------------------------------------------------------------------------
****************************************************************************/
#include "ipsi_pse_build_conf.h"
#ifndef __IPSI_SEC_NO_SCEP__

#ifndef __IPSI_OBJ_SCEP_H__
#define __IPSI_OBJ_SCEP_H__

#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_crypto.h"
#include "ipsi_trans_method.h"
#include "sec_list.h"
#include "x509_basictypes.h"
#include "pkcs10.h"
#include "scep.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define IPSI_SCEP_MAX_FINGER_PRINT_LEN 64

#define IPSI_SCEP_ERROR -1

#define IPSI_SCEP_SUCCESS 0

#define IPSI_SCEP_FILETYPE_ASN1 2

#define IPSI_SCEP_FILETYPE_PEM  1

#define IPSI_SCEP_FILETYPE_PFX  4

#define IPSI_SCEP_MAX_CA_ISSUER_ID_LEN 255

#define IPSI_SCEP_SUPPORT_VERISIGN_EXTENSIONREQ      1

// IPSI_SCEP_RESP_CERT_LIST macro will be used with the API IPSI_SCEP_ObjSetOptions.
// IPSI_SCEP_RESP_CERT_LIST option indicate that the response of the GetCert and Enrollment
// request will be povided as certificate list.
#define IPSI_SCEP_RESP_CERT_LIST 2



/** @defgroup SCEP
* This section contains the SCEP Functions.
*/


/** @defgroup Structures
* @ingroup SCEP
* This section contains the Structures.
*/

/** @defgroup Object_Functions
* @ingroup SCEP
* This section contains the Object Functions.
*/

/**
* @defgroup IPSI_SCEP_FINGER_PRINT_S
* @ingroup Structures
* @par Description
* This structure holds the finger print and finger print length.
* @par Prototype
* @code
* typedef struct stFingerPrint
* {
*    SEC_UCHAR aucFingerPrint[IPSI_SCEP_MAX_FINGER_PRINT_LEN];
*    SEC_UINT uiFingerPrintLen;
* } IPSI_SCEP_FINGER_PRINT_S;
* @endcode
*
* @datastruct aucFingerPrint Array to store finger print.
* @datastruct uiFingerPrintLen Finger print length.
* The maximum length of Finger print is 64.
*/
typedef struct stFingerPrint
{
    SEC_UCHAR aucFingerPrint[IPSI_SCEP_MAX_FINGER_PRINT_LEN];
    
    SEC_UINT uiFingerPrintLen;
} IPSI_SCEP_FINGER_PRINT_S;

/**
* @defgroup IPSI_SCEP_MSG_TYPE_E
* @ingroup Enums
* @par Description
* This enum holds all the SCEP message types.
* @par Prototype
* @code
* typedef enum enSCEP_MSG_TYPE
* {
*    IPSI_SCEP_MSG_TYPE_UNKNOWN,
*    IPSI_SCEP_CRL,
*    IPSI_SCEP_CERT,
*    IPSI_SCEP_CA_CERT,
*    IPSI_SCEP_CA_RA_CERT_LIST,
*    IPSI_SCEP_CA_CAPS,
*    IPSI_SCEP_CERT_PENDING
* }IPSI_SCEP_MSG_TYPE_E;
* @endcode
*
* @datastruct IPSI_SCEP_MSG_TYPE_UNKNOWN indicates that message type is unknown.
* @datastruct IPSI_SCEP_CRL indicates SCEP getCRL message.
* @datastruct IPSI_SCEP_CERT indicates SCEP getCert message.
* @datastruct IPSI_SCEP_CA_CERT indicates SCEP GetCACert message 
* for single CA certificate.
* @datastruct IPSI_SCEP_CA_RA_CERT_LIST indicates list of CA/RA certificates.
* @datastruct IPSI_SCEP_CA_CAPS indicates GetCACaps message.
* @datastruct IPSI_SCEP_CERT_PENDING indicates pending message.
* @datastruct IPSI_SCEP_CERT_LIST indicates certificate list in response of the GetCert or Enrollment 
* request. This message type will be received if the IPSI_SCEP_RESP_CERT_LIST option is set in the SCEP context.
*/
typedef enum enSCEP_MSG_TYPE
{
    IPSI_SCEP_MSG_TYPE_UNKNOWN,
    IPSI_SCEP_CRL,
    IPSI_SCEP_CERT,
    IPSI_SCEP_CA_CERT,
    IPSI_SCEP_CA_RA_CERT_LIST,
    IPSI_SCEP_CA_CAPS,
    IPSI_SCEP_CERT_PENDING,
    IPSI_SCEP_CERT_LIST
}IPSI_SCEP_MSG_TYPE_E;

/**
* @defgroup IPSI_SCEP_REQ_TYPE_E
* @ingroup Enums
* @par Description
* This enum holds all the SCEP request types.
* @par Prototype
* @code
* typedef enum enSCEP_REQ_TYPE
* {
    IPSI_SCEP_REQ_TYPE_UNKNOWN,
*    IPSI_SCEP_GET_CRL_REQ,
*    IPSI_SCEP_GET_CERT_REQ,
     IPSI_SCEP_CERT_REQ,
*    IPSI_SCEP_GET_CA_CERT_REQ,
*    IPSI_SCEP_GET_CA_CAPS_REQ,
     IPSI_SCEP_GET_NEXT_CA_REQ
* }IPSI_SCEP_REQ_TYPE_E;
* @endcode
*
* @datastruct IPSI_SCEP_REQ_TYPE_UNKNOWN indicates that request type is unknown.
* @datastruct IPSI_SCEP_GET_CRL_REQ indicates SCEP getCRL request message.
* @datastruct IPSI_SCEP_GET_CERT_REQ indicates SCEP getCert request message.
* @datastruct IPSI_SCEP_CERT_REQ indicates CertReq request message.
* @datastruct IPSI_SCEP_GET_CA_CERT_REQ indicates SCEP GetCACert request 
* message.
* @datastruct IPSI_SCEP_GET_CA_CAPS_REQ indicates GetCACaps request message.
* @datastruct IPSI_SCEP_GET_NEXT_CA_REQ indicates GetNextCA request message.
*/
typedef enum enSCEP_REQ_TYPE
{
    IPSI_SCEP_REQ_TYPE_UNKNOWN,
    IPSI_SCEP_GET_CRL_REQ,
    IPSI_SCEP_GET_CERT_REQ,
    IPSI_SCEP_CERT_REQ,
    IPSI_SCEP_GET_CA_CERT_REQ,
    IPSI_SCEP_GET_CA_CAPS_REQ,
    IPSI_SCEP_GET_NEXT_CA_REQ
}IPSI_SCEP_REQ_TYPE_E;


/**
* @defgroup IPSI_SCEP_RESP
* @ingroup Structures
* @par Description
* This structure contains the certificate or CRL depending on the response.
* @par Prototype
* @code
* typedef SEC_VOID* IPSI_SCEP_RESP;
* @endcode
*
* @par Description
* This structure will contain the pointer to output depending upon the
* response.
* For GetCert and Enrollment it will hold the address of X509_CERT_S.
* For GetCRL  it will hold the address of  X509_CRL_S.
* For GetCA and GetNextCA it will hold the address of IPSI_SCEP_CA_RA_CERT_S.
* For GetCACaps it will hold the unsigned integer value.
*/
typedef SEC_VOID* IPSI_SCEP_RESP;




/**
* @defgroup IPSI_SCEP_RESP_MSG_S
* @ingroup Structures
* @par Description
* This structure holds the response message, message type
* and request type which will be provided to the user.
* @par Prototype
* @code
* typedef struct stIpsiScepResponseMsg
* {
*    IPSI_SCEP_MSG_TYPE_E enMsgType;
*    IPSI_SCEP_REQ_TYPE_E enReqType;
*    SCEP_REASON_E enFailureReason;
*    IPSI_SCEP_RESP ScepMsg;
* }IPSI_SCEP_RESP_MSG_S;
* @endcode
*
* @datastruct enMsgType Type of response message.
* @datastruct enReqType Request type sent for response received.
* @datastruct enFailureReason Failure Reason for response received.
* @datastruct ScepMsg SCEP response message.
*/
typedef struct stIpsiScepResponseMsg
{
    IPSI_SCEP_MSG_TYPE_E enMsgType;
    IPSI_SCEP_REQ_TYPE_E enReqType;
    SCEP_REASON_E enFailureReason;
    IPSI_SCEP_RESP ScepMsg;
}IPSI_SCEP_RESP_MSG_S;

/**
* @defgroup IPSI_SCEP_CERTKEY_IN_PARAM_S
* @ingroup Structures
* @par Description
* This structure contains the certificate or key details such as, 
* filetype and password.
* @par Prototype
* @code
* typedef struct stIpsiScepCertKeyInputParam
* {
*   SEC_CHAR *pcFile;
*   SEC_INT iType;
*   SEC_CHAR *pcPasswd;
*   SEC_UINT uiPasswdLen;
* } IPSI_SCEP_CERTKEY_IN_PARAM_S;
* @endcode
*
* @datastruct pcFile Pointer to the file.
* @datastruct iType It indicate the content type of the file i.e. 
*             IPSI_SCEP_FILETYPE_PEM or IPSI_SCEP_FILETYPE_ASN1
*             or IPSI_SCEP_FILETYPE_PFX.
* @datastruct pcPasswd Pointer to password.
* @datastruct uiPasswdLen Password length.
*/
typedef struct stIpsiScepCertKeyInputParam
{
    SEC_CHAR *pcFile;
    SEC_INT iType;
    SEC_CHAR *pcPasswd;
    SEC_UINT uiPasswdLen;
} IPSI_SCEP_CERTKEY_IN_PARAM_S;


/**
* @defgroup IPSI_SCEP_CERTKEY_CONF_S
* @ingroup Structures
* @par Description
* This structure contains the certificate and key details.
* @par Prototype
* @code
* typedef struct stIpsiScepCertKeyConfig
* {
*     IPSI_SCEP_CERTKEY_IN_PARAM_S stClientCert;
*     IPSI_SCEP_CERTKEY_IN_PARAM_S stClientKey;
* } IPSI_SCEP_CERTKEY_CONF_S;
* @endcode
*
* @datastruct stClientCert Contains the details of the certificate.
* @datastruct stClientKey Contains the details of the key.
*/
typedef struct stIpsiScepCertKeyConfig
{
    IPSI_SCEP_CERTKEY_IN_PARAM_S stClientCert;
    IPSI_SCEP_CERTKEY_IN_PARAM_S stClientKey;
}IPSI_SCEP_CERTKEY_CONF_S;

/**
* @defgroup IPSI_SCEP_CERTKEY_BUF_IN_PARAM_S
* @ingroup Structures
* @par Description
* This structure contains the certificate or key buffer details such as, 
* filetype and password.
* @par Prototype
* @code
* typedef struct stIpsiScepCertKeyInputParamBuf
* {
*     SEC_CHAR *pcBuff;
*     SEC_UINT uiBufLen;
*     SEC_INT iType;
*     SEC_CHAR *pcPasswd;
*     SEC_UINT uiPasswdLen;
* }IPSI_SCEP_CERTKEY_BUF_IN_PARAM_S;
* @endcode
*
* @datastruct pcBuff Pointer to the buffer.
* @datastruct uiBufLen Buffer length.
* @datastruct iType It indicate the content type of the file i.e. 
*                IPSI_SCEP_FILETYPE_PEM or IPSI_SCEP_FILETYPE_ASN1 or 
*                IPSI_SCEP_FILETYPE_PFX.
* @datastruct pcPasswd Pointer to the password.
* @datastruct uiPasswdLen Password length.
*/

typedef struct stIpsiScepCertKeyInputParamBuf
{
    SEC_CHAR *pcBuff;
    SEC_UINT uiBufLen;
    SEC_INT iType;
    SEC_CHAR *pcPasswd;
    SEC_UINT uiPasswdLen;
}IPSI_SCEP_CERTKEY_BUF_IN_PARAM_S;

/**
* @defgroup IPSI_SCEP_CERTKEY_BUFF_CONF_S
* @ingroup Structures
* @par Description
* This structure contains the certificate and key buffer details.
* @par Prototype
* @code
* typedef struct stIpsiScepCertKeyConfigBuf
* {
*     IPSI_SCEP_CERTKEY_BUF_IN_PARAM_S stClientCert;
*     IPSI_SCEP_CERTKEY_BUF_IN_PARAM_S stClientKey;
* }IPSI_SCEP_CERTKEY_BUFF_CONF_S;
* @endcode
*
* @datastruct stClientCert Contains the details of the buffer.
* @datastruct stClientKey Contains the details of the key.
*/
typedef struct stIpsiScepCertKeyConfigBuf
{
    IPSI_SCEP_CERTKEY_BUF_IN_PARAM_S stClientCert;
    IPSI_SCEP_CERTKEY_BUF_IN_PARAM_S stClientKey;
}IPSI_SCEP_CERTKEY_BUFF_CONF_S;


/**
* @defgroup IPSI_SCEP_CA_RA_CERT_S
* @ingroup Structures
* @par Description
* This structure contains the CA and RA Certificates.
* @par Prototype
* @code
* typedef struct stIpsiScepCaRaCerts
* {
*    SEC_List_S *pstRAList;
*    X509_CERT_S *pstCACert;
* }IPSI_SCEP_CA_RA_CERT_S;
* @endcode
*
* @datastruct pstRAList List of RA certificates.
* @datastruct pstCACert Pointer to CA certificates.
*/
typedef struct stIpsiScepCaRaCerts
{
    SEC_List_S *pstRAList;
    X509_CERT_S *pstCACert;
}IPSI_SCEP_CA_RA_CERT_S;

/**
* @defgroup EKUEC EXTENDED_KEY_USAGE_EXTENSION_CONSTANTS
* @ingroup Enums
* @par Description
* These enums can be used to set the extended key usage extension.
* @par Prototype
* @code
* enum
{
    IPSI_SCEP_SERVERAUTH,
    IPSI_SCEP_CLIENTAUTH,
    IPSI_SCEP_CODESIGNING,
    IPSI_SCEP_EMAILPROTECTION,
    IPSI_SCEP_TIMESTAMPING,
    IPSI_SCEP_OCSPSIGNING
};
* @endcode
*
* @datastruct IPSI_SCEP_SERVERAUTH identifies SERVERAUTH.
* @datastruct IPSI_SCEP_CLIENTAUTH identifies CLIENTAUTH.
* @datastruct IPSI_SCEP_CODESIGNING identifies CODESIGNING.
* @datastruct IPSI_SCEP_EMAILPROTECTION identifies EMAILPROTECTION
* @datastruct IPSI_SCEP_TIMESTAMPING identifies TIMESTAMPING.
* @datastruct IPSI_SCEP_OCSPSIGNING identifies OCSPSIGNING.
*/
enum 
{
    IPSI_SCEP_SERVERAUTH = 1,
    IPSI_SCEP_CLIENTAUTH = 2,
    IPSI_SCEP_CODESIGNING = 4,
    IPSI_SCEP_EMAILPROTECTION = 8,
    IPSI_SCEP_TIMESTAMPING = 16,
    IPSI_SCEP_OCSPSIGNING = 32
};


/**
* @defgroup IPSI_SCEP_EXTN_IN_PARAM_S
* @ingroup Structures
* @par Description
* This structure contains the certificate request extensions.
* @par Prototype
* @code
* typedef struct stIpsiScepExtnInputParam
 {
    SEC_List_S *pstExtList;
    SEC_UINT uiKeyUsageExtnAttr;
    SEC_UINT uiExtKeyUsageExtnAttr;
    SEC_BOOL bExtKeyUsageCriticalFlag;
 }IPSI_SCEP_EXTN_IN_PARAM_S;
 * 
* @endcode
*
* @datastruct pstExtList Contains the list of extensions
* i.e., SEC_EXTN_S structure pointer.
* @datastruct uiKeyUsageExtnAttr Key usage
* @datastruct uiExtKeyUsageExtnAttr Extended key usage
* @datastruct bExtKeyUsageCriticalFlag Extended key usage critical flag.
* The value should be set to SEC_TRUE or SEC_FALSE
*/
typedef struct stIpsiScepExtnInputParam
{
    SEC_List_S *pstExtList;
    SEC_UINT uiKeyUsageExtnAttr;
    SEC_UINT uiExtKeyUsageExtnAttr;
    SEC_BOOL bExtKeyUsageCriticalFlag;
}IPSI_SCEP_EXTN_IN_PARAM_S;


/**
* @defgroup IPSI_SCEP_CERTREQ_IN_PARAM_S
* @ingroup Structures
* @par Description
* This structure contains the certificate request inputs.
* @par Prototype
* @code
* typedef struct stIpsiScepCertReqInputParam
 {
    SEC_NAME_S *pstSubjectName;
    SEC_PKEY_S *pstPubKey;
    SEC_PKEY_S *pstPvtKey;
    IPSI_SCEP_EXTN_IN_PARAM_S stExtnParam;
 }IPSI_SCEP_CERTREQ_IN_PARAM_S;
* 
* @endcode
*
* @datastruct pstSubjectName Subject name
* @datastruct pstPubKey Public key
* @datastruct pstPvtKey Private key
* @datastruct stExtnParam Extension structure
*/
typedef struct stIpsiScepCertReqInputParam
{
    SEC_NAME_S *pstSubjectName;
    SEC_PKEY_S *pstPubKey;
    SEC_PKEY_S *pstPvtKey;
    IPSI_SCEP_EXTN_IN_PARAM_S stExtnParam;
}IPSI_SCEP_CERTREQ_IN_PARAM_S;


/**
* @defgroup IPSI_SCEP_CHALL_PASS_S
* @ingroup Structures
* @par Description
* This structure contains the challenge password.
* @par Prototype
* @code
* typedef struct stIpsiChallPass
 {
    SEC_UCHAR *pucChallengePass;
    SEC_UINT uiChallengePassLen;
 }IPSI_SCEP_CHALL_PASS_S;
* @endcode
*
* @datastruct pucChallengePass Challenge password buffer pointer
* @datastruct uiChallengePassLen Challenge password length
*/
typedef struct stIpsiChallPass
{
    SEC_UCHAR *pucChallengePass;
    SEC_UINT uiChallengePassLen;
}IPSI_SCEP_CHALL_PASS_S;

/**
* @defgroup IPSI_SCEP_ENROLL_CERT_IN_PARAM_S
* @ingroup Structures
* @par Description
* This structure contains certificate request input parameter structure and 
* challenge password structure.
* @par Prototype
* @code
* typedef struct stIpsiScepEnrollCertInputParam
 {
    IPSI_SCEP_CERTREQ_IN_PARAM_S stCertReqParam;
    IPSI_SCEP_CHALL_PASS_S stChallPass;
 }IPSI_SCEP_ENROLL_CERT_IN_PARAM_S;
* @endcode
*
* @datastruct stCertReqParam Certificate request parameter structure
* @datastruct stChallPass Challenge password structure
*/
typedef struct stIpsiScepEnrollCertInputParam
{
    IPSI_SCEP_CERTREQ_IN_PARAM_S stCertReqParam;
    IPSI_SCEP_CHALL_PASS_S stChallPass;
}IPSI_SCEP_ENROLL_CERT_IN_PARAM_S;

/**
* @defgroup IPSI_SCEP_ENROLL_CERTOBJ_S
* @ingroup Structures
* 
* @par Description
* This structure contains the enrollment parameters which are used
* in SCEP polling request.
* 
* @par Prototype
* @code
* typedef struct stIpsiEnrollCertObj IPSI_SCEP_ENROLL_CERTOBJ_S;
* @endcode
*
*
*/


typedef struct stIpsiEnrollCertObj IPSI_SCEP_ENROLL_CERTOBJ_S;

/**
* @defgroup IPSI_SCEP_OBJ_S
* @ingroup Structures
*
* @par Description
* This structure holds the configurations and states of SCEP Client.
* 
* @par Prototype
* @code
* typedef struct stObj IPSI_SCEP_OBJ_S;
* @endcode
*
*/
typedef struct stScepObj IPSI_SCEP_OBJ_S;


/**
* @defgroup IPSI_SCEP_ObjNew
* @ingroup Object_Functions
* @par Prototype
* @code
* IPSI_SCEP_OBJ_S* IPSI_SCEP_ObjNew(IPSI_TRANS_METH_S *pstTransMeth);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjNew creates SCEP object.
* @par Description
* IPSI_SCEP_ObjNew function creates the SCEP object.
* @param[in] pstTransMeth Pointer to transport method.[NA/NA]
* @param[out] NA NA [NA/NA]
* @retval IPSI_SCEP_OBJ_S* On successful execution of object. [New Object|NA]
* @retval IPSI_SCEP_OBJ_S* On all failure conditions. Failure happens if the  
* input parameters passed are NULL or invalid or if memory allocation 
* fails. [NULL|NA]
* 
* @par Memory Handling
* ipsi will allocate memory for IPSI_SCEP_OBJ_S.
* To free this memory user has to call the IPSI_SCEP_ObjFree function.
* 
* @par Note
*\n
*	- IPSI_SCEP_ObjNew can be called only after calling IPSI_SCEP_Library_Init  
*     and cannot be called after IPSI_SCEP_Library_Fini.
*	- The default value
*     for the digest algorithm will be set to MD5(ALGID_MD5).
*	- The default value for the encryption algorithm
*     will be set to DES algorithm in CBC mode(ALGID_DES_CBC).
*
* @par Related Topic
* IPSI_SCEP_ObjFree
*
*/
PSELINKDLL 
IPSI_SCEP_OBJ_S* IPSI_SCEP_ObjNew(IPSI_TRANS_METH_S *pstTransMeth);


/**
* @defgroup IPSI_SCEP_ObjSetAlgo
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjSetAlgo( IPSI_SCEP_OBJ_S *pstScepObj, 
                               SEC_UINT uiDigestAlgo, SEC_UINT uiCEAlgo);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjSetAlgo sets the digest and encryption algorithm for SCEP Object.
* @par Description
* IPSI_SCEP_ObjSetAlgo sets the digest and encryption algorithm for the SCEP 
* object.
*
* The digest algorithms supported are:
* 	- MD5(ALGID_MD5).
* 	- SHA1(ALGID_SHA1).
* 	- SHA256(ALGID_SHA256).
*	- SHA512(ALGID_SHA512).
*
* The encryption algorithms supported are:
* 	- 3 key triple DES algorithm in CBC mode(ALGID_DES_EDE3_CBC).
*	- DES algorithm in CBC mode(ALGID_DES_CBC).
*	- DES algorithm in ECB mode(ALGID_DES_ECB).
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiDigestAlgo Digest algorithm.[NA/NA]
* @param[in] uiCEAlgo Encryption algorithm.[NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or if the algorithms passed are invalid.
* [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjSetAlgo can be called only after calling IPSI_SCEP_Library_Init 
* and cannot be called after IPSI_SCEP_Library_Fini.
* @par Related Topic
* IPSI_SCEP_ObjGetAlgo
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjSetAlgo(IPSI_SCEP_OBJ_S *pstScepObj, 
                                      SEC_UINT uiDigestAlgo, SEC_UINT uiCEAlgo);


/**
* @defgroup IPSI_SCEP_ObjGetAlgo
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjGetAlgo( IPSI_SCEP_OBJ_S *pstScepObj,
                          SEC_UINT *puiDigestAlgo,  SEC_UINT *puiCEAlgo);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjGetAlgo gets the algorithms from the SCEP object.
* @par Description
* IPSI_SCEP_ObjGetAlgo gets the digest algorithm and encryption 
* algorithm from the SCEP object. If no algorithms have been set by the user 
* using IPSI_SCEP_ObjSetAlgo API, then the default values of MD5 (ALGID_MD5) for
* digest algorithm and DES (ALGID_DES_CBC) for encryption algorithm which are 
* set in the object at the time of creation will be returned.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[out] puiDigestAlgo Pointer to store digest algorithm.[NA/NA]
* @param[out] puiCEAlgo Pointer to store encryption algorithm.[NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions. Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjGetAlgo can be called only after calling IPSI_SCEP_Library_Init 
* and cannot be called after IPSI_SCEP_Library_Fini.
*
* @par Related Topic
* IPSI_SCEP_ObjSetAlgo
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjGetAlgo(IPSI_SCEP_OBJ_S *pstScepObj,  
                          SEC_UINT *puiDigestAlgo,  SEC_UINT *puiCEAlgo);

/**
* @defgroup IPSI_SCEP_ObjFree
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_VOID IPSI_SCEP_ObjFree( IPSI_SCEP_OBJ_S * pstScepObj);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjFree frees the SCEP object.
* @par Description
* IPSI_SCEP_ObjFree frees the SCEP object information.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjFree can be called only after calling IPSI_SCEP_Library_Init and
* cannot be called after IPSI_SCEP_Library_Fini.
* @par Related Topic
* IPSI_SCEP_ObjNew
*
*/
PSELINKDLL
SEC_VOID IPSI_SCEP_ObjFree(IPSI_SCEP_OBJ_S * pstScepObj);

/**
* @defgroup IPSI_SCEP_ObjSetOptions
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjSetOptions(IPSI_SCEP_OBJ_S *pstScepObj , SEC_UINT32 uiOption);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjSetOptions sets the option to the SCEP object.
* @par Description
* IPSI_SCEP_ObjSetOptions sets the option to the SCEP object. Two different options are declared in SCEP
* 1. IPSI_SCEP_SUPPORT_VERISIGN_EXTENSIONREQ - It indicates that the verisign extensions should
* be used while creating the PKCS10 request.
* 2.  IPSI_SCEP_RESP_CERT_LIST  - This option indicate that the response of the GetCert and Enrollment
* request should be povided as certificate list.
* 
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiOption  Option need to set.
* [IPSI_SCEP_SUPPORT_VERISIGN_EXTENSIONREQ | IPSI_SCEP_RESP_CERT_LIST/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions. Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_ERROR |NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjSetOptions can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* @par Related Topic
*   - IPSI_SCEP_ObjClientDoEnrollCertReq
*   - IPSI_SCEP_ObjClientDoGetCertReq
*   - IPSI_SCEP_ObjClearOptions
*
*/

PSELINKDLL 
SEC_INT IPSI_SCEP_ObjSetOptions(IPSI_SCEP_OBJ_S *pstScepObj, SEC_UINT32 uiOption);


/**
* @defgroup IPSI_SCEP_ObjClearOptions
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClearOptions(IPSI_SCEP_OBJ_S *pstScepObj , SEC_UINT32 uiOption);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjClearOptions clears the paased  option  from SCEP object.
* @par Description
* IPSI_SCEP_ObjClearOptions clears the paased  option  from SCEP object.
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiOption  Option need to cleared.
* [IPSI_SCEP_SUPPORT_VERISIGN_EXTENSIONREQ | IPSI_SCEP_RESP_CERT_LIST/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_ERROR |NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjClearOptions can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* @par Related Topic
* IPSI_SCEP_ObjSetOptions
*/


PSELINKDLL 
SEC_INT IPSI_SCEP_ObjClearOptions(IPSI_SCEP_OBJ_S *pstScepObj, SEC_UINT32 uiOption);


/**
* @defgroup IPSI_SCEP_ObjSetFingerPrint
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjSetFingerPrint( IPSI_SCEP_OBJ_S *pstScepObj,
                                     IPSI_SCEP_FINGER_PRINT_S *pstFingerPrint);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjSetFingerPrint sets the finger print for the SCEP object.
* @par Description
* IPSI_SCEP_ObjSetFingerPrint sets the finger print for the SCEP object.The
* maximum size of the finger print we support is 64. Check is done whether 
* the finger print length is 16(MD5 digest length) or 20(SHA1 digest length).
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] pstFingerPrint Pointer to structure variable of fingerprint.
* [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjSetFingerPrint can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* @par Related Topic
* IPSI_SCEP_ObjSetFingerPrint
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjSetFingerPrint(IPSI_SCEP_OBJ_S *pstScepObj,
                             IPSI_SCEP_FINGER_PRINT_S *pstFingerPrint);


/**
* @defgroup IPSI_SCEP_ObjGetFingerPrint
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjGetFingerPrint( IPSI_SCEP_OBJ_S *pstScepObj,
                                 IPSI_SCEP_FINGER_PRINT_S* pstFingerPrint);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjGetFingerPrint gets the finger print for the SCEP object.
* @par Description
* IPSI_SCEP_ObjGetFingerPrint gets the finger print for the SCEP object.
* Error will be returned to the user if this API is called without setting the 
* fingerprint using the API IPSI_SCEP_ObjSetFingerPrint.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[out] pstOutFingerPrint Pointer to store the value of finger print 
* [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions. Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjGetFingerPrint can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* @par Related Topic
* IPSI_SCEP_ObjSetFingerPrint
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjGetFingerPrint(IPSI_SCEP_OBJ_S *pstScepObj, 
                                 IPSI_SCEP_FINGER_PRINT_S* pstFingerPrint);

/**
* @defgroup IPSI_SCEP_ObjLoadCARACert
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjLoadCARACert( IPSI_SCEP_OBJ_S *pstScepObj,
                                    IPSI_SCEP_CA_RA_CERT_S *pstCaRaCerts);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjLoadCARACert loads CA/RA certificate list into SCEP Object.
* @par Description
* IPSI_SCEP_ObjLoadCARACert loads CA/RA certificate list into SCEP Object.
* The CA certificate is expected as pointer to X509_CERT_S structure
* and RA certificate list is expected as list of X509_CERT_S structure.
* On successful execution, CA/RA certficate will be stored in SCEP
* Object.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] pstCaRaCerts Pointer to structure variable holding
*                         CA/RA certificates.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions. Failure happens if the input
* parameters passed are NULL or invalid. [IPSI_SCEP_FAILURE |NA]
*
* @par Note
* \n
*	- IPSI_SCEP_ObjLoadCARACert can be called only after calling 
*     IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*	- If two RA certificates are present in RA list, if one of the RA certificate
*     has both digital signature and data encipherment capabilities, it
*     will return error as there is an extra certificate which is not
*     necessary.
*	- If two RA certificates are present in RA list, if both certificates
*     does not have capabilities in key usage extensions, it will return
*     error.
*	- If CA certificate is not present even if RA certificate list is 
      present, it will return error as it can not validate RA certificate.
*	- If one RA certificate is present and if it does not have key usage
      extensions in it, it will be considered as certificate with both
      capabilities.
*	- If two RA certificates are present, if any one of the RA does not
      have key usage extensions, it will return error as one certificate
      will be considered as certificate with both capabilities and other
      is extra certificate.
*	- If only CA certificate is present, RA certificate list should be NULL.
*	- If two RA certificates are present, one is expected for digital signature
      capability and other one is expected for data encipherment capability.
*	- If there are more than two RA certificates present in RA certificate
      list, it will return error.
*	- User should ensure that RA certificate list contains list of X509_CERT_S
      structures as RA certificates. If there is other data other than
      X509_CERT_S, application may crash.

* @par Related Topic
* IPSI_SCEP_Library_Init
* \n
* IPSI_SCEP_Library_Fini
* \n
* IPSI_SCEP_ObjNew
*/
PSELINKDLL SEC_INT IPSI_SCEP_ObjLoadCARACert(IPSI_SCEP_OBJ_S *pstScepObj,
                                    IPSI_SCEP_CA_RA_CERT_S *pstCaRaCerts);


/**
* @defgroup IPSI_SCEP_Library_Init
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_Library_Init(SEC_VOID);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_Library_Init initializes the SCEP library.
* @par Description
* IPSI_SCEP_Library_Init initializes the SCEP library.
* No other API's can be called before calling Init.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if registering 
* the error string fails. [IPSI_SCEP_FAILURE |NA]
*
* @par Note
* \n
* SCEP library Init and Fini should not be called in threads but should
* be called only in the main thread.
*
* @par Related Topic
* IPSI_SCEP_Library_Fini
*/
PSELINKDLL
SEC_INT IPSI_SCEP_Library_Init(SEC_VOID);


/**
* @defgroup IPSI_SCEP_Library_Fini
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_Library_Fini(SEC_VOID);
*
* @endcode
*
* @par Purpose
* This API is depricated.
* @par Description
* This API is depricated. It will always return IPSI_SCEP_SUCCESS.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
*
*
* @par Related Topic
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_Library_Fini(SEC_VOID);

/**
* @defgroup IPSI_SCEP_ObjLoadClientCertKeyFile
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjLoadClientCertKeyFile( IPSI_SCEP_OBJ_S *pstScepObj,
                                 IPSI_SCEP_CERTKEY_CONF_S *pstCertKeyConf);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjLoadClientCertKeyFile loads the client certificate and key
* from the file into the SCEP object.
*
* @par Description
* IPSI_SCEP_ObjLoadClientCertKeyFile loads the client certificate and key
* from the file into the SCEP Object. This function reads the client  
* certificate and key in 
*\n
*	- "PEM" (IPSI_SCEP_FILETYPE_PEM)
*	- "DER"(IPSI_SCEP_FILETYPE_ASN1)
*	- "PFX" (IPSI_SCEP_FILETYPE_PFX) formats and adds the client certificate
* and key to the client certificate of the SCEP object. The client certificates
* are overriden. Only RSA certificates are supported.
* Certificate password is an optional input but it is 
* applicable only for PFX format. Key file password is also optional.
* The public key in certificate and private key passed should be a valid pair.
* The maximum key size supported is 4096 bits.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] pstCertKeyConf Pointer to the structure IPSI_SCEP_CERTKEY_CONF_S.
* This structure holds the details of the certificate(certificate filename, 
* algorithm type of public key in certificate,password,password length) and key
* (key filename, algorithm type of private key,password,password length).[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid or public key algorithm is DSA or 
* if the key size is greater than 4096 bits. [IPSI_SCEP_FAILURE|NA]
* @par Note
* \n
* IPSI_SCEP_ObjLoadClientCertKeyFile can be called only after 
* calling IPSI_SCEP_Library_Init and cannot be called after 
* IPSI_SCEP_Library_Fini.
* 
* @par Related Topic
* IPSI_SCEP_ObjLoadClientCertKeyBuf
* \n
* IPSI_SCEP_ObjGetClientCertKey
* \n
* IPSI_SCEP_ObjLoadClientCertKey
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjLoadClientCertKeyFile(IPSI_SCEP_OBJ_S *pstScepObj,
                                 IPSI_SCEP_CERTKEY_CONF_S *pstCertKeyConf);

/**
* @defgroup IPSI_SCEP_ObjLoadClientCertKeyBuf
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjLoadClientCertKeyBuf( IPSI_SCEP_OBJ_S *pstScepObj,
                                 IPSI_SCEP_CERTKEY_BUFF_CONF_S *pstCertKeyConf);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjLoadClientCertKeyBuf loads the client certificate and key 
* from the buffer into the SCEP object.
* @par Description
* IPSI_SCEP_ObjLoadClientCertKeyBuf loads the buffer that contains the client 
* certificate and key in.
*\n
*	- "PEM"(IPSI_SCEP_FILETYPE_PEM)
*	- "DER"(IPSI_SCEP_FILETYPE_ASN1)
*	- "PFX" (IPSI_SCEP_FILETYPE_PFX) formats. Only RSA certificates are supported.
* The certificate and private key passed should be a valid pair.
* The maximum key size supported is 4096 bits.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] pstCertKeyConf Pointer to the structure 
* IPSI_SCEP_CERTKEY_BUFF_CONF_S.
* This structure holds the details of the certificate(buffer to certificate,
* buffer length, algorithm type of public key in certificate,password,
* password length) and key(buffer to key,buffer length ,algorithm type of 
* private key,password,password length).[NA/NA][NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid or public key algorithm is DSA or 
* if the key size is greater than 4096 bits. [IPSI_SCEP_FAILURE|NA]
*
* @par Note
* \n
* IPSI_SCEP_ObjLoadClientCertKeyBuf can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* 
* @par Related Topic
* IPSI_SCEP_ObjLoadClientCertKey
* \n
* IPSI_SCEP_ObjLoadClientCertKeyFile
* \n
* IPSI_SCEP_ObjLoadClientCertKey
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjLoadClientCertKeyBuf(
                                 IPSI_SCEP_OBJ_S *pstScepObj,
                                 IPSI_SCEP_CERTKEY_BUFF_CONF_S *pstCertKeyConf);

/**
* @defgroup IPSI_SCEP_ObjLoadClientCertKey
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjLoadClientCertKey( IPSI_SCEP_OBJ_S *pstScepObj,
                                    X509_CERT_S *pstCert, SEC_PKEY_S *pstKey);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjLoadClientCertKey loads the client certificate and key 
* into the SCEP object.
* @par Description
* IPSI_SCEP_ObjLoadClientCertKey loads the client certificate and key
* into the SCEP object. The client certificate and key are overridden.
* The public key in certificate and private key passed should be a valid pair.
* The maximum key size supported is 4096 bits.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] pstCert Pointer to X509 certificate.[NA/NA]
* @param[in] pstKey Pointer to private key.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid or public key algorithm is DSA or 
* if the key size is greater than 4096 bits. [IPSI_SCEP_FAILURE|NA]
*
* @par Note
* \n
* IPSI_SCEP_ObjLoadClientCertKey can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* 
* @par Related Topic
* IPSI_SCEP_ObjGetClientCertKey
* \n
* IPSI_SCEP_ObjLoadClientCertKeyBuf
*\n
* IPSI_SCEP_ObjLoadClientCertKeyFile
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjLoadClientCertKey(
                               IPSI_SCEP_OBJ_S *pstScepObj,
                               X509_CERT_S *pstCert, SEC_PKEY_S *pstKey);

/**
* @defgroup IPSI_SCEP_ObjGetClientCertKey
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjGetClientCertKey( IPSI_SCEP_OBJ_S *pstScepObj,
                                X509_CERT_S** dpstCert, SEC_PKEY_S** dpstKey);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjGetClientCertKey gets the client certificate and private key 
* from the SCEP object into the variables dpstCert and dpstKey.
*
* @par Description
* IPSI_SCEP_ObjGetClientCertKey gets the client certificate and key
* into the SCEP object. The client certificate and key are overridden.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[out] dpstCert Double pointer which will contain X509 certificate.
* [NA/NA]
* @param[out] dpstKey Double pointer which will contain private key.[NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid. [IPSI_SCEP_FAILURE|NA]
*
* @par Memory Handling
* ipsi will do duplication of output certificate structure and
* key structure. User should use X509_freeCert to free certificate 
* and should use CRYPT_PKEY_free to free the private key.
* User should free those structures only after its use.
*
* @par Note
* \n
* IPSI_SCEP_ObjGetClientCertKey can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* 
* @par Related Topic
* IPSI_SCEP_ObjLoadClientCertKeyFile
* \n
* IPSI_SCEP_ObjLoadClientCertKeyBuf
* \n
* IPSI_SCEP_ObjLoadClientCertKey
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjGetClientCertKey(
                                    IPSI_SCEP_OBJ_S *pstScepObj,
                                    X509_CERT_S** dpstCert, 
                                    SEC_PKEY_S** dpstKey);




/**
* @defgroup IPSI_SCEP_ObjClientDoGetCAReq
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientDoGetCAReq( IPSI_SCEP_OBJ_S *pstScepObj,
                                            SEC_UINT uiRequestId,
                                            SEC_UCHAR *pucCAIssuerId,
                                            SEC_UINT uiCAIssuerIdLen);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjClientDoGetCAReq creates the GetCACert request message
* and sends the message through HTTP.
* @par Description
* IPSI_SCEP_ObjClientDoGetCAReq creates the GetCACert request message
* and sends the message through HTTP with operation set to "GetCACert".
* On success of sending request, returns IPSI_SCEP_SUCCESS. On failure,
* returns IPSI_SCEP_ERROR.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiRequestId Request identifier.[2^32-1/NA]
* @param[in] pucCAIssuerId CA issuer identifier.[NA/NA]
* @param[in] uiCAIssuerIdLen CA issuer identifier length.[1-255/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
*	- IPSI_SCEP_ObjClientDoGetCAReq can be called only after calling 
*     IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*     For uiRequestId, 0 is not the valid input.
*	- If CA issuer ID is NULL and length passed is not zero, this API will return
*     error.
*	- If CA issuer ID is not NULL and length passed is zero, this API will return
*     error.
*	- If there is no issuer identifier for CA server, both CA issuer ID and CA
*     issuer ID length should be passed as NULL and zero.
*	- The CA issuer ID and its length is optional. User should check in out
*     of bound mechanism whether server is configured with any identifier.
*	- The maximum length of CA issuer ID supported is 255.

* @par Related Topic
* IPSI_SCEP_ObjClientHandleResp
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientDoGetCAReq(IPSI_SCEP_OBJ_S *pstScepObj,
                                            SEC_UINT uiRequestId,
                                            SEC_UCHAR *pucCAIssuerId,
                                            SEC_UINT uiCAIssuerIdLen);

/**
* @defgroup IPSI_SCEP_ObjClientHandleResp
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientHandleResp( IPSI_SCEP_OBJ_S *pstScepObj,
                                         SEC_UINT uiRequestId,
                                         SEC_UCHAR *pucBuf,
                                         SEC_UINT uiLen,
                                         SEC_VOID *pData,
                           IPSI_SCEP_RESP_MSG_S *pstRespMsg);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjClientHandleResp parses the SCEP response messages and
* outputs the response structure according to request message.
* @par Description
* IPSI_SCEP_ObjClientHandleResp parses the SCEP response messages and
* outputs the response structure according to request message.
* The content in response message structure varies according to
* response message.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiRequestId Request identifier.[2^32-1/NA]
* @param[in] pucBuf Buffer holding SCEP response message.[NA/NA]
* @param[in] uiLen Buffer length.[NA/NA]
* @param[in] pData Pointer to data.[NA/NA]
* @param[out] pstRespMsg Pointer to SCEP response structure [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
*	- IPSI_SCEP_ObjClientHandleResp can be called only after calling 
*     IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*	- The parameter pData should be passed when ever received from HTTP
*     response callback. pData should not be modified by users as the same
*     will be used in parsing response messages.
*	- The content of response message for GetCACert message in response
*     message structure is IPSI_SCEP_CA_RA_S.
*	- The content of response message for GetCert message in response
*     message structure is X509_CERT_S.
*	- The content of response message for GetCACaps message in response
*     message structure is SEC_UINT(unsigned integer).
*	- For GetCACaps response message, the content of response message contains
*     OR operation of capabilites received. User should do "AND" operation
*     with the desired capability value for which macros are available with the
*     content of response message.
*	- For GetCACaps response message, client will ignore if server sends any
*     other capabilities which are not mentioned in SCEP draft.
*	- The content of response message for GetCrl message in response
*     message structure is X509_CRL_S.      
*	- The content of response message for PKCSReq or Enrollment and
*     GetCertInitial message in response message structure is X509_CERT_S.
*	- For uiRequestId, 0 is not the valid input. 
*	- The content of response message for GetNextCA message in response
*     message structure is IPSI_SCEP_CA_RA_S.
* 	- If the response buffer length for the CA capability request is more than 
*     1023 then the response will not be processed by 
*     IPSI_SCEP_ObjClientHandleResp and IPSI_SCEP_ObjClientHandleResp 
*     will return error.
* @par Related Topic
*	- IPSI_SCEP_ObjClientDoGetCAReq
*	- IPSI_SCEP_ObjClientDoGetCertReq
*	- IPSI_SCEP_ObjClientDoGetCrlReq
*	- IPSI_SCEP_ObjClientDoGetNextCAReq
*	- IPSI_SCEP_ObjClientDoEnrollCertReq
*	- IPSI_SCEP_ObjClientDoGetCertInitialReq
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientHandleResp(IPSI_SCEP_OBJ_S *pstScepObj,
                                        SEC_UINT uiRequestId,
                                        SEC_UCHAR *pucBuf,
                                        SEC_UINT uiLen,
                                        SEC_VOID *pData,
                        IPSI_SCEP_RESP_MSG_S *pstRespMsg);


/**
* @defgroup IPSI_SCEP_ObjClientDoGetCertReq
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientDoGetCertReq( IPSI_SCEP_OBJ_S *pstScepObj,
                                       SEC_UINT uiRequestId, 
                                       SEC_NAME_S* pstIssuerName, 
                                       SEC_BIGINT_S* pstSerial);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjClientDoGetCertReq creates the GetCert request message
* and sends the message through HTTP.
* @par Description
* IPSI_SCEP_ObjClientDoGetCertReq creates the GetCert request message
* and sends the message through HTTP with operation set to "GetCert".
* On success of sending request, returns IPSI_SCEP_SUCCESS. On failure,
* returns IPSI_SCEP_ERROR.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiRequestId Request identifier.[2^32-1/NA]
* @param[in] pstIssuerName Certificate issuer name being requested.[NA/NA]
* @param[in] pstSerial Serial number of certficate being requested.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions. Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
*	- IPSI_SCEP_ObjClientDoGetCertReq can be called only after calling 
*     IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*	- For uiRequestId, 0 is not the valid input.
*	- For calling IPSI_SCEP_ObjClientDoGetCertReq user need to load client 
*        certificate and CA/RA certificate to the SCEP object, otherwise API 
*        will return error.
*
* @par Related Topic
*	- IPSI_SCEP_ObjClientHandleResp
*	- IPSI_SCEP_ObjClientHandleError
*     - IPSI_SCEP_ObjSetOptions
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientDoGetCertReq(
                        IPSI_SCEP_OBJ_S *pstScepObj,
                        SEC_UINT uiRequestId, 
                        SEC_NAME_S* pstIssuerName, 
                        SEC_BIGINT_S* pstSerial);


/**
* @defgroup IPSI_SCEP_ObjClientDoEnrollCertReq
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientDoEnrollCertReq(
*                    IPSI_SCEP_OBJ_S *pstScepObj,
*                    SEC_UINT uiRequestId,
*                    IPSI_SCEP_ENROLL_CERT_IN_PARAM_S *pstEnrollCertParam,
*                    IPSI_SCEP_ENROLL_CERTOBJ_S **dpstEnrollObj,
*                    PKCS10_REQ_S **dpstPKCSReq);
* @endcode
* @par Purpose
* This function creates and sends the certificate enrollment request.
* @par Description
* IPSI_SCEP_ObjClientDoEnrollCertReq Creates the enrollment request message
* and sends the message through HTTP with operation set to "PKCSReq".
* On success, updates IPSI_ENROL_REQ_S pointer. On failure,
* returns IPSI_SCEP_ERROR. In case of a pending response being received
* for this Enroll Request, IPSI_SCEP_ObjClientDoGetCertInitialReq API should 
* be called by passing the IPSI_SCEP_ENROLL_CERTOBJ_S pointer for querying 
* the status of enrollment certificate request
* @param[in] pstScepObj Pointer to SCEP object [NA/NA]
* @param[in] uiRequestId Request identifier. The maximum unsigned
* integer value((2^32)-1/NA), this parameter inputs any value 
* other than 0 [Refer-Description]
* @param[in] pstEnrollCertParam Certificate enrollment input structure [NA/NA]
* @param[out] dpstEnrollObj Enrollment request structure pointer, can be
* used, if pending response is received. Should be freed by calling 
* IPSI_SCEP_freeEnrollReq, only after response is success or failure for the 
* request.
* Any further query for the request is not required [NA/NA]
* @param[out] dpstPKCSReq PKCS10 request supports maximum 
* key size of 4096 bits [NA/NA]
* Request is sent to the server [NA/NA]
* @retval SEC_INT On successful execution [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE|NA]
* @par Note
*\n
*	- IPSI_SCEP_ObjClientDoEnrollCertReq can be called only after calling 
*     IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*	- Challenge password is optional because as defined in draft-nounse-scep-20
*     section 2.3, the client may not have challenge password and if the server 
*     is in manual mode, the client provides the fingerprint of the PKCS10 
*     request to the server by out of band method.
*	- To ignore the challenge password, the challenge password buffer and length
*     should be set to SEC_NULL and 0.
*\n
* @par Related Topic
*   - IPSI_SCEP_ObjClientHandleResp
*   - IPSI_SCEP_ObjClientDoGetCertInitialReq
*   - IPSI_SCEP_freeEnrollCertObj
*   - IPSI_SCEP_ObjSetOptions
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientDoEnrollCertReq(IPSI_SCEP_OBJ_S *pstScepObj,
                         SEC_UINT uiRequestId,
                         IPSI_SCEP_ENROLL_CERT_IN_PARAM_S *pstEnrollCertParam,
                         IPSI_SCEP_ENROLL_CERTOBJ_S **dpstEnrollObj,
                         PKCS10_REQ_S **dpstPKCSReq);


/**
* @defgroup IPSI_SCEP_ObjClientDoGetCertInitialReq
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientDoGetCertInitialReq(
*                                 IPSI_SCEP_OBJ_S *pstScepObj,
*                                 SEC_UINT uiRequestId,
*                                 IPSI_SCEP_ENROLL_CERTOBJ_S *pstEnrollObj);
*
* @endcode
*
* @par Purpose
* This function creates the polling request to the server.
* @par Description
* IPSI_SCEP_ObjClientDoGetCertInitialReq creates the polling request message
* and sends the message through HTTP with operation set to "GetCertInitial".
* On success, returns IPSI_SCEP_SUCCESS. On failure,
* returns IPSI_SCEP_ERROR. In case of a pending response being received for
* this GetCertInitial request, GetCertInitial API should be called again
* passing the IPSI_SCEP_ENROLL_CERTOBJ_S pointer for querying the status of
* enrollment Certificate Request.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiRequestId Request identifier. The maximum unsigned integer value
* ((2^32)-1/NA), this parameter inputs any value other than 0 
* [Refer-Description]
* @param[in] pstEnrollObj Certificate Enrollment object structure obtained
* during IPSI_SCEP_ObjClientDoEnrollCertReq when the request is completed.
* pstEnrollObj should be freed by calling IPSI_SCEP_freeEnrollReq only, after
* response is success or failure for the request. Any further query for the
* request is not required [NA/NA]
* @param[out] NA NA [NA/NA]
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE|NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjClientDoGetCertInitialReq can be called only after calling
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*
* @par Related Topic
*	- IPSI_SCEP_ObjClientHandleResp
*	- IPSI_SCEP_freeEnrollCertObj
*
*/

PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientDoGetCertInitialReq(IPSI_SCEP_OBJ_S *pstScepObj,
                                    SEC_UINT uiRequestId,
                                    IPSI_SCEP_ENROLL_CERTOBJ_S *pstEnrollObj);


/**
* @defgroup IPSI_SCEP_freeEnrollCertObj
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_freeEnrollCertObj(
*                  IPSI_SCEP_ENROLL_CERTOBJ_S *pstEnrollObj);
*
* @endcode
* @par Purpose
* This  function frees the enroll request structure.
* @par Description
* IPSI_SCEP_freeEnrollReq is provided to free the enroll request structure.
* When response from the server of the enrollment request is success or failure,
* then user should free the enrollment request structure.
* @param[in] pstEnrollObj Certificate Enrollment object structure.[NA/NA]
* @param[out] NA NA [NA/NA]
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameter passed is NULL [IPSI_SCEP_FAILURE|NA]
* @par Note
*\n
* IPSI_SCEP_freeEnrollReq should be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini. 
*\n
* @par Related Topic
*	- IPSI_SCEP_ObjClientDoEnrollCertReq
*	- IPSI_SCEP_ObjClientDoGetCertInitialReq
*
*/
PSELINKDLL
SEC_VOID IPSI_SCEP_freeEnrollCertObj(IPSI_SCEP_ENROLL_CERTOBJ_S *pstEnrollObj);


/**
* @defgroup IPSI_SCEP_ObjClientDoGetCACapsReq
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientDoGetCACapsReq(IPSI_SCEP_OBJ_S *pstScepObj,
                                            SEC_UINT uiRequestId,
                                            SEC_UCHAR *pucCAIssuerId,
                                            SEC_UINT uiCAIssuerIdLen);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjClientDoGetCACapsReq creates the GetCACaps request message
* and sends the message through HTTP.
* @par Description
* IPSI_SCEP_ObjClientDoGetCACapsReq creates the GetCACaps request message
* and sends the message through HTTP with operation set to "GetCACaps".
* On success of sending request, returns IPSI_SCEP_SUCCESS. On failure,
* returns IPSI_SCEP_ERROR.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiRequestId Request identifier.[NA/NA]
* @param[in] pucCAIssuerId CA issuer identifier.[NA/NA]
* @param[in] uiCAIssuerIdLen CA issuer identifier length.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
*	- IPSI_SCEP_ObjClientDoGetCACapsReq can be called only after calling 
*     IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*	- If CA server is not supporting the GetCACaps request message,
*     either it may respond with empty message or it may give HTTP
*     error.
*	- The CA issuer ID and its length is optional. User should check in out
*     of bound mechanism whether server is configured with any identifier.
*     The maximum length of CA issuer ID supported is 255.
* 	- If CA issuer ID is NULL and length passed is not zero, this API will return
*     error.
* 	- If CA issuer ID is not NULL and length passed is zero, this API will return
*     error.
* 	- If there is no issuer identifier for CA server, both CA issuer ID and CA
*     issuer ID length should be passed as NULL and zero.
* 	- If the response buffer length for the CA Capability request is more than 
*     1023 then the response will not be processed by 
*     IPSI_SCEP_ObjClientHandleResp and IPSI_SCEP_ObjClientHandleResp will 
*     return error.
*
* @par Related Topic
* IPSI_SCEP_ObjClientHandleResp
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientDoGetCACapsReq(IPSI_SCEP_OBJ_S *pstScepObj,
                                            SEC_UINT uiRequestId,
                                            SEC_UCHAR *pucCAIssuerId,
                                            SEC_UINT uiCAIssuerIdLen);

/**
* @defgroup IPSI_SCEP_ObjClientDoGetNextCAReq
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientDoGetNextCAReq(IPSI_SCEP_OBJ_S *pstScepObj,
                                            SEC_UINT uiRequestId,
                                            SEC_UCHAR *pucCAIssuerId,
                                            SEC_UINT uiCAIssuerIdLen);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjClientDoGetNextCAReq creates the GetNextCA request message
* and sends the message through HTTP.
* @par Description
* IPSI_SCEP_ObjClientDoGetNextCAReq creates the GetNextCA request message
* and sends the message through HTTP with operation set to "GetNextCA".
* On success of sending request, returns IPSI_SCEP_SUCCESS. On failure,
* returns IPSI_SCEP_ERROR.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiRequestId Request identifier.[NA/NA]
* @param[in] pucCAIssuerId CA issuer identifier.[NA/NA]
* @param[in] uiCAIssuerIdLen CA issuer identifier length.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
*  - IPSI_SCEP_ObjClientDoGetNextCAReq can be called only after calling
*    IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*  - The CA issuer ID and its length is optional. User should check in out
*    of bound mechanism whether server is configured with any identifier.
*  - The maximum length of CA issuer ID supported is 255.
*  - If CA issuer ID is NULL and length passed is not zero, this API will
*    return error.
*  - If CA issuer ID is not NULL and length passed is zero, this API will
*    return error.
*  - If there is no issuer identifier for CA server, both CA issuer ID and CA
*    issuer ID length should be passed as NULL and zero.
*  - It is recommended that before sending GetNextCA request message, user
*    should check whether GetNextCA capability supported by CA server or not.
*  - If the CA server does not support GetNextCA capability, 
*    server rejects GetNextCA request message which gives HTTP error.
*  - If the CA server supports GetNextCA capability but does not have any
*    rollover certificates, server rejects GetNextCA request message
*    which gives HTTP error.
*
* @par Related Topic
* IPSI_SCEP_ObjClientHandleResp
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientDoGetNextCAReq(IPSI_SCEP_OBJ_S *pstScepObj,
                                            SEC_UINT uiRequestId,
                                            SEC_UCHAR *pucCAIssuerId,
                                            SEC_UINT uiCAIssuerIdLen);


/**
* @defgroup IPSI_SCEP_ObjClientHandleError
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientHandleError( IPSI_SCEP_OBJ_S *pstScepObj,
                                  SEC_UINT uiRequestId, 
*                                  SEC_UINT uiErr);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjClientHandleError handles the error received and deletes
* the request id from SCEP storage.
* @par Description
* IPSI_SCEP_ObjClientHandleError handles the error received and deletes
* the request id from SCEP storage.
*
* @param[in] pstScepObj Pointer to SCEP object [NA/NA]
* @param[in] uiRequestId Request identifier [NA/NA]
* @param[in] uiErr Error number [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjClientHandleError can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* @par Related Topic
*	- IPSI_SCEP_ObjClientDoGetCAReq
*	- IPSI_SCEP_ObjClientDoGetCertReq
*	- IPSI_SCEP_ObjClientHandleResp
*	- IPSI_SCEP_ObjClientDoEnrollCertReq
*	- IPSI_SCEP_ObjClientDoGetCertInitialReq
*	- IPSI_SCEP_ObjClientDoGetCrlReq
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientHandleError(IPSI_SCEP_OBJ_S *pstScepObj, 
                                  SEC_UINT uiRequestId, SEC_UINT uiErr);

/**
* @defgroup IPSI_SCEP_FreeRespMsg
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_VOID IPSI_SCEP_FreeRespMsg( SEC_UINT uiMsgType,
*                             IPSI_SCEP_RESP stResp);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_FreeRespMsg frees the response message depending on SCEP
* message type.
* @par Description
* IPSI_SCEP_FreeRespMsg frees the response message depending on SCEP
* message type. The message type should be one of them from enum
* IPSI_SCEP_MSG_TYPE_E.
*
* @param[in] uiMsgType SCEP message type.[NA/NA]
* @param[in] stResp Pointer to SCEP response of message type.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_VOID This function does not return any value [NA |NA]
*@par Note
*\n
* IPSI_SCEP_FreeRespMsg can be called only after calling IPSI_SCEP_Library_Init
* and cannot be called after IPSI_SCEP_Library_Fini.
* 
* @par Related Topic
*	- IPSI_SCEP_ObjClientDoGetCAReq
*	- IPSI_SCEP_ObjClientDoGetCertReq
*	- IPSI_SCEP_ObjClientHandleResp
*	- IPSI_SCEP_ObjClientDoEnrollCertReq
*	- IPSI_SCEP_ObjClientDoGetCertInitialReq
*	- IPSI_SCEP_ObjClientDoGetCrlReq
*
*/
PSELINKDLL
SEC_VOID IPSI_SCEP_FreeRespMsg(SEC_UINT uiMsgType, IPSI_SCEP_RESP stResp);



/**
* @defgroup IPSI_SCEP_ObjClientDoGetCrlReq
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjClientDoGetCrlReq( IPSI_SCEP_OBJ_S *pstScepObj,
                                   SEC_UINT uiRequestId, 
                                   SEC_NAME_S* pstIssuerName, 
                                   SEC_BIGINT_S* pstSerial);
*
* @endcode
*
* @par Purpose
* IPSI_SCEP_ObjClientDoGetCrlReq creates the GetCrl request message
* and sends the message through HTTP.
* @par Description
* IPSI_SCEP_ObjClientDoGetCrlReq creates the GetCrl request message
* and sends the message through HTTP with operation set to "GetCrl".
* On success of sending request, returns IPSI_SCEP_SUCCESS. On failure,
* returns IPSI_SCEP_ERROR.
*
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[in] uiRequestId Request identifier.[2^32-1/NA]
* @param[in] pstIssuerName Certificate Issuer name for which crl 
* is requested [NA/NA]
* @param[in] pstSerial Serial number of certficate for which crl is 
* requested [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
*	- IPSI_SCEP_ObjClientDoGetCrlReq can be called only after calling 
*     IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
*	- For calling IPSI_SCEP_ObjClientDoGetCrlReq user need to load client 
      certificate and CA/RA certificate to SCEP object, otherwise API will 
      return error.
* @par Related Topic \n
* IPSI_SCEP_ObjClientHandleResp
*
*/
PSELINKDLL
SEC_INT IPSI_SCEP_ObjClientDoGetCrlReq(
                        IPSI_SCEP_OBJ_S *pstScepObj,
                        SEC_UINT uiRequestId, SEC_NAME_S* pstIssuerName,
                        SEC_BIGINT_S* pstSerial);


/**
* @defgroup IPSI_SCEP_ObjFreeAllRequest
* @ingroup Object_Functions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjFreeAllRequest( IPSI_SCEP_OBJ_S *pstScepObj);
*
* @endcode
* @par Purpose
* IPSI_SCEP_ObjFreeAllRequest releases all the request IDs from the SCEP object
* @par Description
* IPSI_SCEP_ObjFreeAllRequest provides the functionality of releasing all the 
* request IDs from the SCEP object store. After calling this API, the requests 
* which had already been sent to the server should be dropped, otherwise 
* processing those reponses will fail, that is IPSI_SCEP_ObjClientHandleResp 
* will return error for the response which is sent before calling 
* IPSI_SCEP_ObjFreeAllRequest.
* @param[in] pstScepObj Pointer to SCEP object.[NA/NA]
* @param[out] NA NA [NA/NA]
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
* @par Note
*\n
* IPSI_SCEP_ObjFreeAllRequest can be called only after calling 
* IPSI_SCEP_Library_Init and cannot be called after IPSI_SCEP_Library_Fini.
* This API should be called when configurations are changed,
* and some of the responses are still pending.
* 
* @par Related Topic
*	- IPSI_SCEP_ObjClientHandleResp
*	- IPSI_SCEP_ObjClientDoGetCrlReq
*/
PSELINKDLL SEC_INT IPSI_SCEP_ObjFreeAllRequest(IPSI_SCEP_OBJ_S *pstScepObj);


/**
* @defgroup IPSI_SCEP_DEBUG_MSG_CB
* @ingroup Callback_Functions
* @par Prototype
* @code
* typedef SEC_INT (*IPSI_SCEP_DEBUG_MSG_CB)(IPSI_SCEP_OBJ_S *pstScepObj,
*                        SEC_UCHAR* pucDebugBuf,
*                        SEC_UINT uiBufLen,
*                        SEC_INT iLevel,
*                        SEC_VOID *pvUserData);
* @endcode
*
* @par Purpose
* This is the prototype of debug message callback function.
*
* @par Description
* IPSI_SCEP_DEBUG_MSG_CB provides the prototype of SCEP debug message 
* callback function which will be called when SCEP message is sent.
*
* @param[in] pstScepObj Pointer to scep object. [NA/NA]
* @param[in] pucDebugBuf Pointer to debug message buffer.[NA/NA]
* @param[in] uiBufLen Length of the debug message buffer. [NA/NA]
* @param[in] iLevel  Reserved for future use.[NA/NA]
* @param[in] pvUserData Pointer to user specific data. You can pass your 
*            own pointer to pUserData. Same pointer will be passed
*            when callback is called. This parameter is provided if
*            you want to use any of the application
*            data in callback. [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
*/
typedef SEC_INT (*IPSI_SCEP_DEBUG_MSG_CB)(IPSI_SCEP_OBJ_S *pstScepObj,
                        SEC_UCHAR* pucDebugBuf,
                        SEC_UINT uiBufLen,
                        SEC_INT iLevel,
                        SEC_VOID *pvUserData);


/**
* @defgroup IPSI_SCEP_setDebugMsgCB
* @ingroup Object_CallbackFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_setDebugMsgCB(IPSI_SCEP_DEBUG_MSG_CB *pfDebugMsgCB,
                                                          SEC_VOID* pvUserData)
* @endcode
*
* @par Purpose
* This function is used to register the debug message callback function with
* the global structure.
*
* @par Description
* IPSI_SCEP_setDebugMsgCB function registers the debug message callback function
* with the global structure.
*
* @param[in] pfDebugMsgCB Debug Message Callback [NA/NA]
* @param[in] pvUserData Pointer to user specific data. You can pass your 
*            own pointer to pUserData. Same pointer will be
*            passed when callback is called. This parameter is
*             provided if you want to use
*             any of the application data in callback [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT If the set is successful. [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT If it fails to set. [IPSI_SCEP_ERROR|NA]
*
*/
PSELINKDLL SEC_INT IPSI_SCEP_setDebugMsgCB(IPSI_SCEP_DEBUG_MSG_CB pfDebugMsgCB,
                                                          SEC_VOID* pvUserData);

/**
* @defgroup IPSI_SCEP_ObjSetDebugMsgCB
* @ingroup Object_CallbackFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjSetDebugMsgCB(IPSI_SCEP_OBJ_S *pstScepObj,
                                       IPSI_SCEP_DEBUG_MSG_CB *pfDebugMsgCB,
                                             SEC_VOID* pvUserData);
* @endcode
*
* @par Purpose
* This function is used to register the debug message callback function 
* with the object.
*
* @par Description
* IPSI_SCEP_setDebugMsgCB function registers the debug message callback 
* function with the object.
*
* @param[in] pstScepObj Pointer to object.[NA/NA]
* @param[in] pfDebugMsgCB Debug Message Callback [NA/NA]
* @param[in] pvUserData Pointer to user specific data. You can pass your 
*            own pointer to pUserData. Same pointer will be
*            passed when callback is called. This parameter is
*             provided if you want to use
*             any of the application data in callback [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT If the set is successful. [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT If it fails to set. [IPSI_SCEP_ERROR|NA]
*
*/
PSELINKDLL SEC_INT IPSI_SCEP_ObjSetDebugMsgCB(IPSI_SCEP_OBJ_S *pstScepObj,
                                       IPSI_SCEP_DEBUG_MSG_CB pfDebugMsgCB,
                                             SEC_VOID* pvUserData);




/**
* @defgroup IPSI_SCEP_CA_FINGERPRINT_CB
* @ingroup Callback_Functions
* @par Prototype
* @code
* typedef SEC_INT (*IPSI_SCEP_CA_FINGERPRINT_CB)(IPSI_SCEP_OBJ_S *pstScepObj,
*                        SEC_UINT uiRequestId,
*                        X509_CERT_S * pstCACert,
*                        SEC_VOID *pvUserData);
* @endcode
*
* @par Purpose
* This is the prototype of CA fingerprint callback function.
*
* @par Description
* IPSI_SCEP_CA_FINGERPRINT_CB provides the prototype of SCEP CA fingerprint 
* verification callback function which will be called during GetCA operation.
* This callback function will be called when the internal fingerprint 
* matching fails during GetCA operation.
* 
* @param[in] pstScepObj Pointer to scep object. [NA/NA]
* @param[in] uiRequestId Request identifier.[2^32-1/NA]
* @param[in] pstCACert Pointer to CA certificate received from server.[NA/NA]
* @param[in] pvUserData Pointer to user specific data. You can pass your 
*            own pointer to pUserData. Same pointer will be passed
*            when callback is called. This parameter is provided if
*            you want to use any of the application
*            data in callback. [NA/NA]
*
* @retval SEC_INT On successful execution. [IPSI_SCEP_SUCCESS |NA]
* @retval SEC_INT On all failure conditions.Failure happens if the input
* parameters passed are NULL or invalid [IPSI_SCEP_FAILURE |NA]
*
*/
typedef SEC_INT (*IPSI_SCEP_CA_FINGERPRINT_CB)(IPSI_SCEP_OBJ_S *pstScepObj,
                     SEC_UINT uiRequestId,
                        X509_CERT_S * pstCACert,
                        SEC_VOID *pvUserData);




/**
* @defgroup IPSI_SCEP_ObjSetFingerPrintCB
* @ingroup Object_CallbackFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SCEP_ObjSetFingerPrintCB(IPSI_SCEP_OBJ_S *pstScepObj,
*                                     IPSI_SCEP_CA_FINGERPRINT_CB *pfCAFngPrnCB,
*                                     SEC_VOID* pvUserData);
* @endcode
*
* @par Purpose
* This function is used to register the fingerprint callback function 
* with the object.
*
* @par Description
* IPSI_SCEP_ObjSetFingerPrintCB function registers the fingerprint callback 
* function with the object.This callback function will be called when the 
* CA certificate fingerprint verification is failed during GetCA operation.
*
* @param[in] pstScepObj Pointer to object.[NA/NA]
* @param[in] pfCAFngPrnCB FingerPrint Callback. [NA/NA]
* @param[in] pvUserData Pointer to user specific data.
* The same pointer will be returned when the callback is called [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT If the set is successful. [IPSI_SCEP_SUCCESS|NA]
* @retval SEC_INT If it fails to set. [IPSI_SCEP_ERROR|NA]
*
*/
PSELINKDLL SEC_INT IPSI_SCEP_ObjSetFingerPrintCB(IPSI_SCEP_OBJ_S *pstScepObj,
                                       IPSI_SCEP_CA_FINGERPRINT_CB pfCAFngPrnCB,
                                             SEC_VOID* pvUserData);

#ifdef  __cplusplus
}
#endif

#endif /*__IPSI_OBJ_SCEP_H__*/

#endif /*__IPSI_SEC_NO_SCEP__*/
