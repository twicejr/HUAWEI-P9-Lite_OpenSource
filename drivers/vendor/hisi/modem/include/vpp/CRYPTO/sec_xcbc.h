/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_xcbc.h
  Version:
  Date Created: 2005-09-22
  Author: Prabhat Kumar Gopalika, Kaushik Sarkar
  Descrption: Contains AES XCBC interface functions
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
 
*/

#ifndef _SEC_AES_XCBC_H_
#define _SEC_AES_XCBC_H_


#include "ipsi_crypto_buildconf.h"

#ifndef __IPSI_NO_XCBC_AES__

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif

#define IPSI_AES_XCBC_CTX_SIZE 432
#define IPSI_XCBC_DIGEST_SIZE 16

/* The AES Xcbc representation */

/**
* @defgroup ipsi_aes_xcbc_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*  SEC_UCHAR data[IPSI_XCBC_CTX_SIZE];
* }ipsi_aes_xcbc_ctx_t;
* @endcode
*
* @datastruct data[IPSI_XCBC_CTX_SIZE] Represents the buffer for AES XCBC
* context.
*/

typedef struct
{
    SEC_UCHAR data[IPSI_AES_XCBC_CTX_SIZE];
}ipsi_aes_xcbc_ctx_t;

/*
    Func Name:  ipsi_aes_xcbc_init
*/

/** 
* @defgroup ipsi_aes_xcbc_init
* @ingroup LLF Low Level Functions 
* @par Prototype
* @code
* SEC_UINT32 ipsi_aes_xcbc_init (
*                            ipsi_aes_xcbc_ctx_t* pCtx,
*                            const SEC_UCHAR *pucKey,
*                            const SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the context for a AES XCBC MAC operation.
*
* @par Description
* ipsi_aes_xcbc_init function initializes the context for a xcbc MAC operation.
* This function must be called before any Update
* or Final operations. This method of MACing is used when data is
* present in multiple buffers or not available all at once.
* The caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] pucKey Key for XCBC MAC [N/A]
* @param[in] ulKlen Key length [N/A]
* @param[out] pCtx The context which will be filled [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments 
* are missing [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If the key length is invalid 
* [SEC_ERR_INVALID_KEY_LEN|N/A]
*
* @par Required Header File
* sec_xcbc.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_aes_xcbc_init(
                        ipsi_aes_xcbc_ctx_t *pCtx,
                        const SEC_UCHAR *pucKey,
                        const SEC_UINT32 ulKlen);


/*
    Func Name:  ipsi_aes_xcbc_update
*/

/** 
* @defgroup ipsi_aes_xcbc_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_aes_xcbc_update (
*                              ipsi_aes_xcbc_ctx_t *pCtx,
*                              const SEC_UCHAR *pucData,
*                              SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform xcbc MAC operation on chunks of data.
*
* @par Description
* ipsi_aes_xcbc_update function performs xcbc MAC operation on chunks of 
* data. This method of MACing is used when data is present
* in multiple buffers or not available all at once. An xcbc_init must 
* have been called before calling this function.
*
* @param[in] pCtx The context for xcbc mac [N/A]
* @param[in] pucData The input data [N/A]
* @param[in] ulDataLen The input data length [N/A]
*
* @retval SEC_UINT32 If partial MAC is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are 
* not correct [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments 
* are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_xcbc.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_aes_xcbc_update(
                        ipsi_aes_xcbc_ctx_t *pCtx,
                        const SEC_UCHAR *data,
                        SEC_UINT32 nbytes);




/*
    Func Name:  ipsi_aes_xcbc_final
*/

/** 
* @defgroup ipsi_aes_xcbc_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_aes_xcbc_final (
*                           ipsi_aes_xcbc_ctx_t *ctx,
*                           SEC_UCHAR pucMac[IPSI_XCBC_DIGEST_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete xcbc MAC operation on remaining data. 
* Called at the end of MAC operation.
*
* @par Description
* ipsi_aes_xcbc_final function completes xcbc MAC operation on 
* remaining data. It is called at the end of MAC operation. A xcbc_init
* must have been called before calling this function. 
* This function calculates the MAC and frees the context. The memory
* for MAC must have already been allocated.
*
* @param[in] pCtx The context for xcbc mac [N/A]
* @param[out] pucMac The XCBC MAC [N/A]

* @retval SEC_UINT32 If MAC is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context values are 
* not correct [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments 
* are missing [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_xcbc.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_UINT32 ipsi_aes_xcbc_final(
                        ipsi_aes_xcbc_ctx_t *ctx,
                        SEC_UCHAR digest[IPSI_XCBC_DIGEST_SIZE]);

#ifdef __cplusplus
}
#endif

#endif

#endif /* _SEC_AES_XCBC_H_ */

