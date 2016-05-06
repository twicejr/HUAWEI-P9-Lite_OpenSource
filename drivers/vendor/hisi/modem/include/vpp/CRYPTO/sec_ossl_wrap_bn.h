/*

                Copyright 2003, Huawei Technologies Co. Ltd.
                            ALL RIGHTS RESERVED

  Project Code: iPSI
  Module Name: sec_ossl_wrap_bn.h
  Version:
  Date Created: 2013-06-18
  Author: Anand 71457
  Descrption: Contains wrapper interface functions for OpenSSL Big Num functions
----------------------------------------------------------------------
  Modification History
  DATE        NAME             DESCRIPTION
  --------------------------------------------------------------------

*/

#ifndef _IPSI_OSSL_WRAP_BN_H__
#define _IPSI_OSSL_WRAP_BN_H__

#include "ipsi_crypto_buildconf.h"

#include "sec_sys.h"
#include "ipsi_types.h"

#ifdef __cplusplus
extern  "C" {
#endif

/* Abstraction for BN ULONG data type
   To maintain compatability with VPP crypto existing BIGNUM,
   we can support only 32-bit mode of BN. */
#define IPSI_OSSL_WRAP_BN_ULONG SEC_UINT32


#define IPSI_OSSL_WRAP_BN_FLG_CONSTTIME    0x04


/**
* @defgroup IPSI_OSSL_WRAP_BIGNUM
* @ingroup sec_cryptoStructures
* @par Description
* This structure holds the big number (BIGNUM) parameters.
* @par Prototype
* @code
* typedef struct ipsi_bignum_st IPSI_OSSL_WRAP_BIGNUM;
* @endcode
*
*/
typedef struct ipsi_bignum_st IPSI_OSSL_WRAP_BIGNUM;

/**
* @defgroup IPSI_OSSL_WRAP_BN_CTX
* @ingroup sec_cryptoStructures
* @par Description
* A IPSI_OSSL_WRAP_BN_CTX is a structure that holds IPSI_OSSL_WRAP_BIGNUM temporary variables
* used by library functions. Since dynamic memory allocation to create
* IPSI_OSSL_WRAP_BIGNUM is rather expensive when used in conjunction with repeated
* subroutine calls, the IPSI_OSSL_WRAP_BN_CTX structure is used.
* @par Prototype
* @code
* typedef struct ipsi_bignum_ctx IPSI_OSSL_WRAP_BN_CTX;
* @endcode
*
*/
typedef struct ipsi_bignum_ctx IPSI_OSSL_WRAP_BN_CTX;

/**
* @defgroup IPSI_OSSL_WRAP_BN_MONT_CTX
* @ingroup sec_cryptoStructures
* @par Description
* This structure is used for montgomery multiplication
* @par Prototype
* @code
* typedef struct ipsi_xbn_mont_ctx_st IPSI_OSSL_WRAP_BN_MONT_CTX;
* @endcode
*
*/
typedef struct ipsi_xbn_mont_ctx_st IPSI_OSSL_WRAP_BN_MONT_CTX;

/* Macro to set the value of BIGNUM to 0 */
#define IPSI_OSSL_WRAP_BN_zero(a)  (ipsi_ossl_wrap_BN_set_word((a),0))

/**
* @defgroup ipsi_ossl_wrap_BN_new
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_new(SEC_VOID);
* @endcode
*
* @par Purpose
* Allocates and initializes a IPSI_OSSL_WRAP_BIGNUM structure.
*
* @par Description
* Allocates and initializes a IPSI_OSSL_WRAP_BIGNUM structure.
*
* @param[in] SEC_VOID  This function does not accept any paramters [N/A]
*
* @retval IPSI_OSSL_WRAP_BIGNUM* Returns a pointer to the newly created IPSI_OSSL_WRAP_BIGNUM structure [N/A|N/A]
* @retval IPSI_OSSL_WRAP_BIGNUM* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_new(SEC_VOID);



/**
* @defgroup ipsi_ossl_wrap_BN_free
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_ossl_wrap_BN_free(IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* Frees the components of the IPSI_OSSL_WRAP_BIGNUM, and if it was created by ipsi_ossl_wrap_BN_new(),
* also the structure itself.
*
* @par Description
* Frees the components of the IPSI_OSSL_WRAP_BIGNUM, and if it was created by ipsi_ossl_wrap_BN_new(),
* also the structure itself.
*
* @param[in] a  Pointer to IPSI_OSSL_WRAP_BIGNUM structure which needs to be freed [N/A]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID ipsi_ossl_wrap_BN_free(IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_clear_free
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_ossl_wrap_BN_clear_free(IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* Frees the components of the IPSI_OSSL_WRAP_BIGNUM, and if it was created by ipsi_ossl_wrap_BN_new(),
* also the structure itself. Additionally it is used to destroy sensitive data such as keys when they
* are no longer needed.
*
* @par Description
* Frees the components of the IPSI_OSSL_WRAP_BIGNUM, and if it was created by ipsi_ossl_wrap_BN_new(),
* also the structure itself. Additionally it is used to destroy sensitive data such as keys when they
* are no longer needed.
*
* @param[in] a  Pointer to IPSI_OSSL_WRAP_BIGNUM structure which needs to be cleared and freed [N/A]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID ipsi_ossl_wrap_BN_clear_free(IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_CTX_new
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BN_CTX *ipsi_ossl_wrap_BN_CTX_new(SEC_VOID);
* @endcode
*
* @par Purpose
* Allocates and initializes a IPSI_OSSL_WRAP_BN_CTX structure.
*
* @par Description
* Allocates and initializes a IPSI_OSSL_WRAP_BN_CTX structure.
*
* @param[in] SEC_VOID  This function does not accept any paramters [N/A]
*
* @retval IPSI_OSSL_WRAP_BN_CTX* Returns a pointer to the newly created IPSI_OSSL_WRAP_BN_CTX structure [N/A|N/A]
* @retval IPSI_OSSL_WRAP_BN_CTX* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL IPSI_OSSL_WRAP_BN_CTX *ipsi_ossl_wrap_BN_CTX_new(SEC_VOID);




/**
* @defgroup ipsi_ossl_wrap_BN_CTX_free
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_ossl_wrap_BN_CTX_free(IPSI_OSSL_WRAP_BN_CTX *c);
* @endcode
*
* @par Purpose
* This function frees the components of the IPSI_OSSL_WRAP_BN_CTX, and if it was
* created by ipsi_ossl_wrap_BN_CTX_new(), also the structure itself. If
* ipsi_ossl_wrap_BN_CTX_start() has been used on the IPSI_OSSL_WRAP_BN_CTX,
* ipsi_ossl_wrap_BN_CTX_end() must be called before the IPSI_OSSL_WRAP_BN_CTX may
* be freed by ipsi_ossl_wrap_BN_CTX_free().
*
* @par Description
* This function frees the components of the IPSI_OSSL_WRAP_BN_CTX, and if it was
* created by ipsi_ossl_wrap_BN_CTX_new(), also the structure itself. If
* ipsi_ossl_wrap_BN_CTX_start() has been used on the IPSI_OSSL_WRAP_BN_CTX,
* ipsi_ossl_wrap_BN_CTX_end() must be called before the IPSI_OSSL_WRAP_BN_CTX may
* be freed by ipsi_ossl_wrap_BN_CTX_free().
*
* @param[in] c  Pointer to IPSI_OSSL_WRAP_BN_CTX structure which needs to be freed [N/A]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID ipsi_ossl_wrap_BN_CTX_free(IPSI_OSSL_WRAP_BN_CTX *c);



/**
* @defgroup ipsi_ossl_wrap_BN_CTX_start
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_ossl_wrap_BN_CTX_start(IPSI_OSSL_WRAP_BN_CTX *ctx);
* @endcode
*
* @par Purpose
* These functions are used to obtain temporary IPSI_OSSL_WRAP_BIGNUM variables
*
* @par Description
* These functions are used to obtain temporary IPSI_OSSL_WRAP_BIGNUM variables from a
* IPSI_OSSL_WRAP_BN_CTX (which can been created by using ipsi_ossl_wrap_BN_CTX_new())
* in order to save the overhead of repeatedly creating and freeing IPSI_OSSL_WRAP_BIGNUMs
* in functions that are called from inside a loop.
* A function must call ipsi_ossl_wrap_BN_CTX_start() first. Then, ipsi_ossl_wrap_BN_CTX_get()
* may be called repeatedly to obtain temporary IPSI_BIGNUMs. All ipsi_ossl_wrap_BN_CTX_get()
* calls must be made before calling any other functions that use the ctx as an argument. Finally,
* ipsi_ossl_wrap_BN_CTX_end() must be called before returning from the function. When
* ipsi_ossl_wrap_BN_CTX_end() is called, the IPSI_OSSL_WRAP_BIGNUM pointers obtained from
* ipsi_ossl_wrap_BN_CTX_get() become invalid
*
* @param[in] ctx  Pointer to IPSI_OSSL_WRAP_BN_CTX structure which needs to be started [N/A]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID ipsi_ossl_wrap_BN_CTX_start(IPSI_OSSL_WRAP_BN_CTX *ctx);



/**
* @defgroup ipsi_ossl_wrap_BN_CTX_get
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_CTX_get(IPSI_OSSL_WRAP_BN_CTX *ctx);
* @endcode
*
* @par Purpose
* These functions are used to obtain temporary IPSI_OSSL_WRAP_BIGNUM variables
*
* @par Description
* A function must call ipsi_ossl_wrap_BN_CTX_start() first. Then, ipsi_ossl_wrap_BN_CTX_get()
* may be called repeatedly to obtain temporary IPSI_BIGNUMs. All ipsi_ossl_wrap_BN_CTX_get()
* calls must be made before calling any other functions that use the ctx as an argument.
*
* @param[in] ctx  The IPSI_OSSL_WRAP_BN_CTX context from which the temporary variables might be obtained [N/A]
*
* @retval IPSI_OSSL_WRAP_BIGNUM* Returns a pointer to the BIGNUM.[NA|NA]
* @retval IPSI_OSSL_WRAP_BIGNUM* On error or if invalid input parameter is passed [SEC_NULL|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_CTX_get(IPSI_OSSL_WRAP_BN_CTX *ctx);



/**
* @defgroup ipsi_ossl_wrap_BN_CTX_end
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_ossl_wrap_BN_CTX_end(IPSI_OSSL_WRAP_BN_CTX *ctx);
* @endcode
*
* @par Purpose
* These functions are used to release IPSI_OSSL_WRAP_BIGNUM variables
*
* @par Description
* When ipsi_ossl_wrap_BN_CTX_end() is called, the IPSI_OSSL_WRAP_BIGNUM pointers obtained from
* ipsi_ossl_wrap_BN_CTX_get() become invalid
*
* @param[in] ctx  Pointer to the IPSI_OSSL_WRAP_BN_CTX structure for which the
*                 temporary variables needs to be made available for reuse [N/A]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID ipsi_ossl_wrap_BN_CTX_end(IPSI_OSSL_WRAP_BN_CTX *ctx);




/**
* @defgroup ipsi_ossl_wrap_BN_MONT_CTX_new
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BN_MONT_CTX *ipsi_ossl_wrap_BN_MONT_CTX_new(void);
* @endcode
*
* @par Purpose
* Allocates and initializes and initializes a IPSI_OSSL_WRAP_BN_MONT_CTX structure.
*
* @par Description
* Allocates and initializes and initializes a IPSI_OSSL_WRAP_BN_MONT_CTX structure.
*
* @param[in] SEC_VOID  This function does not accept any paramters [N/A]
*
* @retval IPSI_OSSL_WRAP_BN_CTX* Returns a pointer to the newly created IPSI_OSSL_WRAP_BN_MONT_CTX structure [N/A|N/A]
* @retval IPSI_OSSL_WRAP_BN_CTX* If memory allocation fails. [SEC_NULL|N/A]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL IPSI_OSSL_WRAP_BN_MONT_CTX *ipsi_ossl_wrap_BN_MONT_CTX_new(void);




/**
* @defgroup ipsi_ossl_wrap_BN_MONT_CTX_free
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_ossl_wrap_BN_MONT_CTX_free(IPSI_OSSL_WRAP_BN_MONT_CTX *mont);
* @endcode
*
* @par Purpose
* Frees the components of the IPSI_OSSL_WRAP_BN_MONT_CTX, and, if it was created by
* ipsi_ossl_wrap_BN_MONT_CTX_new(), also the structure itself.
*
* @par Description
* Frees the components of the IPSI_OSSL_WRAP_BN_MONT_CTX, and, if it was created by
* ipsi_ossl_wrap_BN_MONT_CTX_new(), also the structure itself.
*
* @param[in] c  Pointer to IPSI_OSSL_WRAP_BN_MONT_CTX structure which needs to be freed [N/A]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_VOID ipsi_ossl_wrap_BN_MONT_CTX_free(IPSI_OSSL_WRAP_BN_MONT_CTX *mont);



/**
* @defgroup ipsi_ossl_wrap_BN_MONT_CTX_set
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_MONT_CTX_set(IPSI_OSSL_WRAP_BN_MONT_CTX *mont,
* const IPSI_OSSL_WRAP_BIGNUM *mod, IPSI_OSSL_WRAP_BN_CTX *ctx);
* @endcode
*
* @par Purpose
* Sets up the mont structure from the modulus m by precomputing its inverse and a value R.

* @par Description
* Sets up the mont structure from the modulus m by precomputing its inverse and a value R.
*
* @param[in] mont  The Montgomery context [N/A]
* @param[in] mod  The modulus for precomputation [N/A]
* @param[in] ctx  The IPSI_OSSL_WRAP_BN_CTX context for holding the temporary variables [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if invalid input parameter is passed.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. Empty Bignumer which was created using ipsi_ossl_wrap_BN_CTX_new is not allowed to pass directly to this API.
*    If its passed API will return failure. Valid big number needs to be generated using ipsi_ossl_wrap_BN_rand API or 
*    binary/hexadecimal to BN.\n
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_MONT_CTX_set(IPSI_OSSL_WRAP_BN_MONT_CTX *mont,
    const IPSI_OSSL_WRAP_BIGNUM *mod, IPSI_OSSL_WRAP_BN_CTX *ctx);



/**
* @defgroup ipsi_ossl_wrap_BN_mod_exp_mont_word
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_mod_exp_mont_word(IPSI_OSSL_WRAP_BIGNUM *r, IPSI_OSSL_WRAP_BN_ULONG a,
* const IPSI_OSSL_WRAP_BIGNUM *p, const IPSI_OSSL_WRAP_BIGNUM *m,
* IPSI_OSSL_WRAP_BN_CTX *ctx, IPSI_OSSL_WRAP_BN_MONT_CTX *m_ctx);
* @endcode
*
* @par Purpose
* ipsi_ossl_wrap_BN_mod_exp_mont_word is a variant of ipsi_ossl_wrap_BN_mod_exp_mont that can be used
* if the number to be exponentiated fits into a single word.
*
* @par Description
* ipsi_ossl_wrap_BN_mod_exp_mont_word is a variant of ipsi_ossl_wrap_BN_mod_exp_mont that can be used
* if the number to be exponentiated fits into a single word.
* It's about 15-20 % faster than ipsi_ossl_wrap_BN_mod_exp_mont for such bases, which frequently occur in DH
* exchanges.  ipsi_ossl_wrap_BN_mod_exp_mont_word uses BN functions that ipsi_ossl_wrap_BN_mod_exp_mont does
* not use [it exploits the fact that, if one factor is small, then standard modular multiplication is faster
* than Montgomery multiplication],
*
* @param[in] r The Montgomery mod exponential result r =  a^p mod m [N/A]
* @param[in] a Input to the Montgomery mod exponential function [N/A]
* @param[in] p Input to the Montgomery mod exponential function [N/A]
* @param[in] m Input to the Montgomery mod exponential function [N/A]
* @param[in] ctx  The IPSI_OSSL_WRAP_BN_CTX context for holding the temporary variables [N/A]
* @param[in] m_ctx  The Montgomery context [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if invalid input parameter is passed. [0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. If m_ctx is NULL then montgomery context will be created internally and the modulus value will be set.\n
* 2. If zero is passed as a, then resultant bignumber r will be resetted to 0. In this case BN context can be
* passed as NULL also.\n
* 3. If zero is passed as p, then resultant bignumber r will be resetted to 1. In this case BN context can be
* passed as NULL also.\n
* 4. If both p and a is passed as 0, then resultant bignumber r will be resetted to 1. In this case BN context 
* can be passed as NULL also.\n
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_mod_exp_mont_word(IPSI_OSSL_WRAP_BIGNUM *r, IPSI_OSSL_WRAP_BN_ULONG a,
    const IPSI_OSSL_WRAP_BIGNUM *p, const IPSI_OSSL_WRAP_BIGNUM *m,
    IPSI_OSSL_WRAP_BN_CTX *ctx, IPSI_OSSL_WRAP_BN_MONT_CTX *m_ctx);



/**
* @defgroup ipsi_ossl_wrap_BN_mod_exp_mont
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_mod_exp_mont(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a,
* const IPSI_OSSL_WRAP_BIGNUM *p, const IPSI_OSSL_WRAP_BIGNUM *m,
* IPSI_OSSL_WRAP_BN_CTX *ctx, IPSI_OSSL_WRAP_BN_MONT_CTX *m_ctx);
* @endcode
*
* @par Purpose
* Do Modulous Exponential using the montgomery algorithm
*
* @par Description
* Do Modulous Exponential using the montgomery algorithm
*
* @param[in] r The Montgomery mod exponential result r =  a^p mod m [N/A]
* @param[in] a Input to the Montgomery mod exponential function [N/A]
* @param[in] p Input to the Montgomery mod exponential function [N/A]
* @param[in] m Input to the Montgomery mod exponential function [N/A]
* @param[in] ctx  The IPSI_OSSL_WRAP_BN_CTX context for holding the temporary variables [N/A]
* @param[in] m_ctx  The Montgomery context [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if invalid input parameter is passed.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. If m_ctx is NULL then montgomery context will be created internally and the modulus value will be set.\n
* 2. If p is 0, then resultant bignumber r will be set to 1 and it will returns success even if a or BN ctx is passed
* as NULL.\n
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_mod_exp_mont(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a,
    const IPSI_OSSL_WRAP_BIGNUM *p, const IPSI_OSSL_WRAP_BIGNUM *m,
    IPSI_OSSL_WRAP_BN_CTX *ctx, IPSI_OSSL_WRAP_BN_MONT_CTX *m_ctx);



/**
* @defgroup ipsi_ossl_wrap_BN_add_word
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_add_word(IPSI_OSSL_WRAP_BIGNUM *a, IPSI_OSSL_WRAP_BN_ULONG w);
* @endcode
*
* @par Purpose
* Adds w to a ("a+=w")
*
* @par Description
* Adds w to a ("a+=w")
*
* @param[in] a The input BIGNUM a in which the result of a+w is stored [N/A]
* @param[in] w The input word [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. If NULL pointer is passed as big number and zero is passed as word, then OpenSSL returns success. But this 
* behaviour has been changed to return failure. So this API will return failure in all case if NULL pointer is passed 
* as BN. \n
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_add_word(IPSI_OSSL_WRAP_BIGNUM *a, IPSI_OSSL_WRAP_BN_ULONG w);



/**
* @defgroup ipsi_ossl_wrap_BN_sub
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_sub(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a,
* const IPSI_OSSL_WRAP_BIGNUM *b);
* @endcode
*
* @par Purpose
* Subtracts b from a and places the result in r (r=a-b)
*
* @par Description
* Subtracts b from a and places the result in r (r=a-b)
*
* @param[in] r The result of a - b [N/A]
* @param[in] a Input parameter for subtraction [N/A]
* @param[in] b Input parameter for subtraction [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_sub(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a,
    const IPSI_OSSL_WRAP_BIGNUM *b);



/**
* @defgroup ipsi_ossl_wrap_BN_add
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_add(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a,
* const IPSI_OSSL_WRAP_BIGNUM *b);
* @endcode
*
* @par Purpose
* Adds a and b and places the result in r (r=a+b). r may be the same BIGNUM as a or b.
*
* @par Description
* Adds a and b and places the result in r (r=a+b). r may be the same BIGNUM as a or b.
*
* @param[in] r The result of a + b [N/A]
* @param[in] a Input parameter for addition [N/A]
* @param[in] b Input parameter for addition [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_add(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a,
    const IPSI_OSSL_WRAP_BIGNUM *b);



/**
* @defgroup ipsi_ossl_wrap_BN_bn2bin
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_bn2bin(const IPSI_OSSL_WRAP_BIGNUM *a, SEC_UCHAR *to);
* @endcode
*
* @par Purpose
* Converts the absolute value of 'a' into big-endian form and stores it at 'to'.
* 'to' must point to IPSI_OSSL_WRAP_BN_num_bytes(a) bytes of memory.
*
* @par Description
* Converts the absolute value of 'a' into big-endian form and stores it at 'to'.
* 'to' must point to IPSI_OSSL_WRAP_BN_num_bytes(a) bytes of memory.
*
* @param[in] a The big number to be converted into binary [N/A]
* @param[in] to Pointer to the buffer in which the converted integer is stored [N/A]
*
* @retval SEC_INT Returns the length of the big-endian number placed at to.[NA|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number or buffer.[-1|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_bn2bin(const IPSI_OSSL_WRAP_BIGNUM *a, SEC_UCHAR *to);




/**
* @defgroup ipsi_ossl_wrap_BN_bin2bn
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_bin2bn(const SEC_UCHAR *s, SEC_INT len, IPSI_OSSL_WRAP_BIGNUM *ret);
* @endcode
*
* @par Purpose
* Converts the positive integer in big-endian form of length len at s into a BIGNUM and places it in ret.
* If ret is NULL, a new IPSI_OSSL_WRAP_BIGNUM is created.
*
* @par Description
* Converts the positive integer in big-endian form of length len at s into a BIGNUM and places it in ret.
* If ret is NULL, a new IPSI_OSSL_WRAP_BIGNUM is created.
*
* @param[in] s Pointer to the buffer which holds the big number in binary form [N/A]
* @param[in] len Length of the buffer holding the big number [N/A]
* @param[out] ret The IPSI_OSSL_WRAP_BIGNUM which holds the converted big number [N/A]
*
* @retval IPSI_OSSL_WRAP_BIGNUM* Returns the BIGNUM which holds the converted big number.[NA|NA]
* @retval IPSI_OSSL_WRAP_BIGNUM* On error or if NULL pointer is passed as binary buffer or negative value is 
* passed for length.[SEC_NULL|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. If NULL pointer is passed as big number, then new big number will be generated for storing converted values 
* which will be returned.\n
* 2. If NULL buffer is passed and length is 0, then it will reset the bignumer to zero and returns success.\n
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_bin2bn(const SEC_UCHAR *s, SEC_INT len, 
                                                                        IPSI_OSSL_WRAP_BIGNUM *ret);


/**
* @defgroup ipsi_ossl_wrap_BN_bn2hex
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_CHAR *ipsi_ossl_wrap_BN_bn2hex(const IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function returns printable strings containing the hexadecimal encoding. For negative numbers,
* the string is prefaced with a leading '-'. The string must be freed later using ipsi_free().
*
* @par Description
* This function returns printable strings containing the hexadecimal encoding. For negative numbers,
* the string is prefaced with a leading '-'. The string must be freed later using ipsi_free().
*
* @param[in] a The big number to be converted into hexadecimal encoding [N/A]
*
* @retval SEC_CHAR* Returns pointer to the buffer which holds the null-terminated string.[NA|NA]
* @retval SEC_CHAR* On error or if NULL pointer is passed as big number.[SEC_NULL|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_CHAR *ipsi_ossl_wrap_BN_bn2hex(const IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_hex2bn
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_hex2bn(IPSI_OSSL_WRAP_BIGNUM **a, const SEC_CHAR *str);
* @endcode
*
* @par Purpose
* This function converts the string str containing a hexadecimal number to a IPSI_OSSL_WRAP_BIGNUM
*
* @par Description
* This function converts the string str containing a hexadecimal number to a IPSI_OSSL_WRAP_BIGNUM
* and stores it in **a. If *a is NULL, a new IPSI_OSSL_WRAP_BIGNUM will be created, even if the user passed 
* invalid hexadecimal strings (eg. "-", "xx", "-xyz"). If a is NULL, it only computes the number's length in 
* hexadecimal digits. If the string starts with '-', the number is negative.
*
* @param[in] a Pointer to pointer to IPSI_OSSL_WRAP_BIGNUM structure where the converted big number
* is stored [N/A]
* @param[in] str The input null-terminated string containing the hexadecimal encoding of big number [N/A]
*
* @retval SEC_INT Returns the big number's length in hexadecimal.[NA|NA]
* @retval SEC_INT On error or if NULL string is passed.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. Length of the hex string which the user passed should not be more than (INT_MAX-31)/4.\n
* 2. If "-0" is passed as hex string, then OpenSSL set negative flag also and returns 2. But this behaviour is not 
* necessary to support. So our API will not set negative flag and it returns 1.
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_hex2bn(IPSI_OSSL_WRAP_BIGNUM **a, const SEC_CHAR *str);



/**
* @defgroup ipsi_ossl_wrap_BN_num_bits
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_num_bits(const IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function returns the number of significant bits in a BIGNUM
*
* @par Description
* This function returns the number of significant bits in a BIGNUM. If we take 0x00000432 as an example,
* it returns 11, not 16, not 32. Basically, except for a zero, it returns floor(log2(w))+1.
*
* @param[in] a Pointer to IPSI_OSSL_WRAP_BIGNUM structure [N/A]
*
* @retval SEC_INT Returns the number of significant bits in a BIGNUM.[NA|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number.[-1|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_num_bits(const IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_num_bytes
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_num_bytes(const IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function returns the number of significant bytes in a BIGNUM
*
* @par Description
* This function returns the number of significant bytes in a BIGNUM. If we take 0x00000432 as an example,
* it returns 2, not 3, not 4.
*
* @param[in] a Pointer to IPSI_OSSL_WRAP_BIGNUM structure [N/A]
*
* @retval SEC_INT Returns the number of significant bytes in a BIGNUM.[NA|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number.[-1|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_num_bytes(const IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_is_odd
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_is_odd(const IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function returns 1 if the BIGNUM is odd, 0 otherwise
*
* @par Description
* This function returns 1 if the BIGNUM is odd. And returns 0 on error or if BIGNUM is even.
*
* @param[in] a Pointer to IPSI_OSSL_WRAP_BIGNUM structure [N/A]
*
* @retval SEC_INT Returns 1 if the BIGNUM is odd.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big numer of if BIGNUM is even.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_is_odd(const IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_set_word
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_set_word(IPSI_OSSL_WRAP_BIGNUM *a, IPSI_OSSL_WRAP_BN_ULONG w);
* @endcode
*
* @par Purpose
* Sets the value of w to IPSI_OSSL_WRAP_BIGNUM a
*
* @par Description
* Sets the value of w to IPSI_OSSL_WRAP_BIGNUM a
*
* @param[in] a Pointer to IPSI_OSSL_WRAP_BIGNUM structure where the word is set [N/A]
* @param[in] w The word to be set in the BIGNUM [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_set_word(IPSI_OSSL_WRAP_BIGNUM *a, IPSI_OSSL_WRAP_BN_ULONG w);



/**
* @defgroup ipsi_ossl_wrap_BN_get_word
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BN_ULONG ipsi_ossl_wrap_BN_get_word(const IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function returns the value of BIGNUM if it fits in a word.
*
* @par Description
* This function returns the value of BIGNUM if it fits in a word, otherwise 0xffffffffL.
*
* @param[in] a The BIGNUM for which the value needs to be obtained [N/A]
*
* @retval IPSI_OSSL_WRAP_BN_ULONG Returns the value of BIGNUM if it fits in a word.[NA|NA]
* @retval IPSI_OSSL_WRAP_BN_ULONG If the BIGNUM size is greater than word .[0xffffffffL|NA]
* @retval IPSI_OSSL_WRAP_BN_ULONG On error or if NULL pointer is passed as big number or if value itself is zero.[0 |NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL IPSI_OSSL_WRAP_BN_ULONG ipsi_ossl_wrap_BN_get_word(const IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_lshift
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_lshift(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT n);
* @endcode
*
* @par Purpose
* This function shifts IPSI_OSSL_WRAP_BIGNUM a left by n bits and places the result in r (r=a*2^n)
*
* @par Description
* This function shifts IPSI_OSSL_WRAP_BIGNUM a left by n bits and places the result in r (r=a*2^n).
* For the shift functions, r and a may be the same variable.
*
* @param[in] r Result of the left shift [N/A]
* @param[in] a BIGNUM which needs to be left shift [N/A]
* @param[in] n Shift by n bits [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error.or if NULL pointer is passed as big number or negative value is passed as n. [0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_lshift(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT n);


/**
* @defgroup ipsi_ossl_wrap_BN_rshift
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_rshift(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT n);
* @endcode
*
* @par Purpose
* This function shifts IPSI_OSSL_WRAP_BIGNUM a right by n bits and places the result in r (r=a/2^n).
*
* @par Description
* This function shifts IPSI_OSSL_WRAP_BIGNUM a right by n bits and places the result in r (r=a/2^n).
* For the shift functions, r and a may be the same variable.
*
* @param[in] r Result of the right shift [N/A]
* @param[in] a BIGNUM which needs to be right shift [N/A]
* @param[in] n Shift by n bits [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number or negative value is passed as n.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_rshift(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT n);



/**
* @defgroup ipsi_ossl_wrap_BN_is_zero
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_is_zero(const IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function returns 1 if the BIGNUM is zero, 0 otherwise
*
* @par Description
* This function returns 1 if the BIGNUM is zero. And returns 0 on error or if BIGNUM is not zero.
*
* @param[in] a Pointer to IPSI_OSSL_WRAP_BIGNUM structure [N/A]
*
* @retval SEC_INT Returns 1 if the BIGNUM is zero.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number or if BIGNUM is not zero.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_is_zero(const IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_is_bit_set
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_is_bit_set(const IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT n);
* @endcode
*
* @par Purpose
* This function is to check whether nth bit is set or not
*
* @par Description
* This function is to check whether nth bit is set or not. If set it returns 1 otherwise 0.
*
* @param[in] a The BIGNUM which has to be tested for a bit set [N/A]
* @param[in] n The bit which needs to be checked [N/A]
*
* @retval SEC_INT Returns 1 if the bit is set.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number or is negative value is passed as n or 
* if the bit is not set.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_is_bit_set(const IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT n);



/**
* @defgroup ipsi_ossl_wrap_BN_cmp
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_cmp(const IPSI_OSSL_WRAP_BIGNUM *a, const IPSI_OSSL_WRAP_BIGNUM *b);
* @endcode
*
* @par Purpose
* This function compares the numbers a and b.
*
* @par Description
* This function compares the numbers a and b. Returns -1 if a < b, 0 if a = b and 1 if a > b
*
* @param[in] a The input BIGNUM [N/A]
* @param[in] b The input BIGNUM [N/A]
*
* @retval SEC_INT Returns -1 if a < b or a is valid pointer and b is NULL pointer value.[-1|NA]
* @retval SEC_INT Returns 0 if a == b.[0|NA]
* @retval SEC_INT Returns 1 if a > b or if a is NULL pointer and b is valid pointer.[1|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. If Big number having value as -0 and 0 are passed to this API will gives result as -1. Even though both
*    -0 and 0 are same. Similarly for 0 and -0 result will be 1. This behaviour is same as OpenSSL.\n
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_cmp(const IPSI_OSSL_WRAP_BIGNUM *a, const IPSI_OSSL_WRAP_BIGNUM *b);



/**
* @defgroup ipsi_ossl_wrap_BN_rand
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_rand(IPSI_OSSL_WRAP_BIGNUM *rnd, SEC_INT bits, SEC_INT top, SEC_INT bottom);
* @endcode
*
* @par Purpose
* This function generates a cryptographically strong pseudo-random number.
*
* @par Description
* This function generates a cryptographically strong pseudo-random number of bits bits in length and
* stores it in rnd. If top is -1, the most significant bit of the random number can be zero or one.
* If top is 0, it is set to 1, and if top is 1, the two most significant bits of the number will be
* set to 1, so that the product of two such random numbers will always have 2*bits length.
* If bottom is true (non zero value), the generated random number will be converted to odd if it is even, if it is
* false it just generates and gives the random number so it can be odd or even.
*
* @param[in] rnd The input BIGNUM in which the random number generated is stored [N/A]
* @param[in] bits Length of the random number to be generated in bits [N/A]
* @param[in] top Flag to indicate if the most significant bit of the random number should be set [N/A]
* @param[in] bottom Flag to indicate the random number generated should be odd [N/A]
*
* @retval SEC_INT For success.[1|NA]
* @retval SEC_INT On error or if NULL pointer is passed as big number or if negative number is passed as 
* no of bits.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. Values passed to top other than -1 and 0 will be considered as 1.\n
* 2. If number of bit is passed as 1 and values passed to top is other than -1 and 0, then API will return failure.\n
* 3. If number of bit is passed as 0, then API will reset the BN to zero and returns success. In this case valid
*    values passed as top and bottom will not be considered.\n
* 4. Number of bits supported is from 0 to  536870880.\n
* 5. Since internal implementation of random contains a global rand object access. In intel thread checker it may
*    show as race condition. But this is not a problem as it is random output and it does not has any functional 
*    impact. Application can add a lock before calling this API, if they want to avoid those warning in that tool.\n
*
* @par Related Topics
* N/A
*/
CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_rand(IPSI_OSSL_WRAP_BIGNUM *rnd, SEC_INT bits, SEC_INT top, SEC_INT bottom);


/**
* @defgroup ipsi_ossl_wrap_BN_dup
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_dup(const IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function duplicates the Big number.
*
* @par Description
* This function duplicates the Big number.
*
* @param[in] a The source BIGNUM which needs to be duplicated. [N/A]
*
* @retval IPSI_OSSL_WRAP_BIGNUM* Valid Big number on success.[NA|NA]
* @retval IPSI_OSSL_WRAP_BIGNUM* On error or if NULL pointer is passed as big number.[SEC_NULL|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_dup(const IPSI_OSSL_WRAP_BIGNUM *a);


/**
* @defgroup ipsi_ossl_wrap_BN_bn2dec
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_CHAR *ipsi_ossl_wrap_BN_bn2dec(const IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function converts the big number to decimal string.
*
* @par Description
* This function converts the big number to decimal string, and returns the pointer to the buffer.
* Later user has to call ipsi_free to free the buffer generated by this API.
*
* @param[in] a The BIGNUM which needs to be converted to decimal string. [N/A]
*
* @retval IPSI_OSSL_WRAP_BIGNUM* Valid decimal string buffer on success.[NA|NA]
* @retval IPSI_OSSL_WRAP_BIGNUM* On error or if NULL pointer is passed as big number.[SEC_NULL|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_CHAR *ipsi_ossl_wrap_BN_bn2dec(const IPSI_OSSL_WRAP_BIGNUM *a);



/**
* @defgroup ipsi_ossl_wrap_BN_mask_bits
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_mask_bits(IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT n);
* @endcode
*
* @par Purpose
* This function truncates the Big number a to n bit number.
*
* @par Description
* This function truncates the Big number a to n bit number.
*
* @param[in] a The BIGNUM which needs to be truncated. [N/A]
* @param[in] n Number of bits, the user wants in resultant BN. [N/A]
*
* @retval SEC_INT On success.[1|NA]
* @retval SEC_INT On failure or if NULL pointer is passed as big number.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. If the value passed to n is positive value which is greater than size of BN
* then this API will return 0, and also for negative value API will return 0.\n
* 2. OpenSSL returns failure in case where n and size of BN is same and n is of 
* multiples of word size. But this is not correct. So this behaviour has been changed to return success.\n
* 3. Similarly OpenSSL returns success in case where n is greater than number of bits of BN and 
* the difference is not more than 32. For example if n is 34 and BN size is 33 openssl returns success. But this 
* is wrong. So this behaviour has been changed to return failure if n is greater than size of BN.\n
* 4. OpenSSL`s implementation doesnt update Negative flag, if the BN becomes 0 after truncation.
* This has been fixed in this function. So if a negative BN is truncated to 0 then negative flag also
* will be reset to 0.
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_mask_bits(IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT n);



/**
* @defgroup ipsi_ossl_wrap_BN_is_negative
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_is_negative(IPSI_OSSL_WRAP_BIGNUM *a);
* @endcode
*
* @par Purpose
* This function checks whether big number is negative or not.
*
* @par Description
* This function checks whether big number is negative or not. It will return success if negative 
* flag is set and BN value is Non zero.
*
* @param[in] a The BIGNUM which needs to be checked. [N/A]
*
* @retval SEC_INT On success.[1|NA]
* @retval SEC_INT On failure or if NULL pointer is passed as big number.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* N/A
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_is_negative(IPSI_OSSL_WRAP_BIGNUM *a);


/**
* @defgroup ipsi_ossl_wrap_BN_set_flags
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_set_flags(IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT iFlags);
* @endcode
*
* @par Purpose
* This function used to set flags to bignumber.
*
* @par Description
* This function used to set flags to bignumber. Currently only IPSI_OSSL_WRAP_BN_FLG_CONSTTIME
* flag is allowed to set through this API.
*
* @param[in] a The BIGNUM in which the flag has to be set. [N/A]
*
* @retval SEC_INT On success.[1|NA]
* @retval SEC_INT On failure or if NULL pointer is passed as BN or invalid flags is passed.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. Currently only IPSI_OSSL_WRAP_BN_FLG_CONSTTIME flag is supported in big number, so any other values 
* passed as flags to this API will be treated as failure.\n
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_set_flags(IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT iFlags);


/**
* @defgroup ipsi_ossl_wrap_BN_get_flags
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_get_flags(IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT iFlags);
* @endcode
*
* @par Purpose
* This function used to check whether some flag is set or not in bignumber.
*
* @par Description
* This function used to check whether some flag is set or not in bignumber. Currently only 
* IPSI_OSSL_WRAP_BN_FLG_CONSTTIME flag is allowed. So by this API user can check 
* whether IPSI_OSSL_WRAP_BN_FLG_CONSTTIME flag is set or not.
*
* @param[in] a The BIGNUM in which the flag has to be set. [N/A]
*
* @retval SEC_INT If flag is set.[Non Zero Value |NA]
* @retval SEC_INT If flag is not set or on failure or if NULL pointer is passed as BN.[0|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. Currently only IPSI_OSSL_WRAP_BN_FLG_CONSTTIME flag is supported in big number, so any other values 
* passed as flags to this API will be treated as failure.\n
* 2. If the flag is set in big number then this API will return a NON zero value with the same flag bit enabled.
* So user can do bitwise AND operation between return value and flag to check whether it is set or not.
* Currently only IPSI_OSSL_WRAP_BN_FLG_CONSTTIME is supported so currently this API return only
* IPSI_OSSL_WRAP_BN_FLG_CONSTTIME in success case.
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_get_flags(IPSI_OSSL_WRAP_BIGNUM *a, SEC_INT iFlags);


/**
* @defgroup ipsi_ossl_wrap_BN_div_word
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BN_ULONG ipsi_ossl_wrap_BN_div_word(IPSI_OSSL_WRAP_BIGNUM *a, IPSI_OSSL_WRAP_BN_ULONG w);
* @endcode
*
* @par Purpose
* This function divides the BN number with a word and returns remainder and updates BN value as quotient.
*
* @par Description
* This function divides the BN number with a word and returns remainder and update BN value as quotient.
*
* @param[in,out] a The BIGNUM which needs to be divided. [N/A]
* @param[in] w The divisor word. [N/A]
*
* @retval IPSI_OSSL_WRAP_BN_ULONG On success.[Remainder|NA]
* @retval IPSI_OSSL_WRAP_BN_ULONG On failure or if NULL pointer is passed as big number 
* or 0 is passed as divisior.[SEC_ERROR|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* This API fails if input parameter a is passed as NULL.
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL IPSI_OSSL_WRAP_BN_ULONG ipsi_ossl_wrap_BN_div_word(IPSI_OSSL_WRAP_BIGNUM *a, IPSI_OSSL_WRAP_BN_ULONG w);


/**
* @defgroup ipsi_ossl_wrap_BN_copy
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_copy(IPSI_OSSL_WRAP_BIGNUM *dst, IPSI_OSSL_WRAP_BIGNUM *src);
* @endcode
*
* @par Purpose
* This function copies the BN number from source to destination.
*
* @par Description
* This function copies the BN number from source to destination.
*
* @param[in] dst Destination BIGNUM. [N/A]
* @param[in] src Source BIGNUM. [N/A]
*
* @retval IPSI_OSSL_WRAP_BIGNUM* Destination BIGNUM on success.[dst|NA]
* @retval IPSI_OSSL_WRAP_BIGNUM* On failure or if NULL pointer is passed as big number.[NULL|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. This API fails if input parameter dst or src is passed as NULL.\n
* 2. This API doesn't copy the flags (whichever set by ipsi_ossl_wrap_BN_set_flags) from source to 
* destination and it doesn't modify the flags in destination.\n
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL IPSI_OSSL_WRAP_BIGNUM *ipsi_ossl_wrap_BN_copy(IPSI_OSSL_WRAP_BIGNUM *dst, 
                                                                    IPSI_OSSL_WRAP_BIGNUM *src);

/**
* @defgroup ipsi_ossl_wrap_BN_mul_word
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_mul_word(IPSI_OSSL_WRAP_BIGNUM *a, IPSI_OSSL_WRAP_BN_ULONG w);
* @endcode
*
* @par Purpose
* This function multiplies the BN number with the word.
*
* @par Description
* This function multiplies the BN number with the word.
*
* @param[in,out] a The BIGNUM which needs to be multiplied. [N/A]
* @param[in] w The multiplier. [N/A]
*
* @retval SEC_INT On success.[SEC_TRUE |NA]
* @retval SEC_INT On failure or invalid input parameter.[SEC_FALSE|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* This API fails if input parameter a is passed as NULL.
*
* @par Related Topics
* N/A
*/


CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_mul_word(IPSI_OSSL_WRAP_BIGNUM *a, IPSI_OSSL_WRAP_BN_ULONG w);


/**
* @defgroup ipsi_ossl_wrap_BN_mod_exp
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_INT ipsi_ossl_wrap_BN_mod_exp(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a, 
                          const IPSI_OSSL_WRAP_BIGNUM *p, const IPSI_OSSL_WRAP_BIGNUM *m, IPSI_OSSL_WRAP_BN_CTX *ctx);

* @endcode
*
* @par Purpose
* This function computes a to the p-th power modulo m ("r=a^p % m"). 
*
* @par Description
* This function computes a to the p-th power modulo m ("r=a^p % m"). 
*
* @param[out] r Resultant BIGNUM. [N/A]
* @param[in] a Base BIGNUM. [N/A]
* @param[in] p Power BIGNUM. [N/A]
* @param[in] m Modulo BIGNUM. [N/A]
* @param[in] ctx BN context. [N/A]
*
* @retval SEC_INT On success.[SEC_TRUE |NA]
* @retval SEC_INT On failure or invalid input parameter.[SEC_FALSE|NA]
* @retval SEC_INT On internal failure.[SEC_ERROR|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* This API fails if any one of the paramter is passed as NULL.
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_INT ipsi_ossl_wrap_BN_mod_exp(IPSI_OSSL_WRAP_BIGNUM *r, const IPSI_OSSL_WRAP_BIGNUM *a, 
                          const IPSI_OSSL_WRAP_BIGNUM *p, const IPSI_OSSL_WRAP_BIGNUM *m, IPSI_OSSL_WRAP_BN_CTX *ctx);



/**
* @defgroup ipsi_ossl_wrap_BN_clear
* @ingroup LLF Low Level Functions
* @par Prototype
* @code
* SEC_VOID ipsi_ossl_wrap_BN_clear(IPSI_OSSL_WRAP_BIGNUM *a);
*
* @endcode
*
* @par Purpose
* This function clears the big number by setting zero.
*
* @par Description
* This function clears the big number by setting zero and also it disables the negative flag if BN is negative.
*
* @param[in] a BIGNUM. [N/A]
*
* @retval SEC_VOID This function does not return any value.[NA|NA]
*
* @par Required Header File
* sec_ossl_wrap_bn.h
*
* @par Note
* 1. This API doesn't perform anything if user passed NULL as input parameter.\n
* 2. This API doesn't clear the flags set using ipsi_ossl_wrap_BN_set_flags.\n
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_VOID ipsi_ossl_wrap_BN_clear(IPSI_OSSL_WRAP_BIGNUM *a);


#ifdef __cplusplus
}
#endif

#endif /* _IPSI_OSSL_WRAP_BN_H__ */

