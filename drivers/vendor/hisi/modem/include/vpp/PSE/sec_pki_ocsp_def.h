/***************************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: sec_pki_ocsp_def.h
Version: 1
Author:
Creation Date:
Description: This file contains definitions of the ocsp

Function List:

History:
<Author>   <date>          <desc>

***************************************************************************/
#include "ipsi_pse_build_conf.h"

#ifndef __SEC_PKI_OCSP_DEF_H__
#define __SEC_PKI_OCSP_DEF_H__

#include "sec_sys.h"
#include "sec_crypto.h"
#include "ipsi_types.h"

#ifdef  __cplusplus
extern "C" {
#endif

// Signature algorithm

/**
* @defgroup Enum
*.@ingroup OCSP_Validation
* This section contains all the Enums.
*/
/**
* @defgroup SEC_PKI_OCSP_SIGNALG_TYPE_E
* @ingroup Enum
* @par Description
* Enum to indicate the Hash algorithm.
* @par Prototype
* @code
* typedef enum 
* {
*     SEC_PKI_OCSP_WITH_SHA1 = ALGID_SHA1,
*     SEC_PKI_OCSP_WITH_SHA256 = ALGID_SHA256
* }SEC_PKI_OCSP_SIGNALG_TYPE_E;
* @endcode
* @datastruct SEC_PKI_OCSP_WITH_SHA1 Enables to use SHA1 algorithm for 
                                     request creation
* @datastruct SEC_PKI_OCSP_WITH_SHA256 Enables to use SHA1 algorithm for
                                     request creation

*/

typedef enum 
{
    SEC_PKI_OCSP_WITH_SHA1 = ALGID_SHA1,
    SEC_PKI_OCSP_WITH_SHA256 = ALGID_SHA256
}SEC_PKI_OCSP_SIGNALG_TYPE_E;

/**
* @defgroup SEC_PKI_OCSP_LOAD_RESP_FLAG_E
* @ingroup Enum
* @par Description
* Flags indicating OCSP response buffer loading type.
* @par Prototype
* @code
* typedef enum 
* {
*     SEC_PKI_OCSP_LOAD_COMPLETE_RESP = 0,
*     SEC_PKI_OCSP_LOAD_WITHOUT_CERTS_IN_MSG = 1
* }   SEC_PKI_OCSP_LOAD_RESP_FLAG_E;
* @endcode
* @datastruct SEC_PKI_OCSP_LOAD_COMPLETE_RESP Enables to load OCSP response
* along with certificates in message if present.
* @datastruct SEC_PKI_OCSP_LOAD_WITHOUT_CERTS_IN_MSG Enables to load OCSP 
* response without certificates in message even if it is present.
*/

typedef enum 
{
    SEC_PKI_OCSP_LOAD_COMPLETE_RESP = 0,
    SEC_PKI_OCSP_LOAD_WITHOUT_CERTS_IN_MSG = 1
}SEC_PKI_OCSP_LOAD_RESP_FLAG_E;


/* OCSP Configuration parameters */
/**
* @defgroup SEC_PKI_OCSP_CONF_TYPE_E
* @ingroup Enum
* @par Description
* Flags indicating OCSP configuration type.
* @par Prototype
* @code
* typedef enum
* {
*    SEC_PKI_OCSP_RESP_CHECK_TIME  = 0x00000001,
*    SEC_PKI_OCSP_RESP_CHECK_CRL = 0x00000002,
*    SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL = 0x00000008,
*    SEC_PKI_OCSP_RESP_X509_V_FLAG_IGNORE_CRITICAL = 0x00000040,
*    SEC_PKI_OCSP_SIGN_REQUEST = 0x00000400,
*    SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN = 0x00000800,
*    SEC_PKI_OCSP_TRUST_RESP_CERTS_IN_MSG  = 0x00001000,
*    SEC_PKI_OCSP_EXTN_NONCE =  0x00002000,
*    SEC_PKI_OCSP_EXTN_RESP_TYPES = 0x00004000
* }  SEC_PKI_OCSP_CONF_TYPE_E;
* @endcode
* @datastruct SEC_PKI_OCSP_RESP_CHECK_TIME Enable responder certificate 
* validation with time.
* @datastruct SEC_PKI_OCSP_RESP_CHECK_CRL Enables CRL validation only for 
* responder cert.
* @datastruct SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL Enables delta CRL validation
* only for responder cert.
* @datastruct SEC_PKI_OCSP_RESP_X509_V_FLAG_IGNORE_CRITICAL Ignores 
* critical extension
* @datastruct SEC_PKI_OCSP_SIGN_REQUEST Enables signing OCSP request.
* @datastruct SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN Enables sending certs 
* with OCSP request.
* @datastruct SEC_PKI_OCSP_TRUST_RESP_CERTS_IN_MSG Enables to use 
* certificate in response messsage as responder certificate.
* @datastruct SEC_PKI_OCSP_EXTN_NONCE Enables Nonce verification of 
* OCSP response.
* @datastruct SEC_PKI_OCSP_EXTN_RESP_TYPES Enables response type specification.

*
*/
typedef enum
{
    SEC_PKI_OCSP_RESP_CHECK_TIME  = 0x00000001,
    SEC_PKI_OCSP_RESP_CHECK_CRL = 0x00000002,
    SEC_PKI_OCSP_RESP_CHECK_DELTA_CRL = 0x00000008,
    SEC_PKI_OCSP_RESP_X509_V_FLAG_IGNORE_CRITICAL = 0x00000040,
    SEC_PKI_OCSP_SIGN_REQUEST = 0x00000400,
    SEC_PKI_OCSP_SIGN_REQ_WITH_CERT_CHAIN = 0x00000800,
    SEC_PKI_OCSP_TRUST_RESP_CERTS_IN_MSG  = 0x00001000,
    SEC_PKI_OCSP_EXTN_NONCE =  0x00002000,
    SEC_PKI_OCSP_EXTN_RESP_TYPES = 0x00004000
}SEC_PKI_OCSP_CONF_TYPE_E;


/**
* @defgroup SEC_PKI_OCSP_MSG_TYPE_E
* @ingroup Enum
* @par Description
* Flags indicating OCSP Message type.
* @par Prototype
* @code
* typedef enum 
* {
*    SEC_PKI_OCSP_SEND_MSG,
*    SEC_PKI_OCSP_RCV_MSG
* }SEC_PKI_OCSP_MSG_TYPE_E;
* @endcode
* @datastruct SEC_PKI_OCSP_SEND_MSG Indicates the message is being sent.
* @datastruct SEC_PKI_OCSP_RCV_MSG Indicates the message is being received.
*
*/

typedef enum 
{
    SEC_PKI_OCSP_SEND_MSG,
    SEC_PKI_OCSP_RCV_MSG
}SEC_PKI_OCSP_MSG_TYPE_E;


/**
* @defgroup Callback_Function
* @ingroup OCSP_Validation
* This section contains all the Callback Functions.
*/

/**
* @defgroup IPSI_OCSP_MSG_TRACE_CB
* @ingroup Callback_Function
* @par Prototype
* @code
* typedef SEC_VOID (*IPSI_OCSP_MSG_TRACE_CB)(
*    SEC_UINT32 ulReqId,
*    SEC_PKI_OCSP_MSG_TYPE_E enPacketType, 
*    SEC_UCHAR *pcMsg, 
*    SEC_UINT uiLen,
*	 SEC_VOID * pAppData);
* @endcode
*
* @par Purpose
* This provides the prototype of OCSP message trace callback function.
*
* @par Description
* IPSI_OCSP_MSG_TRACE_CB provides the prototype of OCSP message trace callback
* function which will be called when OCSP message is sent.
*
* @param[in] ulReqId Request ID of message [NA/NA]
* @param[in] enPacketType Type of packet 
* [SEC_PKI_OCSP_SEND_MSG|SEC_PKI_OCSP_RCV_MSG/NA]
* @param[in] pcMsg OCSP message [NA/NA]
* @param[in] uiLen Length of OCSP message [NA/NA]
* @param[in] pAppData void pointer contains information of store context.[NA/NA]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
* @par Note
* \n
* Before sending the OCSP message to the HTTP module, this callback function 
*   will be called with DER encoded OCSP message.
*
*/

typedef SEC_VOID (*IPSI_OCSP_MSG_TRACE_CB)(
    SEC_UINT32 ulReqId,
    SEC_PKI_OCSP_MSG_TYPE_E enPacketType, 
    SEC_UCHAR *pcMsg, 
    SEC_UINT uiLen,
    SEC_VOID * pAppData);



#ifdef __cplusplus
}
#endif

#endif /*__SEC_PKI_DEF_H__*/
