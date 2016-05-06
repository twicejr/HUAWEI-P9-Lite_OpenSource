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
#ifndef _IPSI_OCSP_EX_H_
#define _IPSI_OCSP_EX_H_

#include "ipsi_types.h"
#include "asn-types.h"
#include "sec_sys.h"
#include "ocsp.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
* @defgroup ocsp_calcKeyHash_ex
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UCHAR* ocsp_calcKeyHash_ex(const SEC_AsnBits_S * pstPubKey,
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
PSELINKDLL SEC_UCHAR* ocsp_calcKeyHash_ex(const SEC_AsnBits_S * pstPubKey,
							SEC_UINT32 ulHashAlg,
							SEC_UINT32* pulHashLength);




/**
* @defgroup OCSP_addSingleReqToOCSPReq_ex
* @ingroup ocspFunctions
* @par Prototype
* @code
* SEC_UINT32 OCSP_addSingleReqToOCSPReq_ex(OCSP_SINGLE_REQ_S* pSingleReq,
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
* @retval SEC_UINT32 Single reqquest list creation or addition of the
*										single request to the OCSP request is failed [SEC_ERR_LIST_OPERATION_FAILED|N/A]
* @retval SEC_UINT32 Single OCSP request already exists [SEC_OCSP_ERR_REQ_EXISTS|N/A]
*
* @par Dependency
* ocsp.h
*
* @par Note
* It will not Dup the Single Request. Hence the user should not free the OCSP Single request
* which is added to the OCSP request. It will get freed while freeing the OCSP request.
*
* @par Related Topics
* N/A
*
* 
*/

PSELINKDLL SEC_UINT32 OCSP_addSingleReqToOCSPReq_ex(OCSP_SINGLE_REQ_S* pSingleReq,
									  const OCSP_REQUEST_S* pOCSPReq);


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_OCSP_EX_H_ */
#endif  /* __SEC_NO_OCSP__ */




