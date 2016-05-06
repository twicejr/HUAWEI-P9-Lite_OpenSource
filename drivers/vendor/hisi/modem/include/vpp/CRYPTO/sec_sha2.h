/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_sha2.h
  Version:
  Date Created: 2005-09-22
  Author: Prabhat Kumar Gopalika, Kaushik Sarkar
  Descrption: Contains interface functions for SHA2 family
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
 
*/

#ifndef _IPSI_CORE_SHA2_H__
#define _IPSI_CORE_SHA2_H__

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif



#define IPSI_SHA224_CTX_SIZE 104
#define IPSI_SHA224_DIGEST_SIZE 28

#define IPSI_SHA256_CTX_SIZE 104
#define IPSI_SHA256_DIGEST_SIZE 32


#define IPSI_SHA384_CTX_SIZE 208
#define IPSI_SHA384_DIGEST_SIZE 48

#define IPSI_SHA512_CTX_SIZE 208
#define IPSI_SHA512_DIGEST_SIZE 64



/**
* @defgroup ipsi_sha224_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*  SEC_UCHAR data[IPSI_SHA224_CTX_SIZE];
* }ipsi_sha224_ctx_t;
* @endcode
*
* @datastruct data[IPSI_SHA224_CTX_SIZE] Represents the buffer for SHA 224
* context.
*/
typedef struct
{
    SEC_UCHAR data[IPSI_SHA224_CTX_SIZE];
}ipsi_sha224_ctx_t;

/**
* @defgroup ipsi_sha256_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*  SEC_UCHAR data[IPSI_SHA256_CTX_SIZE];
* }ipsi_sha256_ctx_t;
* @endcode
*
* @datastruct data[IPSI_SHA256_CTX_SIZE] Represents the buffer for SHA 256
* context.
*/
typedef struct
{
    SEC_UCHAR data[IPSI_SHA256_CTX_SIZE];
}ipsi_sha256_ctx_t;


/**
* @defgroup ipsi_sha384_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*  SEC_UCHAR data[IPSI_SHA384_CTX_SIZE];
* }ipsi_sha384_ctx_t;
* @endcode
*
* @datastruct data[IPSI_SHA384_CTX_SIZE] Represents the buffer for SHA 384
* context.
*/
typedef struct
{
    SEC_UCHAR data[IPSI_SHA384_CTX_SIZE];
}ipsi_sha384_ctx_t;


/**
* @defgroup ipsi_sha512_ctx_t
* @ingroup sec_cryptoStructures
* @par Prototype
* @code
* typedef struct
* {
*    SEC_UCHAR data[IPSI_SHA512_CTX_SIZE];
* }ipsi_sha512_ctx_t;
* @endcode
*
* @datastruct data[IPSI_SHA512_CTX_SIZE] Represents the buffer for SHA 512
* context.
*/
typedef struct
{
    SEC_UCHAR data[IPSI_SHA512_CTX_SIZE];
}ipsi_sha512_ctx_t;




/*
    Func Name:  ipsi_sha224_init
*/

/** 
* @defgroup ipsi_sha224_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha224_init(ipsi_sha224_ctx_t *ctx);
* @endcode
*
* @par Purpose
* This is used to initialize the SHA224 context for a digest operation.
*
* @par Description
* ipsi_sha224_init function initializes the context for
* a digest operation. This function must be called before
* ipsi_sha224_update or ipsi_sha224_final operations. This function will not
* allocate memory for any of the context variables. Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx The sha224 context [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
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
CRYPTOLINKDLL SEC_UINT32 ipsi_sha224_init(ipsi_sha224_ctx_t *ctx);

/**
* @defgroup ipsi_sha224_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha224_update(ipsi_sha224_ctx_t *ctx,
*                               const SEC_UCHAR *data,
*                               SEC_UINT32 nbytes);
* @endcode
*
* @par Purpose
* This is used to perform sha224 digest operation on chunks of data.
*
* @par Description
* ipsi_sha224_update function performs digest operation on 
* chunks of data. This method of digesting is used when data is
* present in multiple buffers or not available all at once.  
* ipsi_sha224_init must have been called before calling this
* function.
*
* @param[in] ctx The sha224 context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
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
CRYPTOLINKDLL SEC_UINT32 ipsi_sha224_update(
                                        ipsi_sha224_ctx_t *ctx,
                                        const SEC_UCHAR *data,
                                        SEC_UINT32 nbytes);

/** 
* @defgroup ipsi_sha224_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha224_final(ipsi_sha224_ctx_t *ctx,
*                              SEC_UCHAR digest[IPSI_SHA224_DIGEST_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete sha224 digest operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_sha224_final function completes digest operation on remaining data, and
* is called at the end of digest operation.
* ipsi_sha224_init must have been called before calling this function. This 
* function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The sha224 context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
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

CRYPTOLINKDLL SEC_UINT32 ipsi_sha224_final(
                                ipsi_sha224_ctx_t *ctx,
                                SEC_UCHAR digest[IPSI_SHA224_DIGEST_SIZE]);



/*
    Func Name:  ipsi_sha256_init
*/

/** 
* @defgroup ipsi_sha256_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha256_init(ipsi_sha256_ctx_t *ctx);
* @endcode
*
* @par Purpose
* This is used to initialize the SHA256 context for a digest operation.
*
* @par Description
* ipsi_sha256_init function initializes the context for
* a digest operation. This function must be called before
* ipsi_sha256_update or ipsi_sha256_final operations. This function will not
* allocate memory for any of the context variables. Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx The sha256 context [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
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
CRYPTOLINKDLL SEC_UINT32 ipsi_sha256_init(ipsi_sha256_ctx_t *ctx);

/**
* @defgroup ipsi_sha256_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha256_update(ipsi_sha256_ctx_t *ctx,
*                               const SEC_UCHAR *data,
*                               SEC_UINT32 nbytes);
* @endcode
*
* @par Purpose
* This is used to perform sha256 digest operation on chunks of data.
*
* @par Description
* ipsi_sha256_update function performs digest operation on 
* chunks of data. This method of digesting is used when data is
* present in multiple buffers or not available all at once.  
* ipsi_sha256_init must have been called before calling this
* function.
*
* @param[in] ctx The sha256 context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
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
CRYPTOLINKDLL SEC_UINT32 ipsi_sha256_update(
                                        ipsi_sha256_ctx_t *ctx,
                                        const SEC_UCHAR *data,
                                        SEC_UINT32 nbytes);

/** 
* @defgroup ipsi_sha256_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha256_final(ipsi_sha256_ctx_t *ctx,
*                              SEC_UCHAR digest[IPSI_SHA256_DIGEST_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete sha256 digest operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_sha256_final function completes digest operation on remaining data, and
* is called at the end of digest operation.
* ipsi_sha256_init must have been called before calling this function. This 
* function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The sha256 context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
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

CRYPTOLINKDLL SEC_UINT32 ipsi_sha256_final(
                                ipsi_sha256_ctx_t *ctx,
                                SEC_UCHAR digest[IPSI_SHA256_DIGEST_SIZE]);


/*
    Func Name:  ipsi_sha384_init
*/

/** 
* @defgroup ipsi_sha384_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha384_init(ipsi_sha384_ctx_t *ctx);
* @endcode
*
* @par Purpose
* This is used to initialize the SHA384 context for a digest operation.
*
* @par Description
* ipsi_sha384_init function initializes the context for
* a digest operation. This function must be called before
* ipsi_sha384_update or ipsi_sha384_final operations. This function will not
* allocate memory for any of the context variables. Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx The sha384 context [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
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
CRYPTOLINKDLL SEC_UINT32 ipsi_sha384_init(ipsi_sha384_ctx_t *ctx);

/**
* @defgroup ipsi_sha384_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha384_update(ipsi_sha384_ctx_t *ctx,
*                               const SEC_UCHAR *data,
*                               SEC_UINT32 nbytes);
* @endcode
*
* @par Purpose
* This is used to perform sha384 digest operation on chunks of data.
*
* @par Description
* ipsi_sha384_update function performs digest operation on 
* chunks of data. This method of digesting is used when data is
* present in multiple buffers or not available all at once.  
* ipsi_sha384_init must have been called before calling this
* function.
*
* @param[in] ctx The sha384 context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
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
CRYPTOLINKDLL SEC_UINT32 ipsi_sha384_update(
                                        ipsi_sha384_ctx_t *ctx,
                                        const SEC_UCHAR *data,
                                        SEC_UINT32 nbytes);

/** 
* @defgroup ipsi_sha384_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha384_final(ipsi_sha384_ctx_t *ctx,
*                              SEC_UCHAR digest[IPSI_SHA384_DIGEST_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete sha384 digest operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_sha384_final function completes digest operation on remaining data, and
* is called at the end of digest operation.
* ipsi_sha384_init must have been called before calling this function. This 
* function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The sha384 context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
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

CRYPTOLINKDLL SEC_UINT32 ipsi_sha384_final(
                                    ipsi_sha384_ctx_t *ctx,
                                    SEC_UCHAR digest[IPSI_SHA384_DIGEST_SIZE]);


/*
    Func Name:  ipsi_sha512_init
*/

/** 
* @defgroup ipsi_sha512_init
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha512_init(ipsi_sha512_ctx_t *ctx);
* @endcode
*
* @par Purpose
* This is used to initialize the SHA512 context for a digest operation.
*
* @par Description
* ipsi_sha512_init function initializes the context for
* a digest operation. This function must be called before
* ipsi_sha512_update or ipsi_sha512_final operations. This function will not
* allocate memory for any of the context variable. Instead the caller is 
* expected to pass a context pointer pointing to a valid memory location
* (either locally or dynamically allocated).
*
* @param[in] ctx The sha512 context [N/A]
*
* @retval SEC_UINT32 If context is initialized [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
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
CRYPTOLINKDLL SEC_UINT32 ipsi_sha512_init(ipsi_sha512_ctx_t *ctx);

/**
* @defgroup ipsi_sha512_update
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha512_update(ipsi_sha512_ctx_t *ctx,
*                               const SEC_UCHAR *data,
*                               SEC_UINT32 nbytes);
* @endcode
*
* @par Purpose
* This is used to perform sha512 digest operation on chunks of data.
*
* @par Description
* ipsi_sha512_update function performs digest operation on 
* chunks of data. This method of digesting is used when data is
* present in multiple buffers or not available all at once.  
* ipsi_sha512_init must have been called before calling this
* function.
*
* @param[in] ctx The sha512 context [N/A]
* @param[in] data The input data [N/A]
* @param[in] nbytes The input data length [N/A]
*
* @retval SEC_UINT32 If partial digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
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
CRYPTOLINKDLL SEC_UINT32 ipsi_sha512_update(
                                        ipsi_sha512_ctx_t *ctx,
                                        const SEC_UCHAR *data,
                                        SEC_UINT32 nbytes);

/** 
* @defgroup ipsi_sha512_final
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_UINT32 ipsi_sha512_final(ipsi_sha512_ctx_t *ctx,
*                              SEC_UCHAR digest[IPSI_SHA512_DIGEST_SIZE]);
* @endcode
*
* @par Purpose
* This is used to complete sha512 digest operation on remaining data, and is
* called at the end of digest operation.
*
* @par Description
* ipsi_sha512_final function completes digest operation on remaining data, and
* is called at the end of digest operation.
* ipsi_sha512_init must have been called before calling this function. This 
* function calculates the digest. The memory for digest must
* already have been allocated.
*
* @param[in] ctx The sha512 context [N/A]
* @param[out] digest The digest [N/A]
*
* @retval SEC_UINT32 If digest is calculated [SEC_SUCCESS|N/A]
* @retval SEC_UINT32 If arguments are invalid[SEC_ERR_INVALID_ARG|N/A]
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

CRYPTOLINKDLL SEC_UINT32 ipsi_sha512_final(
                                ipsi_sha512_ctx_t *ctx,
                                SEC_UCHAR digest[IPSI_SHA512_DIGEST_SIZE]);




#ifdef __cplusplus
}
#endif

#endif /* _IPSI_CORE_SHA2_H__ */

