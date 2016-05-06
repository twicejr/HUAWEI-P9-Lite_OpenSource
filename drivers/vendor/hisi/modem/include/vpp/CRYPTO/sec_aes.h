/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_aes.h
  Version:
  Date Created: 2010-10-08
  Author: Kaushik Sarkar
  Descrption: Contains interface functions for AES
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
 
*/

#ifndef _IPSI_CORE_AES_H__
#define _IPSI_CORE_AES_H__

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif

#define IPSI_AES_CTX_SIZE 244
#define IPSI_AES_BLOCK_SIZE 16

/**
* @defgroup ipsi_aes_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct{
*   SEC_UCHAR data[IPSI_AES_CTX_SIZE];
* }ipsi_aes_ctx_t;
* @endcode
*
* @datastruct data[IPSI_AES_CTX_SIZE] Define the AES Context structure,
* user does not need to care what is inside the context
*/
typedef struct{
    SEC_UCHAR data[IPSI_AES_CTX_SIZE];/*!< The context data to encrypt block */
}ipsi_aes_ctx_t;


/*
    Func Name:  ipsi_aes_set_enc_key
*/
/** 
* @defgroup ipsi_aes_set_enc_key
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_aes_set_enc_key(
*                           ipsi_aes_ctx_t *ctx,
*                           const SEC_UCHAR *key,
*                           const SEC_INT klen);
* @endcode
*
* @par Purpose
* This function is used to set the key for AES encryption operation.
*
* @par Description
* The ipsi_aes_set_enc_key function is used to set the key for the AES
* encryption operation. This function must be called before calling
* any of the encryption functions.
*
* @param[in] key The pointer to the buffer holding the encryption key 
			 for AES operation [N/A]
* @param[in] klen The length of the key in bytes. The klen should be either 
			 16 (for 128 bits keys) or 24 (for 192 bits keys) or 
			 32 (for 256 bits keys) [N/A]
* @param[out] ctx The AES context [N/A] 
*
* @retval SEC_INT32 If AES context is properly set [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If any of the arguments 
* are invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If the AES key length is not 
* valid [SEC_ERR_INVALID_KEY_LEN|NA]
*
* @par Required Header File
* sec_aes.h
*
* @par Note
* \n
*  Caller is responsible for allocating memory for structure 'ctx'.
* 
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT32 ipsi_aes_set_enc_key(
                            ipsi_aes_ctx_t *ctx, 
                            const SEC_UCHAR *key, 
                            const SEC_INT klen);
    
/*
    Func Name:  ipsi_aes_set_dec_key
*/
/** 
* @defgroup ipsi_aes_set_dec_key
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_aes_set_dec_key(
*                           ipsi_aes_ctx_t *ctx,
*                           const SEC_UCHAR *key,
*                           const SEC_INT klen);
* @endcode
*
* @par Purpose
* This function is used to set the key for AES decryption operation.
*
* @par Description
* The ipsi_aes_set_dec_key function is used to set the key for the AES
* decryption operation. This function must be called before calling
* any of the decryption functions.
*
* @param[in] key The pointer to the buffer holding the decryption key 
			 for AES operation [N/A]
* @param[in] klen The length of the key in bytes. The klen should be either 
			 16 (for 128 bits keys) or 24 (for 192 bits keys) or 
			 32 (for 256 bits keys) [N/A]
* @param[out] ctx The AES context [N/A] 
*
* @retval SEC_INT32 If AES context is properly set [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If any of the arguments 
* are invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If the AES key length is not 
* valid [SEC_ERR_INVALID_KEY_LEN|NA]
*
* @par Required Header File
* sec_aes.h
*
* @par Note
* \n
* Caller is responsible for allocating memory for structure 'ctx'.
* 
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT32 ipsi_aes_set_dec_key(
                            ipsi_aes_ctx_t *ctx, 
                            const SEC_UCHAR *key, 
                            const SEC_INT klen);


/*
    Func Name:  ipsi_aes_encrypt
*/

/** 
* @defgroup ipsi_aes_encrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_aes_encrypt(
*                           const ipsi_aes_ctx_t *ctx, 
*                           const SEC_UCHAR *in, 
*                           SEC_UCHAR *out);
* @endcode
*
* @par Purpose
* This function is used to encrypt a single block of data using AES.
*
* @par Description
* The ipsi_aes_encrypt function is used to encrypt a single block of data
* using AES.
*
* @param[in] ctx The AES context [N/A]
* @param[in] in The pointer to input plaintext buffer; the buffer should be
* AES_BLOCK_SIZE long [N/A]
* @param[out] out The pointer to output ciphertext buffer; the buffer should
* be AES_BLOCK_SIZE long [N/A]
* 
* @retval SEC_INT32 If encryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* 
* @par Required Header File
* sec_aes.h
*
* @par Note
* \n
* Caller is responsible for allocating memory for the character pointer 'out'.
*
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT32 ipsi_aes_encrypt(
                            const ipsi_aes_ctx_t *ctx, 
                            const SEC_UCHAR *in, 
                            SEC_UCHAR *out);

/*
    Func Name:  ipsi_aes_decrypt
*/

/** 
* @defgroup ipsi_aes_decrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_aes_decrypt(
*                           const ipsi_aes_ctx_t *ctx,
*                           const SEC_UCHAR *in,
*                           SEC_UCHAR *out);
* @endcode
*
* @par Purpose
* This function is used to decrypt a single block of data using AES.
*
* @par Description
* The ipsi_aes_decrypt function is used to decrypt a single block of data
* using AES.
*
* @param[in] ctx The AES context [N/A]
* @param[in] in The pointer to input plaintext buffer; the buffer should be
* AES_BLOCK_SIZE long [N/A]
* @param[out] out The pointer to output plaintext buffer; the buffer should be
* AES_BLOCK_SIZE long [N/A]
* @retval SEC_INT32 If decryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* 
* @par Required Header File
* sec_aes.h
*
* @par Note 
* \n
* Caller is responsible for allocating memory the character pointer 'out'.
* 
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_aes_decrypt(
                            const ipsi_aes_ctx_t *ctx, 
                            const SEC_UCHAR *in, 
                            SEC_UCHAR *out);

/*
    Func Name:  ipsi_aes_cbc_encrypt
*/
/** 
* @defgroup ipsi_aes_cbc_encrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_aes_cbc_encrypt(
*                           const ipsi_aes_ctx_t *ctx, 
*                           const SEC_UCHAR *in, 
*                           SEC_UCHAR *out, 
*                           const SEC_UINT32 dlen, 
*                           SEC_UCHAR *iv);
* @endcode
*
* @par Purpose
* This function is used to encrypt data in CBC mode using AES.
*
* @par Description
* The ipsi_aes_cbc_encrypt function is used to encrypt data in CBC mode
* using AES.
* @param[in] ctx The AES context [N/A]
* @param[in] in The input plaintext [N/A]
* @param[out] out The output ciphertext. The length of this buffer should
* be ((plaintext_buffer_length + 15)/16)*16[N/A]
* @param[in] dlen The length of the input plaintext data in bytes [N/A]
* @param[in] iv The IV for the CBC operation; should be
* IPSI_AES_BLOCK_SIZE bytes long [N/A]
* @param[out] iv The IV for encryption. It will be updated by the CBC 
* operation. [N/A]
*
* @retval SEC_INT32 If encryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
*
* @par Required Header File
* sec_aes.h
*
* @par Note
* \n
* 1. The encryption operation updates the IV. Caller is 
*    responsible for keeping a local copy of the IV before calling this 
*    function. The updated IV should be used for encryption of the next data 
*    buffer.
* 2. The pointers'in' and 'out' can point to the same buffer.
* 3. The caller is responsible for allocating memory for the character 
*    pointer 'out'.
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_aes_cbc_encrypt(
                            const ipsi_aes_ctx_t *ctx, 
                            const SEC_UCHAR *in, 
                            SEC_UCHAR *out, 
                            const SEC_UINT32 dlen, 
                            SEC_UCHAR *iv);
    
/*
    Func Name:  ipsi_aes_cbc_decrypt
*/
/** 
* @defgroup ipsi_aes_cbc_decrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_aes_cbc_decrypt(
*                           const ipsi_aes_ctx_t *ctx, 
*                           const SEC_UCHAR *in, 
*                           SEC_UCHAR *out, 
*                           const SEC_UINT32 dlen, 
*                           SEC_UCHAR *iv);
* @endcode
*
* @par Purpose
* This function is used to decrypt data in CBC mode using AES.
*
* @par Description
* The ipsi_aes_cbc_decrypt function is used to decrypt data in CBC mode 
* using AES.
* @param[in] ctx The AES context [N/A]
* @param[in] in The input ciphertext. The length of the buffer should be
* a multiple of IPSI_AES_BLOCK_SIZE [N/A]
* @param[out] out The output plaintext [N/A]
* @param[in] dlen The length of the original plaintext data in bytes [N/A]
* @param[in] iv The IV for the CBC operation; should be
* IPSI_AES_BLOCK_SIZE bytes long [N/A]
* @param[out] iv The IV for decryption. IV will be updated by the CBC 
* operation.[N/A]
*
* @retval SEC_INT32 If decryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If arguments 
* are invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If context is 
* invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
*
* @par Required Header File
* sec_aes.h
*
* @par Note 
* \n
* 1. The decryption operation updates the IV. Caller is 
*    responsible for keeping a local copy of the IV before calling this 
*    function. The updated IV should be used for decryption of the next data 
*    buffer.
* 2. in and out can point to the same buffer.
* 3. The caller is responsible for allocating memory for the character
*    pointer 'out'.
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_aes_cbc_decrypt(
                            const ipsi_aes_ctx_t *ctx, 
                            const SEC_UCHAR *in, 
                            SEC_UCHAR *out, 
                            const SEC_UINT32 dlen, 
                            SEC_UCHAR *iv);


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_CORE_AES_H__ */

