/*****************************************************************************

Copyright (C), 2008, Huawei Tech. Co., Ltd.                
ALL RIGHTS RESERVED                             

------------------------------------------------------------------------------

FileName     :cmpv2.h
Author       : Mallesh K M
Version      :1
Date         :14-10-2009
Description  :CMPV2 Functions
Function List: 

History:
<author>   <date>          <desc>
----------------------------------------------------------------------------
****************************************************************************/

#include "ipsi_pse_build_conf.h"

#ifndef _SSL_

#ifndef _IPSI_CMPV2_H_
#define _IPSI_CMPV2_H_


#include "sec_list.h"
#include "sec_sys.h"
#include "cmp.h"
#include "ipsi_types.h"
#include "x509_basictypes.h"
#include "asn-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
* This data structure is used by the client to send a confirmation to
* the CA/RA to accept or reject certificates.
*/
/** @defgroup cmpv2
* This section contains the cmpv2 Structures and Functions */

/** @defgroup cmpv2Structures
* @ingroup cmpv2
* This section contains the cmpv2 Structures
*/

/** @defgroup cmpv2Functions
* @ingroup cmpv2
* This section contains the cmpv2 Functions
*/
/**
* @defgroup CMPV2_CERT_CONF_S
* @ingroup cmpv2Structures
* @par Prototype
* @code
* typedef struct stCMPV2_CertConf
* {
*    SEC_AsnOcts_S stCertHash;
*    SEC_INT32 iCertReqId;
*    CMP_PKISTATUS_S *pstPKIStatus;
* }CMP_CERT_CONF_S;
* @endcode
*
* @datastruct stCertHash Hash of the certificate
* @datastruct iCertReqId Request id of the certificate request
* randomly-generated INTEGER.
* @datastruct pstPKIStatus Status of the certificate
*/

typedef struct stCMPV2_CertConf
{
    SEC_AsnOcts_S stCertHash;
    SEC_INT32 iCertReqId;
    CMP_PKISTATUS_S *pstPKIStatus;
}CMPV2_CERT_CONF_S;


/* 
* This data structure is used by the client to send a confirmation to
* the CA/RA to accept or reject certificates.
*/
/**
* @defgroup CMPV2_POLL_REQ_S
* @ingroup cmpv2Structures
* @par Prototype
* @code
* typedef struct stCMPV2_PollReq
* {
*    SEC_INT32 iCertReqId;
* }CMPV2_POLL_REQ_S;
* @endcode
*
* @datastruct iCertReqId Request id of the certificate request
*/
typedef struct stCMPV2_PollReq
{
    SEC_INT32 iCertReqId;
}CMPV2_POLL_REQ_S;


/* 
* This data structure is used by the client to send a confirmation to
* the CA/RA to accept or reject certificates.
*/
/**
* @defgroup CMPV2_POLL_REP_S
* @ingroup cmpv2Structures
* @par Prototype
* @code
* typedef struct stCMPV2_PollRep
* {
*    SEC_INT32 iCertReqId;
*    SEC_INT32 iCheckAfter;
*    SEC_List_S* pStReason;
* }CMPV2_POLL_REP_S;
* @endcode
*
* @datastruct iCertReqId Request id of the certificate request
* @datastruct iCheckAfter poll time in seconds
* @datastruct pStReason reason 
*/
typedef struct stCMPV2_PollRep
{
    SEC_INT32 iCertReqId;
    SEC_INT32 iCheckAfter;
    SEC_List_S* pStReason; /* Reason Optional*/
}CMPV2_POLL_REP_S;

/**
* @defgroup CMPv2_createConfContent
* @ingroup cmpv2Functions
* @par Prototype
* @code
* CMPV2_CERT_CONF_S* CMPv2_createConfContent (
* X509_CERT_S *pstCert,
* SEC_INT32 iCertReqID,
* CMP_PKISTATUS_S* pstPKIStatusInfo);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstCert NA [NA]
* @param[in] iCertReqID NA [NA]
* @param[in] pstPKIStatusInfo NA [NA]
* @param[out] NA NA [NA]
*
* @retval CMPV2_CERT_CONF_S* NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/
/*
CMPv2_createConfContent Function creates the Confirmation content
*/
PSELINKDLL CMPV2_CERT_CONF_S* CMPv2_createConfContent (
                                   X509_CERT_S *pstCert,
                                   SEC_INT32 iCertReqID,
                                   CMP_PKISTATUS_S* pstPKIStatusInfo);

/**
* @defgroup CMPV2_createConfMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* CMPV2_CERT_CONF_MSG_S * CMPV2_createConfMsg(
* CMPV2_CERT_CONF_S *pstConf);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstConf NA [NA]
* @param[out] NA NA [NA]
*
* @retval CMPV2_CERT_CONF_MSG_S* NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/
/*
CMPV2_createConfMsg Function creates the Conf message 
*/

PSELINKDLL CMPV2_CERT_CONF_MSG_S * CMPV2_createConfMsg(
         CMPV2_CERT_CONF_S *pstConf);
/**
* @defgroup CMPV2_addToConfMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* SEC_INT CMPV2_addToConfMsg(
* CMPV2_CERT_CONF_MSG_S*pstConfMsg,
* CMPV2_CERT_CONF_S *pstCMPConf);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstConfMsg NA [NA]
* @param[in] pstCMPConf NA [NA]
* @param[out] NA NA [NA]
*
* @retval SEC_INT NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/
/*
CMPV2_addConfMsg Adds the Confirmation content to the Confirmation Msg
*/
PSELINKDLL SEC_INT CMPV2_addToConfMsg(
         CMPV2_CERT_CONF_MSG_S*pstConfMsg,
         CMPV2_CERT_CONF_S *pstCMPConf);

/**
* @defgroup CMPV2_getCertConf
* @ingroup cmpv2Functions
* @par Prototype
* @code
* CMPV2_CERT_CONF_S *CMPV2_getCertConf(
* CMPV2_CERT_CONF_MSG_S *pstConfMsg,
* SEC_INT32 iCertReqId);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstConfMsg NA [NA]
* @param[in] iCertReqId NA [NA]
* @param[out] NA NA [NA]
*
* @retval CMPV2_CERT_CONF_S* NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/
PSELINKDLL CMPV2_CERT_CONF_S *CMPV2_getCertConf(
         CMPV2_CERT_CONF_MSG_S *pstConfMsg,
         SEC_INT32 iCertReqId);

/**
* @defgroup CMPV2_freeCertConf
* @ingroup cmpv2Functions
* @par Prototype
* @code
* SEC_VOID CMPV2_freeCertConf(
* CMPV2_CERT_CONF_S *pstCertConf);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstCertConf NA [NA]
* @param[out] NA NA [NA]
*
* @retval SEC_VOID This function does not return any value. [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/

PSELINKDLL SEC_VOID CMPV2_freeCertConf(
    CMPV2_CERT_CONF_S *pstCertConf);

/**
* @defgroup CMPV2_freeCertConfMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* SEC_VOID CMPV2_freeCertConfMsg(
* CMPV2_CERT_CONF_MSG_S *pstCertConfMsg);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstCertConfMsg NA [NA]
* @param[out] NA NA [NA]
*
* @retval SEC_VOID This function does not return any value. [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/
PSELINKDLL SEC_VOID CMPV2_freeCertConfMsg(
    CMPV2_CERT_CONF_MSG_S *pstCertConfMsg);

/**
* @defgroup CMPV2_createPollReqMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* CMPV2_POLL_REQ_MSG_S* CMPV2_createPollReqMsg(
* SEC_INT32 iCertReqID);
* @endcode
* 
* @par Description
* 
* 
* @param[in] iCertReqID NA [NA]
* @param[out] NA NA [NA]
*
* @retval CMPV2_POLL_REQ_MSG_S* NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/
PSELINKDLL CMPV2_POLL_REQ_MSG_S* CMPV2_createPollReqMsg(
    SEC_INT32 iCertReqID);

/**
* @defgroup CMPV2_addToPollReqMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* SEC_INT CMPV2_addToPollReqMsg(
* CMPV2_POLL_REQ_MSG_S *pstPollReqMsg,
* SEC_INT32 iCertReqID);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstPollReqMsg NA [NA]
* @param[in] iCertReqID NA [NA]
* @param[out] NA NA [NA]
*
* @retval SEC_INT NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/

PSELINKDLL SEC_INT CMPV2_addToPollReqMsg(
    CMPV2_POLL_REQ_MSG_S *pstPollReqMsg,
    SEC_INT32 iCertReqID);


/**
* @defgroup CMPV2_createPollRep
* @ingroup cmpv2Functions
* @par Prototype
* @code
* CMPV2_POLL_REP_S* CMPV2_createPollRep(
* SEC_INT32 iCertReqID, SEC_INT32 iCheckAfter, SEC_List_S* pStReason);
* @endcode
* 
* @par Description
* 
* 
* @param[in] iCertReqID NA [NA]
* @param[in] iCheckAfter NA [NA]
* @param[in] pStReason NA [NA]
* @param[out] NA NA [NA]
*
* @retval CMPV2_POLL_REP_S* NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/

PSELINKDLL CMPV2_POLL_REP_S* CMPV2_createPollRep(
    SEC_INT32 iCertReqID, SEC_INT32 iCheckAfter, SEC_List_S* pStReason);

/**
* @defgroup CMPV2_createPollRepMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* CMPV2_POLL_REP_MSG_S* CMPV2_createPollRepMsg(
* CMPV2_POLL_REP_S *pstPollRep);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstPollRep NA [NA]
* @param[out] NA NA [NA]
*
* @retval CMPV2_POLL_REP_MSG_S* NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/
PSELINKDLL CMPV2_POLL_REP_MSG_S* CMPV2_createPollRepMsg(
    CMPV2_POLL_REP_S *pstPollRep);


/**
* @defgroup CMPV2_addToPollRepMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* SEC_INT CMPV2_addToPollRepMsg(
* CMPV2_POLL_REP_MSG_S *pstPollRepMsg, CMPV2_POLL_REP_S *pstPollRep);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstPollRepMsg NA [NA]
* @param[in] pstPollRep NA [NA]
* @param[out] NA NA [NA]
*
* @retval SEC_INT NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/

PSELINKDLL SEC_INT CMPV2_addToPollRepMsg(
    CMPV2_POLL_REP_MSG_S *pstPollRepMsg, CMPV2_POLL_REP_S *pstPollRep);


/**
* @defgroup CMPV2_freePollReqMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* SEC_VOID CMPV2_freePollReqMsg(CMPV2_POLL_REQ_MSG_S* pstPollReqMsg);
* @endcode
* 
* @par Description
* 
* 
* @param[in] pstPollReqMsg NA [NA]
* @param[out] NA NA [NA]
*
* @retval SEC_VOID NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/

PSELINKDLL SEC_VOID CMPV2_freePollReqMsg(CMPV2_POLL_REQ_MSG_S* pstPollReqMsg);


/**
* @defgroup CMPV2_freePollRepMsg
* @ingroup cmpv2Functions
* @par Prototype
* @code
* SEC_VOID CMPV2_freePollRepMsg(CMPV2_POLL_REP_MSG_S* pstPollRepMsg);
* @endcode
* 
* @par Description
* 
* 
* @param[in] NA NA [NA]
* @param[out] NA NA [NA]
*
* @retval SEC_VOID NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/

PSELINKDLL SEC_VOID CMPV2_freePollRepMsg(CMPV2_POLL_REP_MSG_S* pstPollRepMsg);


/**
* @defgroup CMPV2_freePollRep
* @ingroup cmpv2Functions
* @par Prototype
* @code
* SEC_VOID CMPV2_freePollRep(CMPV2_POLL_REP_S* pstPollRep);
* @endcode
* 
* @par Description
* 
* 
* @param[in] NA NA [NA]
* @param[out] NA NA [NA]
*
* @retval SEC_VOID NA [NA|NA]
*
* @par Dependency
* None
*
* @par Note
* \n
* 
* None
*
* @par Related Topics
* None
*/

PSELINKDLL SEC_VOID CMPV2_freePollRep(CMPV2_POLL_REP_S* pstPollRep);


#ifdef __cplusplus
}
#endif

#endif /*_IPSI_CMPV2_H_*/

#endif /*_SSL_*/

