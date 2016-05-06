/*****************************************************************************

             Copyright (C), 2008, Huawei Tech. Co., Ltd.                
                         ALL RIGHTS RESERVED                             

------------------------------------------------------------------------------


FileName     :tls12.h 
Author       : Shiva Kumar N
Version      :1
Date         :20-08-2011
Description  :Macros and data structure for TLS 1.2
Function List: 

History:
<author>   <date>          <desc>
----------------------------------------------------------------------------
****************************************************************************/

/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
  All rights reserved.
 
  This package is an SSL implementation written
  by Eric Young (eay@cryptsoft.com).
  The implementation was written so as to conform with Netscapes SSL.
  
  This library is free for commercial and non-commercial use as long as
  the following conditions are aheared to.  The following conditions
  apply to all code found in this distribution, be it the RC4, RSA,
  lhash, DES, etc., code; not just the SSL code.  The SSL documentation
  included with this distribution is covered by the same copyright terms
  except that the holder is Tim Hudson (tjh@cryptsoft.com).
  
  Copyright remains Eric Young's, and as such any Copyright notices in
  the code are not to be removed.
  If this package is used in a product, Eric Young should be given attribution
  as the author of the parts of the library used.
  This can be in the form of a textual message at program startup or
  in documentation (online or textual) provided with the package.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement:
     "This product includes cryptographic software written by
      Eric Young (eay@cryptsoft.com)"
     The word 'cryptographic' can be left out if the rouines from the library
     being used are not cryptographic related :-).
  4. If you include any Windows specific code (or a derivative thereof) from 
     the apps directory (application code) you must include an acknowledgement:
     "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
  
  THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.
  
  The licence and distribution terms for any publically available version or
  derivative of this code cannot be changed.  i.e. this code cannot simply be
  copied and put under another distribution licence
  [including the GNU Public Licence.]
 */
/* ====================================================================
  Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 
  Portions of the attached software ("Contribution") are developed by 
  SUN MICROSYSTEMS, INC., and are contributed to the OpenSSL project.
 
  The Contribution is licensed pursuant to the OpenSSL open source
  license provided above.
 
  ECC cipher suite support in OpenSSL originally written by
  Vipul Gupta and Sumit Gupta of Sun Microsystems Laboratories.
 
 */

#include "ipsi_ssl_build_conf.h"

#ifndef __IPSI_TLS12_H__
#define __IPSI_TLS12_H__

#ifndef IPSI_NO_TLS12

#include "ipsi_types.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
* @defgroup MacroDefinitions Macro Definitions
* @code
* #define TLS12_VERSION			0x0303
* #define TLS12_VERSION_MAJOR		0x03
* #define TLS12_VERSION_MINOR		0x03
* 
* //Anonymous ciphers
* 
* #define TLS12_CK_ADH_RC4_128_MD5                0x03000018
* #define TLS12_CK_ADH_3DES_EDE_CBC_SHA           0x0300001B
* #define TLS12_CK_ADH_AES_128_CBC_SHA            0x03000034
* #define TLS12_CK_ADH_AES_256_CBC_SHA            0x0300003A
* #define TLS12_CK_ADH_AES_128_CBC_SHA256         0x0300006C
* #define TLS12_CK_ADH_AES_256_CBC_SHA256         0x0300006D
* 
* #define TLS12_CK_RSA_NULL_MD5                   0x03000001
* #define TLS12_CK_RSA_NULL_SHA                   0x03000002
* #define TLS12_CK_RSA_NULL_SHA256                0x0300003B
* #define TLS12_CK_RSA_RC4_128_MD5                0x03000004
* #define TLS12_CK_RSA_RC4_128_SHA                0x03000005
* #define TLS12_CK_RSA_3DES_EDE_CBC_SHA           0x0300000A
* #define TLS12_CK_RSA_AES_128_CBC_SHA            0x0300002F
* #define TLS12_CK_RSA_AES_256_CBC_SHA            0x03000035
* #define TLS12_CK_RSA_AES_128_CBC_SHA256         0x0300003C
* #define TLS12_CK_RSA_AES_256_CBC_SHA256         0x0300003D
* #define TLS12_CK_DHE_DSS_3DES_EDE_CBC_SHA       0x03000013
* #define TLS12_CK_DHE_RSA_3DES_EDE_CBC_SHA       0x03000016
* #define TLS12_CK_DHE_DSS_AES_128_CBC_SHA        0x03000032
* #define TLS12_CK_DHE_RSA_AES_128_CBC_SHA        0x03000033
* #define TLS12_CK_DHE_DSS_AES_256_CBC_SHA        0x03000038
* #define TLS12_CK_DHE_RSA_AES_256_CBC_SHA        0x03000039
* #define TLS12_CK_DHE_DSS_AES_128_CBC_SHA256     0x03000040
* #define TLS12_CK_DHE_RSA_AES_128_CBC_SHA256     0x03000067
* #define TLS12_CK_DHE_DSS_AES_256_CBC_SHA256     0x0300006A
* #define TLS12_CK_DHE_RSA_AES_256_CBC_SHA256     0x0300006B
* 
* 
* #define TLS12_TXT_ADH_RC4_128_MD5                  "ADH-RC4-MD5"
* #define TLS12_TXT_ADH_3DES_EDE_CBC_SHA         "ADH-DES-CBC3-SHA"
* #define TLS12_TXT_ADH_AES_128_CBC_SHA           "ADH-AES128-SHA"
* #define TLS12_TXT_ADH_AES_256_CBC_SHA           "ADH-AES256-SHA"
* #define TLS12_TXT_ADH_AES_128_CBC_SHA256      "ADH-AES128-SHA256"
* #define TLS12_TXT_ADH_AES_256_CBC_SHA256      "ADH-AES256-SHA256"
* 
* 
* #define TLS12_TXT_RSA_NULL_MD5                   "NULL-MD5"
* #define TLS12_TXT_RSA_NULL_SHA                   "NULL-SHA"
* #define TLS12_TXT_RSA_NULL_SHA256                "NULL-SHA256"
* #define TLS12_TXT_RSA_RC4_128_MD5                "RC4-MD5"
* #define TLS12_TXT_RSA_RC4_128_SHA                "RC4-SHA"
* #define TLS12_TXT_RSA_3DES_EDE_CBC_SHA           "DES-CBC3-SHA"
* #define TLS12_TXT_RSA_AES_128_CBC_SHA            "AES128-SHA"
* #define TLS12_TXT_RSA_AES_256_CBC_SHA            "AES256-SHA"
* #define TLS12_TXT_RSA_AES_128_CBC_SHA256         "AES128-SHA256"
* #define TLS12_TXT_RSA_AES_256_CBC_SHA256         "AES256-SHA256"
* #define TLS12_TXT_DHE_DSS_3DES_EDE_CBC_SHA       "EDH-DSS-DES-CBC3-SHA"
* #define TLS12_TXT_DHE_RSA_3DES_EDE_CBC_SHA       "EDH-RSA-DES-CBC3-SHA"
* #define TLS12_TXT_DHE_DSS_AES_128_CBC_SHA        "DHE-DSS-AES128-SHA"
* #define TLS12_TXT_DHE_RSA_AES_128_CBC_SHA        "DHE-RSA-AES128-SHA"
* #define TLS12_TXT_DHE_DSS_AES_256_CBC_SHA        "DHE-DSS-AES256-SHA"
* #define TLS12_TXT_DHE_RSA_AES_256_CBC_SHA        "DHE-RSA-AES256-SHA"
* #define TLS12_TXT_DHE_DSS_AES_128_CBC_SHA256     "DHE-DSS-AES128-SHA256"
* #define TLS12_TXT_DHE_RSA_AES_128_CBC_SHA256     "DHE-RSA-AES128-SHA256"
* #define TLS12_TXT_DHE_DSS_AES_256_CBC_SHA256  "DHE-DSS-AES256-SHA256"
* #define TLS12_TXT_DHE_RSA_AES_256_CBC_SHA256  "DHE-RSA-AES256-SHA256"
* 
* //Anonymous ciphers
* 
* 
* #define TLS_CT_RSA_SIGN			1
* #define TLS_CT_DSS_SIGN			2
* #define TLS_CT_RSA_FIXED_DH		3
* #define TLS_CT_DSS_FIXED_DH		4
* #define TLS_CT_ECDSA_SIGN		5
* #define TLS_CT_RSA_FIXED_ECDH		6
* #define TLS_CT_ECDSA_FIXED_ECDH 	7
* #define TLS_CT_NUMBER			7
* 
* #define TLS12_FINISH_MAC_LENGTH		12
* 
* #define TLS_MD_MAX_CONST_SIZE				20
* #define TLS_MD_CLIENT_FINISH_CONST			"client finished"
* #define TLS_MD_CLIENT_FINISH_CONST_SIZE		15
* #define TLS_MD_SERVER_FINISH_CONST			"server finished"
* #define TLS_MD_SERVER_FINISH_CONST_SIZE		15
* #define TLS_MD_SERVER_WRITE_KEY_CONST		"server write key"
* #define TLS_MD_SERVER_WRITE_KEY_CONST_SIZE	16
* #define TLS_MD_KEY_EXPANSION_CONST			"key expansion"
* #define TLS_MD_KEY_EXPANSION_CONST_SIZE		13
* #define TLS_MD_CLIENT_WRITE_KEY_CONST		"client write key"
* #define TLS_MD_CLIENT_WRITE_KEY_CONST_SIZE	16
* #define TLS_MD_IV_BLOCK_CONST				"IV block"
* #define TLS_MD_IV_BLOCK_CONST_SIZE			8
* #define TLS_MD_MASTER_SECRET_CONST			"master secret"
* #define TLS_MD_MASTER_SECRET_CONST_SIZE		13
* 
* #ifdef CHARSET_EBCDIC
* #undef TLS_MD_CLIENT_FINISH_CONST
* #define TLS_MD_CLIENT_FINISH_CONST    
                "\x63\x6c\x69\x65\x6e\x74\x20\x66\x69\x6e\x69\x73\x68\x65\x64" 
* #undef TLS_MD_SERVER_FINISH_CONST
* #define TLS_MD_SERVER_FINISH_CONST    
                "\x73\x65\x72\x76\x65\x72\x20\x66\x69\x6e\x69\x73\x68\x65\x64" 
* #undef TLS_MD_SERVER_WRITE_KEY_CONST
* #define TLS_MD_SERVER_WRITE_KEY_CONST 
            "\x73\x65\x72\x76\x65\x72\x20\x77\x72\x69\x74\x65\x20\x6b\x65\x79"
* #undef TLS_MD_KEY_EXPANSION_CONST
* #define TLS_MD_KEY_EXPANSION_CONST    
                "\x6b\x65\x79\x20\x65\x78\x70\x61\x6e\x73\x69\x6f\x6e"
* #undef TLS_MD_CLIENT_WRITE_KEY_CONST
* #define TLS_MD_CLIENT_WRITE_KEY_CONST 
            "\x63\x6c\x69\x65\x6e\x74\x20\x77\x72\x69\x74\x65\x20\x6b\x65\x79"
* #undef TLS_MD_IV_BLOCK_CONST
* #define TLS_MD_IV_BLOCK_CONST         
                "\x49\x56\x20\x62\x6c\x6f\x63\x6b"
* #undef TLS_MD_MASTER_SECRET_CONST
* #define TLS_MD_MASTER_SECRET_CONST    
                "\x6d\x61\x73\x74\x65\x72\x20\x73\x65\x63\x72\x65\x74"
* #endif
* 
* 
* #define IPSI_TLS12_MAX_NUM_SIGN_HASH_ALG    18
* @endcode
*/


#define TLS12_VERSION			0x0303
#define TLS12_VERSION_MAJOR		0x03
#define TLS12_VERSION_MINOR		0x03

//Anonymous ciphers

#define TLS12_CK_ADH_RC4_128_MD5                0x03000018
#define TLS12_CK_ADH_3DES_EDE_CBC_SHA           0x0300001B
#define TLS12_CK_ADH_AES_128_CBC_SHA            0x03000034
#define TLS12_CK_ADH_AES_256_CBC_SHA            0x0300003A
#define TLS12_CK_ADH_AES_128_CBC_SHA256         0x0300006C
#define TLS12_CK_ADH_AES_256_CBC_SHA256         0x0300006D

#define TLS12_CK_RSA_NULL_MD5                   0x03000001
#define TLS12_CK_RSA_NULL_SHA                   0x03000002
#define TLS12_CK_RSA_NULL_SHA256                0x0300003B
#define TLS12_CK_RSA_RC4_128_MD5                0x03000004
#define TLS12_CK_RSA_RC4_128_SHA                0x03000005
#define TLS12_CK_RSA_3DES_EDE_CBC_SHA           0x0300000A
#define TLS12_CK_RSA_AES_128_CBC_SHA            0x0300002F
#define TLS12_CK_RSA_AES_256_CBC_SHA            0x03000035
#define TLS12_CK_RSA_AES_128_CBC_SHA256         0x0300003C
#define TLS12_CK_RSA_AES_256_CBC_SHA256         0x0300003D
#define TLS12_CK_DHE_DSS_3DES_EDE_CBC_SHA       0x03000013
#define TLS12_CK_DHE_RSA_3DES_EDE_CBC_SHA       0x03000016
#define TLS12_CK_DHE_DSS_AES_128_CBC_SHA        0x03000032
#define TLS12_CK_DHE_RSA_AES_128_CBC_SHA        0x03000033
#define TLS12_CK_DHE_DSS_AES_256_CBC_SHA        0x03000038
#define TLS12_CK_DHE_RSA_AES_256_CBC_SHA        0x03000039
#define TLS12_CK_DHE_DSS_AES_128_CBC_SHA256     0x03000040
#define TLS12_CK_DHE_RSA_AES_128_CBC_SHA256     0x03000067
#define TLS12_CK_DHE_DSS_AES_256_CBC_SHA256     0x0300006A
#define TLS12_CK_DHE_RSA_AES_256_CBC_SHA256     0x0300006B


#define TLS12_TXT_ADH_RC4_128_MD5                  "ADH-RC4-MD5"
#define TLS12_TXT_ADH_3DES_EDE_CBC_SHA         "ADH-DES-CBC3-SHA"
#define TLS12_TXT_ADH_AES_128_CBC_SHA           "ADH-AES128-SHA"
#define TLS12_TXT_ADH_AES_256_CBC_SHA           "ADH-AES256-SHA"
#define TLS12_TXT_ADH_AES_128_CBC_SHA256      "ADH-AES128-SHA256"
#define TLS12_TXT_ADH_AES_256_CBC_SHA256      "ADH-AES256-SHA256"


#define TLS12_TXT_RSA_NULL_MD5                   "NULL-MD5"
#define TLS12_TXT_RSA_NULL_SHA                   "NULL-SHA"
#define TLS12_TXT_RSA_NULL_SHA256                "NULL-SHA256"
#define TLS12_TXT_RSA_RC4_128_MD5                "RC4-MD5"
#define TLS12_TXT_RSA_RC4_128_SHA                "RC4-SHA"
#define TLS12_TXT_RSA_3DES_EDE_CBC_SHA           "DES-CBC3-SHA"
#define TLS12_TXT_RSA_AES_128_CBC_SHA            "AES128-SHA"
#define TLS12_TXT_RSA_AES_256_CBC_SHA            "AES256-SHA"
#define TLS12_TXT_RSA_AES_128_CBC_SHA256         "AES128-SHA256"
#define TLS12_TXT_RSA_AES_256_CBC_SHA256         "AES256-SHA256"
#define TLS12_TXT_DHE_DSS_3DES_EDE_CBC_SHA       "EDH-DSS-DES-CBC3-SHA"
#define TLS12_TXT_DHE_RSA_3DES_EDE_CBC_SHA       "EDH-RSA-DES-CBC3-SHA"
#define TLS12_TXT_DHE_DSS_AES_128_CBC_SHA        "DHE-DSS-AES128-SHA"
#define TLS12_TXT_DHE_RSA_AES_128_CBC_SHA        "DHE-RSA-AES128-SHA"
#define TLS12_TXT_DHE_DSS_AES_256_CBC_SHA        "DHE-DSS-AES256-SHA"
#define TLS12_TXT_DHE_RSA_AES_256_CBC_SHA        "DHE-RSA-AES256-SHA"
#define TLS12_TXT_DHE_DSS_AES_128_CBC_SHA256     "DHE-DSS-AES128-SHA256"
#define TLS12_TXT_DHE_RSA_AES_128_CBC_SHA256     "DHE-RSA-AES128-SHA256"
#define TLS12_TXT_DHE_DSS_AES_256_CBC_SHA256  "DHE-DSS-AES256-SHA256"
#define TLS12_TXT_DHE_RSA_AES_256_CBC_SHA256  "DHE-RSA-AES256-SHA256"

//Anonymous ciphers

/* Begin */
#undef TLS_CT_RSA_SIGN
#undef TLS_CT_DSS_SIGN
#undef TLS_CT_RSA_FIXED_DH
#undef TLS_CT_DSS_FIXED_DH
#undef TLS_CT_ECDSA_SIGN
#undef TLS_CT_RSA_FIXED_ECDH
#undef TLS_CT_ECDSA_FIXED_ECDH
#undef TLS_CT_NUMBER

#undef TLS12_FINISH_MAC_LENGTH

#undef TLS_MD_MAX_CONST_SIZE
#undef TLS_MD_CLIENT_FINISH_CONST
#undef TLS_MD_CLIENT_FINISH_CONST_SIZE
#undef TLS_MD_SERVER_FINISH_CONST
#undef TLS_MD_SERVER_FINISH_CONST_SIZE
#undef TLS_MD_SERVER_WRITE_KEY_CONST
#undef TLS_MD_SERVER_WRITE_KEY_CONST_SIZE
#undef TLS_MD_KEY_EXPANSION_CONST
#undef TLS_MD_KEY_EXPANSION_CONST_SIZE
#undef TLS_MD_CLIENT_WRITE_KEY_CONST
#undef TLS_MD_CLIENT_WRITE_KEY_CONST_SIZE
#undef TLS_MD_IV_BLOCK_CONST
#undef TLS_MD_IV_BLOCK_CONST_SIZE
#undef TLS_MD_MASTER_SECRET_CONST
#undef TLS_MD_MASTER_SECRET_CONST_SIZE

/* End */


#define TLS_CT_RSA_SIGN			1
#define TLS_CT_DSS_SIGN			2
#define TLS_CT_RSA_FIXED_DH		3
#define TLS_CT_DSS_FIXED_DH		4
#define TLS_CT_ECDSA_SIGN		5
#define TLS_CT_RSA_FIXED_ECDH		6
#define TLS_CT_ECDSA_FIXED_ECDH 	7
#define TLS_CT_NUMBER			7

#define TLS12_FINISH_MAC_LENGTH		12

#define TLS_MD_MAX_CONST_SIZE				20
#define TLS_MD_CLIENT_FINISH_CONST			"client finished"
#define TLS_MD_CLIENT_FINISH_CONST_SIZE		15
#define TLS_MD_SERVER_FINISH_CONST			"server finished"
#define TLS_MD_SERVER_FINISH_CONST_SIZE		15
#define TLS_MD_SERVER_WRITE_KEY_CONST		"server write key"
#define TLS_MD_SERVER_WRITE_KEY_CONST_SIZE	16
#define TLS_MD_KEY_EXPANSION_CONST			"key expansion"
#define TLS_MD_KEY_EXPANSION_CONST_SIZE		13
#define TLS_MD_CLIENT_WRITE_KEY_CONST		"client write key"
#define TLS_MD_CLIENT_WRITE_KEY_CONST_SIZE	16
#define TLS_MD_IV_BLOCK_CONST				"IV block"
#define TLS_MD_IV_BLOCK_CONST_SIZE			8
#define TLS_MD_MASTER_SECRET_CONST			"master secret"
#define TLS_MD_MASTER_SECRET_CONST_SIZE		13

#ifdef CHARSET_EBCDIC
#undef TLS_MD_CLIENT_FINISH_CONST

/*client finished*/
#define TLS_MD_CLIENT_FINISH_CONST    
                "\x63\x6c\x69\x65\x6e\x74\x20\x66\x69\x6e\x69\x73\x68\x65\x64"

#undef TLS_MD_SERVER_FINISH_CONST

/*server finished*/
#define TLS_MD_SERVER_FINISH_CONST    
                "\x73\x65\x72\x76\x65\x72\x20\x66\x69\x6e\x69\x73\x68\x65\x64"
#undef TLS_MD_SERVER_WRITE_KEY_CONST

/*server write key*/
#define TLS_MD_SERVER_WRITE_KEY_CONST 
            "\x73\x65\x72\x76\x65\x72\x20\x77\x72\x69\x74\x65\x20\x6b\x65\x79"

#undef TLS_MD_KEY_EXPANSION_CONST

/*key expansion*/
#define TLS_MD_KEY_EXPANSION_CONST    
                "\x6b\x65\x79\x20\x65\x78\x70\x61\x6e\x73\x69\x6f\x6e"

#undef TLS_MD_CLIENT_WRITE_KEY_CONST

/*client write key*/
#define TLS_MD_CLIENT_WRITE_KEY_CONST 
            "\x63\x6c\x69\x65\x6e\x74\x20\x77\x72\x69\x74\x65\x20\x6b\x65\x79"

#undef TLS_MD_IV_BLOCK_CONST

/*IV block*/
#define TLS_MD_IV_BLOCK_CONST
                "\x49\x56\x20\x62\x6c\x6f\x63\x6b"

#undef TLS_MD_MASTER_SECRET_CONST

/*master secret*/
#define TLS_MD_MASTER_SECRET_CONST
                "\x6d\x61\x73\x74\x65\x72\x20\x73\x65\x63\x72\x65\x74"
#endif

 /**
* @defgroup TLS_EXTNS_MODE_E
* @ingroup sslEnum
* @par Description
* 
* @par Prototype
* @code
* typedef enum enTLSExtnsMode
* {
*     TLS_SET_EXTENSION = 0,    
*     TLS_APPEND_EXTENSION     
* }TLS_EXTNS_MODE_E;
* @endcode
* @datastruct TLS_SET_EXTENSION To overwrite the old value
* @datastruct TLS_APPEND_EXTENSION Append toexisting extension
*/
typedef enum enTLSExtnsMode
{
    TLS_SET_EXTENSION = 0,    // to overwrite the old value 
    TLS_APPEND_EXTENSION      // Append to existing extension
}TLS_EXTNS_MODE_E;

#define IPSI_TLS12_MAX_NUM_SIGN_HASH_ALG    18

 /**
* @defgroup IPSI_TLS12_SIGN_HASH_S
* @ingroup sslStructures
* @par Description
* 
* @par Prototype
* @code
* typedef struct stIpsiT12SignHash
* {
*     SEC_UCHAR ucHash;
*     SEC_UCHAR ucSign;
* }IPSI_TLS12_SIGN_HASH_S;
* @endcode
* @datastruct ucHash Contains hash algorithm id (RFC5246 defined value)
* @datastruct ucSign Contains sign algorithm id (RFC5246 defined value)
*/
typedef struct stIpsiT12SignHash
{
    SEC_UCHAR ucHash;
    SEC_UCHAR ucSign;
}IPSI_TLS12_SIGN_HASH_S;

 /**
* @defgroup IPSI_TLS12_SUPPORTED_SIGN_HASH_S
* @ingroup sslStructures
* @par Description
* 
* @par Prototype
* @code
* typedef struct stIpsiT12SignSupported
* {
*     SEC_UINT uiValidEntry;
*     IPSI_TLS12_SIGN_HASH_S astSignHash[ IPSI_TLS12_MAX_NUM_SIGN_HASH_ALG ];
* }IPSI_TLS12_SUPPORTED_SIGN_HASH_S;
* @endcode
* @datastruct uiValidEntry Contains the number of supported sign/hash pairs
* @datastruct astSignHash Contains sign/hash pairs
*/
typedef struct stIpsiT12SignSupported
{
    SEC_UINT uiValidEntry;
    IPSI_TLS12_SIGN_HASH_S astSignHash[IPSI_TLS12_MAX_NUM_SIGN_HASH_ALG];
}IPSI_TLS12_SUPPORTED_SIGN_HASH_S;

#define MAX_NUM_HASH_CONTEXT 6

#ifdef  __cplusplus
}
#endif

#endif // IPSI_NO_TLS12

#endif//__IPSI_TLS12_H__




