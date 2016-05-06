/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_dh.h
  Version:
  Date Created: 2010-10-08
  Author: Kaushik Sarkar
  Descrption: Contains functions for DH implementation
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
 
*/
#ifndef _IPSI_CORE_DH_H__
#define _IPSI_CORE_DH_H__

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#include "sec_bn.h"

#ifdef __cplusplus
extern  "C" {
#endif

#define IPSI_DH_GENERATOR_2     2
#define IPSI_DH_GENERATOR_3     3 
#define IPSI_DH_GENERATOR_5     5

/* ipsi_dh_check error codes */
#define IPSI_DH_CHECK_P_NOT_PRIME           0x01
#define IPSI_DH_CHECK_P_NOT_SAFE_PRIME      0x02
#define IPSI_DH_UNABLE_TO_CHECK_GENERATOR   0x04
#define IPSI_DH_NOT_SUITABLE_GENERATOR      0x08


/**
* @defgroup IPSI_DH
* @ingroup sec_cryptoStructures
* @par Description
* This structure holds the DH parameters. Memory for this parameters must
* be allocated dynamically.
* @par Prototype
* @code
* typedef struct dh_st
{
    ipsi_bn_t *p;           
    ipsi_bn_t *g;           
    ipsi_bn_t *pub_key; 
    ipsi_bn_t *priv_key;    
    ipsi_bn_t *q;
    long length;
} IPSI_DH;
* @endcode
*
* @datastruct p The prime used to generate the DH Key Exchange Group
* @datastruct g The generator chosen for the DH Key Exchange
* @datastruct pub_key The public key for key exchange, 
* pub_key = (g ^ priv_key ) mod p
* @datastruct priv_key The randomly chosen private key
* @datastruct q The Sophie Germain prime. 
* If p is a strong prime then p = 2q + 1
* @datastruct length The length of the prime p in number of bits
*/

typedef struct dh_st
{
    ipsi_bn_t *p;           /* the prime */
    ipsi_bn_t *g;           /* the generator */
    ipsi_bn_t *pub_key;     /* g^x */
    ipsi_bn_t *priv_key;    /* x */
    ipsi_bn_t *q;
    long length;            /* optional */
} IPSI_DH;

/** 
* @defgroup ipsi_dh_new
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_DH *ipsi_dh_new(void)
* @endcode
*
* @par Purpose
* This is used to allocated and initializes a DH structure.
*
* @par Description
* This is used to allocated and initializes a DH structure.
*
* @retval IPSI_DH * Pointer to a newly created DH structure [N/A|N/A]
* @retval SEC_NULL If memory allocation fails [SEC_NULL|N/A]
*
* @par Required Header File
* sec_dh.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL IPSI_DH *ipsi_dh_new(void);

/** 
* @defgroup ipsi_dh_free
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_dh_free(IPSI_DH *dh);
* @endcode
*
* @par Purpose
* This is used to free the IPSI_DH structure.
*
* @par Description
* It is used to free a IPSI_DH structure created by ipsi_dh_new().
* It frees the member fields also if they are not NULL.
*
* @param[in] dh  Pointer to big num structure which needs to be freed [N/A]
*
* @par Required Header File
* sec_dh.h
*
* @par Note This function will free the member pointers first. Application code
* must not set this pointers to point to locally allocated objects, since in
* that case ipsi_dh_free will fail.
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID ipsi_dh_free(IPSI_DH *dh);

/** 
* @defgroup ipsi_dh_generate_key
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_dh_generate_key(IPSI_DH *dh);
* @endcode
*
* @par Purpose
* This is used to generate public/private key pair.
*
* @par Description
* This function genearates a public/private key pair for DH key exchange.
* The algorithm parameters are taken from dh. If dh does not already contains
* a private key then a random private key is genearated.
*
* @param[in] dh The DH structure.[N/A]
*
* @retval SEC_INT32 on success [SEC_SUCCESS|N/A]
* @retval SEC_INT32 if input parameter is invalid 
* [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 internal system failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_dh.h
*
* @par Note
* \n
* The parameters p (i.e the prime) and g (i.e. the generator) must be set
* with valid values into the IPSI_DH structure pointed by dh before calling
* this function
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT32 ipsi_dh_generate_key(IPSI_DH *dh);

/** 
* @defgroup ipsi_dh_compute_key
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
SEC_INT32 ipsi_dh_compute_key(
                            IPSI_DH *dh,
                            const ipsi_bn_t *pub_key, 
                            SEC_UCHAR *key, 
                            SEC_INT *klen);
* @endcode
*
* @par Purpose
* This is used to compute a shared key.
*
* @par Description
* This function computes a shared key from the remote pub_key and the local
* priv_key and stores in key. Memory for key should be allocated before
* calling this function. 
*
* @param[in] dh The IPSI_DH structure that stores the local DH context [N/A]
* @param[in] pub_key The public key of the remote side [N/A]
* @param[out] key The buffer for storing the shared key [N/A]
* @param[out] klen Pointer to the computed klen [N/A]
*
* @retval SEC_INT32 on success [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If input parameters are invalid [SEC_ERR_INVALID_ARG|N/A] 
* @retval SEC_INT32 If the private key is not present in the IPSI_DH
* structure [SEC_ERR_INVALID_PRIVATE_KEY|N/A]
* @retval SEC_INT32 For internal system failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_dh.h
*
* @par Note 
* \n
* 1. The value at key and klen should be used only if the return 
* value is SEC_SUCCESS
* 2. The prime and generator of the IPSI_DH structure must be set before 
* calling this function
* \n
* N/A
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT32 ipsi_dh_compute_key(
                                    IPSI_DH *dh,
                                    const ipsi_bn_t *pub_key, 
                                    SEC_UCHAR *key, 
                                    SEC_INT *klen);

/** 
* @defgroup ipsi_dh_size
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_dh_size(const IPSI_DH *dh, SEC_INT *pLen);
* @endcode
*
* @par Purpose
* This is used to get the number of bytes of the prime used in the DH group.
*
* @par Description
* This function returns the size of the prime in the DH group in bytes.
*
* @param[in] dh The IPSI_DH structure.[N/A]
* @param[out] pLen Pointer to the length of the prime [N/A]
*
* @retval SEC_INT32 on success [SEC_SUCCESS|N/A]
* @retval SEC_INT32 if input arguments are invalid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_dh.h
*
* @par Note 
* \n
* 1. The function should be called on a dh structure whose 'p' field, i.e.
* the prime is set.
* 2. The length stored in pLen should only be checked if the return
* value is SEC_SUCCESS
* 
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT32 ipsi_dh_size(const IPSI_DH *dh, SEC_INT *pLen);

/** 
* @defgroup ipsi_dh_check
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_dh_check(const IPSI_DH *dh, SEC_INT *codes);
* @endcode
*
* @par Purpose
* This function is used to check the suitability of the prime and the generator
* used in the DH group.
*
* @par Description
* This function is used to check the suitability of the prime and the generator
* used in the DH group.
* This function checks that p is a safe prime. i.e.
* p is a prime of the form p = 2q + 1, where q is also a prime
* and if g is 2, 3 or 5, check that is is a suitable generator
*                 where
*                 for 2, p mod 24 == 11
*                 for 3, p mod 12 == 5
*                 for 5, p mod 10 == 3 or 7
*                 should hold.
*
* @param[in] dh The IPSI_DH structure. [N/A]
* @param[out] codes; return code.
* \n if IPSI_DH_CHECK_P_NOT_PRIME first bit of *codes will be set
* \n if IPSI_DH_CHECK_P_NOT_SAFE_PRIME second bit of *codes will be set
* \n if IPSI_DH_UNABLE_TO_CHECK_GENERATOR third bit of *codes will be set
* \n if IPSI_DH_NOT_SUITABLE_GENERATOR fourth bit of *codes will be set [N/A]
*
* @retval SEC_INT on success [SEC_SUCCESS|N/A]
* @retval SEC_INT32 if input parameter is invalid 
* [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_INT32 for internal system failure [SEC_ERR|N/A]
*
* @par Required Header File
* sec_dh.h
*
* @par Note
* \n
* This function should only be called on a dh structure variable whose
* prime and generator members are set.
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT32 ipsi_dh_check(const IPSI_DH *dh, SEC_INT *codes);

#ifdef __cplusplus
}
#endif

#endif /* _IPSI_CORE_DH_H__ */



