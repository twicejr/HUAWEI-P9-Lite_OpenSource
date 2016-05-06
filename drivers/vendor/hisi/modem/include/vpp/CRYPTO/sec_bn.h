/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_bn.h
  Version:
  Date Created: 2010-10-08
  Author: Prabhat Kumar Gopalika, Kaushik Sarkar
  Descrption: Contains interface functions for Big Num
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------
 
*/

#ifndef _IPSI_CORE_BN_H__
#define _IPSI_CORE_BN_H__

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif

/**
* @defgroup ipsi_bn_t
* @ingroup sec_cryptoStructures
* @par Description
* This structure holds the big number parameters.
* @par Prototype
* @code
* typedef struct ipsi_bignum_st ipsi_bn_t;
* @endcode
*
*/
typedef struct ipsi_big_num_type ipsi_bn_t;

/** 
* @defgroup ipsi_bn_new
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* ipsi_bn_t *ipsi_bn_new(void);
* @endcode
*
* @par Purpose
* This is used to allocate and initialize an ipsi_bn_t structure.
*
* @par Description
* This is used to allocate and initialize an ipsi_bn_t structure.
*
* @retval ipsi_bn_t* Pointer to a newly created ipsi_bn_t structure. [N/A|N/A]
* @retval ipsi_bn_t* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Required Header File
* sec_bn.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL ipsi_bn_t *ipsi_bn_new(void);

/** 
* @defgroup ipsi_bn_free
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_bn_free(ipsi_bn_t *a);
* @endcode
*
* @par Purpose
* This is used to free the ipsi_bn_t structure pointed by 'a'.
*
* @par Description
* This is used to free the ipsi_bn_t structure pointed by 'a'.
* 
* @param[in] a  Pointer to ipsi_bn_t structure which needs to be freed [N/A]
*
* @par Required Header File
* sec_bn.h
* 
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID ipsi_bn_free(ipsi_bn_t *a);

/** 
* @defgroup ipsi_bn_bin2bn
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* ipsi_bn_t *ipsi_bn_bin2bn(const SEC_UCHAR *s, SEC_INT len, ipsi_bn_t *ret)
* @endcode
*
* @par Purpose
* Converts the positive integer in big-endian form of length 'len' from 
* buffer 's' into an ipsi_bn_t structure and places the reference in 'ret'.
*
* @par Description
* Converts the positive integer in big-endian form of length 'len' from 
* buffer 's' into an ipsi_bn_t structure and places the reference in 'ret'.
* If ret is NULL , a new ipsi_bn_t is created. 
*
* @param[in] s  Character pointer pointing to the Big Number [N/A]
* @param[in] len  The length in the character pointers [N/A]
* @param[out] ret The returned BigNumber [N/A]
*
* @retval ipsi_bn_t* Ponter to the converted ipsi_bn_t is returned [N/A|N/A]
* @retval ipsi_bn_t* If failure occurs [SEC_NULL|N/A]
*
* @par Required Header File
* sec_bn.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL ipsi_bn_t *ipsi_bn_bin2bn(
                                        const SEC_UCHAR *s, 
                                        SEC_UINT len, 
                                        ipsi_bn_t *ret);

/** 
* @defgroup ipsi_bn_bn2bin
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_bn_bn2bin(const ipsi_bn_t *a, SEC_UCHAR *to);
* @endcode
*
* @par Purpose
* Converts the big num 'a' into a big-endian binary number represented by 
* a byte string. The byte string is placed at a location pointed by 'to'.
*
* @par Description
* This function converts the big num 'a' into a big-endian binary number 
* represented by a byte string. The byte string is placed at a location 
* pointed by 'to'.
*
* @param[in] a  The big num structure to be converted [N/A]
* @param[out] to Converted big num in big-endian form byte string [N/A]
*
* @retval SEC_INT32 Returns the length of the byte string (in bytes) [NA|NA]
* @retval SEC_INT32 if arguments are not valid [SEC_ERROR|N/A]
*
* @par Required Header File
* sec_bn.h
*
* @par Note
* \n
* N/A
*       
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT32 ipsi_bn_bn2bin(const ipsi_bn_t *a, SEC_UCHAR *to);

/** 
* @defgroup ipsi_bn_num_bits
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT32 ipsi_bn_num_bits(const ipsi_bn_t *a, 
                             SEC_INT *piNumBits);
* @endcode
*
* @par Purpose
* Returns the number of significant bits in the bignum 'a'
*
* @par Description
* This function returns the number of significant bits in the bignum 'a'.
* The number of significant bits is updated in the integer pointed by
* 'piNumBits'.
*
* @param[in] a  The big num structure whose number of significant bits
*               will be returned [N/A]
* @param[out] piNumBits The pointer to the integer which will hold the
*               number of significant bits of 'a' on success [N/A]
*
* @retval SEC_INT32 on success [SEC_SUCCESS|N/A]
* @retval SEC_INT32 if arguments are not valid [SEC_ERR_INVALID_ARG|N/A]
*
* @par Required Header File
* sec_bn.h
*
* @par Note
* \n
* The pointer 'a' passed to the function must have been obtained through
* ipsi_bn_new().
*       
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT32 ipsi_bn_num_bits(const ipsi_bn_t *a, 
                                         SEC_INT *piNumBits);

#ifdef __cplusplus
}
#endif

#endif /* _IPSI_CORE_BN_H__ */

