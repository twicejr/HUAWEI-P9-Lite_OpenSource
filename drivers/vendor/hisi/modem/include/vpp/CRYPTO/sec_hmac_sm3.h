/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_hmac_sm3.h
  Version:
  Date Created: 2012-10-15
  Author: Prabhat Kumar Gopalika
  Descrption: Contains HMAC SM3 core interface functions
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
 
*/

#ifndef _IPSI_CORE_HMAC_SM3_H
#define _IPSI_CORE_HMAC_SM3_H

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif


#define IPSI_HMAC_SM3_CTX_SIZE 208

#define IPSI_HMAC_SM3_SIZE 32


/**
* @defgroup ipsi_hmac_sm3_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*     SEC_UCHAR data[IPSI_HMAC_SM3_CTX_SIZE];
* }ipsi_hmac_sm3_ctx;
* @endcode
*
* @datastruct data[IPSI_HMAC_SM3_CTX_SIZE] Represents the buffer for 
* HMAC SM3
* context.
*/

typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SM3_CTX_SIZE];
}ipsi_hmac_sm3_ctx_t; 

/*
    Func Name:  ipsi_hmac_sm3_init
*/

/** 
* @defgroup ipsi_hmac_sm3_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sm3_init(ipsi_hmac_sm3_ctx_t * ctx, 
*                              cont SEC_UCHAR * pucKey, SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the ipsi_hmac_sm3_ctx_t context for a mac 
* operation.
*
* @par Description
* ipsi_hmac_sm3_init function initializes the context for
* a mac operation. This function must be called before any
* ipsi_hmac_sm3_update or ipsi_hmac_sm3_final operations.
* This function will not allocate memory for any of the context variables.
* Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx ipsi_hmac_sm3_t context [N/A]
* @param[in] pucKey Key for HMAC
* @param[in] ulKlen Key length [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sm3 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If key is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sm3.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sm3_init(
                                 ipsi_hmac_sm3_ctx_t *ctx,
                                 const SEC_UCHAR * pucKey, 
                                 SEC_UINT32 ulKlen);

/**
* @defgroup ipsi_hmac_sm3_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sm3_update(ipsi_hmac_sm3_ctx_t *ctx,
*                                    SEC_UCHAR *pucData, 
*                                    SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform hmac sm3 operation on chunks of data.
*
* @par Description
* ipsi_hmac_sm3_update function performs hmac operation on 
* chunks of data. This method of MACing is used when data is present
* in multiple buffers or not available all at once. 
* A ipsi_hmac_sm3_init must have been called before calling this function.
*
* @param[in] ctx The ipsi_hmac_sm3_t context [N/A]
* @param[in] pucData The input data [N/A]
* @param[in] ulDataLen The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sm3 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If data is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sm3.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sm3_update(
                                        ipsi_hmac_sm3_ctx_t *ctx,
                                        SEC_UCHAR *pucData, 
                                        SEC_UINT32 ulDataLen);


/** 
* @defgroup ipsi_hmac_sm3_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sm3_final(ipsi_hmac_sm3_ctx_t *ctx,
*                            SEC_UCHAR pucDigest[IPSI_HMAC_SM3_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete hmac-sm3 mac operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_hmac_sm3_final function completes digest operation on remaining
* data, and is called at the end of digest operation.
* ipsi_hmac_sm3_init must have been called before calling this function. 
* This function calculates the mac. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The ipsi_hmac_sm3_ctx_t context [N/A]
* @param[out] pucDigest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sm3 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sm3.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sm3_final(
                            ipsi_hmac_sm3_ctx_t *ctx,
                            SEC_UCHAR pucDigest[IPSI_HMAC_SM3_SIZE]);



#ifdef __cplusplus
}


#endif

#endif /* _IPSI_CORE_HMAC_SM3_H */

