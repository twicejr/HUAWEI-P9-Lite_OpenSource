/*****************************************************************************
                                                                            
                Copyright (C), 2008, Huawei Tech. Co., Ltd.                
                            ALL RIGHTS RESERVED                             
                                                                            
------------------------------------------------------------------------------


FileName     : common_error.h
Author       : Vinay Gudur  
Version      : 1
Date         : 2007-08-30
Description  : This file contains common crypto errors.
Function List: 
SEC_getCryptoErrorText

          History:
                    <author>   <date>          <desc>
----------------------------------------------------------------------------

****************************************************************************/

#ifndef _IPSI_COMMON_ERROR_H
#define _IPSI_COMMON_ERROR_H

#ifdef   __cplusplus
extern  "C"{
#endif

#include "ipsi_types.h"
#include "sec_sys.h"

/* All error codes starts from this value for this module */
#define SEC_COMMON_ERR_BASE                 0x73010000UL
    
#define DEFINE_COMMON_ERR(v)                (SEC_COMMON_ERR_BASE + (v))

#define SEC_ERR_ADD_RECIPIENT_FAILED        DEFINE_COMMON_ERR(1)
#define SEC_ERR_ADD_SIGNER_FAILED           DEFINE_COMMON_ERR(2)
#define SEC_ERR_ATTR_NOT_AVAILABLE          DEFINE_COMMON_ERR(3)
#define SEC_ERR_BUF_COPY_FAILED             DEFINE_COMMON_ERR(4)
#define SEC_ERR_CERT_NOT_AVAILABLE          DEFINE_COMMON_ERR(5)
#define SEC_ERR_CID_MISMATCH                DEFINE_COMMON_ERR(6)
#define SEC_ERR_CONVERT_FAILED              DEFINE_COMMON_ERR(7)
#define SEC_ERR_CREATE_DIGEST_FAIL          DEFINE_COMMON_ERR(8)
#define SEC_ERR_CREATE_ENVDATA_FAILED       DEFINE_COMMON_ERR(9)
#define SEC_ERR_CREATE_REQUEST_FAILED       DEFINE_COMMON_ERR(10)
#define SEC_ERR_CREATE_SIGNDATA_FAILED      DEFINE_COMMON_ERR(11)
#define SEC_ERR_CREATE_SIGNER_INFO_FAILED   DEFINE_COMMON_ERR(12)
#define SEC_ERR_CREATE_SIMPLEDATA_FAILED    DEFINE_COMMON_ERR(13)
#define SEC_ERR_DATA_COPY_FAILED            DEFINE_COMMON_ERR(14)
#define SEC_ERR_DATA_NOT_AVAILABLE          DEFINE_COMMON_ERR(15)
#define SEC_ERR_DECODE_BASE64_FAILED        DEFINE_COMMON_ERR(16)
#define SEC_ERR_DECODE_FAILED               DEFINE_COMMON_ERR(17)
#define SEC_ERR_DECRYPT_FAILED              DEFINE_COMMON_ERR(18)
#define SEC_ERR_DIGEST_VERIFY_FAILED        DEFINE_COMMON_ERR(19)
#define SEC_ERR_DUPLICATE_EXTN              DEFINE_COMMON_ERR(20)
#define SEC_ERR_DUPLICATE_LIST_DATA         DEFINE_COMMON_ERR(21)
#define SEC_ERR_ENCODE_BASE64_FAILED        DEFINE_COMMON_ERR(22)
#define SEC_ERR_ENCODE_FAILED               DEFINE_COMMON_ERR(23)
#define SEC_ERR_ENCRYPT_FAILED              DEFINE_COMMON_ERR(24)
#define SEC_ERR_EXCESS_NODES                DEFINE_COMMON_ERR(25)
#define SEC_ERR_EXTN_NOT_AVAILABLE          DEFINE_COMMON_ERR(26)
#define SEC_ERR_FILE_OPEN_FAILED            DEFINE_COMMON_ERR(27)
#define SEC_ERR_FILE_READ_FAILED            DEFINE_COMMON_ERR(28)
#define SEC_ERR_FILE_WRITE_FAILED           DEFINE_COMMON_ERR(29)
#define SEC_ERR_GET_OID_FAILED              DEFINE_COMMON_ERR(30)
#define SEC_ERR_HASH_FAILED                 DEFINE_COMMON_ERR(31)
#define SEC_ERR_INVALID_ALGID               DEFINE_COMMON_ERR(32)
#define SEC_ERR_INVALID_ARG                 DEFINE_COMMON_ERR(33)
#define SEC_ERR_INVALID_ATTR                DEFINE_COMMON_ERR(34)
#define SEC_ERR_INVALID_BASE64              DEFINE_COMMON_ERR(35)
#define SEC_ERR_INVALID_CID                 DEFINE_COMMON_ERR(36)
#define SEC_ERR_INVALID_DATA_LEN            DEFINE_COMMON_ERR(37)
#define SEC_ERR_INVALID_DATETIME            DEFINE_COMMON_ERR(38)
#define SEC_ERR_INVALID_EXTN                DEFINE_COMMON_ERR(39)
#define SEC_ERR_INVALID_FILE_SIZE           DEFINE_COMMON_ERR(40)
#define SEC_ERR_INVALID_ISSUERNAME          DEFINE_COMMON_ERR(41)
#define SEC_ERR_INVALID_IV                  DEFINE_COMMON_ERR(42)
#define SEC_ERR_INVALID_IV_LEN              DEFINE_COMMON_ERR(43)
#define SEC_ERR_INVALID_KEY_LEN             DEFINE_COMMON_ERR(44)
#define SEC_ERR_INVALID_LIST                DEFINE_COMMON_ERR(45)
#define SEC_ERR_INVALID_LIST_CURRENT        DEFINE_COMMON_ERR(46)
#define SEC_ERR_INVALID_LIST_INDEX          DEFINE_COMMON_ERR(47)
#define SEC_ERR_INVALID_LIST_POSITION       DEFINE_COMMON_ERR(48)
#define SEC_ERR_INVALID_MAC                 DEFINE_COMMON_ERR(49)
#define SEC_ERR_INVALID_MODE                DEFINE_COMMON_ERR(50)
#define SEC_ERR_INVALID_OID                 DEFINE_COMMON_ERR(51)
#define SEC_ERR_INVALID_PRINTABLE           DEFINE_COMMON_ERR(52)
#define SEC_ERR_INVALID_SALT_LEN            DEFINE_COMMON_ERR(53)
#define SEC_ERR_INVALID_SERIALNUMBER        DEFINE_COMMON_ERR(54)
#define SEC_ERR_INVALID_VERSION             DEFINE_COMMON_ERR(55)
#define SEC_ERR_ISSUER_MISMATCH             DEFINE_COMMON_ERR(56)
#define SEC_ERR_KEY_DERIV_FAILED            DEFINE_COMMON_ERR(57)
#define SEC_ERR_KEY_GEN_FAILED              DEFINE_COMMON_ERR(58)
#define SEC_ERR_KEY_MISMATCH                DEFINE_COMMON_ERR(59)
#define SEC_ERR_KEYPAIR_MISMATCH            DEFINE_COMMON_ERR(60)
#define SEC_ERR_LIST_OPERATION_FAILED       DEFINE_COMMON_ERR(61)
#define SEC_ERR_NAME_MISMATCH               DEFINE_COMMON_ERR(62)
#define SEC_ERR_NAME_NOT_AVAILABLE          DEFINE_COMMON_ERR(63)
#define SEC_ERR_NONCE_MISMATCH              DEFINE_COMMON_ERR(64)
#define SEC_ERR_OID_MISMATCH                DEFINE_COMMON_ERR(65)
#define SEC_ERR_OPEN_ENVELOP_FAILED         DEFINE_COMMON_ERR(66)
#define SEC_ERR_RANDOM_FAILED               DEFINE_COMMON_ERR(67)
#define SEC_ERR_REQ_RESP_MISMATCH           DEFINE_COMMON_ERR(68)
#define SEC_ERR_SIGN_VERIFY_FAILED          DEFINE_COMMON_ERR(69)
#define SEC_ERR_SIGNING_FAILED              DEFINE_COMMON_ERR(70)
#define SEC_ERR_STRING_MISMATCH             DEFINE_COMMON_ERR(71)
#define SEC_ERR_MALLOC_FAIL                 DEFINE_COMMON_ERR(72)
#define SEC_ERR_NULL_PTR                    DEFINE_COMMON_ERR(73)
#define SEC_ERR_VERIFY_FAILED               DEFINE_COMMON_ERR(74)
#define SEC_HW_ERR_PERMISSION               DEFINE_COMMON_ERR(75)
#define SEC_HW_ERR_FILENAME                 DEFINE_COMMON_ERR(76)
#define SEC_HW_ERR_DEVICE                   DEFINE_COMMON_ERR(77)
#define SEC_HW_ERR_INVALID_OPERATION        DEFINE_COMMON_ERR(78)
#define SEC_HW_ERR_CLOSE                    DEFINE_COMMON_ERR(79)
#define SEC_HW_ERR_NOT_SUPPORTED            DEFINE_COMMON_ERR(80)
#define SEC_ERR_INITLIB                     DEFINE_COMMON_ERR(81)
#define SEC_ERR_INITDEVICE                  DEFINE_COMMON_ERR(82)
#define SEC_ERR_INVALID_PRIVATE_KEY         DEFINE_COMMON_ERR(83)
#define SEC_ERR_INVALID_PRV_OID_TYPE_CODE           DEFINE_COMMON_ERR(84)
#define SEC_ERR_DUPLICATE_PRV_OID           DEFINE_COMMON_ERR(85)
#define SEC_ERR_INVALID_PRV_OID_NAME_LENGTH           DEFINE_COMMON_ERR(86)
#define SEC_ERR_MEMCPY_FAILED               DEFINE_COMMON_ERR(87)
#define SEC_ERR_MEMSET_FAILED               DEFINE_COMMON_ERR(88)

/* This structure is used for storing error information. apcTabBase
represents error strings and uiMaxErr represents number of errors of a 
specific type 
For example,
PKCS5 error strings could have following possible values :
MAC generation failed, Get Salt failed, Invalid iteration value.
So apcTabBase should point to the above strings and uiMaxErr should be set to
3(total number of errors).
*/

/** @defgroup common_error
* This section contains the common_error Structure.
*/

/** @defgroup common_errorStructure
* @ingroup common_error
* This section contains the common_error Structure.
*/

/**
* @defgroup ERROR_TAB_S
* @ingroup common_errorStructure
* @par Prototype
* @code
* typedef struct
* {
*  SEC_CHAR** apcTabBase;
*  SEC_UINT32 uiMaxErr;
* }ERROR_TAB_S;
* @endcode
*
* @datastruct apcTabBase It point to PKCS5 error strings.
PKCS5 error strings could have following values:\n
* MAC generation failed\n
* Get Salt failed\n
* Invalid iteration value
* @datastruct uiMaxErr It should be set to 3 (total number of errors)
*/
typedef struct
{
    SEC_CHAR** apcTabBase;
    SEC_UINT32 uiMaxErr;
}ERROR_TAB_S;


#ifdef  __cplusplus
}
#endif /* end of __cplusplus */


#endif  /* _IPSI_COMMON_ERROR_H */


