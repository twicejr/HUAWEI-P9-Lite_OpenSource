/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_des.h
  Version:
  Date Created: 2010-10-08
  Author: Prabhat Kumar Gopalika, Kaushik Sarkar
  Descrption: Contains interface functions for DES
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
*/

#ifndef _IPSI_CORE_DES_H__
#define _IPSI_CORE_DES_H__

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif

#define IPSI_DES_CTX_SIZE 128
#define IPSI_DES_BLOCK_SIZE 8

/**
* @defgroup ipsi_des_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct{
*   SEC_UCHAR data[IPSI_DES_CTX_SIZE];
* }ipsi_des_ctx_t;
* @endcode
*
* @datastruct data[IPSI_DES_CTX_SIZE] Define the DES Context structure,
* user does not need to care what is inside the context
*/
typedef struct{
    SEC_UCHAR data[IPSI_DES_CTX_SIZE];/*!< The context data to encrypt block */
}ipsi_des_ctx_t;

/*
    Func Name:  ipsi_des_set_key
*/

/** 
* @defgroup ipsi_des_set_key
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_des_set_key(
*                           ipsi_des_ctx_t *ctx, 
*                           const SEC_UCHAR *key, 
*                           const SEC_INT klen);
* @endcode
*
* @par Purpose
* This function is used to set the key for DES encryption/decryption
* operation.
*
* @par Description
* The ipsi_des_set_key function is used to set the key for the DES
* operation. This function must be called before calling
* any of the encryption or decrytion functions.
* 
* @param[in] key The pointer to the buffer holding the encryption and 
*            decryption key for DES operation [N/A]
* @param[in] klen The length of the key in bytes. The key should 
*            be 8 bytes long [N/A]
* @param[out] ctx The DES context [N/A] 
*
* @retval SEC_INT32 If DES context is properly set [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If arguments 
* are invalid [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 If Key length is not equal to 8
* [SEC_ERR_INVALID_KEY_LEN|N/A]
*
* @par Required Header File
* sec_des.h
*
* @par Note Caller is responsible for allocating memory for ctx.
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_des_set_key(
                            ipsi_des_ctx_t *ctx, 
                            const SEC_UCHAR *key, 
                            const SEC_INT klen);

/*
    Func Name:  ipsi_des_ncbc_encrypt
*/
/** 
* @defgroup ipsi_des_ncbc_encrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_des_ncbc_encrypt(
*                           const ipsi_des_ctx_t *ctx, 
*                           const SEC_UCHAR *in, 
*                           SEC_UCHAR *out, 
*                           const SEC_INT32 dlen, 
*                           SEC_UCHAR *iv);
* @endcode
*
* @par Purpose
* This function is used to encrypt data in NCBC mode using DES.
*
* @par Description
* The ipsi_des_ncbc_encrypt function is used to encrypt data in NCBC 
* mode using DES. 
*
* @param[in] ctx The DES context [N/A]
* @param[in] in The input plaintext [N/A]
* @param[out] out The output ciphertext [N/A]
* @param[in] dlen The length of the input data [N/A]
* @param[in] iv The IV for the NCBC operation [N/A]
* @param[out] iv The IV for the NCBC operation on next data buffer [N/A]
*
* @retval SEC_INT32 If encryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_INT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_des.h
*
* @par Note
* \n
* 1. This function updates the IV. Caller should keep a local copy of
*    the original IV before calling this function. The updated IV should 
*    be used for encryption of the next data buffer. 
* 2. Caller is responsible for allocating memory for out.
* 3. The out should point to a data buffer of length
*    ((plaintext length + 7)/8)*8
* 
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_des_ncbc_encrypt(
                            const ipsi_des_ctx_t *ctx, 
                            const SEC_UCHAR *in, 
                            SEC_UCHAR *out, 
                            const SEC_INT32 dlen, 
                            SEC_UCHAR *iv);

/*
    Func Name:  ipsi_des_ncbc_decrypt
*/
/** 
* @defgroup ipsi_des_ncbc_decrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_des_ncbc_decrypt(
*                           const ipsi_des_ctx_t *ctx, 
*                           const SEC_UCHAR *in, 
*                           SEC_UCHAR *out, 
*                           const SEC_UINT32 dlen, 
*                           SEC_UCHAR *iv);
* @endcode
*
* @par Purpose
* This function is used to decrypt data in NCBC mode using DES.
*
* @par Description
* The ipsi_des_ncbc_decrypt function is used to decrypt data in NCBC 
* mode using DES. 
*
* @param[in] ctx The AES context [N/A]
* @param[in] in The input ciphertext [N/A]
* @param[out] out The output plaintext [N/A]
* @param[in] dlen The length of the input data [N/A]
* @param[in] iv The IV for the NCBC operation [N/A]
* @param[out] iv The IV for the NCBC operation on next data buffer [N/A]
* 
* @retval SEC_INT32 If decryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_INT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
* 
* @par Required Header File
* sec_des.h
*
* @par Note
* \n
* 1. This function updates the IV. Caller should keep a local copy of
*    the original IV before calling this function. The updated IV should 
*    be used for decryption of the next data buffer. 
* 2. Caller is responsible for allocating memory for out.
* 3. Character pointer 'in' should point to a data buffer whose length
*    is a multiple of 8
* 
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_des_ncbc_decrypt(
                            const ipsi_des_ctx_t *ctx, 
                            const SEC_UCHAR *in, 
                            SEC_UCHAR *out, 
                            const SEC_INT32 dlen, 
                            SEC_UCHAR *iv);

/*
    Func Name:  ipsi_des_encrypt
*/
/** 
* @defgroup ipsi_des_encrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_des_encrypt(
*                             const ipsi_des_ctx_t *ctx,
*                             const SEC_UCHAR *in,
*                             SEC_UCHAR *out)
* @endcode
*
* @par Purpose
* This function is used to encrypt a single block of data using DES.
*
* @par Description
* The ipsi_des_encrypt function is used to encrypt a single block 
* of data using DES.
*
* @param[in] ctx The DES context [N/A]
* @param[in] in The input plaintext. It must be 8 bytes long [N/A]
* @param[out] out The output ciphertext. it must be 8 bytes long [N/A]
*
* @retval SEC_INT32 If encryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_INT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_des.h
*
* @par Note
* \n
* 1. The buffers pointed by 'in' and 'out' must be 8 bytes long \n
* 2. User must allocate the memory for 'out' \n
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_des_encrypt(
                              const ipsi_des_ctx_t *ctx,
                              const SEC_UCHAR *in,
                              SEC_UCHAR *out);

/*
    Func Name:  ipsi_des_decrypt
*/
/** 
* @defgroup ipsi_des_decrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_des_decrypt(
*                             const ipsi_des_ctx_t *ctx,
*                             const SEC_UCHAR *in,
*                             SEC_UCHAR *out)
* @endcode
*
* @par Purpose
* This function is used to decrypt a single block of data using DES.
*
* @par Description
* The ipsi_des_decrypt function is used to decrypt a single block 
* of data using DES.
*
* @param[in] ctx The DES context [N/A]
* @param[in] in The input ciphertext. It must be 8 bytes long [N/A]
* @param[out] out The output plaintext. It must be 8 bytes long [N/A]
*
* @retval SEC_INT32 If decryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_INT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_des.h
*
* @par Note
* \n
* 1. The buffers pointed by 'in' and 'out' must be 8 bytes long \n
* 2. User must allocate the memory for 'out' \n
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_des_decrypt(
                              const ipsi_des_ctx_t *ctx,
                              const SEC_UCHAR *in,
                              SEC_UCHAR *out);


/*
    Func Name:  ipsi_des_ede3_cbcm_encrypt
*/
/** 
* @defgroup ipsi_des_ede3_cbcm_encrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_des_ede3_cbcm_encrypt(ipsi_des_ctx_t *k1ctx, ipsi_des_ctx_t *k2ctx,
*    ipsi_des_ctx_t *k3ctx, const SEC_UCHAR *in, SEC_LONG length,
*    SEC_UCHAR *ivec1, SEC_UCHAR *ivec2, SEC_UCHAR *out)
* @endcode
*
* @par Purpose
* This function is used to encrypt the data in 3DES CBCM mode.
*
* @par Description
* The ipsi_des_ede3_cbcm_encrypt function is used to encrypt the data in 3DES CBCM mode.
*
* @param[in] k1ctx key schedule for key1 [N/A]
* @param[in] k2ctx key schedule for key2 [N/A]
* @param[in] k3ctx key schedule for key3 [N/A]
* @param[in] in The input plain text.[N/A]
* @param[in] length The length of the plaintext.[N/A]
* @param[in,out] ivec1 The pointer to the buffer holding the Initialization Vector used for OFB portion in CBCM mode.
*                         The IV buffer must be of 8 bytes [N/A]
* @param[in,out] ivec2 The pointer to the buffer holding the Initialization Vector used for CBC portion in CBCM mode.
*                         The IV buffer must be of 8 bytes [N/A]
* @param[out] out The output cipher text.[N/A]
*
* @retval SEC_UINT32 If encryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are NULL or invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_des.h
*
* @par Note
* \n
* 1. This function updates the both initialization vectors (ivec1 & ivec2). Caller should keep a local copy of
* the original IVs before calling this function.
* The updated IVs should be used for encryption of the next data buffer.\n
* 2. Caller is responsible for allocating memory for out.\n
* 3. The out should point to a data buffer of length ((plaintext length + 7)/8)*8.\n
* 4. If the input length is not multiple of block size, the original input length should be passed to CBCM
*    decryption operation.\n
* 
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_des_ede3_cbcm_encrypt(ipsi_des_ctx_t *k1ctx, ipsi_des_ctx_t *k2ctx,
    ipsi_des_ctx_t *k3ctx, const SEC_UCHAR *in, SEC_LONG length,
    SEC_UCHAR *ivec1, SEC_UCHAR *ivec2, SEC_UCHAR *out);


/*
    Func Name:  ipsi_des_ede3_cbcm_decrypt
*/
/** 
* @defgroup ipsi_des_ede3_cbcm_decrypt
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_des_ede3_cbcm_decrypt(ipsi_des_ctx_t *k1ctx, ipsi_des_ctx_t *k2ctx,
*    ipsi_des_ctx_t *k3ctx, const SEC_UCHAR *in, SEC_LONG length,
*    SEC_UCHAR *ivec1, SEC_UCHAR *ivec2, SEC_UCHAR *out)
* @endcode
*
* @par Purpose
* This function is used to decrypt cipher text encrypted using 3DES CBCM mode.
*
* @par Description
* The ipsi_des_ede3_cbcm_decrypt function is used to ddecrypt cipher text encrypted using 3DES CBCM mode.
*
* @param[in] k1ctx key schedule for key1 [N/A]
* @param[in] k2ctx key schedule for key2 [N/A]
* @param[in] k3ctx key schedule for key3 [N/A]
* @param[in] in The input cipher text. It must be multiple of 8 bytes [N/A]
* @param[in] length The length of the ciphertext.[N/A]
* @param[in,out] ivec1 The pointer to the buffer holding the Initialization Vector used for OFB portion in CBCM mode.
*                         The IV buffer must be of 8 bytes [N/A]
* @param[in,out] ivec2 The pointer to the buffer holding the Initialization Vector used for CBC portion in CBCM mode.
*                         The IV buffer must be of 8 bytes [N/A]
* @param[out] out The output plaintext. The output buffer must be greater than or equal to length [N/A]
*
* @retval SEC_UINT32 If decryption operation is successful [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If context is invalid [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are NULL or invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_des.h
*
* @par Note
* \n
* 1. This function updates the both initialization vectors (ivec1 & ivec2). Caller should keep a local copy of
*     the original IVs before calling this function. The updated IVs should 
*     be used for decryption of the next data buffer. \n
* 2. Caller is responsible for allocating memory for out.\n
* 3. Character pointer "in" should point to a data buffer whose length is a multiple of 8.\n
* 4. If the original plaintext length passed for CBCM enryption operation is not multiple of block size.
*    Then the same length should be passed while doing CBCM decryption operation.\n
* 
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_des_ede3_cbcm_decrypt(ipsi_des_ctx_t *k1ctx, ipsi_des_ctx_t *k2ctx,
    ipsi_des_ctx_t *k3ctx, const SEC_UCHAR *in, SEC_LONG length,
    SEC_UCHAR *ivec1, SEC_UCHAR *ivec2, SEC_UCHAR *out);


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_CORE_DES_H__ */

