/*****************************************************************************
                                                                            
                Copyright (C), 2008, Huawei Tech. Co., Ltd.                
                            ALL RIGHTS RESERVED                             
                                                                            
------------------------------------------------------------------------------


FileName     : crypto_error.h
Author       : 
Version      : 1
Date         : 
Description  : This file contains crypto errors
Function List: 
OSI_bits
uLong_bits
uLong_I2OSP
uLong_OS2IP

          History:
                    <author>   <date>          <desc>
----------------------------------------------------------------------------
****************************************************************************/

#ifndef	_IPSI_CRYPTO_ERROR_H
#define	_IPSI_CRYPTO_ERROR_H

#include "common_error.h"
#include "sec_sys.h"

/* Check if x is true, If true return the error code corresponding to c */
#define	ASSERT_RET_CODE(x,c)	do {\
if (x) \
{ \
    SEC_REPORT_ERROR (c);\
    return (c);\
}\
} while (0)


/* All error codes starts from this value for this module */
#define	SEC_CRYPT_ERR_BASE						0x73020000UL
#define DEFINE_CRYPTO_ERR(v)					(SEC_CRYPT_ERR_BASE + (v))

#define SEC_CRYPT_ERR_INVALID_PKEY				DEFINE_CRYPTO_ERR(1)
#define SEC_CRYPT_ERR_UNDEFINED_KEY_OPERATION	DEFINE_CRYPTO_ERR(2)
#define SEC_CRYPT_ERR_UNDEFINED_PADDING			DEFINE_CRYPTO_ERR(3)
#define SEC_CRYPT_ERR_INVALID_CTX				DEFINE_CRYPTO_ERR(4)
#define SEC_CRYPT_ERR_INVALID_PKEY_TYPE			DEFINE_CRYPTO_ERR(5)
#define SEC_CRYPT_ERR_LARGE_DATA_SIZE			DEFINE_CRYPTO_ERR(6)
#define SEC_CRYPT_ERR_SMALL_DATA_SIZE			DEFINE_CRYPTO_ERR(7)
#define SEC_CRYPT_ERR_INVALID_PADDING			DEFINE_CRYPTO_ERR(8)
#define SEC_CRYPT_ERR_UNDEFINED_FIELD			DEFINE_CRYPTO_ERR(9)
#define SEC_ERR_INVALID_PUB_KEY_E_LENGTH		DEFINE_CRYPTO_ERR(10)
#define SEC_ERR_INVALID_PUB_KEY_N_LENGTH		DEFINE_CRYPTO_ERR(11)
#define SEC_ERR_NON_RSA_KEY                     DEFINE_CRYPTO_ERR(12)
#define SEC_ERR_NO_KEY			                DEFINE_CRYPTO_ERR(13)
#define SEC_ERR_DATA_GREATER_THAN_KEY_LEN       DEFINE_CRYPTO_ERR(14)
#define SEC_CRYPT_ERR_AAD_LEN_EXCEED_MAXLIMIT       DEFINE_CRYPTO_ERR(15)
#define SEC_CRYPT_ERR_INVALID_TAG_LEN           DEFINE_CRYPTO_ERR(16)
#define SEC_CRYPT_ERR_IV_LEN_EXCEED_MAXLIMIT       DEFINE_CRYPTO_ERR(17)
#define SEC_CRYPT_ERR_SET_AAD_AFTER_CIPHER_OPERATION       DEFINE_CRYPTO_ERR(18)

#endif	/* _IPSI_CRYPTO_ERROR_H */

