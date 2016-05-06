/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_sm3.h
  Version:
  Date Created: 2012-11-19
  Author: Prabhat Kumar Gopalika
  Descrption: Contains interface functions for SM3
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
 
*/

#ifndef _IPSI_SEC_SM3_H__
#define _IPSI_SEC_SM3_H__

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif

#define IPSI_SM3_CTX_SIZE 104
#define IPSI_SM3_DIGEST_SIZE 32

/**
* @defgroup ipsi_sm3_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*  SEC_UCHAR data[IPSI_SM3_CTX_SIZE];
* }ipsi_sm3_ctx_t;
* @endcode
*
* @datastruct data[IPSI_SM3_CTX_SIZE] Represents the buffer for SM3
* context.
*/
typedef struct
{
    SEC_UCHAR data[IPSI_SM3_CTX_SIZE];
}ipsi_sm3_ctx_t;


/*
    Func Name:  ipsi_sm3_init
*/

/** 
* @defgroup ipsi_sm3_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sm3_init(ipsi_sm3_ctx_t *ctx);
* @endcode
*
* @par Purpose
* This is used to initialize the SM3 context for a digest operation.
*
* @par Description
* ipsi_sm3_init function initializes the context for
* a digest operation. This function must be called before
* ipsi_sm3_update or ipsi_sm3_final operations. This function will not
* allocate memory for any of the context variables. Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx The sm3 context [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_sm3.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_sm3_init(ipsi_sm3_ctx_t *ctx);

/**
* @defgroup ipsi_sm3_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sm3_update(ipsi_sm3_ctx_t *ctx,
*                               const SEC_UCHAR *data,
*                               SEC_UINT32 nbytes);
* @endcode
*
* @par Purpose
* This is used to perform sm3 digest operation on chunks of data.
*
* @par Description
* ipsi_sm3_update function performs digest operation on 
* chunks of data. This method of digesting is used when data is
* present in multiple buffers or not available all at once.  
* ipsi_sm3_init must have been called before calling this
* function.
*
* @param[in] ctx The sm3 context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_sm3.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_sm3_update(
                                        ipsi_sm3_ctx_t *ctx,
                                        const SEC_UCHAR *data,
                                        SEC_UINT32 nbytes);

/** 
* @defgroup ipsi_sm3_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sm3_final(ipsi_sm3_ctx_t *ctx,
*                              SEC_UCHAR digest[IPSI_SM3_DIGEST_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete sm3 digest operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_sm3_final function completes digest operation on remaining data, and
* is called at the end of digest operation.
* ipsi_sm3_init must have been called before calling this function. This 
* function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The sm3 context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_sm3.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 ipsi_sm3_final(
                                ipsi_sm3_ctx_t *ctx,
                                SEC_UCHAR digest[IPSI_SM3_DIGEST_SIZE]);


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_SEC_SM3_H__ */

