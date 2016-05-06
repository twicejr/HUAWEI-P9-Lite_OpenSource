/******************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: ipsi_error.h
Version: 1
Author:  Mallesh
Creation Date: 2009-4-24
Description: This file declares the error
handling function

Function List:
1.  IPSI_push_error
2.  IPSI_clear_error
3.  IPSI_delete_err_stack

History:<author>   <date>          <desc>
              
*********************************************/

#ifndef __IPSI_ERROR_H__
#define __IPSI_ERROR_H__

#include "ipsi_types.h"
#include "sec_sys.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* Minimum error value for EAP */
#define IPSI_EAP_MIN_ERR_VAL        10000

/* Maximum error value for EAP */
#define IPSI_EAP_MAX_ERR_VAL        14999


/* Minimum error value for PKI */
#define IPSI_PKI_MIN_ERR_VAL        1000

/* Maximum error value for PKI */
#define IPSI_PKI_MAX_ERR_VAL        9999

/* Minimum error value for PKI */
#define IPSI_CAT_MIN_ERR_VAL        15000

/* Maximum error value for PKI */
#define IPSI_CAT_MAX_ERR_VAL        19999

/* Minimum error value for SIGCBB_VRF */
#define IPSI_SIGCBB_VRF_MIN_ERR_VAL        20000

/* Maximum error value for SIGCBB_VRF */
#define IPSI_SIGCBB_VRF_MAX_ERR_VAL        24999

/* Minimum error value for SIGCBB_CLI */
#define IPSI_SIGCBB_CLI_MIN_ERR_VAL        25000

/* Maximum error value for SIGCBB_CLI */
#define IPSI_SIGCBB_CLI_MAX_ERR_VAL        29999

/* Minimum error value for SIGCBB_CLI */
#define IPSI_SIGCBB_GUI_MIN_ERR_VAL        30000

/* Maximum error value for SIGCBB_CLI */
#define IPSI_SIGCBB_GUI_MAX_ERR_VAL        34999

/* Minimum error value for CMP */
#define IPSI_CMP_MIN_ERR_VAL        40000

/* Maximum error value for CMP */
#define IPSI_CMP_MAX_ERR_VAL        44999

/* Minimum error value for HTTP */
#define IPSI_HTTP_MIN_ERR_VAL       50000

/* Maximum error value for HTTP */
#define IPSI_HTTP_MAX_ERR_VAL       54999

/*Minimum error value for SCEP*/
#define IPSI_SCEP_MIN_ERR_VAL        55000

/*Maximum error value for SCEP*/
#define IPSI_SCEP_MAX_ERR_VAL        59999


/**
* @defgroup Error_Function
* This section contains all the error functions used in iPSI library.
*/

/**
* @defgroup IPSI_getlast_error
* @ingroup Error_Function
* @par Prototype
* @code
* SEC_UINT IPSI_getlast_error(SEC_VOID);
* @endcode
* 
* @par Purpose
* This function is used to get the last error occurred.
* @par Description
* IPSI_getlast_error gets the last error occurred.
*
* @param[in] NA NA [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_UINT Error Code [NA|NA]
*/

CRYPTOLINKDLL SEC_UINT IPSI_getlast_error(SEC_VOID);

#ifndef __IPSI_NO_ERROR_STRING__

/**
* @defgroup IPSI_get_error_string
* @ingroup Error_Function
* @par Prototype
* @code
* const SEC_CHAR* IPSI_get_error_string(SEC_UINT uiErrCode);
* @endcode
* 
* @par Purpose
* This function is used to get the error string for a particular error code. 
* @par Description
* IPSI_get_error_string function gets the error string for a particular
* error code.The user has to pass the reason error code to get the error string.

*
* @param[in] uiErrCode Error code [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_CHAR Character pointer to error string. [NA|NA]
*
*/

CRYPTOLINKDLL const SEC_CHAR* IPSI_get_error_string(SEC_UINT uiErrCode);

#endif // __IPSI_NO_ERROR_STRING__


// Gives the error code
#define IPSI_ERR_REASON_CODE(err)\
    (err & 0x0000FFFF)

// Gives the function code where error is occured
#define IPSI_FUNC_REASON_CODE(err)\
    (err >> 16)


#ifdef  __cplusplus
}
#endif

#endif


