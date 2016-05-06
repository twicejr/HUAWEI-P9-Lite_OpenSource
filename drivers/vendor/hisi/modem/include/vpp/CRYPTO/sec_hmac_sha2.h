/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_hmac_sha2.h
  Version:
  Date Created: 2005-09-22
  Author: Prabhat Kumar Gopalika, Kaushik Sarkar
  Descrption: Contains HMAC interface functions
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
 
*/

#ifndef _IPSI_CORE_HMAC_SHA2_H
#define _IPSI_CORE_HMAC_SHA2_H

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif

#define IPSI_HMAC_SHA224_CTX_SIZE 208

#define IPSI_HMAC_SHA256_CTX_SIZE 208

#define IPSI_HMAC_SHA384_CTX_SIZE 416

#define IPSI_HMAC_SHA512_CTX_SIZE 416

#define IPSI_HMAC_SHA224_SIZE 28

#define IPSI_HMAC_SHA256_SIZE 32

#define IPSI_HMAC_SHA384_SIZE 48

#define IPSI_HMAC_SHA512_SIZE 64

/**
* @defgroup ipsi_hmac_sha224_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SHA224_CTX_SIZE];
}ipsi_hmac_sha224_ctx;
* @endcode
*
* @datastruct data[IPSI_HMAC_SHA224_CTX_SIZE] Represents the buffer 
* for HMAC SHA224
* context.
*/

typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SHA224_CTX_SIZE];
}ipsi_hmac_sha224_ctx_t; 

/**
* @defgroup ipsi_hmac_sha256_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SHA256_CTX_SIZE];
}ipsi_hmac_sha256_ctx;
* @endcode
*
* @datastruct data[IPSI_HMAC_SHA256_CTX_SIZE] Represents the buffer for 
* HMAC SHA256
* context.
*/

typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SHA256_CTX_SIZE];
}ipsi_hmac_sha256_ctx_t; 

/**
* @defgroup ipsi_hmac_sha384_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SHA384_CTX_SIZE];
}ipsi_hmac_sha384_ctx;
* @endcode
*
* @datastruct data[IPSI_HMAC_SHA384_CTX_SIZE] Represents the buffer for 
* HMAC SHA384
* context.
*/

typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SHA384_CTX_SIZE];
}ipsi_hmac_sha384_ctx_t; 

/**
* @defgroup ipsi_hmac_sha512_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SHA512_CTX_SIZE];
}ipsi_hmac_sha512_ctx;
* @endcode
*
* @datastruct data[IPSI_HMAC_SHA512_CTX_SIZE] Represents the buffer for 
* HMAC SHA512
* context.
*/

typedef struct
{
    SEC_UCHAR data[IPSI_HMAC_SHA512_CTX_SIZE];
}ipsi_hmac_sha512_ctx_t; 

/*
    Func Name:  ipsi_hmac_sha224_init
*/

/** 
* @defgroup ipsi_hmac_sha224_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha224_init(ipsi_hmac_sha224_ctx_t * ctx, 
                cont SEC_UCHAR * pucKey, SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the ipsi_hmac_sha224_ctx context for a 
* digest operation.
*
* @par Description
* ipsi_hmac_sha224_init function initializes the context for
* a digest operation. This function must be called before any
* ipsi_hmac_sha224_update or ipsi_hmac_sha224_final operations. 
* This function will not
* allocate memory for any of the context variables. Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx ipsi_hmac_sha224 context [N/A]
* @param[in] pucKey Key for HMAC
* @param[in] ulKlen Key length [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha224 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If key is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha224_init(
                                        ipsi_hmac_sha224_ctx_t *ctx,
                                        const SEC_UCHAR * pucKey, 
                                        SEC_UINT32 ulKlen);


/**
* @defgroup ipsi_hmac_sha224_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha224_update(
*                                            ipsi_hmac_sha224_ctx_t *ctx, 
*                                            SEC_UCHAR *pucData, 
*                                            SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform sha224 digest operation on chunks of data.
*
* @par Description
* ipsi_hmac_sha224_update function performs hmac operation on 
* chunks of data. This method of MACing is used when data is present
* in multiple buffers or not available all at once. 
* A ipsi_hmac_sha224_init must have been called before calling this function.
*
* @param[in] ctx The sha224 context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha224 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If data is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto_ctx.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha224_update(
                                            ipsi_hmac_sha224_ctx_t *ctx, 
                                            SEC_UCHAR *pucData, 
                                            SEC_UINT32 ulDataLen);


/** 
* @defgroup ipsi_hmac_sha224_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha224_final(ipsi_hmac_sha256_ctx_t *ctx,
*                            SEC_UCHAR pucDigest[IPSI_HMAC_SHA224_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete hmac-sha224 mac operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_hmac_sha224_final function completes digest operation on remaining 
*data, and is called at the end of digest operation.
* ipsi_hmac_sha224_init must have been called before calling this function. 
* This function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The ipsi_hmac_sha224_ctx_t context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha224 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha224_final(
                                ipsi_hmac_sha224_ctx_t *ctx,
                                SEC_UCHAR pucDigest[IPSI_HMAC_SHA224_SIZE]);


/*
    Func Name:  ipsi_hmac_sha256_init
*/

/** 
* @defgroup ipsi_hmac_sha256_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha256_init(ipsi_hmac_sha256_ctx_t * ctx, 
*                              cont SEC_UCHAR * pucKey, SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the ipsi_hmac_sha256_ctx_t context for a mac 
* operation.
*
* @par Description
* ipsi_hmac_sha256_init function initializes the context for
* a digest operation. This function must be called before any
* ipsi_hmac_sha256_update or ipsi_hmac_sha256_final operations.
* This function will not allocate memory for any of the context variables.
* Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx ipsi_hmac_sha256_t context [N/A]
* @param[in] pucKey Key for HMAC
* @param[in] ulKlen Key length [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha256 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If key is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha256_init(
                                 ipsi_hmac_sha256_ctx_t *ctx,
                                 const SEC_UCHAR * pucKey, 
                                 SEC_UINT32 ulKlen);

/**
* @defgroup ipsi_hmac_sha256_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha256_update(ipsi_hmac_sha256_ctx_t *ctx,
*                                    SEC_UCHAR *pucData, 
*                                    SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform hmac sha256 operation on chunks of data.
*
* @par Description
* ipsi_hmac_sha256_update function performs hmac operation on 
* chunks of data. This method of MACing is used when data is present
* in multiple buffers or not available all at once. 
* A ipsi_hmac_sha256_init must have been called before calling this function.
*
* @param[in] ctx The ipsi_hmac_sha256_t context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha256 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If data is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto_ctx.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha256_update(
                                        ipsi_hmac_sha256_ctx_t *ctx,
                                        SEC_UCHAR *pucData, 
                                        SEC_UINT32 ulDataLen);


/** 
* @defgroup ipsi_hmac_sha256_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha256_final(ipsi_hmac_sha256_ctx_t *ctx,
*                            SEC_UCHAR pucDigest[IPSI_HMAC_SHA256_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete hmac-sha256 mac operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_hmac_sha256_final function completes digest operation on remaining
* data, and is called at the end of digest operation.
* ipsi_hmac_sha256_init must have been called before calling this function. 
* This function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The ipsi_hmac_sha256_ctx_t context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha256 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha256_final(
                            ipsi_hmac_sha256_ctx_t *ctx,
                            SEC_UCHAR pucDigest[IPSI_HMAC_SHA256_SIZE]);


/*
    Func Name:  ipsi_hmac_sha384_init
*/

/** 
* @defgroup ipsi_hmac_sha384_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha384_init(ipsi_hmac_sha384_ctx_t * ctx, 
*                              cont SEC_UCHAR * pucKey, SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the ipsi_hmac_sha384_ctx_t context for a mac 
* operation.
*
* @par Description
* ipsi_hmac_sha384_init function initializes the context for
* a digest operation. This function must be called before any
* ipsi_hmac_sha384_update or ipsi_hmac_sha384_final operations.
* This function will not allocate memory for any of the context variable.
* Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx ipsi_hmac_sha384_t context [N/A]
* @param[in] pucKey Key for HMAC
* @param[in] ulKlen Key length [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha384 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If key is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha384_init(
                                            ipsi_hmac_sha384_ctx_t *ctx,
                                            const SEC_UCHAR * pucKey,
                                            SEC_UINT32 ulKlen);


/**
* @defgroup ipsi_hmac_sha384_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha384_update(ipsi_hmac_sha384_ctx_t *ctx,
*                                    SEC_UCHAR *pucData, 
*                                    SEC_UINT32 ulDataLen);
* @endcode
*
* @par Purpose
* This is used to perform mac-sha384 operation on chunks of data.
*
* @par Description
* ipsi_hmac_sha384_update function performs hmac operation on 
* chunks of data. This method of MACing is used when data is present
* in multiple buffers or not available all at once. 
* A ipsi_hmac_sha384_init must have been called before calling this function.
*
* @param[in] ctx The mac-sha384 context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha384 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If data is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_crypto_ctx.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha384_update(
                                        ipsi_hmac_sha384_ctx_t *ctx,
                                        SEC_UCHAR *pucData, 
                                        SEC_UINT32 ulDataLen);

/** 
* @defgroup ipsi_hmac_sha384_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha384_final(ipsi_hmac_sha384_ctx_t *ctx,
*                            SEC_UCHAR pucDigest[IPSI_HMAC_SHA384_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete hmac-sha384 mac operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_hmac_sha384_final function completes digest operation on remaining
* data, and is called at the end of digest operation.
* ipsi_hmac_sha384_init must have been called before calling this function. 
* This function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The ipsi_hmac_sha384_ctx_t context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha384 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha384_final(
                                ipsi_hmac_sha384_ctx_t *ctx,
                                SEC_UCHAR pucDigest[IPSI_HMAC_SHA384_SIZE]);


/*
    Func Name:  ipsi_hmac_sha512_init
*/

/** 
* @defgroup ipsi_hmac_sha512_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha512_init(ipsi_hmac_sha512_ctx_t * ctx, 
*                              cont SEC_UCHAR * pucKey, SEC_UINT32 ulKlen);
* @endcode
*
* @par Purpose
* This is used to initialize the ipsi_hmac_sha512_ctx_t context for a 
* mac operation.
*
* @par Description
* ipsi_hmac_sha512_init function initializes the context for
* a digest operation. This function must be called before any
* ipsi_hmac_sha512_update or ipsi_hmac_sha512_final operations.
* This function will not allocate memory for any of the context variable.
* Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx ipsi_hmac_sha512_t context [N/A]
* @param[in] pucKey Key for HMAC
* @param[in] ulKlen Key length [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha512 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If key is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha512_init(
                                        ipsi_hmac_sha512_ctx_t *ctx,
                                        const SEC_UCHAR * pucKey, 
                                        SEC_UINT32 ulKlen);


/**
* @defgroup ipsi_hmac_sha512_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha512_update(ipsi_hmac_sha512_ctx_t *ctx,
*                               const SEC_UCHAR *data,
*                               SEC_UINT32 nbytes);
* @endcode
*
* @par Purpose
* This is used to perform sha512 digest operation on chunks of data.
*
* @par Description
* ipsi_hmac_sha512_update function performs hmac operation on 
* chunks of data. This method of MACing is used when data is present
* in multiple buffers or not available all at once. 
* A ipsi_hmac_sha512_init must have been called before calling this function.
*
* @param[in] ctx The hmac-sha512 context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha512 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If data is NULL and the length is not zero [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha512_update(
                                        ipsi_hmac_sha512_ctx_t *ctx, 
                                        SEC_UCHAR *pucData, 
                                        SEC_UINT32 ulDataLen);

/** 
* @defgroup ipsi_hmac_sha512_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_hmac_sha512_final(ipsi_hmac_sha512_ctx_t *ctx,
*                            SEC_UCHAR pucDigest[IPSI_HMAC_SHA512_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete hmac-sha512 mac operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_hmac_sha512_final function completes digest operation on remaining 
* data, and
* is called at the end of digest operation.
* ipsi_hmac_sha512_init must have been called before calling this function. 
* This function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The ipsi_hmac_sha512_ctx_t context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If hmac sha512 context is NULL [SEC_CRYPT_ERR_INVALID_CTX|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_hmac_sha2.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 ipsi_hmac_sha512_final(
                                ipsi_hmac_sha512_ctx_t *ctx,
                                SEC_UCHAR pucDigest[IPSI_HMAC_SHA512_SIZE]);


#ifdef __cplusplus
}


#endif

#endif /* IPSI_CORE_hmac_SHA2_H */

