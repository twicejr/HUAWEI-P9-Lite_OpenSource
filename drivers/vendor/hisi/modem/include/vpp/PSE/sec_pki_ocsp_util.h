#include "ipsi_pse_build_conf.h"

#ifndef __SEC_PKI_OCSP_UTIL_H__
#define __SEC_PKI_OCSP_UTIL_H__

#include "sec_pki_buildconf.h"
#include "ipsi_types.h"
#include "sec_sys.h"
#include "x509_basictypes.h"
#include "x509v3_extn.h"


#ifdef  __cplusplus
extern "C" {
#endif

/** @defgroup OCSP_Validation
* This section contains the OCSP_Validation Functions.
*/

/** @defgroup Utility_Function
* @ingroup OCSP_Validation
* This section contains the Utility Functions.
*/
/**
* @defgroup SEC_PKI_getOCSPResponderLocation
* @ingroup Utility_Function
* @par Prototype
* @code
* SEC_INT SEC_PKI_getOCSPResponderLocation (
*    X509_CERT_S *pstCert, SEC_GEN_NAME_S **dpstOCSPRespLocation);
* @endcode
*
* @par Purpose
* This function is used to get the OCSP responder location from the certificate.
*
* @par Description
* SEC_PKI_getOCSPResponderLocation function 
* gets the OCSP responder location from the input certificate which is 
* present in the AIA extension in the certificate.If the AIA extension is 
* not present in the certificate then this API will fail to get the 
* OCSP responder location.
*
* @param[in] pstCert X509 Certificate [NA/NA].
* @param[out] pstOCSPRespLocation responder Location.[NA/NA]
*
* @retval SEC_INT On successful execution. [SEC_PKI_SUCCESS|NA]
* @retval SEC_INT On all failure conditions. [SEC_PKI_ERROR|NA]
*
* @Par Memory Handling
* \n
* On success this function will allocate the memory for the pstOCSPRespLocation.
* To free this memory, application has to call X509_freeGeneralName.
*
*/
PSELINKDLL SEC_INT SEC_PKI_getOCSPResponderLocation(
            X509_CERT_S *pstCert, SEC_GEN_NAME_S **dpstOCSPRespLocation);


#ifdef  __cplusplus
}
#endif

#endif /*__SEC_PKI_OCSP_UTIL_H__*/

