/* ssl/ssl.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL_S implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL_S.
 * 
 * This library is free for commercial and non-commercial use as SEC_UINT32 as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL_S code.  The SSL_S documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
/* ====================================================================
 * Copyright (c) 1998-2001 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */
/* ====================================================================
 * Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 * ECC cipher suite support in OpenSSL originally developed by 
 * SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
 */

#include "ipsi_ssl_build_conf.h"

#ifndef _IPSI_HEADER_SSL_H 
#define _IPSI_HEADER_SSL_H 

#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_crypto.h"
#include "sec_def.h"
#include "sec_list.h"
#include "asn-types.h"
#include "x509_basictypes.h"
#include "tls_x509.h"
#include "tls_x509verify.h"
#include "ssl_sock.h"

#include "ssl2.h"
#include "ssl3.h"
#include "tls1.h"
#include "tls11.h"
#include "ssl23.h"
#include "tls12.h"
#include "tls_context.h"

#ifdef IPSI_SSL_NO_SSL
#define SSL_NO_TLSEXT
#endif

#ifndef IPSI_SSL_NO_DTLS
#include "ipsi_aio.h"


#endif

#ifdef  __cplusplus
extern "C" {
#endif

/* Mostly for SSLv3 */
#define SSL_PKEY_RSA_ENC    0
#define SSL_PKEY_RSA_SIGN    1
#define SSL_PKEY_DSA_SIGN    2
#define SSL_PKEY_DH_RSA        3
#define SSL_PKEY_DH_DSA        4
#define SSL_PKEY_ECC        5
#define SSL_PKEY_NUM        6

//#defines to solve the iMAP problem - Start
#define SSL_new IPSI_SSL_new
#define SSL_clear IPSI_SSL_clear 
#define SSL_state IPSI_SSL_state
#define SSL_write IPSI_SSL_write
#define SSL_read IPSI_SSL_read
#define SSL_accept IPSI_SSL_accept
#define SSL_pending IPSI_SSL_pending
#define SSL_free IPSI_SSL_free
#define SSL_peek IPSI_SSL_peek
#define SSL_want IPSI_SSL_want
#define SSL_connect IPSI_SSL_connect
#define SSL_shutdown IPSI_SSL_shutdown
#define SSL_ctrl IPSI_SSL_ctrl
#define TLSv1_method IPSI_TLSv1_method
#define SSLv3_method IPSI_SSLv3_method
#define SSLv2_method IPSI_SSLv2_method
#define SSL_dup IPSI_SSL_dup
#define SSL_renegotiate IPSI_SSL_renegotiate
#define SSL_renegotiate_pending IPSI_SSL_renegotiate_pending
#define SSL_version IPSI_SSL_version
//#defines to solve the IMAP problem - End

/* SSLeay version number for ASN.1 encoding of the session information */
/* Version 0 - initial version
 * Version 1 - added the optional peer certificate
 */
#define SSL_SESSION_ASN1_VERSION        0x0001


/* Sindhu : Added TLS_SUCCESS */
#define TLS_SUCCESS                     1

/* Text Strings for the SSLv2 ciphers */
#define SSL_TXT_RC4_128_WITH_MD5                SSL2_TXT_RC4_128_WITH_MD5       
#define SSL_TXT_RC4_128_EXPORT40_WITH_MD5       SSL2_TXT_RC4_128_EXPORT40_WITH_MD5  
#define SSL_TXT_DES_64_CBC_WITH_MD5             SSL2_TXT_DES_64_CBC_WITH_MD5        
#define SSL_TXT_DES_192_EDE3_CBC_WITH_MD5       SSL2_TXT_DES_192_EDE3_CBC_WITH_MD5  

#define SSL_MAX_SSL_SESSION_ID_LENGTH           32
#define SSL_MAX_SID_CTX_LENGTH                  32

#define SSL_MIN_RSA_MODULUS_LENGTH_IN_BYTES     (512/8)
#define SSL_MAX_KEY_ARG_LENGTH                  8
#define SSL_MAX_MASTER_KEY_LENGTH               48
/*Used to specify the Maximum permitted lengths for PSK and PSK Identity */
#if (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))
#define MAX_PSK_LEN           64
#define MAX_PSK_IDENTITY_LEN  128
#endif

/* These are used to specify which ciphers to use and not to use */
#define SSL_TXT_LOW                             "LOW"
#define SSL_TXT_MEDIUM                          "MEDIUM"
#define SSL_TXT_HIGH                            "HIGH"

#define SSL_TXT_aNULL                           "aNULL"
#define SSL_TXT_eNULL                           "eNULL"
#define SSL_TXT_NULL                            "SEC_NULL"

#define SSL_TXT_kRSA                            "kRSA"
#define SSL_TXT_kDHr                            "kDHr"
#define SSL_TXT_kDHd                            "kDHd" 
#define SSL_TXT_kEDH                            "kEDH"
#if (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))
#define SSL_TXT_kPSK                            "kPSK"
#define SSL_TXT_aPSK                            "aPSK"
#define SSL_TXT_PSK                             "PSK"
#endif

#ifndef SSL_NO_DH_PSK
#define SSL_TXT_kDHPSK                          "kDHPSK"
#define SSL_TXT_aDHPSK                          "aDHPSK"
#define SSL_TXT_PSKDH                           "PSKDH"
#endif
#define SSL_TXT_aRSA                            "aRSA"
#define SSL_TXT_aDSS                            "aDSS"
#define SSL_TXT_aDH                             "aDH"
#define SSL_TXT_DSS                             "DSS"
#define SSL_TXT_DH                              "DH"
#define SSL_TXT_EDH                             "EDH"
#define SSL_TXT_ADH                             "ADH"
#define SSL_TXT_RSA                             "RSA"
#define SSL_TXT_DES                             "DES"
#define SSL_TXT_3DES                            "3DES"
#define SSL_TXT_RC4                             "RC4"
#define SSL_TXT_AES                             "AES"
#define SSL_TXT_MD5                             "MD5"
#define SSL_TXT_SHA1                            "SHA1"
#define SSL_TXT_SHA                             "SHA"
#define SSL_TXT_EXP                             "EXP"
#define SSL_TXT_EXPORT                          "EXPORT"
#define SSL_TXT_EXP40                           "EXPORT40"
#define SSL_TXT_EXP56                           "EXPORT56"
#define SSL_TXT_SSLV2                           "SSLv2"
#define SSL_TXT_SSLV3                           "SSLv3"
#define SSL_TXT_TLSV1                           "TLSv1"
#define SSL_TXT_ALL                             "ALL"
#define SSL_TXT_ECC                             "ECCdraft" /* ECC ciphersuites are not yet official */

#ifndef IPSI_SSL_NO_DTLS
#define SSL_TXT_DTLSV1                             "DTLSv1"
#endif

/*
 * COMPLEMENTOF* definitions. These identifiers are used to (de-select)
 * ciphers normally not being used.
 * Example: "RC4" will activate all ciphers using RC4 including ciphers
 * without authentication, which would normally disabled by DEFAULT (due
 * the "!ADH" being part of default). Therefore "RC4:!COMPLEMENTOFDEFAULT"
 * will make sure that it is also disabled in the specific selection.
 * COMPLEMENTOF* identifiers are portable between version, as adjustments
 * to the default cipher setup will also be included here.
 *
 * COMPLEMENTOFDEFAULT does not experience the same special treatment that
 * DEFAULT gets, as only selection is being done and no sorting as needed
 * for DEFAULT.
 */
#define SSL_TXT_CMPALL                  "COMPLEMENTOFALL"
#define SSL_TXT_CMPDEF                  "COMPLEMENTOFDEFAULT"


SSLLINKDLL extern const int ssl_default_cipher_list[];
SSLLINKDLL extern const int ssl_default_cipher_list_sz;
SSLLINKDLL extern const int ssl2_cipher_list[];
SSLLINKDLL extern const int ssl2_cipher_list_sz;
SSLLINKDLL extern const int ssl3_cipher_list[];
SSLLINKDLL extern const int ssl3_cipher_list_sz;
SSLLINKDLL extern const int tls1_cipher_list[];
SSLLINKDLL extern const int tls1_cipher_list_sz;
SSLLINKDLL extern const int tls11_cipher_list[];
SSLLINKDLL extern const int tls11_cipher_list_sz;
#ifndef IPSI_NO_TLS12
SSLLINKDLL extern const int IPSI_tls12_cipher_list[];
SSLLINKDLL extern const int IPSI_tls12_cipher_list_sz;
#endif

#ifndef IPSI_SSL_NO_DTLS
SSLLINKDLL extern const int dtls1_cipher_list[];
SSLLINKDLL extern const int dtls1_cipher_list_sz;
#endif

#define SSL_DEFAULT_CIPHER_LIST     ssl_default_cipher_list
#define SSL_DEFAULT_CIPHER_LIST_SZ  ssl_default_cipher_list_sz
#define SSL2_CIPHER_LIST        ssl2_cipher_list
#define SSL2_CIPHER_LIST_SZ     ssl2_cipher_list_sz
#define SSL3_CIPHER_LIST        ssl3_cipher_list
#define SSL3_CIPHER_LIST_SZ     ssl3_cipher_list_sz
#define TLS1_CIPHER_LIST        tls1_cipher_list
#define TLS1_CIPHER_LIST_SZ     tls1_cipher_list_sz
#define TLS11_CIPHER_LIST       tls11_cipher_list
#define TLS11_CIPHER_LIST_SZ    tls11_cipher_list_sz
#ifndef IPSI_NO_TLS12
#define IPSI_TLS12_CIPHER_LIST IPSI_tls12_cipher_list
#define IPSI_TLS12_CIPHER_LIST_SZ IPSI_tls12_cipher_list_sz
#endif

#ifndef IPSI_SSL_NO_DTLS
#define DTLS1_CIPHER_LIST        dtls1_cipher_list
#define DTLS1_CIPHER_LIST_SZ     dtls1_cipher_list_sz
#endif


#define SSL_SENT_SHUTDOWN                   1
#define SSL_RECEIVED_SHUTDOWN               2

#if (defined(SSL_NO_RSA) || defined(SSL_NO_MD5)) && !defined(SSL_NO_SSL2)
#define SSL_NO_SSL2
#endif

#define SSL_FILETYPE_ASN1               X509_FILETYPE_ASN1
#define SSL_FILETYPE_PEM                X509_FILETYPE_PEM

#define SSL_FILETYPE_PFX                X509_FILETYPE_PFX

#if (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))

/* Macro used to set PSK callback function for client to get PSK and
 * PSK length.
 * As psk_server_callback is an attribute for both SSL_S and 
 * SSL_CTX_S structures, this macro can be used to set callback
 * function for both SLS_S structure and SSL_CTX_S structure */
#define SSL_CLIENT_PSKSEARCH(ssl,cb)       ((ssl)->psk_client_callback = (cb))

/* Macro used to set PSK callback function for server to get PSK 
 * identity, PSK Idenity length, PSK and PSK length 
 * As psk_client_callback is an attribute for both SSL_S and 
 * SSL_CTX_S structures, this macro can be used to set callback
 * function for both SLS_S structure and SSL_CTX_S structure */
#define SSL_SERVER_PSKSEARCH(ssl,cb)       ((ssl)->psk_server_callback = (cb))

/*  This macro is used to set callback function for PSK search 
    As pfGetPskByPskId_cb is an attribute for both SSL_S and SSL_CTX_S structure,
    this macro can be used to set call back function for both SSL_S structure
    and SSL_CTX_S structure */

/* Note : Usage of Macro SSL_PSKSEARCH is depreciated. For new PSK users,
 * suggested to use SSL_CLIENT_PSKSEARCH and SSL_SERVER_PSKSEARCH.
 * Maintaining below macro for existing customers */
#define SSL_PSKSEARCH(ssl,cb)		((ssl)->pfGetPskByPskId_cb = (cb))
#endif

/* This macro is used to check whether Sever listen mode is finshed or not. DTLS Server listen mode means server
 * recieved client hello and its going to process it. This will return SEC_TRUE after received second client hello 
 * message with cookie, if cookie exchange is used. Otherwise this will return SEC_TRUE just after recieved first
 * client hello. This is required for doing non blocking socket connection. */
#define IPSI_DTLS_IS_SERVER_LISTEN_FINISHED(pstSSL) \
  (((pstSSL != SEC_NULL) && (SSL_GET_MODE(pstSSL) & (SEC_UINT32)SSL_MODE_DTLS_LISTEN_FINISHED)) ? SEC_TRUE : SEC_FALSE)


/* The stTLSSessionExtn structure is contained within the SSL_S  &
 SSL_SESSION_S structures & holds the TLS extensions related data */
struct stTLSSessionExtn;

/* The stTLSSessionExtn structure is contained within the CTX &
 session structures & holds the CTX level (global) TLS extensions related data. */
struct stTLSExtension;

/* 
structure which represents the context of compression. 
*/
typedef struct comp_ctx_st COMP_CTX_S;

/* This is needed to stop compilers complaining about the
 * 'struct ssl_st *' function parameters used to prototype callbacks
 * in SSL_CTX_S. */
typedef struct stSSL *ssl_crock_st;

typedef void * COMP_EX_CTX;/* User/library specific context for compression */

/* 1. This renegotiation managment callback function has to return SEC_SUCCESS if user wants to allow the 
* renegotiation. Or else it has to return SSL_CTRL_BEHAV_NORENEG_FATAL or SSL_CTRL_BEHAV_NORENEG_WARN
* for rejecting renegotiation with fatal or warning alert. Any other value returns from this callback will be considered
* as SEC_SUCCESS only. But its strongly recommended to implement this callback by returning any of these 3 values
* because in future we will be expanding the usage of this callback function for some other feature also.
* 2. ACESSL doesn`t supports  SSL_CTRL_BEHAV_NORENEG_WARN, so if this callback function returns
* SSL_CTRL_BEHAV_NORENEG_WARN in ACESSL, then it treats this as SSL_CTRL_BEHAV_NORENEG_FATAL only.
* 3. SSLv3 RFC mandates to send only fatal alert for rejecting renegotiation. So if negotiated version is SSLv3 and 
* callback returns SSL_CTRL_BEHAV_NORENEG_WARN then renegotiation will be rejected with fatal alert. But
* other versions (TLS 1.0, TLS 1.1 and TLS 1.2) can send both warning and fatal alert. 
* 4. SSL_CTRL_BEHAV_NORENEG_FATAL and SSL_CTRL_BEHAV_NORENEG_WARN can be set as control behaviour options also using
* SSL_SET_BEHAVIOUR_OPTIONS or SSL_CTX_SET_BEHAVIOUR_OPTIONS. If both control behaviour option and this callback are
* set then only callback will be considered, control behaviour option will not be considered. */


typedef SEC_UINT (*IPSI_SSL_RENEG_MANAG_CB)(struct stSSL *, SEC_VOID *);

typedef SEC_INT(*SSLSOCKREAD_CB)(SEC_SOCK, SEC_INT8 *, SEC_INT, SEC_INT);
typedef SEC_INT(*SSLSOCKWRITE_CB)(SEC_SOCK, const SEC_INT8 *, SEC_INT, SEC_INT);

typedef SEC_INT (*IPSISSLSOCKREAD_CB)(SEC_SOCK, SEC_CHAR*, SEC_INT , SEC_VOID*, SEC_INT*);
typedef SEC_INT (*IPSISSLSOCKWRITE_CB)(SEC_SOCK, const SEC_CHAR*, SEC_INT , SEC_VOID*, SEC_INT*);
//New typedefs for send/recv or read/write socket functions callback with providing the facility to send Userdata - End by Jay/Shiva - Begin

/**
* @defgroup ssl
* This section contains all the ssl Enum, Structures, and Functions.
*/

/**
* @defgroup sslEnum
* @ingroup ssl
* This section contains the ssl Enum.
*/

/**
* @defgroup sslStructures
* @ingroup ssl
* This section contains all the ssl Structures.
*/

/** 
* @defgroup sslFunctions
* @ingroup ssl
* This section contains common ssl Functions.
*/

/** 
* @defgroup sslContextFunctions
* @ingroup ssl
* This section contains all the functions related to SSL context.
*/

/** 
* @defgroup sslObjectFunctions
* @ingroup ssl
* This section contains all the functions related to SSL object.
*/

#ifndef IPSI_SSL_NO_DTLS

/*
Structure which holds read/Write AIO
*/
/**
* @defgroup IPSI_RWAIO_S
* @ingroup sslStructures
* @par Description
* Structure which holds read/Write AIO
* @par Prototype
* @code
* typedef struct stRWAIO
* {
*     //read AIO
*     IPSI_AIO_S *raio;
*     //write aio
*     IPSI_AIO_S *waio;
* }IPSI_RWAIO_S;

* @endcode
* @datastruct raio pointer to read AIO
* @datastruct waio pointer to write AIO
*/

//structure for read/write AIO
typedef struct stRWAIO
{

    //read AIO
    IPSI_AIO_S *raio;

    //write aio
    IPSI_AIO_S *waio;
}IPSI_RWAIO_S;


/*
Structure which holds application data for 
cookie generation and cookie verification 
*/
/**
* @defgroup IPSI_CB_APPDATA_S
* @ingroup sslStructures
* @par Description
* Structure which holds application data for 
* cookie generation and cookie verification 
* @par Prototype
* @code
* typedef struct stCBAppData
* {
*     SEC_VOID *pCookieGenAppData;
*     SEC_VOID *pCookieVerAppData;
* }IPSI_CB_APPDATA_S;

* @endcode
* @datastruct pCookieGenAppData pointer to cookie generation app data
* @datastruct pCookieVerAppData pointer to cookie verification app data
*/

//structure for storing appdata for cookie callback
typedef struct stCBAppData
{
    SEC_VOID *pCookieGenAppData;
    SEC_VOID *pCookieVerAppData;
}IPSI_CB_APPDATA_S;

#endif

/*
Structure which holds the details of Ciphers like name, type, pointer to compression & decompression
methods. 
*/
/**
* @defgroup COMP_METHOD_S
* @ingroup sslStructures
* @par Description
* This structure holds the details of Ciphers like name, type and pointer to compression and decompression methods.
* @par Prototype
* @code
* typedef struct comp_method_st
* {
*  int type;
*  const char *name;
*  int (*init)(COMP_EX_CTX *ctx);
*  void (*finish)(COMP_EX_CTX *ctx);
*  int (*compress)(COMP_EX_CTX *ctx,
*  unsigned char *out, unsigned int olen,
*  unsigned char *in, unsigned int ilen);
*  int (*expand)(COMP_EX_CTX *ctx,
*  unsigned char *out, unsigned int olen,
*  unsigned char *in, unsigned int ilen);
*  long (*ctrl)(void);
*  long (*callback_ctrl)(void);
* }COMP_METHOD_S;
* @endcode
* @datastruct type NID for compression library.
* @datastruct name A text string to identify the library.
* @datastruct init This is called for initialization of compression library.
* @datastruct finish This is called for final of compression library.
* @datastruct compress This is called for performing compression.
* @datastruct expand This is called for performing decompression.
* @datastruct ctrl This is kept for backward compatibility.
* @datastruct callback_ctrl This is also kept for backward compatibility.
*/
typedef struct comp_method_st
{
    int type;                           /* NID for compression library */
    const char *name;                   /* A text string to identify the library */
    int (*init)(COMP_EX_CTX *ctx);      /* This is called for init of compression library */
    void (*finish)(COMP_EX_CTX *ctx);   /* This is called for final of compression library */
    int (*compress)(COMP_EX_CTX *ctx,   /* This is called for performing compression */
            unsigned char *out, unsigned int olen,
            unsigned char *in, unsigned int ilen);
    int (*expand)(COMP_EX_CTX *ctx,     /* This is called for performing decompression */
              unsigned char *out, unsigned int olen,
              unsigned char *in, unsigned int ilen);
    /* The following two do NOTHING, but are kept for backward compatibility */
    long (*ctrl)(void);
    long (*callback_ctrl)(void);
} COMP_METHOD_S;


/* 
structure which represents the context of compression. 
*/
/**
* @defgroup COMP_CTX_S
* @ingroup sslStructures
* @par Description
* This structure represents the context of compression.
* @par Prototype
* @code
* struct comp_ctx_st
* {
*  COMP_METHOD_S *meth;
*  unsigned long compress_in;
*  unsigned long compress_out;
*  unsigned long expand_in;
*  unsigned long expand_out;
*  COMP_EX_CTX ex_ctx;
* };
* @endcode
* 
* @datastruct meth The method structure which is supplied by user.
* @datastruct compress_in The fields are for internal house keeping. DO NOT use
* @datastruct compress_out The fields are for internal house keeping. DO NOT use
* @datastruct expand_in The fields are for internal house keeping. DO NOT use
* @datastruct expand_out The fields are for internal house keeping. DO NOT use
* @datastruct ex_ctx Holds the context of compression library
*/
struct comp_ctx_st
{
    COMP_METHOD_S *meth;                /* The method structure which is supplied by user */
    unsigned long compress_in;          /* The fields are for internal house keeping. DO NOT use */
    unsigned long compress_out;         /* The fields are for internal house keeping. DO NOT use */
    unsigned long expand_in;                /* The fields are for internal house keeping. DO NOT use */
    unsigned long expand_out;               /* The fields are for internal house keeping. DO NOT use */


    COMP_EX_CTX ex_ctx;                 /* Holds the context of the compression library */
};



/* forward declaration of buffer memory structure */
struct buf_mem_st;

/* used to hold the information about the ciphers supported in each SSL object */
/**
* @defgroup SSL_CIPHER_S
* @ingroup sslStructures
* @par Description
* This structure is used to hold the information about the ciphers supported in each SSL object.
* @par Prototype
* @code
* typedef struct stSSLCipher
* {
*  SEC_INT iValid;
*  SEC_CHAR *pchName;
*  SEC_UINT32 ulID;
*  SEC_UINT32 ulAlgorithms;
*  SEC_UINT32 ulAlgoStrength;
*  SEC_UINT32 ulAlgorithm2;
*  SEC_INT iStrengthBits;
*  SEC_INT iAlgBits;
*  SEC_UINT32 ulMask;
*  SEC_UINT32 ulMaskStrength;
* }SSL_CIPHER_S;
* @endcode
* 
* @datastruct iValid Flag to check if the cipher is valid (1) or invalid (0).
* @datastruct pchName Cipher Name.
* @datastruct ulID ID 4 byte value used to identify ciphers.
* @datastruct ulAlgorithms Bit mask for algorithms.
* @datastruct ulAlgoStrength Strength and Export flags.
* @datastruct ulAlgorithm2 Extra flags.
* @datastruct iStrengthBits Number of bits really used.
* @datastruct iAlgBits Number of bits for algorithm.
* @datastruct ulMask Used for masking.
* @datastruct ulMaskStrength Also used for masking.
*/
typedef struct stSSLCipher
{
    SEC_INT         iValid;             /* Flag to check if the cipher is valid (1) or invalid (0) */
    SEC_CHAR        *pchName;           /* Cipher Name */
    SEC_UINT32      ulID;               /* id, 4 byte value used to identify ciphers */
    SEC_UINT32      ulAlgorithms;       /* bit mask for algorithms */
    SEC_UINT32      ulAlgoStrength;     /* Strength and Export flags */
    SEC_UINT32      ulAlgorithm2;       /* Extra flags */
    SEC_INT         iStrengthBits;      /* Number of bits really used */
    SEC_INT         iAlgBits;           /* Number of bits for algorithm */
    SEC_UINT32      ulMask;             /* used for masking */
    SEC_UINT32      ulMaskStrength;     /* also used for masking */

} SSL_CIPHER_S;

/*
SSL_S is a structure that represents the SSL object. SSL_S holds the information such as 
version, type, methods, Cipher, Contexts, states, etc. related to SSL. 
*/
struct stSSL;
/*
SSL_CTX_S represents the SSL Context . The context is used to hold all the configuration parameters 
that are specific to the particular context.  
*/
struct stSSLCtx;

/* This structure is used to hold functions for SSLv2 or SSLv3/TLSv1 functions */
/**
* @defgroup SSL_METHOD_S
* @ingroup sslStructures
* @par Description
* This structure is used to hold methods for SSLv2 or SSLv3/TLSv1 functions.
* @par Prototype
* @code
* typedef struct stSSLMethod
* {
*  SEC_INT iVersion; 
*  SEC_INT  (*pfSslNew) (struct stSSL *pstSSL); 
*  SEC_VOID (*pfSslClear) (struct stSSL *pstSSL); 
*  SEC_VOID (*pfSslFree) (struct stSSL *pstSSL);
*  SEC_INT   (*pfSslAccept) (struct stSSL *pstSSL);
*  SEC_INT  (*pfSslConnect) (struct stSSL *pstSSL);
*  SEC_INT  (*pfSslRead) (  struct stSSL *pstSSL, 
*                          SEC_VOID *buf, 
*                          SEC_INT iLen);
*  SEC_INT  (*pfSslPeek) (  struct stSSL *pstSSL, 
*                          SEC_VOID *buf, 
*                          SEC_INT iLen);
*  SEC_INT  (*pfSslWrite) ( struct stSSL *pstSSL, 
*                          const SEC_VOID *buf, 
*                          SEC_INT iLen);
*  SEC_INT  (*pfSslShutdown) (struct stSSL *pstSSL);
*  SEC_INT  (*pfSslRenegotiate) (struct stSSL *pstSSL);
*  SEC_INT  (*pfSslRenegotiateCheck) (struct stSSL *pstSSL);
*  SEC_INT32 (*pfSslGetMessage)(struct stSSL *pstSSL,
*                              SEC_INT iST1,
*                              SEC_INT iStn, 
*                              SEC_INT iMT,
*                              SEC_INT32 lMax,
*                              SEC_INT *iOk);
*  SEC_INT (*pfSslReadBytes) ( struct stSSL *pstSSL, 
*                             SEC_INT iType, 
*                             SEC_UCHAR *buf, 
*                             SEC_INT iLen, 
*                             SEC_INT peek);
*  SEC_INT (*pfSslWriteBytes) (struct stSSL *pstSSL, 
*                             SEC_INT iType, 
*                             const SEC_VOID *pbuf_, 
*                             SEC_INT iLen);
*  SEC_INT (*pfSslDispatchAlert) (struct stSSL *pstSSL);
*  SEC_INT32 (*pfSslCtrl)  (struct stSSL *pstSSL,
*                          SEC_INT iCmd,
*                          SEC_INT32 lArg,
*                          SEC_VOID *pArg);
*  SEC_INT32 (*pfSslCtxCtrl) ( struct stSSLCtx *pstContext,
*                             SEC_INT iCmd,
*                             SEC_INT32 lArg,
*                             SEC_VOID *pArg);
*  SSL_CIPHER_S *(*pfGetCipherByChar) (const SEC_UCHAR *pucPtr);
*  SEC_INT (*pfPutCipherByChar) ( const SSL_CIPHER_S *pstSSLCipher,
*                                SEC_UCHAR *pucPtr);
*  SEC_INT (*pfSslPending)  ( const struct stSSL *pstSSL);
*  SEC_INT (*pfNumCiphers) (SEC_VOID);
*  SSL_CIPHER_S *(*pfGetCipher) (unsigned uiCipher);
*  struct stSSLMethod *(*pfGetSslMethod) (SEC_INT version);
*  SEC_INT32 (*pfGetTimeout) (SEC_VOID);
*  struct stSSL3EncMethod *pstSSL3EncMethod; 
*  SEC_INT (*pfSslVersion) (SEC_VOID);
*  SEC_INT32 (*pfSslCtrl_cb)( struct stSSL *pstSSL, 
*                            SEC_INT iCallbackId, 
*                            SEC_VOID (*fp)(SEC_VOID));
*  SEC_INT32 (*pfSslCtxCtrl_cb) ( struct stSSLCtx *pstSSLContext, 
*                                SEC_INT iCallbackId, 
*                                SEC_VOID (*fp)(SEC_VOID));
* }SSL_METHOD_S;
* @endcode
* @datastruct iVersion Holds the version of SSL
* @datastruct pfSslNew Pointer to function which creates new SSL object
* @datastruct pfSslClear Pointer to function which resets SSL object to allow another connection
* @datastruct pfSslFree Pointer to function  which frees an allocated SSL structure
* @datastruct pfSslAccept Pointer to function which accepts the ssl connection.
* @datastruct pfSslConnect Pointer to function which initiates the ssl connection
* @datastruct pfSslRead Pointer to function which reads the data from the SSL connection.
* @datastruct pfSslPeek Pointer to function which copies the data in the SSL buffer into the buffer passed to this function
* @datastruct pfSslWrite Pointer to function which writes the data to the SSL connection.
* @datastruct pfSslShutdown Pointer to function which closes SSL connection.
* @datastruct pfSslRenegotiate Pointer to function which creates a new set of cipher keys for an existing  SSL session.
* @datastruct pfSslRenegotiateCheck Pointer to function which checks the renegotiation flag.
* @datastruct pfSslGetMessage Pointer to function which gets the message from the peer.
* @datastruct pfSslReadBytes Pointer to function which reads the message from the peer.
* @datastruct pfSslWriteBytes Pointer to function which writes the bytes to the peer entity.
* @datastruct pfSslDispatchAlert Pointer to function which dispatches the alert message.
* @datastruct pfSslCtrl Pointer to function which does control operations on SSL object.
* @datastruct pfSslCtxCtrl Pointer to function which does control operations on SSL context.
* @datastruct pfGetCipherByChar Pointer to function which gets cipher list by characters.
* @datastruct pfPutCipherByChar Pointer to function which puts the cipher list in char * format.
* @datastruct pfSslPending Pointer to function which returns the amount of data in the current SSL data record that is
* immediately available for reading on an SSL session.
* @datastruct pfNumCiphers Pointer to function which returns the number of ciphers.
* @datastruct pfGetCipher Pointer to function which gets the particular cipher.
* @datastruct pfGetSslMethod Pointer to function which gets the methods specific to the version.
* @datastruct pfGetTimeout Pointer to function which gets the time out value.
* @datastruct pstSSL3EncMethod Pointer to structure which contains various functions related to cryptographic operations, which are specific to
* the SSLv3 .
* @datastruct pfSslVersion Pointer to function which gets the SSL version.
* @datastruct pfSslCtrl_cb Pointer to function which sets the callback function for controlling SSL object.
* @datastruct pfSslCtxCtrl_cb Pointer to function which sets the callback function for controlling SSL context object.
*/
typedef struct stSSLMethod
{
    /*holds the version of SSL */
    SEC_INT iVersion; 
    
     /* pointer to function which creates new SSL object*/ 
    SEC_INT  (*pfSslNew) (struct stSSL *pstSSL); 

     /*pointer to Function which resets SSL object to allow another connection */
    SEC_VOID (*pfSslClear) (struct stSSL *pstSSL); 

     /*pointer to Function  which free an allocated SSL structure */     
    SEC_VOID (*pfSslFree) (struct stSSL *pstSSL);

     /*pointer to Function which accepts the connection.*/   
    SEC_INT  (*pfSslAccept) (struct stSSL *pstSSL);

      /*pointer to Function which initiates the ssl connection*/     
    SEC_INT  (*pfSslConnect) (struct stSSL *pstSSL);

     /*pointer to Function which reads the data from the SSL connection.*/   
    SEC_INT  (*pfSslRead) (  struct stSSL *pstSSL, 
                            SEC_VOID *buf, 
                            SEC_INT iLen);

       /*pointer to Function which Copy the data in the SSL buffer into the buffer passed to this function*/     
    SEC_INT  (*pfSslPeek) (  struct stSSL *pstSSL, 
                            SEC_VOID *buf, 
                            SEC_INT iLen);
       
     /*pointer to Function which write  the data to the SSL connection.*/    
    SEC_INT  (*pfSslWrite) ( struct stSSL *pstSSL, 
                            const SEC_VOID *buf, 
                            SEC_INT iLen);

     /*pointer to Function which closes SSL connection.*/    
    SEC_INT  (*pfSslShutdown) (struct stSSL *pstSSL);

     /*pointer to Function which creates a new set of cipher keys for an existing  SSL session.*/    
    SEC_INT  (*pfSslRenegotiate) (struct stSSL *pstSSL);

     /*pointer to Function which checks the renegotiation flag..*/   
    SEC_INT  (*pfSslRenegotiateCheck) (struct stSSL *pstSSL);

     /*pointer to Function which gets the message from the peer.*/   
    SEC_INT32 (*pfSslGetMessage)(struct stSSL *pstSSL,
                                 SEC_INT iST1,
                                 SEC_INT iStn, 
                                 SEC_INT iMT,
                                 SEC_INT32 lMax,
                                 SEC_INT *iOk);
     /*pointer to Function which reads the message from the peer.*/  
    SEC_INT (*pfSslReadBytes) ( struct stSSL *pstSSL, 
                                SEC_INT iType, 
                                SEC_UCHAR *buf, 
                                SEC_INT iLen, 
                                SEC_INT peek);

     /*pointer to Function which writes the bytes to the peer entity.*/  
    SEC_INT (*pfSslWriteBytes) (struct stSSL *pstSSL, 
                                SEC_INT iType, 
                                const SEC_VOID *pbuf_, 
                                SEC_INT iLen);
     /*pointer to Function which dispatches the alert message.*/     
    SEC_INT (*pfSslDispatchAlert) (struct stSSL *pstSSL);

     /*pointer to Function which does control operations on SSL object.*/    
    SEC_INT32 (*pfSslCtrl)  (struct stSSL *pstSSL,
                            SEC_INT iCmd,
                            SEC_INT32 lArg,
                            SEC_VOID *pArg);
     /*pointer to Function which does control operations on SSL context .*/  
    SEC_INT32 (*pfSslCtxCtrl) ( struct stSSLCtx *pstContext,
                                SEC_INT iCmd,
                                SEC_INT32 lArg,
                                SEC_VOID *pArg);
     /*pointer to Function which gets cipher list by chars.*/    
    SSL_CIPHER_S *(*pfGetCipherByChar) (const SEC_UCHAR *pucPtr);
     /*pointer to Function which puts the cipher list in char * format */    
    SEC_INT (*pfPutCipherByChar) ( const SSL_CIPHER_S *pstSSLCipher,
                                    SEC_UCHAR *pucPtr);
    /*pointer to Function which  returns the amount of data in the current SSL data record that 
        is immediately available for reading on an SSL session.*/    
    SEC_INT (*pfSslPending)  ( const struct stSSL *pstSSL);

    /*pointer to Function which returns the number of ciphers */     
    SEC_INT (*pfNumCiphers) (SEC_VOID);
    
    /*pointer to Function which gets the particular cipher*/     
    SSL_CIPHER_S *(*pfGetCipher) (unsigned uiCipher);

    /*pointer to Function which gets the methods specific to the version. */     
    struct stSSLMethod *(*pfGetSslMethod) (SEC_INT version);
    
    /*pointer to Function which gets the time out value */   
    SEC_INT32 (*pfGetTimeout) (SEC_VOID);

    /*pointer to structure contains various function related to encryption/crpto specific to the SSLv3 */    
    struct stSSL3EncMethod *pstSSL3EncMethod; /* Extra SSLv3/TLS stuff */

    /*pointer to Function which gets the SSL version*/   
    SEC_INT (*pfSslVersion) (SEC_VOID);
    
    /*pointer to Function which sets the callback function for controlling SSL object. */    
    SEC_INT32 (*pfSslCtrl_cb)( struct stSSL *pstSSL, 
                                    SEC_INT iCallbackId, 
                                    SEC_VOID (*fp)(SEC_VOID));
    
    /*pointer to Function which sets the callback function for controlling SSL context  object. */   
    SEC_INT32 (*pfSslCtxCtrl_cb) ( struct stSSLCtx *pstSSLContext, 
                                    SEC_INT iCallbackId, 
                                    SEC_VOID (*fp)(SEC_VOID));

} SSL_METHOD_S;


/* This structure represents an SSL session. It holds details like session ID, session 
 * certificate, compression method, cipher suite, application specific data, SSL version
 * and master key.
 */
/**
* @defgroup SSL_SESSION_S
* @ingroup sslStructures
* @par Description
* This structure represents an SSL session. It holds details like session ID, session certificate, compression method,
* cipher suite, application specific data, SSL version and master key.
* @par Prototype
* @code
* typedef struct stSSLSession
* {
*  SEC_INT iSSLVersion; 
*  SEC_UINT uiKeyArgLength;
*  SEC_UCHAR aucKeyArg [SSL_MAX_KEY_ARG_LENGTH];
*  SEC_INT iMasterKeyLength;
*  SEC_UCHAR aucMasterKey [SSL_MAX_MASTER_KEY_LENGTH];
*  SEC_UINT uiSessionIdLength;
*  SEC_UCHAR aucSessionID [SSL_MAX_SSL_SESSION_ID_LENGTH];
*  SEC_UINT uiSidCtxLength;
*  SEC_UCHAR aucSIDContext [SSL_MAX_SID_CTX_LENGTH];
*  SEC_INT iNotResumable;
*  struct stSess_Cert *pstSessCert;
*  X509_CERT_EXTENDED_S *pstPeerCert;
*  SEC_INT32 lVerifyResult;
*  SEC_INT iReferences;
*  SEC_INT32 lTimeout;
*  SEC_INT32 lTime;
*  SEC_INT iCompMethod;
*  SSL_CIPHER_S *pstSSLCipher;
*  SEC_UINT32 ulCipherId;
*  SEC_List_S *pCipherList;
*  struct stSSLSession *pstPrev, *pstNext;
*  #ifndef SSL_NO_TLSEXT
*  struct stTLSSessionExtn * pstTLSExtns;
*  #endif
* }SSL_SESSION_S;
* @endcode
* 
* @datastruct iSSLVersion Version of SSL. It can be SSLv2, SSLv3, TLS1.0 or TLS1.1
* @datastruct uiKeyArgLength Length of the key argument.
* @datastruct aucKeyArg Key argument.
* @datastruct iMasterKeyLength Length of the master key.
* @datastruct aucMasterKey Master Key.
* @datastruct uiSessionIdLength Length of session id.
* @datastruct aucSessionID Session ID.
* @datastruct uiSidCtxLength Length of Session id context.
* @datastruct aucSIDContext Session id context. It is up to the application to set this via SSL_ctxSetSessionIDContext
* or SSL_setSessionIDContext.
* @datastruct iNotResumable Flag to indicate whether the session is resumable or not.
* @datastruct pstSessCert This is the certificate used to establish this connection.
* @datastruct pstPeerCert This is the certificate for the other end. 
* @datastruct lVerifyResult The verify result for the session.
* @datastruct iReferences Number of references to current session.
* @datastruct lTimeout Timeout value.
* @datastruct lTime The time of the session created. It can be changed by SSL_sessionSetTime API.
* @datastruct iCompMethod The algorithm used to compress data prior to encryption. 
* @datastruct pstSSLCipher Cipher used by the current session.
* @datastruct ulCipherId The cipher's ID.
* @datastruct pCipherList List of ciphers send by the client side. For SSLv2, it is the list of shared ciphers.
* @datastruct pstPrev,pstNext These are used to make removal of session-ids more efficient and to implement a
* maximum cache size.
* @datastruct pstTLSExtns Holds the information about TLS extensions.
*/
typedef struct stSSLSession
{
    /* Version of SSL. It can be SSLv2, SSLv3, TLS1.0 or TLS1.1 */
    SEC_INT iSSLVersion;    

    /* Length of the key argument */
    SEC_UINT uiKeyArgLength;

    /* Key argument */
    SEC_UCHAR aucKeyArg [SSL_MAX_KEY_ARG_LENGTH];

    /* Length of the master key */
    SEC_INT iMasterKeyLength;

    /* Master Key */
    SEC_UCHAR aucMasterKey [SSL_MAX_MASTER_KEY_LENGTH];

    /* Length of session id */
    SEC_UINT uiSessionIdLength;

    /*  Session ID */
    SEC_UCHAR aucSessionID [SSL_MAX_SSL_SESSION_ID_LENGTH];

    /* This is used to determine whether the session is being reused in
      the appropriate context. It is up to the application to set this,
      via SSL_new */
    SEC_UINT uiSidCtxLength;

    /* Session id corresponding to the ssl context */
    SEC_UCHAR aucSIDContext [SSL_MAX_SID_CTX_LENGTH];

    /*  flag to indicate whether the session is resumable or not */
    SEC_INT iNotResumable;

    /* The cert is the certificate used to establish this connection */
    struct stSess_Cert *pstSessCert;

    /* This is the cert for the other end.
      On clients, it will be the same as pstSessCert->peer_key->x509
      (the latter is not enough as sess_cert is not retained
      in the external representation of sessions, see ssl_asn1.c). */
    X509_CERT_EXTENDED_S *pstPeerCert;

    /* When app_verify_callback accepts a session where the peer's certificate
      is not ok, we must remember the error for session reuse: */
    SEC_INT32 lVerifyResult; /* only for servers */

    /* Number  of references to current session */
    SEC_INT iReferences;

    /* Timeout value*/
    SEC_INT32 lTimeout;

    /* Holds the time set by SSL_sessionSetTime() API */
    SEC_INT32 lTime;

    /*The algorithm used to compress data prior to    encryption. Need to lookup the method */
    SEC_INT iCompMethod;        

    /* Cipher used by the current session*/
    SSL_CIPHER_S *pstSSLCipher;
                            
    /* When ASN.1 loaded, this needs to be used to load the 'SSL_CIPHER_S' structure */
    SEC_UINT32 ulCipherId;  

    /* List of shared ciphers */
    SEC_List_S *pCipherList; 

    /* These are used to make removal of session-ids more
      efficient and to implement a maximum cache size. */
    struct stSSLSession *pstPrev, *pstNext;

//#ifndef SSL_NO_TLSEXT
    /* Holds information about the TLS extensions */
    struct stTLSSessionExtn * pstTLSExtns;
//#endif

} SSL_SESSION_S;

/**
* @defgroup IPSI_SSL_CERTKEY_FILE_IN_PARAM_S
* @ingroup sslStructures
* @par Description
* This structure holds the certificate or key details such as,
* file, filetype(PEM, ASN1 or PFX), password and password length.
* @par Prototype
* @code
* typedef struct stIpsiSslCertKeyInputParam
* {
*     SEC_CHAR *pcFile;
*     SEC_INT iType;
*     SEC_CHAR *pcPasswd;
*     SEC_UINT uiPasswdLen;
* } IPSI_SSL_CERTKEY_FILE_IN_PARAM_S;
* @endcode
*
* @datastruct pcFile Pointer to the file.
* @datastruct iType Type of file.
* @datastruct pcPasswd Pointer to password.
* @datastruct uiPasswdLen Password length
*/
typedef struct stIpsiSslCertKeyInputParam
{
    SEC_CHAR *pcFile;
    SEC_INT iType;
    SEC_CHAR *pcPasswd;
    SEC_UINT uiPasswdLen;
} IPSI_SSL_CERTKEY_FILE_IN_PARAM_S;


/**
* @defgroup IPSI_SSL_CERTKEY_FILE_CONF_S
* @ingroup sslStructures
* @par Description
* This structure holds the certificate file and private key file configurations.
* @par Prototype
* @code
* typedef struct stIpsiSslCertKeyConfig
* {
*     IPSI_SSL_CERTKEY_FILE_IN_PARAM_S stCert;
*     IPSI_SSL_CERTKEY_FILE_IN_PARAM_S stKey;
* }IPSI_SSL_CERTKEY_FILE_CONF_S;
* @endcode
*
* @datastruct stCert Contains the configurations of the certificate.
* @datastruct stKey Contains the configurations of the private key.
*/
typedef struct stIpsiSslCertKeyConfig
{
    IPSI_SSL_CERTKEY_FILE_IN_PARAM_S stCert;
    IPSI_SSL_CERTKEY_FILE_IN_PARAM_S stKey;
}IPSI_SSL_CERTKEY_FILE_CONF_S;


/**
* @defgroup IPSI_SSL_CERTKEY_BUF_IN_PARAM_S
* @ingroup sslStructures
* @par Description
* This structure holds the certificate or private key buffer details such as
* certificate or key buffer, buffer length, buffer type (PEM, ASN1 or PFX),
* password and password length.
* @par Prototype
* @code
* typedef struct stIpsiSslCertKeyBufInputParam
* {
*     SEC_CHAR *pcBuf;
*     SEC_UINT uiBufLen;
*     SEC_INT iType;
*     SEC_CHAR *pcPasswd;
*     SEC_UINT uiPasswdLen;
} IPSI_SSL_CERTKEY_BUF_IN_PARAM_S;
* @endcode
*
* @datastruct pcBuf Pointer to the buffer.
* @datastruct uiBufLen Buffer length.
* @datastruct iType Type of buffer.
* @datastruct pcPasswd Pointer to the password.
* @datastruct uiPasswdLen Password length.
*/
typedef struct stIpsiSslCertKeyBufInputParam
{
    SEC_CHAR *pcBuf;
    SEC_UINT uiBufLen;
    SEC_INT iType;
    SEC_CHAR *pcPasswd;
    SEC_UINT uiPasswdLen;
} IPSI_SSL_CERTKEY_BUF_IN_PARAM_S;

/**
* @defgroup IPSI_SSL_CERTKEY_BUF_CONF_S
* @ingroup sslStructures
* @par Description
* This structure holds the certificate and private key buffer configurations.
* @par Prototype
* @code
* typedef struct stIpsiSslCertKeyBufConfig
* {
*     IPSI_SSL_CERTKEY_BUF_IN_PARAM_S stCert;
*     IPSI_SSL_CERTKEY_BUF_IN_PARAM_S stKey;
* }IPSI_SSL_CERTKEY_BUF_CONF_S;
* @endcode
*
* @datastruct stCert Contains the configurations of certificate buffer.
* @datastruct stKey Contains the configurations of private key buffer.
*/
typedef struct stIpsiSslCertKeyBufConfig
{
    IPSI_SSL_CERTKEY_BUF_IN_PARAM_S stCert;
    IPSI_SSL_CERTKEY_BUF_IN_PARAM_S stKey;
}IPSI_SSL_CERTKEY_BUF_CONF_S;

/* For options 0x00000008L and 0x00000040L are free. */

#define SSL_OP_MICROSOFT_SESS_ID_BUG            0x00000001L
#define SSL_OP_NETSCAPE_CHALLENGE_BUG           0x00000002L

/* Disable initial Handshake connection to servers / clients
 * that don't support RI(Secure renegotiation) extension */
#define SSL_OP_DISABLE_CONNECT_LEGACY_ENTITY           0x00000004L

/*#define SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG 0x00000008L*/
#define SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG      0x00000010L
#define SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER       0x00000020L

/*#define SSL_OP_MSIE_SSLV2_RSA_PADDING           0x00000040L*/ /* no effect since 0.9.7h and 0.9.8b */
#define SSL_OP_SSLEAY_080_CLIENT_DH_BUG         0x00000080L
#define SSL_OP_TLS_D5_BUG                       0x00000100L
#define SSL_OP_TLS_BLOCK_PADDING_BUG            0x00000200L

/* Disable SSL_S 3.0/TLS 1.0 CBC vulnerability workaround that was added
  in OpenSSL 0.9.6d.  Usually (depending on the application protocol)
  the workaround is not needed.  Unfortunately some broken SSL_S/TLS
  implementations cannot handle it at all, which is why we include
  it in SSL_OP_ALL.
  This option should be used only if really needed (to interoperate with a peer which doesn't recognizes 
  empty fragments) as it disables important vulnerability protection. It can be set either in the SSL Context 
  or SSL Object. If set in the SSL Object, it should be set strictly before the first handshake only. 
  The behavior of the SSL connection is undefined if the option is set either in the middle of the first handshake, 
  or after the handshake.*/
#define SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS       0x00000800L /* added in 0.9.6e */

/* SSL_OP_ALL: various bug workarounds that should be rather harmless.
              This used to be 0x000FFFFFL before 0.9.7. */
/* User should not use SSL_OP_ALL option without consulting with development team */
#define SSL_OP_ALL                              0x00000BB7L

#ifndef IPSI_SSL_NO_DTLS
/* DTLS options */
#define SSL_OP_NO_QUERY_MTU                 0x00001000L
/* Turn on Cookie Exchange (on relevant for servers) */
#define SSL_OP_COOKIE_EXCHANGE              0x00002000L
/*Turn on cookie exchange on resumption 
it's mandatory to set SSL_OP_COOKIE_EXCHANGE with 
SSL_OP_COOKIE_EXCHANGE_ON_RESUMPTION*/
#define SSL_OP_COOKIE_EXCHANGE_ON_RESUMPTION 0x00008000L
/* Turn on fatal alert for bad record mac for DTLS */
#define SSL_OP_DTLS_FATAL_BAD_RECORD_MAC        0x00040000L
#endif

/* As server, disallow session resumption on renegotiation */
#define SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION   0x00010000L


/* Allow unsafe legacy renegotiation. Server or client which is 
 * connecting to legacy entity can enable this option if they
 * still want to continue renegotiation. The renegotiation will
 * be insecure */
#define SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION    0x00020000L


/* If set, always create a new key when using tmp_ecdh parameters */
#define SSL_OP_SINGLE_ECDH_USE                          0x00080000L
/* If set, always create a new key when using tmp_dh parameters */
#define SSL_OP_SINGLE_DH_USE                            0x00100000L

/* Set to always use the temporary  key when doing RSA operations,
  even when this violates protocol specs */
/* Using this option is deprecated as it violates protocol and vulnerability is raised
 * for this option CVE-2015-0204, so even if it is set, it will be ignored.
 * If still need to use this option, user need to enable option
 * SSL_CTRL_BEHAV_SUPPORT_EPHEMERAL_RSA using "SSL_CTX_SET_BEHAVIOUR_OPTIONS"
 * or "SSL_SET_BEHAVIOUR_OPTIONS" */
#define SSL_OP_EPHEMERAL_RSA                            0x00200000L
/* Set on servers to choose the cipher according to the server's
  preferences */
#define SSL_OP_CIPHER_SERVER_PREFERENCE                 0x00400000L
/* If set, a server will allow a client to issue a SSLv3.0 version number
  as latest version supported in the premaster secret, even when TLSv1.0
  (version 3.1) was announced in the client hello. Normally this is
  forbidden to prevent version rollback attacks. */
#define SSL_OP_TLS_ROLLBACK_BUG                         0x00800000L

#define SSL_OP_NO_SSLv2                                 0x01000000L
#define SSL_OP_NO_SSLv3                                 0x02000000L
#define SSL_OP_NO_TLSv1                                 0x04000000L
#define SSL_OP_NO_TLSv1_1                               0x80000000L/* better be 0x08000000  */
#define SSL_OP_NO_TLSv1_2                               0x00000400L

/* The next flag deliberately changes the ciphertest, this is a check
  for the PKCS#1 attack */
#define SSL_OP_PKCS1_CHECK_1                            0x08000000L
#define SSL_OP_PKCS1_CHECK_2                            0x10000000L
#define SSL_OP_NETSCAPE_CA_DN_BUG                       0x20000000L
#define SSL_OP_NETSCAPE_DEMO_CIPHER_CHANGE_BUG          0x40000000L

/*This flag is used to enable the Removal of Expired CRL while loading */
#define SSL_OP_REM_EXP_CRL          0x00004000L


/* Allow SSL_write(..., n) to return r with 0 < r < n (i.e. report success
  when just a single record has been written): */
#define SSL_MODE_ENABLE_PARTIAL_WRITE                   0x00000001L
/* Make it possible to retry SSL_write() with changed buffer location
  (buffer contents must stay the same!); this is not the default to avoid
  the misconception that non-blocking SSL_write() behaves like
  non-blocking write(): */
#define SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER             0x00000002L
/* Never bother the application with retries if the transport
  is blocking: */
#define SSL_MODE_AUTO_RETRY                             0x00000004L
/* Don't attempt to automatically build certificate chain */
#define SSL_MODE_NO_AUTO_CHAIN                          0x00000008L

/* SSL_MODE value 0x00000010L is already used for internal purpose and its defined in ssl_locl.h.
 * while creating the next SSL_MODE option this value should not be used */

/* SSL_MODE_DTLS_LISTEN_FINISHED option is used internally, user will not be able to set it */
#define SSL_MODE_DTLS_LISTEN_FINISHED                   0x00000020L

/* DTLS has an internal timer logic for retransmission if there is a delay in handshake message. This will be used
 * only if DTLS connection is performed on blocking UDP socket. If application wants to run DTLS on nonblocking UDP
 * socket means, SSL_MODE_DTLS_EXTERNAL_TIMER option needs to be set mandatorily. And application has to
 * maintain the timer logic for retransmission. This option should not be set while using DTLS on blocking socket. */
#define SSL_MODE_DTLS_EXTERNAL_TIMER                    0x00000040L

/* Send TLS_FALLBACK_SCSV in the ClientHello.
 * To be set by applications that reconnect with a downgraded protocol
 * version; see draft-ietf-tls-downgrade-scsv-00 for details. */
#define SSL_MODE_SEND_FALLBACK_SCSV                     0x00000080L

/* Behavior control options */
/* Option to disable the Key usage check for End entity cert.
 * Applicable for only TLS1.2*/
#define SSL_CTRL_BEHAV_DISABLE_KUEXTN_CHECK_EE_CERT    0x00000001L

/* Option to disable the SKID/AKID check for certificate chain formation
 * Applicable for only TLS1.2*/
#define SSL_CTRL_BEHAV_DISABLE_SKID_AKID_CHECK              0x00000002L

/* Option to release Read and Write buffers during Idle state.
 * Applicable for SSL(2.0 and 3.0), TLS (1.0, 1.1 and 1.2) and DTLS. 
 * And while using this option with nonblocking socket it is recommended to call SSL_read()
 * after confirming that there is a data to read from socket using system call like select() or poll() 
 * because SSL_read() initially allocates read buffer and its get freed only in success case, if it returns
 * failure without any data in socket means buffer will not get freed. */
#define SSL_CTRL_BEHAV_RELEASE_IDLE_BUFFERS                 0x00000004L


/* Option to restrict the TLS 1.2 ciphers (*_SHA256) to TLS 1.2 version */
#define SSL_CTRL_BEHAV_RESTRICT_TLS12_CIPHERS_TO_TLS12_VERSION          0x00000008L

/* Option to reject the renegotiation requested by the peer, and to send back No renegotiation
 * warning alert from TLS1.0 and above (TLS1.0, TLS1.1, TLS1.2) */
/* If the negotiated version is SSL 3, always fatal alert of handshake failure will be send to reject renegotiation */
/* This option should not be used with DTLS and SSLv2 */
#define SSL_CTRL_BEHAV_NORENEG_WARN                     0x00000010L

/* Option to reject the renegotiation requested by the peer, and to send back Handshake failure
 * fatal alert for all versions (SSLv3, TLS1.0, TLS1.1, TLS1.2) */
/* This option should not be used with DTLS and SSLv2 */
#define SSL_CTRL_BEHAV_NORENEG_FATAL                    0x00000040L

/* Option to accept the renegotiation rejection from the peer side.
 * This option when specified will tolerate a warning "No Renegotiation" alert received from peer side in response to a 
 * Renegotiation Request sent from Self Side. Without this option, for the same scenario, a fatal "Handshake Failure" 
 * alert will be sent and the connection will be closed. With this option, when a  "No Renegotiation" alert is received, 
 * the user will be indicated of Renegotiation Request rejection by peer through an error code, and application if it 
 * wishes can continue to use the connection for further data transfer. This Option will be effective only for TLS 
 * versions 1.0 and above. It should not / cannot be used with SSL 2.0, SSL 3.0 or DTLS.*/
#define SSL_CTRL_BEHAV_ACCEPT_RENEG_REJECTION           0x00000020L


/* Option to enable the fix for Lucky Thirteen Timing Attack (CVE2013-0169) 
    This Option should automatically enable TLS 1.2 Ciphers restriction to TLS 1.2 version */
#define SSL_CTRL_BEHAV_ENABLE_CVE2013_0169_FIX         (0x00000080L | SSL_CTRL_BEHAV_RESTRICT_TLS12_CIPHERS_TO_TLS12_VERSION)

/* As per DTLS RFC bad record mac needs to be discarded silently and continue to read next packet */
/* But in this failure case, if user wants to come out immediately from SSL_connect(), SSL_accept() or */
/* SSL_read() then user needs to enable below option. This option is applicable only for DTLS. */
#define SSL_CTRL_BEHAV_DTLS_ENABLE_BAD_RECORD_MAC_FAILURE     0x00000100L

/* CVE-2015-0204 requires ephemeral RSA keys to be removed for non-export RSA ciphers as it is protocol violation.
 * For users who can not change the code to remove ephemeral RSA keys, need to enable this option. */
/* Option to support ephemeral RSA keys for non-export RSA cipher suites */
#define SSL_CTRL_BEHAV_SUPPORT_EPHEMERAL_RSA     0x00000200L



#define SSL_RESET_CTRL_BEHAV_NORENEG_WARN               0xFFFFFFEFL
#define SSL_RESET_CTRL_BEHAV_NORENEG_FATAL              0xFFFFFFBFL
#define SSL_RESET_CTRL_BEHAV_ACCEPT_RENEG_REJECTION     0xFFFFFFDFL


/* Note: SSL_S[_CTX]_set_{options,mode} use |= op on the previous value,
  they cannot be used to clear bits. */


/* Adds the options set via bitmask in options to the context. 
    Options already set before are not cleared*/
#define SSL_CTX_SET_OPTIONS(pstContext,lArg)\
    SSL_ctxCtrl((pstContext),SSL_CTRL_OPTIONS,(lArg),SEC_NULL)

/* Gets the options set via bitmask in options to the context */
#define SSL_CTX_GET_OPTIONS(pstContext)\
    SSL_ctxCtrl((pstContext),SSL_CTRL_OPTIONS,0,SEC_NULL)

/* Adds the behavior control options set via bitmask to the context. 
    Options already set before are not cleared*/
#define SSL_CTX_SET_BEHAVIOUR_OPTIONS(pstContext, lArg)\
    SSL_ctxCtrl((pstContext), SSL_CTRL_BEHAVIOUR_OPTIONS, (lArg), SEC_NULL)

#define SSL_CTX_GET_BEHAVIOUR_OPTIONS(pstContext)\
    SSL_ctxCtrl((pstContext),SSL_CTRL_BEHAVIOUR_OPTIONS,0,SEC_NULL)


/* Sets/Gets the options set via bitmask in options to ssl. 
    Options already set before are not cleared. 
    The behavior of the SSL library can be changed by setting several options. 
    The options are coded as bitmasks and can be combined by a logical 
    or operation (|). Options can only be added but can never be reset*/
#define SSL_SET_OPTIONS(pstSSL,lArg)\
    SSL_ctrl((pstSSL), SSL_CTRL_OPTIONS, (lArg), SEC_NULL)

/** Gets the options set via bitmask in options to the ssl */
#define SSL_GET_OPTIONS(pstSSL)\
        SSL_ctrl((pstSSL), SSL_CTRL_OPTIONS, 0, SEC_NULL)

/** Adds the mode set via bitmask in mode to context. Options already set 
    before are not cleared. */
#define SSL_CTX_SET_MODE(pstContext,lArg)\
    SSL_ctxCtrl((pstContext), SSL_CTRL_MODE, (lArg), SEC_NULL)

/** Returns the mode set via bitmask in mode to context. */
#define SSL_CTX_GET_MODE(pstContext)\
    SSL_ctxCtrl((pstContext), SSL_CTRL_MODE, 0, SEC_NULL)

/** Adds the mode set via bitmask in mode to ssl. Options already set 
    before are not cleared. */
#define SSL_SET_MODE(pstSSL,lArg)\
    SSL_ctrl((pstSSL), SSL_CTRL_MODE, (lArg), SEC_NULL)

/** Returns the mode set via bitmask in mode to ssl. */
#define SSL_GET_MODE(pstSSL)\
        SSL_ctrl((pstSSL), SSL_CTRL_MODE, 0, SEC_NULL)

/* Returns whether secure renegotiation is there or not */
#define SSL_GET_SECURE_RENEGOTIATION_SUPPORT(ssl) \
    SSL_ctrl((pstSSL), SSL_CTRL_GET_RI_SUPPORT, 0, NULL)

/* Adds the behavior control options set via bitmask to the context. 
    Options already set before are not cleared*/
#define SSL_SET_BEHAVIOUR_OPTIONS(pstSSL, lArg)\
    SSL_ctrl((pstSSL), SSL_CTRL_BEHAVIOUR_OPTIONS, (lArg), SEC_NULL)

#define SSL_GET_BEHAVIOUR_OPTIONS(pstSSL)\
    SSL_ctrl((pstSSL), SSL_CTRL_BEHAVIOUR_OPTIONS, 0, SEC_NULL)

#define SSL_CLEAR_CTRL_BEHAV_ACCEPT_RENEG_REJECTION(pstSSL) \
    SSL_ctrl((pstSSL), SSL_CLEAR_CTRL_BEHAVIOUR_OPTIONS, SSL_RESET_CTRL_BEHAV_ACCEPT_RENEG_REJECTION, SEC_NULL)

#define SSL_CLEAR_CTRL_BEHAV_NORENEG_WARN(pstSSL) \
    SSL_ctrl((pstSSL), SSL_CLEAR_CTRL_BEHAVIOUR_OPTIONS, SSL_RESET_CTRL_BEHAV_NORENEG_WARN, SEC_NULL)

#define SSL_CLEAR_CTRL_BEHAV_NORENEG_FATAL(pstSSL) \
    SSL_ctrl((pstSSL), SSL_CLEAR_CTRL_BEHAVIOUR_OPTIONS, SSL_RESET_CTRL_BEHAV_NORENEG_FATAL, SEC_NULL)


/* This structure is used to hold the details of compression methods in SSL. It is used 
  to identify the available compression algorithms. It contains a COMP_METHOD_S which 
  contains the callbacks for performing the compression on the data.
 */
/**
* @defgroup SSL_COMP_S
* @ingroup sslStructures
* @par Description
* This structure is used to hold the details of compression methods in SSL. It is used to identify the available
* compression algorithms. It contains a COMP_METHOD_S which contains the callbacks for performing the compression on
* the data.
* @par Prototype
* @code
* typedef struct stSSLComp
* {
*  SEC_INT iCompID;
*  const SEC_CHAR *pcName;
*  #ifndef SSL_NO_COMP
*  COMP_METHOD_S *pMethod;
*  #else
*  SEC_CHAR *pMethod;
*  #endif
* }SSL_COMP_S;
* @endcode
*
* @datastruct iCompID ID of compression algorithm.
* @datastruct pcName Name of compression algorithm.
* @datastruct pMethod Contains compression operations like init, compress, decompress, finish.
*/
typedef struct stSSLComp
{
    /* ID of compression algorithm */
    SEC_INT iCompID;

    /* Name of compression algorithm*/
    const SEC_CHAR *pcName;

#ifndef SSL_NO_COMP
    /* Contains compression operations like init, compress, decompress, finish */
    COMP_METHOD_S *pMethod;
#else
    /* Contains compression operations like init, compress, decompress, finish */   
    SEC_CHAR *pMethod;
#endif

} SSL_COMP_S;
#if (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))

/*Structure to store the PSK(pre-shared key) details */
/**
* @defgroup SSL_PSKINFO_S
* @ingroup sslStructures
* @par Description
* This structure stores the Pre-Shared Key(PSK) details.
* @par Prototype
* @code
* typedef struct stSSLPSKINFO
* {
*  SEC_INT16 iPSKIdLen;
*  char PSKID[MAX_PSK_IDENTITY_LEN];
*  SEC_INT16 iPSKLen;
*  unsigned char PSK[MAX_PSK_LEN];
* }SSL_PSKINFO_S;
* @endcode
*
* @datastruct iPSKIdLen Length of the PSK id.
* @datastruct PSKID[MAX_PSK_IDENTITY_LEN] Value of the PSK id.
* @datastruct iPSKLen Length of the PSK.
* @datastruct PSK[MAX_PSK_LEN] Value of the PSK.
*/
typedef struct stSSLPSKINFO
{
    SEC_UINT iPSKIdLen; /* Length of the PSK id */
    char PSKID[MAX_PSK_IDENTITY_LEN]; /* Value of the PSK id */
    SEC_UINT iPSKLen; /* Length of the PSK */
    unsigned char PSK[MAX_PSK_LEN]; /* Value of the PSK */
    SEC_CHAR pcPskIdHint[MAX_PSK_IDENTITY_LEN];
    SEC_UINT hintLen;
}SSL_PSKINFO_S;
#endif

/* This callback type is used inside SSL_CTX_S, SSL_S, and in the functions that set
  them. It is used to override the generation of SSL_S/TLS session IDs in a
  server. Return value should be zero on an error, non-zero to proceed. Also,
  callbacks should themselves check if the id they generate is unique otherwise
  the SSL_S handshake will fail with an error - callbacks can do this using the
  'ssl' value they're passed by;
       SSL_hasMatchingSessionID(ssl, id, *id_len)
  The length value passed in is set at the maximum size the session ID can be.
  In SSLv2 this is 16 bytes, whereas SSLv3/TLSv1 it is 32 bytes. The callback
  can alter this length to be less if desired, but under SSLv2 session IDs are
  supposed to be fixed at 16 bytes so the id will be padded after the callback
  returns in this case. It is also an error for the callback to set the size to
  zero. */
 /* callback function to generate the SSL session. */
typedef SEC_INT (*pfGenSession_cb)  (const struct stSSL *pstSSL,
                                     SEC_UCHAR *pucID,
                                     SEC_UINT *puiIdLen);

/* enum enTLSCertUrlType;

Moved here from "tls1_extns.h" due to c++ compiler issues */

/*
Enum for Certificate URL Type;
It can be {individual_certs(0), pkipath(1)}
*/
/**
* @defgroup TLS_EXTN_CERTURLTYPE_E
* @ingroup sslEnum
* @par Description
* This enum has the certificate URL types.
* @par Prototype
* @code
* typedef enum enTLSCertUrlType
* {
*  TLS_INDIVIDUAL_CERT = 0,
*  TLS_PKI_PATH
* }TLS_EXTN_CERTURLTYPE_E;
* @endcode
*
* @datastruct TLS_INDIVIDUAL_CERT=0 Indicates that the URL in the Certificate URL extensions
* refers to a single DER-Encoded X509V3 Certificate.
* @datastruct TLS_PKI_PATH Indicates that the URL in the Certificate URL extensions refers
* to a DER-encoded certificate chain.
*/
typedef enum enTLSCertUrlType
{
    /*individual_certs(0) : Indicate that the URL in the Cert URL extensions
       referes to a single DER-Encoded X509V3 Certificate*/
    TLS_INDIVIDUAL_CERT = 0,
    /*pkipath(1) : Indicate that the URL in the Cert URL extensions referes
       to a DER-encoded certificate chain*/
    TLS_PKI_PATH
}TLS_EXTN_CERTURLTYPE_E;


/* forward declaration of x509 store ctx */
typedef struct stX509StoreCtx  X509_STORE_CTX_S;


/*structure which represents the context of SSL object. */

/**
* @defgroup SSL_CTX_S
* @ingroup sslStructures
* @par Description
* This structure represents the context of SSL object.
* @par Prototype
* @code
* typedef struct stSSLCtx
* {
*  SSL_METHOD_S *pstMethod;
*  SEC_List_S *pCipherList;
*  SEC_List_S *pCipherListById;
*  X509_STORE_S *pstCertStore;
*  struct lhash_st *pstSessions;
*  SEC_UINT32 ulSessionCacheSize;
*  SSL_SESSION_S *pstSessionCacheHead;
*  SSL_SESSION_S *pstSessionCacheTail;
*  SEC_INT iSessionCacheMode;
*  SEC_INT32 lSessionTimeout;
*  SEC_INT (*pfNewSession_cb) ( struct stSSL *pstSSL,
*                              SSL_SESSION_S *pstSession);
*  SEC_VOID (*pfRemoveSession_cb) ( struct stSSLCtx *pstContext, 
*                                  SSL_SESSION_S *pstSession);
*  SSL_SESSION_S *(*pfGetSession_cb) (struct stSSL *pstSSL,
*                                    SEC_UCHAR *pucData,
*                                    SEC_INT iLen,
*                                    SEC_INT *piCopy);
*  struct
*  {
*   SEC_INT iSessConnect;
*   SEC_INT iSessConnectRenegotiate;
*   SEC_INT iSessConnectGood;
*   SEC_INT iSessAccept;
*   SEC_INT iSessAcceptRenegotiate;
*   SEC_INT iSessAcceptGood;
*   SEC_INT iSessMiss;
*   SEC_INT iSessTimeout;
*   SEC_INT iSessCacheFull;
*   SEC_INT iSessHit;
*   SEC_INT iSessCallbackHit;
*  }stats;
*  SEC_INT iReferences;
*  SEC_INT (*pfAppVerify_cb) (X509_STORE_CTX_S *, SEC_VOID *);
*  SEC_VOID *pAppVerifyArg;
*  SEC_CHAR *pcDefaultPasswd;
*  SEC_VOID *pDefaultPasswdCallbackUserdata;
*  SEC_INT (*pfClientCert_cb) ( struct stSSL *pstSSL, 
*                              X509_CERT_EXTENDED_S **pstX509Cert, 
*                              SEC_PKEY_S **pKey);
*  SEC_ALGID_E rsa_md5;
*  SEC_ALGID_E md5;
*  SEC_ALGID_E sha1;
*  SEC_List_S *pExtraCertList;
*  SEC_List_S *pCompMethodList;
*  SEC_VOID (*pfInfoCallback) ( const struct stSSL *pstSSL, 
*                              SEC_INT iType,
*                              SEC_INT iVal);
*  SEC_List_S *pClientCAList;
*  SEC_UINT32 ulOptions;
*  SEC_UINT32 ulMode;
*  SEC_INT32    lMaxCertList;
*  struct cert_st *pstCert;
*  SEC_INT iReadAhead;
*  SEC_VOID (*pfMsg_cb) (SEC_INT iWritePend,
*                       SEC_INT iVersion, 
*                       SEC_INT iContentType, 
*                       const SEC_VOID *pBuffer, 
*                       SEC_UINT len, 
*                       struct stSSL *pstSSL, 
*                       SEC_VOID *pArg);
*  SEC_VOID *pMsgCallbackArg;
*  SEC_INT iVerifyMode;
*  SEC_UINT uiSidCtxLength;
*  SEC_UCHAR aucSidCtx [SSL_MAX_SID_CTX_LENGTH];
*  SEC_INT (*pfDefaultVerify_cb) (SEC_INT iOk, X509_STORE_CTX_S *pstStoreContext); 
*  pfGenSession_cb generate_session_id;
*  X509_VERIFY_PARAM_S *pstVerifyParam;
*  SEC_INT iQuietShutdown;
*  #ifndef SSL_NO_TLSEXT
*  struct stTLSExtension * pstTLSExtn;
*  SEC_INT (*pfCtxServerCert_cb)(struct stSSL *pstSSL, X509_CERT_EXTENDED_S **x509, SEC_PKEY_S **pkey); 
*  SEC_INT (*pfCtxClientCertUrl_cb) (struct stSSL * pstSSL, enum enTLSCertUrlType*  pURLtype,  
*                                   SEC_List_S * URLnHashList , SEC_PKEY_S **pPrivKey);
*  SEC_INT (*pfCtxServerCertStatus_cb) (struct stSSL *pstSSL, SEC_AsnOcts_S * pStatusResp) ;
*  SEC_INT (*pfCtxClientValidateStatus_cb) (struct stSSL *pstSSL, SEC_AsnOcts_S * pResponse);
*  SEC_INT (*pfCtxServerRetriveCertFromUrl_cb) (SEC_CHAR * pcURL,SEC_AsnOcts_S * pstDerCert);
*  SEC_INT (*pfCtxServerCheckName_cb) (struct stSSL * pstSSL);  
*  #endif  
*  #if (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))
*  SEC_INT (*pfGetPskByPskId_cb) (const char* PskId, SEC_INT PskIdLen, unsigned char* Psk, SEC_INT* PskLen);
*  #endif
*  #ifndef IPSI_NO_TLS12
*     SEC_ALGID_E ensha224;
*     SEC_ALGID_E ensha256;
*     SEC_ALGID_E ensha384;
*     SEC_ALGID_E ensha512;
*     SEC_BOOL bIsExplicitCiphSet;
*  #endif
* 
*  SEC_UINT uiCtrlBehav;
*  SEC_VOID *pVerifyCBAppData;
* }SSL_CTX_S;
* @endcode
*
* @datastruct pstMethod SSL methods used in this context.
* @datastruct pCipherList Cipher list used in this context.
* @datastruct pCipherListById Cipher list used in this context, sorted by id for lookup.
* @datastruct pstCertStore Holds Certificate store.
* @datastruct pstSessions A set of SSL_SESSION_S.
* @datastruct ulSessionCacheSize Session Cache Size.
* @datastruct pstSessionCacheHead Head of session cache.
* @datastruct pstSessionCacheTail Tail of session cache.
* @datastruct iSessionCacheMode This can have the following values, ORed together:\n
* SSL_SESS_CACHE_OFF,\n
* SSL_SESS_CACHE_CLIENT,\n
* SSL_SESS_CACHE_SERVER,\n
* SSL_SESS_CACHE_NO_AUTO_CLEAR,\n
* SSL_SESS_CACHE_NO_INTERNAL_LOOKUP,\n
* SSL_SESS_CACHE_NO_INTERNAL_STORE.
* Default is SSL_SESSION_CACHE_SERVER, which means only SSL_accept which cache SSL_SESSIONS.
* @datastruct lSessionTimeout The timeout of the session. If timeout is set to 0, the session will never be timeout.
* @datastruct pfNewSession_cb Callback for new session generated. See pfNewSession_cb. 
* @datastruct pfRemoveSession_cb Callback for session removed. See pfRemoveSession_cb.
* @datastruct pfGetSession_cb Callback for get session. See pfGetSession_cb.
* @datastruct iSessConnect SSL_S new connection started.
* @datastruct iSessConnectRenegotiate SSL_S renegotiation requested.
* @datastruct iSessConnectGood SSL_S new connection/renegotiation finished.
* @datastruct iSessAccept SSL_S new accept started.
* @datastruct iSessAcceptRenegotiate SSL_S renegotiation requested.
* @datastruct iSessAcceptGood SSL_S accept/renegotiation finished.
* @datastruct iSessMiss Session lookup misses.
* @datastruct iSessTimeout Reuse attempt on timed out session.
* @datastruct iSessCacheFull Session removed due to full cache.
* @datastruct iSessHit Session reuse actually done.
* @datastruct iSessCallbackHit Session-id that was not in the cache was passed back through the callback. This indicates
* that the application is supplying session-id's from other processes.
* @datastruct iReferences Number of references.
* @datastruct pfAppVerify_cb If defined, this overrides the X509_verifyChain calls. See pfAppVerify_cb.
* @datastruct pAppVerifyArg Pointer to arguments.
* @datastruct pcDefaultPasswd Used as Password for PFX FILE, and PEM private key file encrypted.
* @datastruct pDefaultPasswdCallbackUserdata This is kept for backward compatibility. Not used.
* @datastruct pfClientCert_cb Callback to get the client certificate. See pfClientCert_cb.
* @datastruct rsa_md5 algorithm id of rsa md5.
* @datastruct md5 algorithm id of md5.
* @datastruct sha1 algorithm id of sha1.
* @datastruct pExtraCertList List of x509 certificate chain.
* @datastruct pCompMethodList List of SSL_COMP_S, SSLv3/TLSv1 .
* @datastruct pfInfoCallback Pointer to info callback function. See pfInfoCallback.
* @datastruct pClientCAList List of x509 name to hold client CA.
* @datastruct ulOptions Protocol behavior.
* @datastruct ulMode API behavior.
* @datastruct lMaxCertList Maximum certificate list.
* @datastruct pstCert certificate to be used.
* @datastruct iReadAhead Read ahead.
* @datastruct pfMsg_cb Callback that allows applications to peek at protocol messages. See pfMsg_cb.
* @datastruct pMsgCallbackArg arguments to pfMsg_cb.
* @datastruct iVerifyMode Verify mode.
* @datastruct uiSidCtxLength Context session id length.
* @datastruct aucSidCtx Context session ID.
* @datastruct pfDefaultVerify_cb Pointer to default verify callback function. See pfDefaultVerify_cb.
* @datastruct generate_session_id Pointer to generate session ID function. See pfGenSession_cb.
* @datastruct pstVerifyParam Verify parameter.
* @datastruct iQuietShutdown Flag to shutdown method.
* @datastruct pstTLSExtn Holds the TLS extensions related data.
* @datastruct pfCtxServerCert_cb Call back function required for TLS extensions. It gets server certificate.
* See pfCtxServerCert_cb.
* @datastruct pfCtxClientCertUrl_cb It gets client certificate url. See pfCtxClientCertUrl_cb.
* @datastruct pfCtxServerCertStatus_cb It gets the status of the server certificate. See pfCtxServerCertStatus_cb.
* @datastruct pfCtxClientValidateStatus_cb This call back is to validate the server certificate's OCSP status.
* See pfCtxClientValidateStatus_cb.
* @datastruct pfCtxServerRetriveCertFromUrl_cb This call back is provided to retrieve the der encoded certificate or
* certificate chain from a given URL. See pfCtxServerRetriveCertFromUrl_cb.
* @datastruct pfCtxServerCheckName_cb This call back is to validate the server name received in the client hello.
* See pfCtxServerCheckName_cb.
* @datastruct pfGetPskByPskId_cb This callback will input the PSK identity and search for the respective PSK from among a
* list of PSKs at the server's side. See pfGetPskByPskId_cb.
* @datastruct *stCtxDTLS1Info This pointer contains function pointers, mtu and
* timeout related to dtls
* @datastruct ensha224 Algorithm ID of SHA224.
* @datastruct ensha256 Algorithm ID of SHA256.
* @datastruct ensha384 Algorithm ID of SHA384.
* @datastruct ensha512 Algorithm ID of SHA512.
* @datastruct bIsExplicitCiphSet Indicates if ciphers are explicitly loaded into the SSL library. 
* For internal purpose only.
* @datastruct uiCtrlBehav Variable to hold the Behavior control options.
* @datastruct pVerifyCBAppData Variable to hold the application data of pfDefaultVerify_cb.
* @datastruct pfRenegManag_cb Variable to hold SSL renegotiation management callback.
* @datastruct pvRenegManagAppData Variable to hold SSL renegotiation management callback`s application data.
* Applications should not operate on it directly.
*/

typedef struct stSSLCtx
{
    SSL_METHOD_S *pstMethod; /*  SSL methods used in this context */

    SEC_List_S *pCipherList;/* cipher list used in this context*/
    
    /* same as above but sorted for lookup */
    SEC_List_S *pCipherListById;

    X509_STORE_S *pstCertStore; /* holds  cert store.*/
    struct lhash_st /* LHASH */ *pstSessions;   /* a set of SSL_SESSIONs */
    /* Most session-ids that will be cached, default is
      SSL_SESSION_CACHE_MAX_SIZE_DEFAULT. 0 is unlimited. */
    SEC_UINT32 ulSessionCacheSize; /*Session Cache Size */
    SSL_SESSION_S *pstSessionCacheHead;/* head of session cache */
    SSL_SESSION_S *pstSessionCacheTail;/* tail of sessoin cache*/

    /* This can have one of 2 values, ored together,
      SSL_SESS_CACHE_CLIENT,
      SSL_SESS_CACHE_SERVER,
      Default is SSL_SESSION_CACHE_SERVER, which means only
      SSL_accept which cache SSL_SESSIONS. */
    SEC_INT iSessionCacheMode;

    /* If timeout is not 0, it is the default timeout value set
      when SSL_new() is called.  This has been put in to make
      life easier to set things up */
    SEC_INT32 lSessionTimeout;

    /* If this callback is not null, it will be called each
      time a session id is added to the cache.  If this function
      returns 1, it means that the callback will do a
      SSL_sessionFree() when it has finished using it.  Otherwise,
      on 0, it means the callback has finished with it.
      If remove_session_cb is not null, it will be called when
      a session-id is removed from the cache.  After the call,
      SSL library will SSL_sessionFree() it. */
    SEC_INT (*pfNewSession_cb) ( struct stSSL *pstSSL,
                                SSL_SESSION_S *pstSession);
    SEC_VOID (*pfRemoveSession_cb) ( struct stSSLCtx *pstContext, 
                                    SSL_SESSION_S *pstSession);
    SSL_SESSION_S *(*pfGetSession_cb) (struct stSSL *pstSSL,
                                      SEC_UCHAR *pucData,
                                      SEC_INT iLen,
                                      SEC_INT *piCopy);

    struct
    {
        SEC_INT iSessConnect;           /* SSL_S new conn - started */
        SEC_INT iSessConnectRenegotiate;/* SSL_S reneg - requested */
        SEC_INT iSessConnectGood;       /* SSL_S new conne/reneg - finished */
        SEC_INT iSessAccept;            /* SSL_S new accept - started */
        SEC_INT iSessAcceptRenegotiate; /* SSL_S reneg - requested */
        SEC_INT iSessAcceptGood;        /* SSL_S accept/reneg - finished */
        SEC_INT iSessMiss;              /* session lookup misses  */
        SEC_INT iSessTimeout;           /* reuse attempt on timeouted session */
        SEC_INT iSessCacheFull;         /* session removed due to full cache */
        SEC_INT iSessHit;               /* session reuse actually done */
        SEC_INT iSessCallbackHit;       /* session-id that was not
                                          in the cache was
                                          passed back via the callback.  This
                                          indicates that the application is
                                          supplying session-id's from other
                                          processes */
    } stats;

    SEC_INT iReferences; /* number of references*/

    /* if defined, these override the X509_verify_cert() calls */
    SEC_INT (*pfAppVerify_cb) (X509_STORE_CTX_S *, SEC_VOID *);
    SEC_VOID *pAppVerifyArg;/* pointer to arguments */
    /* before OpenSSL 0.9.7, 'app_verify_arg' was ignored
      ('app_verify_callback' was called with just one argument) */

    SEC_CHAR *pcDefaultPasswd; /* Used as Password for PFX FILE */ 

    /* Default password callback user data. */
    SEC_VOID *pDefaultPasswdCallbackUserdata;

    /* get client cert callback */
    SEC_INT (*pfClientCert_cb) ( struct stSSL *pstSSL, 
                                X509_CERT_EXTENDED_S **pstX509Cert, 
                                SEC_PKEY_S **pKey);

    SEC_ALGID_E rsa_md5;            /* For SSLv2 - name is 'ssl2-md5'   */
    
    SEC_ALGID_E md5;                /* For SSLv3/TLSv1 'ssl3-md5'       */
    
    SEC_ALGID_E sha1;               /* For SSLv3/TLSv1 'ssl3->sha1'     */
    
    SEC_List_S *pExtraCertList;     /* list of x509 certificate chain */
    SEC_List_S *pCompMethodList;    /* list of SSL_COMP_S, SSLv3/TLSv1 */

    
    /* Default values used when no per-SSL_S value is defined follow */
    SEC_VOID (*pfInfoCallback) ( const struct stSSL *pstSSL, 
                                SEC_INT iType,
                                SEC_INT iVal); /* used if SSL_S's info_callback is SEC_NULL */

    /* what we put in client cert requests */
    SEC_List_S *pClientCAList; /*list of x509_name to hold client CA */
    
    /* Default values to use in SSL_S structures follow (these are copied by SSL_new) */

    SEC_UINT32  ulOptions;/* protocol behavior */ /* Default values to be used in SSL_S structures. This is copied by SSL_new - protocol behavior */
    SEC_UINT32  ulMode;/* API behavior */
    SEC_INT32   lMaxCertList;/* max cert list */

    struct cert_st *pstCert;/* certificate to be used*/
    SEC_INT iReadAhead; /* read ahead*/

    /* callback that allows applications to peek at protocol messages */
    SEC_VOID (*pfMsg_cb) (SEC_INT iWritePend,
                              SEC_INT iVersion, 
                              SEC_INT iContentType, 
                              const SEC_VOID *pBuffer, 
                              SEC_UINT len, 
                              struct stSSL *pstSSL, 
                              SEC_VOID *pArg);

    SEC_VOID *pMsgCallbackArg; /* arguments to pfMsg_cb*/

    SEC_INT iVerifyMode; /* verify mode*/
    SEC_UINT uiSidCtxLength; /* context session id  length*/
    SEC_UCHAR aucSidCtx [SSL_MAX_SID_CTX_LENGTH]; /* context session ID*/

    /* called 'verify_callback' in the SSL_S */
    SEC_INT (*pfDefaultVerify_cb) (SEC_INT iOk,
                                        X509_STORE_CTX_S *pstStoreContext); 

    /* Default generate session ID callback. */
    pfGenSession_cb generate_session_id;

    X509_VERIFY_PARAM_S *pstVerifyParam; /* verify parameter */ 



    SEC_INT iQuietShutdown;  /* flag to shutdown method */

    /* Moved pstTLSExtn out of NO_EXTNS macro
     * as it will be required by RI extension */
    /* Holds the TLS extensions related data  */
    struct stTLSExtension * pstTLSExtn;

#ifndef SSL_NO_TLSEXT
    /* Holds the TLS extensions related data  */

    /* Commented to move out of macro SSL_NO_TLSEXT - 2010-04-10
    struct stTLSExtension * pstTLSExtn;
     */

    /* Call back functions reqd for TLS extensions */

    /*get server cert call back */
    /* Return value : 1- Success
                      0- Failure                      
    */
    SEC_INT (*pfCtxServerCert_cb)(struct stSSL *pstSSL, X509_CERT_EXTENDED_S **x509, SEC_PKEY_S **pkey); 

    /* get client certificate url */
    /* Return value : 1- Success
                      0- Failure                      
    */
    SEC_INT (*pfCtxClientCertUrl_cb) (struct stSSL * pstSSL, enum enTLSCertUrlType*  pURLtype,  
                                                SEC_List_S * URLnHashList , SEC_PKEY_S **pPrivKey);
        
    /* get the status of the server certificate */
    /* Return value : 1- Success
                      0- Failure                      
    */
    SEC_INT (*pfCtxServerCertStatus_cb) (struct stSSL *pstSSL, SEC_AsnOcts_S * pStatusResp) ;

    /* This call back is to validate the server certificate's OCSP status */
    /* Return value : 1- Success
                      0- Failure                      
    */
    SEC_INT (*pfCtxClientValidateStatus_cb) (struct stSSL *pstSSL, SEC_AsnOcts_S * pResponse);

    /* This call back is provided to retrive the der encoded certificate/certificate chain from a given URL*/
    /* Return value : 1- Success
                      0- Failure [Certificate Unobtainable Alert] 
    */
    SEC_INT (*pfCtxServerRetriveCertFromUrl_cb) (SEC_CHAR * pcURL,SEC_AsnOcts_S * pstDerCert);
    
    /* This callback is to validate the server name recieved in the client hello */
    /* Return value : 1- Validation successful
                      0- Unrecognised name - Send Fatal Alert and abort.
                      -1 - Unrecogined name - Send Warning alert.
    */
    SEC_INT (*pfCtxServerCheckName_cb) (struct stSSL * pstSSL);  

#endif // SSL_NO_TLSEXT
    /* This callback will input the PSK identity and search for the 
        respective PSK from among a list of PSKs at the server's side*/
   /* Return value :
   
    *SEC_SUCCESS - on successful completion of searching 
                        the PSK identity and loading the output values.
                     
    *SEC_ERROR - Error in parameters passed to the function 
                        or when the PSK with the said identity was not found.
    */
    #if (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))
        SEC_INT (*pfGetPskByPskId_cb) (const char* PskId, SEC_INT PskIdLen, unsigned char* Psk, SEC_INT* PskLen);

    /* This callback used to get PSK identity, PSK identity length, PSK and PSK
     * length using hint / with out using hint for client. callback function
     * should return PSK length. Any return value less than or equal to zero
     * and value more than MAX_PSK_LEN will be treated as error */

    unsigned int (*psk_client_callback)(struct stSSL *ssl, const char *hint, char *identity,
        unsigned int *identity_len, unsigned char *psk,
        unsigned int max_psk_len, SEC_VOID *pClientPskAppData);

    /* This callback used to get PSK using PSK identity for server.
     * callback function should return PSK length. Any return value
     * less than or equal to zero and value more than MAX_PSK_LEN
     * will be treated as error */

    unsigned int (*psk_server_callback)(struct stSSL *ssl, const char *identity, unsigned int pskIdLen,
        unsigned char *psk, unsigned int max_psk_len, SEC_VOID *pServerPskAppData);

    /* Application data for PSK client callback */
    SEC_VOID *pClientPskAppData;

    /* Application data for PSK server callback */
    SEC_VOID *pServerPskAppData;

   #endif

/*For Creating a DTLS Ctx*/
#ifndef IPSI_SSL_NO_DTLS
    struct stIpsiDTLS1CtxInfo *stCtxDTLS1Info;
    IPSI_CB_APPDATA_S stCtxAppData;
#endif

#ifndef SSL_NO_PSK
    char *pcPskIdentityHint;
#endif

    SEC_UINT uiCtrlBehav;

#ifndef IPSI_NO_TLS12

    SEC_ALGID_E ensha224;

    SEC_ALGID_E ensha256;

    SEC_ALGID_E ensha384;

    SEC_ALGID_E ensha512;

    SEC_BOOL bIsExplicitCiphSet;

#endif    

    /* This will be available in the pstStoreContext of the 
    *  callback pfDefaultVerify_cb */
    SEC_VOID *pVerifyCBAppData;

    IPSI_SSL_RENEG_MANAG_CB pfRenegManag_cb;
    SEC_VOID* pvRenegManagAppData;
} SSL_CTX_S; /* end of struct stSSLCtx */

#define SSL_SESS_CACHE_OFF                      0x0000
#define SSL_SESS_CACHE_CLIENT                   0x0001
#define SSL_SESS_CACHE_SERVER                   0x0002
#define SSL_SESS_CACHE_BOTH                     (SSL_SESS_CACHE_CLIENT | SSL_SESS_CACHE_SERVER)
#define SSL_SESS_CACHE_NO_AUTO_CLEAR            0x0080


/*
    Func Name: SSL_ctxSessions                                                 
*/

/**
* @defgroup SSL_ctxSessions
* @ingroup sslContextFunctions
* @par Prototype
* @code
* struct lhash_st *SSL_ctxSessions (SSL_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This is used to get the lhash databases containing the internal session cache.
*
* @par Description
* SSL_ctxSessions function returns a pointer to the lhash databases containing the internal session cache for SSL context.
*
* @param[in] pstContext Pointer to SSL context [N/A]
*                                                                               
* @retval lhash_st* Pointer to lhash_st object [N/A|N/A]  
* @retval lhash_st* If the input is invalid [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* N/A
*/

SSLLINKDLL struct lhash_st *SSL_ctxSessions (SSL_CTX_S *pstContext);

/* enough comments already ... see SSL_ctxSetSessionCacheMode(3) */
#define SSL_SESS_CACHE_NO_INTERNAL_LOOKUP       0x0100
#define SSL_SESS_CACHE_NO_INTERNAL_STORE        0x0200
#define SSL_SESS_CACHE_NO_INTERNAL \
        (SSL_SESS_CACHE_NO_INTERNAL_LOOKUP | SSL_SESS_CACHE_NO_INTERNAL_STORE)

/* Returns the current number of sessions in the internal session cache*/
#define SSL_CTX_SESS_NUMBER(pstContext)\
    SSL_ctxCtrl(pstContext,SSL_CTRL_SESS_NUMBER,0,SEC_NULL)

/* Returns the number of started SSL/TLS handshakes in client mode*/
#define SSL_CTX_SESS_CONNECT(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_CONNECT, 0, SEC_NULL)

/* Returns the number of successfully established 
    SSL/TLS sessions in client mode*/
#define SSL_CTX_SESS_CONNECTGOOD(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_CONNECT_GOOD, 0, SEC_NULL)

/* Returns the number of start renegotiations in client mode*/
#define SSL_CTX_SESS_CONNECTRENEGOTIATE(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_CONNECT_RENEGOTIATE, 0, SEC_NULL)

/* Returns the number of started SSL/TLS handshakes in server mode*/
#define SSL_CTX_SESS_ACCEPT(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_ACCEPT, 0, SEC_NULL)

/* Returns the number of start renegotiations in server mode*/
#define SSL_CTX_SESS_ACCEPTRENEGOTIATE(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_ACCEPT_RENEGOTIATE, 0, SEC_NULL)

/* Returns the number of successfully established 
    SSL/TLS sessions in server mode*/
#define SSL_CTX_SESS_ACCEPTGOOD(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_ACCEPT_GOOD, 0, SEC_NULL)

/** Returns the number of successfully reused sessions. In client mode a session 
    set with SSL_setSession() successfully reused is counted as a hit. In server 
    mode a session successfully retrieved from internal or external cache is 
    counted as a hit.*/
#define SSL_CTX_SESS_HITS(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_HIT, 0, SEC_NULL)

/* Returns the number of successfully retrieved sessions 
    from the external session cache in server mode*/
#define SSL_CTX_SESS_CBHITS(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_CB_HIT, 0, SEC_NULL)

/* Returns the number of sessions proposed by clients that 
    were not found in the internal session cache in server mode*/
#define SSL_CTX_SESS_MISSES(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_MISSES, 0, SEC_NULL)

 /** Returns the number of sessions proposed by clients and 
    either found in the internal or external session cache 
    in server mode, but that were invalid due to timeout. 
    These sessions are not included in the SSL_CTX_SESS_HITS() count*/
#define SSL_CTX_SESS_TIMEOUTS(pstContext)\
    SSL_ctxCtrl(pstContext,SSL_CTRL_SESS_TIMEOUTS, 0, SEC_NULL)

/* Returns the number of sessions that were removed because 
    the maximum session cache size was exceeded*/
#define SSL_CTX_SESS_CACHEFULL(pstContext)\
    SSL_ctxCtrl(pstContext, SSL_CTRL_SESS_CACHE_FULL, 0, SEC_NULL)

/* Sets the callback function, which is automatically called 
    whenever a new session was negotiated */
#define SSL_CTXSESS_SETNEW_CB(pstContext,cb)            ((pstContext)->pfNewSession_cb=(cb))

/* Allow to retrieve the function pointers of the provided 
    callback functions. If a callback function has not been set, 
    the NULL pointer is returned*/
#define SSL_CTXSESS_GETNEW_CB(pstContext)               ((pstContext)->pfNewSession_cb)

/* Sets the callback function, which is automatically called 
    whenever a session is removed by the SSL engine, because 
    it is considered faulty or the session has become obsolete 
    because of exceeding the timeout value*/
#define SSL_CTXSESS_SETREMOVE_CB(pstContext,cb)     ((pstContext)->pfRemoveSession_cb=(cb))

/* Allow to retrieve the function pointers of the provided 
    callback functions. If a callback function has not been set, 
    the NULL pointer is returned*/
#define SSL_CTXSESS_GETREMOVE_CB(pstContext)            ((pstContext)->pfRemoveSession_cb)

/* Sets the callback function which is called, whenever 
    a SSL/TLS client proposed to resume a session but the 
    session could not be found in the internal session cache */
#define SSL_CTXSESS_SETGET_CB(pstContext,cb)            ((pstContext)->pfGetSession_cb=(cb))

/* Allows to retrieve the function pointers of the provided 
    callback functions. If a callback function has not been set, 
    the NULL pointer is returned*/
#define SSL_CTXSESS_GETGET_CB(pstContext)               ((pstContext)->pfGetSession_cb)

/* SSL_CTX_SETINFO_CB() sets the callback function, that can be used to obtain state 
    information for SSL objects created from ctx during connection setup and use. The setting 
    for ctx is overridden from the setting for a specific SSL object, if specified. 
    When callback is NULL, not callback function is used.*/ 

#define SSL_CTX_SETINFO_CB(pstContext,cb)       ((pstContext)->pfInfoCallback=(cb))

/* SSL_CTX_GETINFO_CB() returns a pointer to the currently set information callback 
    function for ctx */

#define SSL_CTX_GETINFO_CB(pstContext)          ((pstContext)->pfInfoCallback)

/* SSL_CTX_SETCLIENTCERT_CB() sets the "cb" callback, that is called when a 
    client certificate is requested by a server and no certificate was yet set for the 
    SSL object. 
    When callback "cb" is NULL, no callback function is used.*/

#define SSL_CTX_SETCLIENTCERT_CB(pstContext,cb)     ((pstContext)->pfClientCert_cb=(cb))
    
/* This macro returns a pointer to the currently set callback function*/
#define SSL_CTXGETCLIENTCERT_CB(pstContext)         ((pstContext)->pfClientCert_cb)

/* To set the function pointers of the callback required for getting client certificate url.*/
#define SSL_CTX_SET_CLIENT_CERT_URL_CB(pstContext,cb)       ((pstContext)->pfCtxClientCertUrl_cb=(cb))


/* Allow to retrieve the function pointers of the provided 
    callback for cleint certificate URL retreival. If a callback function has not been set, 
    the NULL pointer is returned*/
#define SSL_CTX_GET_CLIENT_CERT_URL_CB(pstContext)          ((pstContext)->pfCtxClientCertUrl_cb)

/* To set the function pointers of the callback required for getting server certificate OCSP status.*/
#define SSL_CTX_SET_SERVER_CERT_STATUS_CB(pstContext,cb)        ((pstContext)->pfCtxServerCertStatus_cb=(cb))


/* Allow to retrieve the function pointers of the provided 
    callback for server certificate status. If a callback function has not been set, 
    the NULL pointer is returned*/
#define SSL_CTX_GET_SERVER_CERT_STATUS_CB(pstContext)           ((pstContext)->pfCtxServerCertStatus_cb)


/* To set the function pointers of the required callback for getting server certificate.*/
#define SSL_CTX_SET_SERVER_CERT_CB(pstContext,cb)       ((pstContext)->pfCtxServerCert_cb=(cb))


/* Allow to retrieve the function pointers of the provided 
    callback for getting server certificate. If a callback function has not been set, 
    the NULL pointer is returned*/
#define SSL_CTX_GET_SERVER_CERT_CB(pstContext)          ((pstContext)->pfCtxServerCert_cb)


/* To set the function pointers of the callback required for validating
 the OCSP status recieved in the certificate status message.*/
#define SSL_CTX_SET_CLIENT_VALIDATE_STATUS_CB(pstContext,cb)        ((pstContext)->pfCtxClientValidateStatus_cb=(cb))

/* Allow to retrieve the function pointers of the provided 
    callback for validating the OCSP status recieved in the certificate status message. 
    If a callback function has not been set, then NULL pointer is returned*/
#define SSL_CTX_GET_CLIENT_VALIDATE_STATUS_CB(pstContext)           ((pstContext)->pfCtxClientValidateStatus_cb)

/* To set the function pointers of the callback required for retrieving the client certificate from a URL.*/
#define SSL_CTX_SET_SERVER_RETRIVE_CERTCHAIN_URL_CB(pstContext,cb)  ((pstContext)->pfCtxServerRetriveCertFromUrl_cb=(cb))

/* Allow to retrieve the function pointers of the provided 
    callback for retrieveing the certificate from a given URL. 
    If a callback function has not been set, then NULL pointer is returned*/
#define SSL_CTX_GET_SERVER_RETRIVE_CERTCHAIN_URL_CB(pstContext)   ((pstContext)->pfCtxServerRetriveCertFromUrl_cb)

/* To set the function pointers of the callback required for validating the server name 
list sent by the cleint to the server while requesting for support for server name extension.*/
#define SSL_CTX_SET_SERVER_CHECK_NAME_CB(pstContext,cb)     ((pstContext)->pfCtxServerCheckName_cb=(cb))

/* Allow to retrieve the function pointers of the provided 
    callback for validating the server name list sent by client while requesting for server name extension. 
    If a callback function has not been set, then NULL pointer is returned*/
#define SSL_CTX_GET_SERVER_CHECK_NAME_CB(pstContext)            ((pstContext)->pfCtxServerCheckName_cb)


#define SSL_NOTHING                                     1
#define SSL_WRITING                                     2
#define SSL_READING                                     3
#define SSL_X509_LOOKUP                                 4

/* These will only be used when doing non-blocking IO.
    If the SSL_accept/SSL_connect returned with -1, these macros indicate 
    when we should re-call */
#define SSL_WANTNOTHING(s)                              (SSL_want(s) == SSL_NOTHING)
#define SSL_WANTREAD(s)                                 (SSL_want(s) == SSL_READING)
#define SSL_WANTWRITE(s)                                (SSL_want(s) == SSL_WRITING)
#define SSL_WANTX509LOOKUP(s)                           (SSL_want(s) == SSL_X509_LOOKUP)

#define  SSL_BUFFER

#ifdef SSL_BUFFER
#define DEFAULT_SSL_BUFFER_LEN           4096           
#endif
/*  Structure that  represents the SSL object  */
/**
* @defgroup SSL_S
* @ingroup sslStructures
* @par Description
* This structure represents the SSL object.
* @par Prototype
* @code
* typedef struct stSSL
* {
*  SEC_INT iVersion;
*  SEC_INT iType;
*  SSL_METHOD_S *pstMethod;
*  SEC_INT iRWState;
*  SEC_INT iInHandshake;
*  SEC_INT (*pfHandshakeFunc)(struct stSSL *);
*  SEC_SOCK ulSockID;
*  SEC_INT iServer;
*  SEC_INT iNewSession;
*  SEC_INT iQuiet_shutdown;
*  SEC_INT iShutdown;
*  SEC_INT iState;
*  SEC_INT iRState;
*  #ifdef SSL_BUFFER
*  struct buf_mem_st *psslBuffer;
*  #endif
*  struct buf_mem_st *pInitBuffer;
*  SEC_VOID *pInitMsg;
*  SEC_INT iInitNum;
*  SEC_INT iInitOff;
*  SEC_UCHAR *pucPacket;
*  SEC_UINT uiPacketLength;
*  struct stSSL2State *pstSSL2;
*  struct stSSL3State *pstSSL3;
*  SEC_INT iReadAhead;
*  SEC_VOID (*pfMsg_cb) (SEC_INT iWritePend, 
*                        SEC_INT iVersion,
*                        SEC_INT iContentType,
*                        const SEC_VOID *pBuf,
*                        SEC_UINT len,
*                        struct stSSL *pstSSL,
*                        SEC_VOID *pArg);
*  SEC_VOID *pMsgCallbackArg;
*  SEC_INT iHit;
*  X509_VERIFY_PARAM_S *pstParam;
*  SEC_List_S *cipher_list;
*  SEC_List_S *cipher_list_by_id;
*  CRYPT_CTX stEncReadCtx;
*  SEC_ALGID_E enReadHash;
*  #ifndef SSL_NO_COMP
*  COMP_CTX_S *pstExpand;
*  #else
*  SEC_CHAR *pstExpand;
*  #endif
*  CRYPT_CTX stEncwriteCtx;
*  SEC_ALGID_E enWriteHash;
*  #ifndef SSL_NO_COMP
*  COMP_CTX_S *pCompress;
*  #else
*  SEC_CHAR *pCompress;
*  #endif
*  struct cert_st *pstCert;
*  #if (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))
*  struct stSSLPSKINFO stPSKInfo;
*  SEC_INT (*pfGetPskByPskId_cb)(const char *PskId, SEC_INT PskIdLen, unsigned char *Psk, SEC_INT *PskLen);
*  #endif
*  SEC_UINT uiSidCtxLength;
*  SEC_UCHAR aucSidCtx [SSL_MAX_SID_CTX_LENGTH];
*  SSL_SESSION_S *pstSession;
*  pfGenSession_cb generate_session_id;
*  SEC_INT iVerifyMode;
*  SEC_INT (*pfVerify_cb) (SEC_INT iOk, X509_STORE_CTX_S *pstStoreContext);
*  SEC_VOID (*pfInfoCallback) ( const struct stSSL *pstSSL,
*                               SEC_INT iType,
*                               SEC_INT iVal);
*  SEC_INT iError;
*  SEC_INT iErrorCode;
*  SSL_CTX_S *pstContext;
*  SEC_INT iDebug;
*  SEC_INT32 lVerifyResult;
*  SEC_List_S *pClientCAList;
*  SEC_INT iReferences;
*  SEC_UINT32 ulOptions;
*  SEC_UINT32 ulMode;
*  SEC_INT32 lMaxCertList;
*  SEC_INT iFirstPacket;
*  SEC_INT iClientVersion;
*  #ifndef SSL_NO_TLSEXT
*  struct stTLSSessionExtn * pstTLSExtns;
*  #endif
*  SEC_UINT  ulMaxPlainTextLen;
*  SEC_UINT  ulMaxCompDataLen;
*  SEC_UINT  ulMaxEncDataLen;
*  SEC_UINT  ulMaxPktLen;
*  SEC_BOOL  bShortHMACFlag;
*  SSLSOCKREAD_CB pfSockRead_cb;
*  SSLSOCKWRITE_CB pfSockWrite_cb;
*  SEC_ALGID_E EncAlgid;
*  IPSI_TLS12_SUPPORTED_SIGN_HASH_S stSrvSignHash;
*  SEC_BOOL bIsExplicitCiphSet;
*  SEC_UINT uiCtrlBehav;
*  SEC_VOID *pVerifyCBAppData;
*  SEC_UINT uiAlertFlag;
*  SEC_INT iRenegotiate;
* }SSL_S;
* @endcode
*
* @datastruct iVersion Protocol version. That is, one of these - SSL2_VERSION, SSL3_VERSION, TLS1_VERSION, TLS1_1_VERSION
* @datastruct iType Protocol type. It can be SSL_ST_CONNECT or SSL_ST_ACCEPT
* @datastruct pstMethod SSL methods used in this SSL.
* @datastruct iRWState This holds a variable that indicates what we were doing when a 0 or -1 is returned. This is needed for
* non-blocking IO. So we know what request needs re-doing when in SSL_accept or SSL_connect.
* @datastruct iInHandshake True when we are actually in SSL_accept() or SSL_connect().
* @datastruct pfHandshakeFunc pointer to accept or connect function depending on the method chosen.
* @datastruct ulSockID Added for storing socket descriptor.
* @datastruct iServer Mostly used by SSL_clear to check if we are at the server side.
* @datastruct iNewSession 1 If we are to use a new session. 2 If we are a server and are inside a handshake(i.e. not just
* sending a HelloRequest). For servers, the 'new' session may actually be a previously cached session or even the previous
* session unless SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION is set.
* @datastruct iQuiet_shutdown Do not send shutdown packets.
* @datastruct iShutdown We have shut things down, 0x01 sent, 0x02 for received.
* @datastruct iState Indicates the state we are in.
* @datastruct iRState Indicates which state we are in when reading.
* @datastruct psslBuffer. ssl buffer.
* @datastruct pInitBuffer Buffer used during init.
* @datastruct pInitMsg Pointer to handshake message body, set by ssl3_get_message().
* @datastruct iInitNum Amount read/written.
* @datastruct iInitOff Amount read/written.
* @datastruct pucPacket Used internally to point at a raw packet.
* @datastruct uiPacketLength Packet length.
* @datastruct pstSSL2 SSLv2 variables.
* @datastruct pstSSL3 SSLv3 variables.
* @datastruct iReadAhead Read as many input bytes as possible(for non-blocking reads).
* @datastruct pfMsg_cb Callback that allows applications to peek at protocol messages. See pfMsg_cb.
* @datastruct pMsgCallbackArg Arguments to pfMsg_cb.
* @datastruct iHit Reusing a previous session.
* @datastruct pstParam Pointer to verify parameters.
* @datastruct cipher_list List of Cipher.
* @datastruct cipher_list_by_id List of Cipher sorted by ID.
* @datastruct stEncReadCtx Cryptographic state.
* @datastruct enReadHash Used for mac generation.
* @datastruct pstExpand To uncompress
* @datastruct stEncwriteCtx Cryptographic state.
* @datastruct enWriteHash Used for mac generation.
* @datastruct pCompress Compression
* @datastruct pstCert This is used to hold the server certificate used.
* @datastruct stPSKInfo This is used to hold the pre-shared key parameters.
* @datastruct pfGetPskByPskId_cb This callback will input the PSK identity and search for the respective PSK from among a
* list of PSKs at the server's side. See pfGetPskByPskId_cb.
* @datastruct uiSidCtxLength The session id context length.
* @datastruct aucSidCtx the session id context is used to ensure sessions are only reused in the appropriate context 
* @datastruct pstSession This can also be in the session once a session is established.
* @datastruct generate_session_id Pointer to generate session ID function. See pfGenSession_cb.
* @datastruct iVerifyMode Verify mode.
* @datastruct pfVerify_cb Pointer to verify callback function. See pfVerify_cb.
* @datastruct pfInfoCallback Pointer to info callback function. See pfInfoCallback..
* @datastruct iError Error bytes to be written.
* @datastruct iErrorCode Actual code.
* @datastruct pstContext pointer to SSL_CTX_S structure from which SSL_S is obtained.
* @datastruct iDebug Set this flag to 1 and a sleep(1) is put into all SSL_read() and SSL_write() calls.
* @datastruct lVerifyResult The verify result for the connection.
* @datastruct pClientCAList For server side, keep the list of CA_dn we can use.
* @datastruct iReferences Holds number of references.
* @datastruct ulOptions Protocol behavior.
* @datastruct ulMode API behavior.
* @datastruct lMaxCertList Maximum cert list that SSL object can hold.
* @datastruct iFirstPacket Holds first packet.
* @datastruct iClientVersion What was passed, used for SSLv3/TLS rollback check.
* @datastruct pstTLSExtns Holds the TLS extensions related data.
* @datastruct ulMaxPlainTextLen Max plain text length.
* @datastruct ulMaxCompDataLen Max compressed text length.
* @datastruct ulMaxEncDataLen Max encrypted text length.
* @datastruct ulMaxPktLen Max packet length.
* @datastruct bShortHMACFlag Truncated HMAC flag.
* @datastruct pfSockRead_cb Pointer to socket read callback function.
* @datastruct pfSockWrite_cb Pointer to socket write callback function.
* @datastruct EncAlgid Encryption algorithm id.
* @datastruct stSrvSignHash Server supported sign/hash algorithms.
* @datastruct bIsExplicitCiphSet Indicates if ciphers are explicitly loaded into the SSL library. 
* For internal purpose only.
* @datastruct uiCtrlBehav Variable to hold behavior control options.
* @datastruct pVerifyCBAppData Variable to hold the application data of pfVerify_cb.
* @datastruct uiAlertFlag Variable to hold fatal alert information on object.
* @datastruct pfRenegManag_cb Variable to hold SSL renegotiation management callback.
* @datastruct pvRenegManagAppData Variable to hold SSL renegotiation management callback`s application data.
* @datastruct iRenegotiate Variable to indicate that current connection is in renegotiation 
* Applications should not operate on it directly.
*/

typedef struct stSSL
{
    /* protocol version
      (one of SSL2_VERSION, SSL3_VERSION, TLS1_VERSION, TLS1_1_VERSION)
     */
    SEC_INT iVersion;
    SEC_INT iType; /* SSL_ST_CONNECT or SSL_ST_ACCEPT */

    SSL_METHOD_S *pstMethod; /* SSLv3 */

    /* This holds a variable that indicates what we were doing
      when a 0 or -1 is returned.  This is needed for
      non-blocking IO so we know what request needs re-doing when
     * in SSL_accept or SSL_connect */
    SEC_INT iRWState;

    /* true when we are actually in SSL_accept() or SSL_connect() */
    SEC_INT iInHandshake;
    SEC_INT (*pfHandshakeFunc)(struct stSSL *);

    /* Imagine that here's a boolean member "init" that is
      switched as soon as SSL_set_{accept/connect}_state
      is called for the first time, so that "state" and
      "handshake_func" are properly initialized.  But as
      handshake_func is == 0 until then, we use this
      test instead of an "init" member.
     */
    SEC_SOCK ulSockID;      /* Added for storing socket descriptor */
    
    SEC_INT iServer;        /* are we the server side? - mostly used by SSL_clear*/

    SEC_INT iNewSession;    /* 1 if we are to use a new session.
                              2 if we are a server and are inside a handshake
                                (i.e. not just sending a HelloRequest)
                              NB: For servers, the 'new' session may actually be a previously
                              cached session or even the previous session unless
                              SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION is set */

    SEC_INT iQuiet_shutdown;    /* don't send shutdown packets */
    SEC_INT iShutdown;          /* we have shut things down, 0x01 sent, 0x02 for received */
    SEC_INT iState;             /* where we are */
    SEC_INT iRState;            /* where we are when reading */
#ifdef SSL_BUFFER
    struct buf_mem_st *psslBuffer;  /* ssl buffer */ 
#endif

    struct buf_mem_st *pInitBuffer;         /* buffer used during init */
    SEC_VOID *pInitMsg;         /* pointer to handshake message body, set by ssl3_get_message() */
    SEC_INT iInitNum;           /* amount read/written */
    SEC_INT iInitOff;           /* amount read/written */


    SEC_UCHAR *pucPacket;   /* used internally to point at a raw packet */
    SEC_UINT uiPacketLength; /*packet length*/ 

    struct stSSL2State *pstSSL2;    /* SSLv2 variables */
    struct stSSL3State *pstSSL3;    /* SSLv3 variables */
    

    SEC_INT iReadAhead;             /* Read as many input bytes as possible 
                                    (for non-blocking reads) */

    /* callback that allows applications to peek at protocol messages */
    SEC_VOID (*pfMsg_cb) (SEC_INT iWritePend, 
                              SEC_INT iVersion, 
                              SEC_INT iContentType, 
                              const SEC_VOID *pBuf, 
                              SEC_UINT len, 
                              struct stSSL *pstSSL, 
                              SEC_VOID *pArg);
    
    SEC_VOID *pMsgCallbackArg; /* arguments to pfMsg_cb */

    SEC_INT iHit;       /* reusing a previous session */

    X509_VERIFY_PARAM_S *pstParam; /*pointer to verify parameters.*/

    SEC_List_S *cipher_list;            /*List of Cipher*/
    SEC_List_S *cipher_list_by_id;      /*List of Cipher*/
    
    /* These are the ones being used, the ones in SSL_SESSION_S are
     * the ones to be 'copied' into these ones */

    CRYPT_CTX stEncReadCtx;             /* cryptographic state */
    SEC_ALGID_E enReadHash;     /* used for mac generation */

#ifndef SSL_NO_COMP
    COMP_CTX_S *pstExpand;              /* uncompress */
#else
    SEC_CHAR *pstExpand;            /* uncompress */
#endif

    CRYPT_CTX stEncwriteCtx;            /* cryptographic state */
    SEC_ALGID_E enWriteHash;            /* used for mac generation */

#ifndef SSL_NO_COMP
    COMP_CTX_S *pCompress;              /* compression */
#else
    SEC_CHAR *pCompress;        /* compression */
#endif

    /* session info */

    /* client cert? */
    /* This is used to hold the server certificate used */
    struct cert_st *pstCert;
    #if (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))
    /* This is used to hold the pre-shared key parameters*/
    struct stSSLPSKINFO stPSKInfo;

    /* This callback will input the PSK identity and search for the 
        respective PSK from among a list of PSKs at the server's side. */
    /* Return value :
    
     SEC_SUCCESS - on successful completion of searching 
                        the PSK identity and loading the output values.
                     
     SEC_ERROR - Error in parameters passed to the function 
                        or when the PSK with the said identity was not found.
    */

    SEC_INT (*pfGetPskByPskId_cb)(const char *PskId, SEC_INT PskIdLen, \
                unsigned char *Psk, SEC_INT *PskLen);


    /* This callback used to get PSK identity, PSK identity length, PSK and PSK
     * length using hint / with out using hint for client. callback function
     * should return PSK length. Any return value less than or equal to zero
     * and value more than MAX_PSK_LEN will be treated as error */

    unsigned int (*psk_client_callback)(struct stSSL *ssl, const char *hint, char *identity,
        unsigned int *identity_len, unsigned char *psk,
        unsigned int max_psk_len, SEC_VOID *pClientPskAppData);

    /* This callback used to get PSK using PSK identity for server.
     * callback function should return PSK length. Any return value
     * less than or equal to zero and value more than MAX_PSK_LEN
     * will be treated as error */

    unsigned int (*psk_server_callback)(struct stSSL *ssl, const char *identity, unsigned int pskIdLen,
        unsigned char *psk, unsigned int max_psk_len, SEC_VOID *pServerPskAppData);

    /* Application data for PSK client callback */
    SEC_VOID *pClientPskAppData;

    /* Application data for PSK server callback */
    SEC_VOID *pServerPskAppData;

#endif
    /* the session_id_context is used to ensure sessions are only reused
      in the appropriate context */
    SEC_UINT uiSidCtxLength;
    SEC_UCHAR aucSidCtx [SSL_MAX_SID_CTX_LENGTH];

    /* This can also be in the session once a session is established */
    SSL_SESSION_S *pstSession;

    /* Default generate session ID callback. */
    pfGenSession_cb generate_session_id;

    /* Used in SSL2 and SSL3 */
    SEC_INT iVerifyMode;        /* 0 don't care about verify failure
                                  1 fail if verify fails */

    SEC_INT (*pfVerify_cb) (SEC_INT iOk,
                                X509_STORE_CTX_S *pstStoreContext); /* fail if callback returns 0 */

    SEC_VOID (*pfInfoCallback) ( const struct stSSL *pstSSL,
                                SEC_INT iType,
                                SEC_INT iVal); /* optional informational callback */

    SEC_INT iError;     /* error bytes to be written */
    SEC_INT iErrorCode;     /* actual code */

    SSL_CTX_S *pstContext;
    /* set this flag to 1 and a sleep(1) is put into all SSL_read()
      and SSL_write() calls, good for nbio debuging :-) */
    SEC_INT iDebug; 

    /* extra application data */
    SEC_INT32 lVerifyResult;

    /* for server side, keep the list of CA_dn we can use */
    SEC_List_S *pClientCAList;
    
    SEC_INT iReferences;/* holds number of references.*/
    SEC_UINT32 ulOptions; /* protocol behavior */
    SEC_UINT32 ulMode; /* API behavior */
    SEC_INT32 lMaxCertList; /*max cert list that SSL object can hold.*/
    SEC_INT iFirstPacket; /* holds first packet*/
    SEC_INT iClientVersion; /* what was passed, used for SSLv3/TLS rollback check */
    
    /* params for EXTENSIONS */ 

// #ifndef SSL_NO_TLSEXT
    struct stTLSSessionExtn * pstTLSExtns;  /* holds the TLS extensions related data*/
//#endif
//#endif

    SEC_UINT  ulMaxPlainTextLen;  /*Max plain text length*/
    SEC_UINT  ulMaxCompDataLen;  /* Max compressed text length */
    SEC_UINT  ulMaxEncDataLen;   /* Max encrypted text length */
    SEC_UINT  ulMaxPktLen;      /* Max packet length */
    SEC_BOOL  bShortHMACFlag; /* Truncated HMAC flag*/
    SSLSOCKREAD_CB pfSockRead_cb; //Structure members changed based on new typedef's to keep it inline with sock_read callback setting function change.
    SSLSOCKWRITE_CB pfSockWrite_cb; //Structure members changed based on new typedef's to keep it inline with sock_read callback setting function change.

    IPSISSLSOCKREAD_CB pfIpsiSockRead_cb; //Structure members changed based on new typedef's to keep it inline with sock_read callback setting function change.
    void *pIpsiReadCbUserData;//Userdata that can be provided in the above callback during sock_read callback
    IPSISSLSOCKWRITE_CB pfIpsiSockWrite_cb;//Structure members changed based on new typedef's to keep it inline with sock_write callback setting function change.
    void *pIpsiWriteCbUserData;//Userdata that can be provided in the above callback during sock_write callback

    /* Vinay Gudur */
    SEC_ALGID_E EncAlgid;   

#ifndef IPSI_SSL_NO_DTLS
    struct stIpsiDTLS1State *pstDTLS1State;    /* DTLS1 variables */

    //structure for read/write AIO
    IPSI_RWAIO_S stRWAio;

    //structure for cookie callback
    struct stIpsiDTLS1CtxInfo *pstCookiecb;

    IPSI_CB_APPDATA_S stSslAppData;
#endif

    SEC_UINT uiCtrlBehav;

#ifndef IPSI_NO_TLS12

    IPSI_TLS12_SUPPORTED_SIGN_HASH_S stSrvSignHash;
    SEC_BOOL bIsExplicitCiphSet;

#endif

    /* This will be available in the pstStoreContext of the 
    *  callback pfVerify_cb */
    SEC_VOID *pVerifyCBAppData;

    SEC_UINT uiAlertFlag;

    IPSI_SSL_RENEG_MANAG_CB pfRenegManag_cb;
    SEC_VOID* pvRenegManagAppData;
    SEC_INT iRenegotiate;
} SSL_S;



/* Callback Functions and Macros to set the Message to SSL and SSL Context */
/*
    Func Name:  SSL_ctxSetMsg_cb()
*/

/**
* @defgroup SSL_ctxSetMsg_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxSetMsg_cb ( SSL_CTX_S *pstContext, 
* SEC_VOID (*cb) (SEC_INT iWritePending, 
* SEC_INT iVersion, 
* SEC_INT iContentType, 
* const SEC_VOID *pBuffer, 
* SEC_UINT stLen, 
* SSL_S *pstSSL, 
* SEC_VOID *pArg));
* @endcode
* 
* @par Purpose
* This is used to define a callback function for observing all TLS protocol messages.
* 
* @par Description
* SSL_ctxSetMsg_cb function can be used to define a message callback function for observing all TLS protocol messages
* (such as handshake messages) that are received or sent.
* 
* @param[in] pstContext Pointer to SSL Context. [N/A]
* @param[in] cb When cb is called by the TLS library for a protocol message, the function arguments have the following
* meaning:\n\n
* i)  iWritePending\n
*     This flag is 0 when a protocol message has been received and 1 when a protocol message has been sent.\n\n
* ii) iVersion\n
*     The protocol version according to which the protocol message is interpreted by the library. Currently, this is one
*     of SSL2_VERSION, SSL3_VERSION, TLS1_VERSION, TLS11_VERSION and TLS12_VERSION (for SSL 2.0, SSL 3.0, TLS 1.0,
*     TLS 1.1, TLS 1.2 respectively).\n\n
* iii) iContentType\n
*      In the case of SSL 2.0, this is always 0. In the case of SSL 3.0, TLS 1.0, TLS 1.1 or TLS 1.2, this is one of
*      the ContentType values defined in the protocol specification (change_cipher_spec(20), alert(21), handshake(22);
*      but never application_data(23) because the callback will only be called for protocol messages).\n\n
* iv) pBuffer, stLen\n
*     pBuffer points to a buffer containing the protocol message, which consists of stLen bytes. The buffer is no longer
*     valid after the callback function has returned.\n\n
* v) pstSSL\n
*    The pstSSL object that received or sent the message.\n\n
* vi) pArg\n
*    The user-defined argument optionally defined by SSL_CTX_SETMSG_CALLBACKARG_CB() or SSL_SETMSG_CALLBACKARG_CB().[N/A]
* 
* @retval SEC_INT32 On Success. [TLS_SUCCESS|N/A]
* @retval SEC_INT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If NULL is passed as function pointer, then this API fails with SEC_ERROR as return value.\n

* 
* @par Related Topics
* SSL_setMsg_cb.
*/


 SSLLINKDLL SEC_INT32 SSL_ctxSetMsg_cb ( SSL_CTX_S *pstContext, 
                                    SEC_VOID (*cb) (SEC_INT iWritePending, 
                                                    SEC_INT iVersion, 
                                                    SEC_INT iContentType, 
                                                    const SEC_VOID *pBuffer, 
                                                    SEC_UINT stLen, 
                                                    SSL_S *pstSSL, 
                                                    SEC_VOID *pArg));

/*
    Func Name:  SSL_setMsg_cb()
*/
 
/**
* @defgroup SSL_setMsg_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_setMsg_cb (SSL_S *pstSSL,
* SEC_VOID (*cb) ( SEC_INT iWritePending, 
* SEC_INT iVersion, 
* SEC_INT iContentType, 
* const SEC_VOID *pBuffer, 
* SEC_UINT stLen, 
* SSL_S *pstSSL, 
* SEC_VOID *pArg));
* @endcode
* 
* @par Purpose
* This is used to define a message callback function cb for observing all TLS protocol messages.
* 
* @par Description
* SSL_ctxSetMsg_cb or SSL_setMsg_cb function can be used to define a message callback function cb for observing all TLS
* protocol messages (such as handshake messages) that are received or sent.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] cb When cb is called by the TLS library for a protocol message, the function arguments have the following
* meaning:\n\n
* i)  iWritePending\n
*     This flag is 0 when a protocol message has been received and 1 when a protocol message has been sent.\n\n
* ii) iVersion\n
*     The protocol version according to which the protocol message is interpreted by the library. Currently, this is one
*     of SSL2_VERSION, SSL3_VERSION, TLS1_VERSION, TLS11_VERSION and TLS12_VERSION (for SSL 2.0, SSL 3.0, TLS 1.0,
*     TLS 1.1 and TLS 1.2 respectively).\n\n
* iii) iContentType\n
*      In the case of SSL 2.0, this is always 0. In the case of SSL 3.0,TLS 1.0, TLS 1.1 or TLS 1.2, this is one of the
*      ContentType values defined in the protocol specification (change_cipher_spec(20), alert(21), handshake(22); but
*      never application_data(23) because the callback will only be called for protocol messages).\n\n
* iv)  pBuffer, stLen\n
*      pBuffer points to a buffer containing the protocol message, which consists of stLen bytes. The buffer is no longer
*      valid after the callback function has returned.\n\n
* v)   pstSSL\n
*      The pstSSL object that received or sent the message.\n\n
* vi)  pArg\n
*      The user-defined argument optionally defined by SSL_CTX_SETMSG_CALLBACKARG_CB() or SSL_SETMSG_CALLBACKARG_CB(). [N/A]
* 
* @retval SEC_INT32 On Success [TLS_SUCCESS|N/A]
* @retval SEC_INT32 If the input is invalid(NULL pointer is passed as input)[SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If NULL is passed as function pointer, then this API fails with SEC_ERROR as return value.\n
* 
* @par Related Topics
* SSL_ctxSetMsg_cb.
*/

 SSLLINKDLL SEC_INT32 SSL_setMsg_cb (SSL_S *pstSSL,
                               SEC_VOID (*cb) ( SEC_INT iWritePending, 
                                                SEC_INT iVersion, 
                                                SEC_INT iContentType, 
                                                const SEC_VOID *pBuffer, 
                                                SEC_UINT stLen, 
                                                SSL_S *pstSSL, 
                                                SEC_VOID *pArg));

/** SSL_SETMSG_CALLBACKARG_CB() can be used to set 
*   argument pArg to the callback function to the ssl context, which is available for arbitrary application use. 
*   And you should not let it be null, otherwise the callback function set by SSL_setMsg_cb will not execute.
*       
*    TLS_SUCCESS : If the pArg is set
*    SEC_ERROR   : If the invalid input (NULL pointers)
*/

#define SSL_CTX_SETMSG_CALLBACKARG_CB(pstContext, pArg)\
    SSL_ctxCtrl((pstContext), SSL_CTRL_SET_MSG_CALLBACK_ARG, 0, (pArg))

 /** SSL_SETMSG_CALLBACKARG_CB() can be used to set 
*   argument pArg to the callback function to the ssl object, which is available for arbitrary application use. 
*   And you should not let it be null, otherwise the callback function set by SSL_setMsg_cb will not execute.
*       
*    TLS_SUCCESS : If the pArg is set
*    SEC_ERROR   : If the invalid input (NULL pointers)
*/
#define SSL_SETMSG_CALLBACKARG_CB(pstSSL, pArg)\
    SSL_ctrl((pstSSL), SSL_CTRL_SET_MSG_CALLBACK_ARG, 0, (pArg))




#define SSL_MAX_CERT_LIST_DEFAULT               (1024*100) /* 100k max cert list :-) */


#define SSL_SESSION_CACHE_MAX_SIZE_DEFAULT      (1024*20)


/* The following are the possible values for ssl->state are are
 * used to indicate where we are up to in the SSL_S connection establishment.
 * The macros that follow are about the only things you should need to use
 * and even then, only when using non-blocking IO.
 * It can also be useful to work out where you were when the connection
 * failed */

#define SSL_ST_CONNECT                  0x1000
#define SSL_ST_ACCEPT                   0x2000
#define SSL_ST_MASK                     0x0FFF
#define SSL_ST_INIT                     (SSL_ST_CONNECT | SSL_ST_ACCEPT)
#define SSL_ST_BEFORE                   0x4000
#define SSL_ST_OK                       0x03
#define SSL_ST_RENEGOTIATE              (0x04 | SSL_ST_INIT)

#define SSL_CB_LOOP                     0x01
#define SSL_CB_EXIT                     0x02
#define SSL_CB_READ                     0x04
#define SSL_CB_WRITE                    0x08
#define SSL_CB_ALERT                    0x4000  /* used in callback */
#define SSL_CB_READ_ALERT               (SSL_CB_ALERT | SSL_CB_READ)
#define SSL_CB_WRITE_ALERT              (SSL_CB_ALERT | SSL_CB_WRITE)
#define SSL_CB_ACCEPT_LOOP              (SSL_ST_ACCEPT | SSL_CB_LOOP)
#define SSL_CB_ACCEPT_EXIT              (SSL_ST_ACCEPT | SSL_CB_EXIT)
#define SSL_CB_CONNECT_LOOP             (SSL_ST_CONNECT| SSL_CB_LOOP)
#define SSL_CB_CONNECT_EXIT             (SSL_ST_CONNECT | SSL_CB_EXIT)
#define SSL_CB_HANDSHAKE_START          0x10
#define SSL_CB_HANDSHAKE_DONE           0x20
#define SSL_CB_BAD_RECORD_MAC           0x40


/* Is the SSL_connection established? */

/* Returns the state of the SSL */
#define SSL_getState(a)             SSL_state(a)

/* The macro checks whether the state is in SSL_ST_OK.  This is the final state during 
    handshake*/
#define SSL_isInitFinished(a)           (SSL_state(a) == SSL_ST_OK)

/* The macro checks whether the state is in SSL_ST_INIT.  The init state is different
    for server and client.  The client is in SS_ST_CONNECT and server in SSL_ST_ACCEPT
    before connection.  This function checks whether server or client are in initial state.*/
#define SSL_inInit(a)                   (SSL_state(a) & SSL_ST_INIT)

/* This macro is used to check the state of SSL is SSL_ST_BEFORE or not.*/
#define SSL_inBefore(a)             (SSL_state(a) & SSL_ST_BEFORE)

/* This macro is used to check the state of SSL is SSL_ST_CONNECT or not.*/
#define SSL_inConnectInit(a)            (SSL_state(a) & SSL_ST_CONNECT)

/* This macro is used to check the state of SSL is SSL_ST_ACCEPT or not.*/
#define SSL_inAcceptInit(a)         (SSL_state(a) & SSL_ST_ACCEPT)

/* The following 2 states are kept in ssl->rstate when reads fail,
 * you should not need these */
#define SSL_ST_READ_HEADER              0xF0
#define SSL_ST_READ_BODY                0xF1
#define SSL_ST_READ_DONE                0xF2


/*
    Func Name:  SSL_getFinished
*/
 
/**
* @defgroup SSL_getFinished
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_UINT SSL_getFinished  (const SSL_S *pstSSL,
* SEC_VOID *pBuf,
* SEC_UINT count);
* @endcode
* 
* @par Purpose
* This is used to get the latest finished message sent to the peer.
* 
* @par Description
* SSL_getFinished function gets the latest finished message sent to the peer of length equal to count.
*
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] count It is the length of the finished message. [N/A]
* @param[out] pBuf Buffer to hold the message. [N/A]
* 
* @retval SEC_UINT  On success it returns length of the last finished message. [Length of the last finished message|N/A]
* @retval SEC_UINT  On failure. [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getPeerFinished.
*/

 SSLLINKDLL SEC_UINT SSL_getFinished  ( const SSL_S *pstSSL, 
                            SEC_VOID *pBuf, 
                            SEC_UINT count);

/*
    Func Name:  SSL_getPeerFinished
*/
 
/**
* @defgroup SSL_getPeerFinished
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_UINT SSL_getPeerFinished (const SSL_S *pstSSL,
* SEC_VOID *pBuf,
* SEC_UINT count);
* @endcode
* 
* @par Purpose
* This is used to get the latest finished message expected from the peer.
* 
* @par Description
* SSL_getPeerFinished function gets the latest finished message expected form the peer of length equal to count.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] count It is the length of the finished message expected from the peer. [N/A]
* @param[out] pBuf Buffer to hold the message. [N/A]
* 
* @retval SEC_UINT  On success it returns length of the last finished message. [Length of the last finished message|N/A]
* @retval SEC_UINT  On failure it returns SEC_NULL. [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getFinished.
*/


 SSLLINKDLL SEC_UINT SSL_getPeerFinished  (const SSL_S *pstSSL,
                               SEC_VOID *pBuf,
                               SEC_UINT count);


/* use either SSL_VERIFY_NONE or SSL_VERIFY_PEER, the last 2 options
 * are 'ored' with SSL_VERIFY_PEER if they are desired */

#define SSL_VERIFY_NONE                 0x00
#define SSL_VERIFY_PEER                 0x01
#define SSL_VERIFY_FAIL_IF_NO_PEER_CERT 0x02

/* This option is deprecated & should not use this option */
#define SSL_VERIFY_CLIENT_ONCE          0x04

/* RSA Export Key Length */
#define RSA_EXPORT_KEY_LEN      (512)

/* Macro to get the CipherName and CipherBits */
#define SSL_GETCIPHERBITS(s,np) \
        SSL_cipherGetBits(SSL_getCurrentCipher(s),np)/* return number of bits used in the current cipher */
#define SSL_GETCIPHERNAME(s) \
        SSL_cipherGetName(SSL_getCurrentCipher(s))/* return name of current cipher */

/* SSL_GETTIME returns the time at which the session was established. 
    The time is given in seconds since the Epoch and therefore compatible 
    to the time delivered by the time() call. */
#define SSL_GETTIME(a)      SSL_sessionGetTime(a)

/* Sets the time field in SSL structure*/
#define SSL_SETTIME(a,b)    SSL_sessionSetTime((a),(b))

/* Returns the timeout value which are retrieved from Session structure */
#define SSL_GETTIMEOUT(a)   SSL_sessionGetTimeout(a)

/* Sets the timeout to the Session structure in SSL structure.  First parameter is 
     the SSL structure and next parameter is the timeout value*/
#define SSL_SETTIMEOUT(a,b) SSL_sessionSetTimeout((a),(b))


#define SSL_AD_REASON_OFFSET            1000

/* These alert types are for SSLv3 and TLSv1 */
#define SSL_AD_CLOSE_NOTIFY             SSL3_AD_CLOSE_NOTIFY
#define SSL_AD_UNEXPECTED_MESSAGE       SSL3_AD_UNEXPECTED_MESSAGE /* fatal */
#define SSL_AD_BAD_RECORD_MAC           SSL3_AD_BAD_RECORD_MAC     /* fatal */
#define SSL_AD_DECRYPTION_FAILED        TLS1_AD_DECRYPTION_FAILED
#define SSL_AD_RECORD_OVERFLOW          TLS1_AD_RECORD_OVERFLOW
#define SSL_AD_DECOMPRESSION_FAILURE    SSL3_AD_DECOMPRESSION_FAILURE/* fatal */
#define SSL_AD_HANDSHAKE_FAILURE        SSL3_AD_HANDSHAKE_FAILURE/* fatal */
#define SSL_AD_NO_CERTIFICATE           SSL3_AD_NO_CERTIFICATE /* Not for TLS */
#define SSL_AD_BAD_CERTIFICATE          SSL3_AD_BAD_CERTIFICATE
#define SSL_AD_UNSUPPORTED_CERTIFICATE  SSL3_AD_UNSUPPORTED_CERTIFICATE
#define SSL_AD_CERTIFICATE_REVOKED      SSL3_AD_CERTIFICATE_REVOKED
#define SSL_AD_CERTIFICATE_EXPIRED      SSL3_AD_CERTIFICATE_EXPIRED
#define SSL_AD_CERTIFICATE_UNKNOWN      SSL3_AD_CERTIFICATE_UNKNOWN
#define SSL_AD_ILLEGAL_PARAMETER        SSL3_AD_ILLEGAL_PARAMETER   /* fatal */
#define SSL_AD_UNKNOWN_CA               TLS1_AD_UNKNOWN_CA  /* fatal */
#define SSL_AD_ACCESS_DENIED            TLS1_AD_ACCESS_DENIED   /* fatal */
#define SSL_AD_DECODE_ERROR             TLS1_AD_DECODE_ERROR    /* fatal */
#define SSL_AD_DECRYPT_ERROR            TLS1_AD_DECRYPT_ERROR
#define SSL_AD_EXPORT_RESTRICTION       TLS1_AD_EXPORT_RESTRICTION/* fatal */
#define SSL_AD_PROTOCOL_VERSION         TLS1_AD_PROTOCOL_VERSION /* fatal */
#define SSL_AD_INSUFFICIENT_SECURITY    TLS1_AD_INSUFFICIENT_SECURITY/* fatal */
#define SSL_AD_INTERNAL_ERROR           TLS1_AD_INTERNAL_ERROR  /* fatal */
#define SSL_AD_USER_CANCELLED           TLS1_AD_USER_CANCELLED
#define SSL_AD_NO_RENEGOTIATION         TLS1_AD_NO_RENEGOTIATION
#if  (!defined(SSL_NO_PSK)  || !defined(SSL_NO_DH_PSK))
#define SSL_AD_UNKNOWN_PSK_IDENTITY     TLS1_AD_UNKNOWN_PSK_IDENTITY  /* fatal */
#endif
#define SSL_AD_INAPPROPRIATE_FALLBACK   TLS1_AD_INAPPROPRIATE_FALLBACK /* fatal */


/* These alert types are for TLS extensions */
#define SSL_AD_UNSUPPORTED_EXTENSION                TLS1_AD_UNSUPPORTED_EXTENSION      /*fatal*/
#define SSL_AD_CERTIFICATE_UNOBTAINABLE             TLS1_AD_CERTIFICATE_UNOBTAINABLE
#define SSL_AD_UNRECOGNIZED_NAME                    TLS1_AD_UNRECOGNIZED_NAME
#define SSL_AD_BAD_CERTIFICATE_STATUS_RESPONSE      TLS1_AD_BAD_CERTIFICATE_STATUS_RESPONSE
#define SSL_AD_BAD_CERTIFICATE_HASH_VALUE           TLS1_AD_BAD_CERTIFICATE_HASH_VALUE


#define SSL_ERROR_NONE                          0
#define SSL_ERROR_SSL                           1
#define SSL_ERROR_WANT_READ                     2
#define SSL_ERROR_WANT_WRITE                    3
#define SSL_ERROR_WANT_X509_LOOKUP              4
#define SSL_ERROR_SYSCALL                       5 /* look at error stack/return value/errno */
#define SSL_ERROR_ZERO_RETURN                   6
#define SSL_ERROR_WANT_CONNECT                  7
#define SSL_ERROR_WANT_ACCEPT                   8

#define SSL_ERROR_RENEGOTIATION_REJECTED    9


#define SSL_CTRL_NEED_TMP_RSA                   1
#define SSL_CTRL_SET_TMP_RSA                    2
#define SSL_CTRL_SET_TMP_DH                     3
#define SSL_CTRL_SET_TMP_ECDH                   4
#define SSL_CTRL_SET_TMP_RSA_CB                 5
#define SSL_CTRL_SET_TMP_DH_CB                  6
#define SSL_CTRL_SET_TMP_ECDH_CB                7

#define SSL_CTRL_GET_SESSION_REUSED             8
#define SSL_CTRL_GET_CLIENT_CERT_REQUEST        9
#define SSL_CTRL_GET_NUM_RENEGOTIATIONS         10
#define SSL_CTRL_CLEAR_NUM_RENEGOTIATIONS       11
#define SSL_CTRL_GET_TOTAL_RENEGOTIATIONS       12
#define SSL_CTRL_GET_FLAGS                      13
#define SSL_CTRL_EXTRA_CHAIN_CERT               14

#define SSL_CTRL_SET_MSG_CALLBACK               15
#define SSL_CTRL_SET_MSG_CALLBACK_ARG           16

#ifndef IPSI_SSL_NO_DTLS
/* only applies to datagram connections */
#define SSL_CTRL_SET_MTU                        17
#endif
/* Stats */
#define SSL_CTRL_SESS_NUMBER                    20
#define SSL_CTRL_SESS_CONNECT                   21
#define SSL_CTRL_SESS_CONNECT_GOOD              22
#define SSL_CTRL_SESS_CONNECT_RENEGOTIATE       23
#define SSL_CTRL_SESS_ACCEPT                    24
#define SSL_CTRL_SESS_ACCEPT_GOOD               25
#define SSL_CTRL_SESS_ACCEPT_RENEGOTIATE        26
#define SSL_CTRL_SESS_HIT                       27
#define SSL_CTRL_SESS_CB_HIT                    28
#define SSL_CTRL_SESS_MISSES                    29
#define SSL_CTRL_SESS_TIMEOUTS                  30
#define SSL_CTRL_SESS_CACHE_FULL                31
#define SSL_CTRL_OPTIONS                        32
#define SSL_CTRL_MODE                           33

#define SSL_CTRL_GET_READ_AHEAD                 40
#define SSL_CTRL_SET_READ_AHEAD                 41
#define SSL_CTRL_SET_SESS_CACHE_SIZE            42
#define SSL_CTRL_GET_SESS_CACHE_SIZE            43
#define SSL_CTRL_SET_SESS_CACHE_MODE            44
#define SSL_CTRL_GET_SESS_CACHE_MODE            45

#define SSL_CTRL_GET_MAX_CERT_LIST              50
#define SSL_CTRL_SET_MAX_CERT_LIST              51
#ifndef IPSI_SSL_NO_DTLS
#define SSL_CTRL_SET_DTLS_MAX_RETRIES           52
#define SSL_CTRL_GET_DTLS_MAX_RETRIES           53
#endif 

/* Command to get secure renegotiation support */
#define SSL_CTRL_GET_RI_SUPPORT                 54


#ifndef IPSI_NO_TLS12
#define SSL_CTRL_SET_VER_DH_CB                  55
#endif

#define SSL_CTRL_BEHAVIOUR_OPTIONS              56

#define SSL_CTRL_GET_NUM_PEER_RENEGOTIATIONS    57

#define SSL_CLEAR_CTRL_BEHAVIOUR_OPTIONS        58

#define SSL_CTRL_CLEAR_NUM_PEER_RENEGOTIATIONS  59

#define SSL_CTRL_CHECK_PROTO_VERSION            60

/** Query, whether a reused session was negotiated during the handshake. 
    0 is returned, if a new session was negotiated
    1 is returned, if a session was reused */
#define SSL_SESSION_REUSED(ssl) \
    SSL_ctrl((ssl),SSL_CTRL_GET_SESSION_REUSED,0,SEC_NULL)

/** This macro is used to collect the number of renegotiations did on the SSL object*/
#define SSL_NUMRENEGOTIATIONS(ssl) \
    SSL_ctrl((ssl),SSL_CTRL_GET_NUM_RENEGOTIATIONS,0,SEC_NULL)
/** Clear stats related to number of renegotiations */
#define SSL_CLEAR_NUM_RENEGOTIATIONS(ssl) \
    SSL_ctrl((ssl),SSL_CTRL_CLEAR_NUM_RENEGOTIATIONS,0,SEC_NULL)/* Clear stats related to number of renegotiations */

/** This macro is used to collect the total number of renegotiations did on the SSL object*/
#define SSL_TOTALRENEGOTIATIONS(ssl) \
    SSL_ctrl((ssl),SSL_CTRL_GET_TOTAL_RENEGOTIATIONS,0,SEC_NULL)

/** Returns 1, if a temporary/ephemeral RSA key is needed for 
    RSA-based strength-limited 'exportable' ciphersuites 
    because a RSA key with a keysize larger than 512 bits is installed*/
#define SSL_CTX_NEED_TEMPRSA(ctx) \
    SSL_ctxCtrl(ctx,SSL_CTRL_NEED_TMP_RSA,0,SEC_NULL)

/** SSL_CTX_SET_TEMPRSA() sets the temporary/ephemeral RSA key to be used to be rsa. 
    The key is inherited by all SSL objects newly created from ctx with                                                         
    SSL_new(). Already created SSL objects are not affected. */

#define SSL_CTX_SET_TEMPRSA(ctx,rsa) \
    SSL_ctxCtrl(ctx,SSL_CTRL_SET_TMP_RSA,0,(SEC_CHAR *)rsa)

/** SSL_CTX_SET_TEMPDH() sets DH parameters to be used to be dh. The key is 
    inherited by all ssl objects created from ctx. */

#define SSL_CTX_SET_TEMPDH(ctx,dh) \
    SSL_ctxCtrl(ctx,SSL_CTRL_SET_TMP_DH,0,(SEC_CHAR *)dh)
/** SSL_CTX_SET_TMP_ECDH() sets ECDH parameters to be used to be ecdh for the ssl conetxt. */
#define SSL_CTX_SET_TMP_ECDH(ctx,ecdh) \
    SSL_ctxCtrl(ctx,SSL_CTRL_SET_TMP_ECDH,0,(SEC_CHAR *)ecdh)

/** Returns 1, if a temporary/ephemeral RSA key is needed for 
    RSA-based strength-limited 'exportable' ciphersuites 
    because a RSA key with a keysize larger than 512 bits is installed*/
#define SSL_NEED_TEMPRSA(ssl) \
    SSL_ctrl(ssl,SSL_CTRL_NEED_TMP_RSA,0,SEC_NULL)
/** Sets the temporary/ephemeral RSA key to be used to be rsa, only for ssl object.  */
#define SSL_SET_TEMPRSA(ssl,rsa) \
    SSL_ctrl(ssl,SSL_CTRL_SET_TMP_RSA,0,(SEC_CHAR *)rsa)
/** sets DH parameters to be used to be dh, only for the ssl object */
#define SSL_SET_TEMPDH(ssl,dh) \
    SSL_ctrl(ssl,SSL_CTRL_SET_TMP_DH,0,(SEC_CHAR *)dh)
/** SSL_SET_TEMPECDH() sets ECDH parameters to be used to be ecdh for the ssl conetxt. */
#define SSL_SET_TEMPECDH(ssl,ecdh) \
    SSL_ctrl(ssl,SSL_CTRL_SET_TMP_ECDH,0,(SEC_CHAR *)ecdh)
    
/** The SSL_CTX_ADD_EXTRACHAINCERT() function adds the certificate x509 
    to the certificate chain presented together with the certificate.                                                                   
    Several certificates can be added one after the other*/ 
#define SSL_CTX_ADD_EXTRACHAINCERT(ctx,x509) \
    SSL_ctxCtrl(ctx,SSL_CTRL_EXTRA_CHAIN_CERT,0,(SEC_CHAR *)x509)

#define SSL_SET_MAX_RETRIES(ssl,max_retries) \
    SSL_ctrl((ssl),SSL_CTRL_SET_DTLS_MAX_RETRIES,max_retries,SEC_NULL)

#define SSL_GET_MAX_RETRIES(ssl) \
    SSL_ctrl((ssl),SSL_CTRL_GET_DTLS_MAX_RETRIES,NULL,SEC_NULL)


/** This macro is used to collect the number of renegotiations requested from peer side on the SSL object*/
#define SSL_NUM_PEER_RENEGOTIATIONS(ssl) \
    SSL_ctrl((ssl), SSL_CTRL_GET_NUM_PEER_RENEGOTIATIONS, 0, SEC_NULL)

/** This macro is used to reset the counter which holds the number of renegotiation requested from peer side 
    on the SSL object. The return value of this macro function will be the value which that counter holds before 
    resetting. */
#define SSL_CLEAR_NUM_PEER_RENEGOTIATIONS(ssl) \
    SSL_ctrl((ssl), SSL_CTRL_CLEAR_NUM_PEER_RENEGOTIATIONS, 0, SEC_NULL)

/*
    Func Name:  SSL_ctxSetCipherList
*/
 
/**
* @defgroup SSL_ctxSetCipherList
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetCipherList (SSL_CTX_S *pstCtx,
* const SEC_INT ciphers[], 
* const SEC_INT iCipherNum);
* @endcode
* 
* @par Purpose
* This is used to set the list of available ciphers to the SSL context.
* 
* @par Description
* SSL_ctxSetCipherList function sets the list of available ciphers for SSL context using the cipher set ciphers[].
* The list of ciphers is inherited by all SSL objects created from SSL context.
* 
* @param[in] pstCtx Pointer to SSL Context. [N/A]
* @param[in] ciphers Array of ciphers. [N/A]
* @param[in] iCipherNum Number of ciphers in an array. [N/A]
* 
* @retval SEC_INT Function was successful. [TLS_SUCCESS|N/A]
* @retval SEC_INT An error occurred. [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* 1. If this function is not called, the SSL_DEFAULT_CIPHER_LIST will be used for the context.\n
* 2. If SSL_CTRL_BEHAV_RESTRICT_TLS12_CIPHERS_TO_TLS12_VERSION is enabled, then all TLS 1.2 ciphers will be 
* filtered from the list of ciphers passed to this API, if the SSL method version is specific to SSL 2, SSL 3, TLS 1.0 
* or TLS 1.1.\n
* 
* @par Related Topics
* SSL_ctxAddCipherToList,\n
* SSL_setCipherList,\n
* SSL_getCiphers,\n
* SSL_getCipherList,\n
* SSL_getCurrentCipher,\n
* SSL_getSharedCiphers.
*/


 SSLLINKDLL SEC_INT SSL_ctxSetCipherList (SSL_CTX_S *pstCtx,
                              const SEC_INT ciphers[], 
                              const SEC_INT iCipherNum);


/*
    Func Name: SSL_ctxAddCipherToList
*/

/**
* @defgroup SSL_ctxAddCipherToList
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxAddCipherToList (SSL_CTX_S *pstSSL,
* const SEC_INT iCipher);
* @endcode
* 
* @par Purpose
* This is used to add the given cipher to the SSL context.
* 
* @par Description
* SSL_ctxAddCipherToList function adds the given cipher to the SSL context object with top priority to the existing
* cipher list.
* 
* @param[in] pstSSL SSL context object. [N/A]
* @param[in] iCipher New cipher. [N/A]
* 
* @retval SEC_INT If the cipher is set. [TLS_SUCCESS|N/A]
* @retval SEC_INT If the cipher could not be set. [SEC_ERROR|N/A]
* @retval SEC_INT If an error occur. [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If SSL_CTRL_BEHAV_RESTRICT_TLS12_CIPHERS_TO_TLS12_VERSION is enabled, then all TLS 1.2 ciphers will be 
* removed from the final list of ciphers if the SSL method version is specific to SSL 2, SSL 3, TLS 1.0 or TLS 1.1.
* \n
* 
* @par Related Topics
* SSL_ctxSetCipherList.
*/

 SSLLINKDLL SEC_INT SSL_ctxAddCipherToList (SSL_CTX_S *pstSSL, 
                                const SEC_INT iCipher);

/*
    Func Name: SSL_ctxNew
*/

/**
* @defgroup SSL_ctxNew
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SSL_CTX_S *SSL_ctxNew(SSL_METHOD_S *pstMeth);
* @endcode
* 
* @par Purpose
* This is used to create a new SSL context object.
* 
* @par Description
* SSL_ctxNew function creates a new SSL_CTX_S object as framework for TLS/SSL enabled functions.
* 
* @param[in] pstMeth SSL method. [N/A]
*
* @retval SSL_CTX_S* Pointer to SSL_CTX_S which points to an allocated SSL_CTX_S object. [Pointer to the SSL context|N/A]
* @retval SSL_CTX_S* SEC_NULL is returned if the creation of a new SSL_CTX_S object failed.
* Failure can happen in case of malloc failure or input method passed is NULL [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_New,\n SSL_ctxFree,\n
* SSL_ctxExNew,\n
* \n
* SSLv2_method,\n
* SSLv2_serverMethod,\n
* SSLv2_clientMethod,\n 
* SSLv3_method,\n
* SSLv3_serverMethod,\n
* SSLv3_clientMethod,\n 
* TLSv1_method,\n
* TLSv1_serverMethod,\n
* TLSv1_clientMethod,\n 
* TLSv11_method,\n
* TLSv11_serverMethod,\n
* TLSv11_clientMethod,\n 
* SSL_method,\n
* SSL_serverMethod,\n
* SSL_clientMethod,\n
* TLSv12_method,\n
* TLSv12_serverMethod,\n
* TLSv12_clientMethod.
*/

SSLLINKDLL SSL_CTX_S *SSL_ctxNew(SSL_METHOD_S *pstMeth);


/*
    Func Name:  SSL_ctxFree
*/

/**
* @defgroup SSL_ctxFree
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_VOID SSL_ctxFree (SSL_CTX_S *pstContext);
* @endcode
* 
* @par Purpose
* This is used to free an SSL context object.
* 
* @par Description
* SSL_ctxFree function decrements the reference count of context, and removes the SSL_CTX_S object pointed to by ctx
* and frees up the allocated memory, if the reference count has reached 0.
* 
* @param[in] pstContext Pointer to SSL context. [N/A]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxNew.
*/

SSLLINKDLL SEC_VOID SSL_ctxFree ( SSL_CTX_S *pstContext);


/*
    Func Name:  SSL_ctxSetTimeout
*/
 
/**
* @defgroup SSL_ctxSetTimeout
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxSetTimeout (SSL_CTX_S *pstContext,
* SEC_INT32 lTimeOut);
* @endcode
* 
* @par Purpose
* This is used to set the timeout value for a newly created session.
* 
* @par Description
* SSL_ctxSetTimeout function sets the timeout for newly created sessions for context to lTimeOut. lTimeOut must be given
* in seconds. It is used to manipulate timeout values for session caching.
* 
* @param[in] pstContext Pointer to SSL Context. [N/A]
* @param[in] lTimeOut Timeout value in seconds. [N/A]
* 
* @retval SEC_INT32 Returns the previously set timeout value. [Previously set timeout value|N/A]
* @retval SEC_INT32 In case of error. [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If this function is not called, the default timeout value will be used. For SSLv2, it is 5 minutes. For others,
*    it is 2 hours.\n\n
* 2. If lTimeOut<0, then the session can not be resumed.\n
*    If lTimeOut=0, then the session will never be timeout. Only when the session cache reaches its maximum size,
*    the session will be flushed out.
* 
* @par Related Topics
* SSL_ctxGetTimeout,\n
* SSL_getDefaultTimeout,\n
* SSL_sessionSetTimeout,\n
* SSL_sessionGetTimeout,\n
* SSL_sessionSetTime,\n
* SSL_sessionGetTime,\n
* SSL_CTX_SESS_SETCACHESIZE.
*/


SSLLINKDLL SEC_INT32 SSL_ctxSetTimeout (SSL_CTX_S *pstContext, 
                             SEC_INT32 lTimeOut);


/*
    Func Name: SSL_ctxGetTimeout
*/

/**
* @defgroup SSL_ctxGetTimeout
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxGetTimeout ( const SSL_CTX_S *pstContext);
* @endcode
* 
* @par Purpose
* This is used to get the currently set timeout value for SSL context.
* 
* @par Description
* SSL_ctxGetTimeout function returns the currently set timeout value for SSL_CTX_S context.
*                                                                          
* @param[in] pstContext SSL_CTX_S context structure from which the timeout is obtained. [N/A]
* 
* @retval SEC_INT32 If input parameter passed is null. [SEC_ERROR|N/A]
* @retval SEC_INT32 Timeout value (in seconds) set in SSL_CTX_S structure. [n|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* If we set the session’s timeout to -1, SSL_ctxGetTimeout will return -1. It is same as SEC_ERROR. We should
* avoid using this timeout value.
* 
* @par Related Topics
* SSL_ctxSetTimeout,\n
* SSL_getDefaultTimeout,\n
* SSL_sessionSetTimeout,\n
* SSL_sessionGetTimeout,\n
* SSL_sessionSetTime,\n
* SSL_sessionGetTime,\n
* SSL_CTX_SESS_SETCACHESIZE.
*/

SSLLINKDLL SEC_INT32 SSL_ctxGetTimeout ( const SSL_CTX_S *pstContext);

/*
    Func Name:  SSL_ctxGetCertStore
*/

/**
* @defgroup SSL_ctxGetCertStore
* @ingroup sslContextFunctions
* @par Prototype
* @code
* X509_STORE_S *SSL_ctxGetCertStore (const SSL_CTX_S *pstContext);
* @endcode
* 
* @par Purpose
* This is used to get the X509_STORE_S structure in the SSL_CTX_S structure.
* 
* @par Description
* SSL_ctxGetCertStore function gets the X509_STORE_S structure in the SSL_CTX_S structure. An X509_STORE_S
* structure holds information for certificate verification including cache of trusted certificate and a pointer to
* a certificate verification function.
* 
* @param[in] pstContext Pointer to SSL context structure. [N/A]
* 
* @retval X509_STORE_S* On success returns pointer to X509_STORE_S structure. [Valid pointer to X509 store structure|N/A]
* @retval X509_STORE_S* On failure returns a null pointer. [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetCertStore,\n
* X509_storeNew,\n
* X509_storeFree,\n
* X509_storeSetFlags,\n
* X509_storeSetTime,\n
* X509_storeAddCert,\n
* X509_storeAddCRL.
*/

SSLLINKDLL X509_STORE_S *SSL_ctxGetCertStore (const SSL_CTX_S *pstContext);


/*
    Func Name:  SSL_ctxSetCertStore
*/
 
/**
* @defgroup SSL_ctxSetCertStore
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetCertStore (SSL_CTX_S* pstContext,
* X509_STORE_S* pstStore);
* @endcode
* 
* @par Purpose
* This is used to set the X509_STORE_S structure to the SSL_CTX_S structure.
* 
* @par Description
* SSL_ctxSetCertStore function sets the X509_STORE_S structure to the SSL_CTX_S structure. In order to verify the
* certificates presented by the peer, trusted CA certificates are stored in X509_STORE_S structure that is used during
* certificate chain validation. From the X509_STORE_S the X509_STORE_CTX_S is used when verifying certificates.
* 
* @param[in] pstContext Pointer to SSL Context. [N/A]
* @param[in] pstStore Pointer to X509_STORE_S structure that has to be set to the SSL_CTX_S structure. [N/A]
* 
* @retval SEC_INT On success  [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL Pointer is passed) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxGetCertStore,\n
* X509_storeNew,\n
* X509_storeFree,\n
* X509_storeSetFlags,\n
* X509_storeSetTime,\n
* X509_storeAddCert,\n
* X509_storeAddCRL.
*/

SSLLINKDLL SEC_INT SSL_ctxSetCertStore (SSL_CTX_S* pstContext,
                              X509_STORE_S* pstStore);


/*
    Func Name:  SSL_want
*/

/**
* @defgroup SSL_want
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_want (const SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the state information of TLS/SSL I/O operation.
* 
* @par Description
* SSL_want function returns state information of TLS/SSL I/O operation for the SSL object ssl. SSL_WANTNOTHING,
* SSL_WANTREAD, SSL_WANTWRITE and SSL_WANTX509LOOKUP macros are shortcuts for the possible states returned by SSL_want.
* 
* @param[in] pstSSL Pointer to SSL_S object. [N/A]
* 
* @retval SEC_INT Returns the iRWState in SSL object. [SSL_NOTHING\n
* SSL_WRITING\n
* SSL_READING\n
* SSL_X509_LOOKUP|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed). [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* N/A
*/

SSLLINKDLL SEC_INT SSL_want (const SSL_S *pstSSL);

/*
    Func Name:  SSL_clear
*/

/**
* @defgroup SSL_clear
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_clear(SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to prepare an SSL object for a new connection.
* 
* @par Description
* SSL_clear function is used to prepare an SSL object for a new connection. While all settings are kept, a side effect
* is the handling of the current SSL session. If a session is still open, it is considered bad and will be removed from
* the session cache, as required by RFC2246. A session is considered open, if SSL_shutdown was not called for the
* connection or at least SSL_setShutdown was used to set the SSL_SENT_SHUTDOWN state. If a session was closed cleanly,
* the session object and all corresponding settings will be retained. For example, the special method used during the
* session will be kept for the next handshake. So if the session was a TLSv1 session, a SSL client object will use a
* TLSv1 client method for the next handshake and a SSL server object will use a TLSv1 server method, even if
* SSL_*methods were chosen on startup. This may lead to connection failures.
* 
* @param[in] pstSSL Pointer to SSL_S structure. [N/A]
* 
* @retval SEC_INT On Success [TLS_SUCCESS|N/A]
* @retval SEC_INT Operation could not be performed [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. SSL_clear function resets the SSL object to allow another connection. The reset operation however keeps several 
* settings of the last sessions (some of these settings were made automatically during the last handshake). It is 
* applicable for opening a new session (or reusing an old one) with the same peer that shares these settings.\n
* 2. SSL_clear() is not a short form for the sequence SSL_free(); SSL_new();.\n
* 3. SSL_clear function should be called only after a successful connection. It should not be called after a handshake
* is failed or during handshake is in progress.\n
* 4. Usage of this function is to do a new handshake(not renegotiation) after a successful handshake. This is not to do
* anything with a failed SSL object.\n
* 
* @par Related Topics
* SSL_new,\n
* SSL_free,\n
* SSL_shutdown,\n
* SSL_setShutdown.
*/

SSLLINKDLL SEC_INT  SSL_clear(SSL_S *pstSSL);


/*
    Func Name:  SSL_ctxFlushSessions
*/

/**
* @defgroup SSL_ctxFlushSessions
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_VOID SSL_ctxFlushSessions (SSL_CTX_S *pstContext,
* SEC_INT32 lTime);
* @endcode
* 
* @par Purpose
* This is used to remove sessions expired at a particular time.
* 
* @par Description
* SSL_ctxFlushSessions function causes a run through the session cache of pstContext to remove sessions expired at
* time (lTime).
* 
* @param[in] pstContext Pointer to SSL context. [N/A]
* @param[in] lTime Expiration time for determining sessions. [N/A]
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If enabled, the internal session cache will collect all sessions established up to the specified maximum number
*    (see SSL_CTX_SESS_SETCACHESIZE). As sessions will not be reused ones they are expired, they should be removed from
*    the cache to save resources. This can either be done automatically whenever 255 new sessions were established
*    (see SSL_CTX_SETSESSIONCACHEMODE) or manually by calling SSL_ctxFlushSessions().\n\n
* 2. SSL_ctxFlushSessions() will only check sessions stored in the internal cache. When a session is found and removed,
*    the pfRemoveSession_cb is however called to synchronize with the external cache.
* 
* @par Related Topics
* SSL_CTX_SESS_SETCACHESIZE,\n
* SSL_CTX_SETSESSIONCACHEMODE,\n
* SSL_ctxSetTimeout,\n
* SSL_sessionSetTimeout,\n
* pfRemoveSession_cb.
*/

SSLLINKDLL SEC_VOID SSL_ctxFlushSessions (SSL_CTX_S *pstContext,
                                  SEC_INT32 lTime);

/*
    Func Name:  SSL_getCurrentCipher
*/

/**
* @defgroup SSL_getCurrentCipher
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_CIPHER_S *SSL_getCurrentCipher (const SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the current cipher used with the SSL object.
* 
* @par Description
* SSL_getCurrentCipher function returns a pointer to an SSL_CIPHER_S object containing the description of the actually used cipher
* of a connection established with the SSL object.
* 
* @param[in] pstSSL Pointer to SSL_S object. [N/A]
* 
* @retval SSL_CIPHER_S* On successful execution the SSL_CIPHER_S *. [Pointer to the cipher object|N/A]
* @retval SSL_CIPHER_S* On failure conditions [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_cipherGetBits,\n
* SSL_cipherGetName,\n
* SSL_getCipherList,\n
* SSL_getSharedCiphers,\n
* SSL_ctxSetCipherList,\n
* SSL_setCipherList,\n
* SSL_getCiphers.
*/

SSLLINKDLL SSL_CIPHER_S *SSL_getCurrentCipher (const SSL_S *pstSSL);

/*
    Func Name:  SSL_cipherGetBits
*/

/**
* @defgroup SSL_cipherGetBits
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_INT SSL_cipherGetBits (const SSL_CIPHER_S *pstCipher,
* SEC_INT *piAlgBits);
* @endcode
* 
* @par Purpose
* This is used to determine the number of bits in a cipher.
* 
* @par Description
* SSL_cipherGetBits function determines the number of bits in a cipher. Because of export crippled ciphers there are two
* bits:The bits the algorithm supports in general (stored to piAlgBits) and the bits which are actually used
* (the return value).
* 
* @param[in] pstCipher Pointer to SSL_CIPHER_S object. [N/A]
* @param[out] piAlgBits This is used to hold the bits the algorithm supports in general. [N/A]
* 
* @retval SEC_INT On successful execution the bits which are actually used is returned. [Bits which are actually used|N/A]
* @retval SEC_INT On failure conditions [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getCurrentCipher,\n
* SSL_cipherGetName,\n
* SSL_getCipherList,\n
* SSL_getSharedCiphers.
*/

SSLLINKDLL SEC_INT  SSL_cipherGetBits (const SSL_CIPHER_S *pstCipher,
                           SEC_INT *piAlgBits);

/*
    Func Name:  SSL_cipherGetName
*/

/**
* @defgroup SSL_cipherGetName
* @ingroup sslFunctions
* @par Prototype
* @code
* const SEC_CHAR* SSL_cipherGetName (const SSL_CIPHER_S *pstCipher);
* @endcode
* 
* @par Purpose
* This is used to get the internal name of a cipher as a string.
* 
* @par Description
* SSL_cipherGetName function returns the internal name of cipher as a string.
* 
* @param[in] pstCipher Pointer to SSL_CIPHER_S object. [N/A]
* 
* @retval SEC_CHAR* On successful execution returns the internal name of cipher. [Internal name of the cipher|N/A]
* @retval SEC_CHAR* On failure conditions ["(NONE)" string is returned |N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getCurrentCipher,\n
* SSL_cipherGetBits,\n
* SSL_getCipherList,\n
* SSL_getSharedCiphers.
*/

SSLLINKDLL const SEC_CHAR* SSL_cipherGetName (const SSL_CIPHER_S *pstCipher);


/*
    Func Name:  SSL_getCipherList
*/
/**
* @defgroup SSL_getCipherList
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const SEC_CHAR * SSL_getCipherList (const SSL_S *pstSSL,
* SEC_INT iNum);
* @endcode
* 
* @par Purpose
* This is used to get the cipher name based on the priority specified.
* 
* @par Description
* SSL_getCipherList function returns a pointer to the name of the SSL_CIPHER_S listed for ssl with priority 'iNum'. If ssl is
* NULL, no ciphers are available, or there are less ciphers than priority available, NULL is returned.
* 
* @param[in] pstSSL Pointer to SSL_S object. [N/A]
* @param[in] iNum Priority requested. [N/A]
* 
* @retval SEC_CHAR* On successful execution it returns the internal name of cipher. [Internal name of cipher|N/A]
* @retval SEC_CHAR* On failure conditions [NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getCurrentCipher,\n
* SSL_cipherGetBits,\n
* SSL_cipherGetName,\n
* SSL_getSharedCiphers,\n
* SSL_ctxSetCipherList,\n
* SSL_setCipherList,\n
* SSL_getCiphers.
*/

SSLLINKDLL const SEC_CHAR* SSL_getCipherList (const SSL_S *pstSSL,
                                     SEC_INT iNum);


/*
    Func Name:  SSL_getSharedCiphers
*/

/**
* @defgroup SSL_getSharedCiphers
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_CHAR* SSL_getSharedCiphers (const SSL_S *pstSSL, 
* SEC_CHAR *pcBuf, 
* SEC_INT iLen);
* @endcode
* 
* @par Purpose
* This is used to get the list of shared ciphers.
* 
* @par Description
* SSL_getSharedCiphers function returns a pointer to a buffer containing a list of shared ciphers. The function can be
* used only for SSLv2 connection. It does not work for SSLv3 and TLSv1. It returns the string like"RC4-SHA: DES-CBC3-SHA".
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] iLen The length of the buffer. [N/A]
* @param[out] pcBuf The buffer where the list of ciphers is filled. [N/A]
* 
* @retval SEC_CHAR* On successful execution returns a buffer to list of shared cipher. [Buffer to the list of shared
* cipher|N/A]
* @retval SEC_CHAR* On failure conditions [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getCurrentCipher,\n
* SSL_cipherGetBits,\n
* SSL_cipherGetName,\n
* SSL_getCipherList,\n
* SSL_ctxSetCipherList,\n
* SSL_setCipherList,\n
* SSL_getCiphers.
*/

SSLLINKDLL SEC_CHAR *   SSL_getSharedCiphers (const SSL_S *pstSSL, 
                                  SEC_CHAR *pcBuf, 
                                  SEC_INT iLen);


/*
    Func Name: SSL_getReadAhead
*/

/**
* @defgroup SSL_getReadAhead
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_getReadAhead (const SSL_S * pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the ReadAhead flag value set in the SSL structure.
* 
* @par Description
* SSL_getReadAhead function returns the ReadAhead Flag value set in the SSL structure. This flag is set for reading as
* many input bytes as possible for socket reads.
* 
* @param[in] pstSSL The structure from which the value has to be extracted [N/A].
* 
* @retval SEC_INT If the flag in the SSL structure is set. [Non-zero|N/A]
* @retval SEC_INT If the flag in the SSL structure is not set. [Zero|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setReadAhead,\n
* SSL_pending,\n
* SSL_read.
*/

SSLLINKDLL SEC_INT  SSL_getReadAhead (const SSL_S * pstSSL);


/*
    Func Name:  SSL_pending
*/

/**
* @defgroup SSL_pending
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_pending (const SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to obtain number of readable bytes buffered in an SSL object.
* 
* @par Description
* SSL_pending function is used to obtain number of readable bytes buffered in an SSL object. It takes pointer to SSL_S
* object and calls the corresponding method in SSL_METHOD_S.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* 
* @retval SEC_INT On successful execution number of readable bytes is returned. [Number of readable bytes|N/A]
* @retval SEC_INT On failure conditions [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. This function cannot work properly if SSL_setReadAhead is calling.\n\n
* 2. This function should only be called after a successful TLS/SSL I/O function, usually SSL_read.
* 
* @par Related Topics
* SSL_getReadAhead,\n
* SSL_setReadAhead,\n
* SSL_read.
*/


 SSLLINKDLL SEC_INT SSL_pending (const SSL_S *pstSSL);


/*
    Func Name:  SSL_setSockId
*/
 
/**
* @defgroup SSL_setSockId
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setSockId (SSL_S *pstSSL,
* SEC_SOCK iFileDesc);
* @endcode
* 
* @par Purpose
* This is used to set the specified file descriptor as the input/output facility for the SSL.
* 
* @par Description
* SSL_setSockId function sets the file descriptor iFileDesc as the input/output facility for the SSL(encrypted) side of SSL.
* iFileDesc will typically be the socket file descriptor of a network connection.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] iFileDesc In client side: The socket descriptor which is obtained from the socket() call.\n
* In Server side: The new descriptor which is obtained from the accept call. [N/A]
* 
* @retval SEC_INT If operation failed. [SEC_ERROR|N/A]
* @retval SEC_INT If operation is successful. [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is NULL. [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSockId.
*/

SSLLINKDLL SEC_INT SSL_setSockId (SSL_S *pstSSL, 
                       SEC_SOCK iFileDesc);


/*
    Func Name:  SSL_getSockId
*/
 
/**
* @defgroup SSL_getSockId
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_SOCK SSL_getSockId ( const SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the file descriptor from the SSL object.
* 
* @par Description
* SSL_getSockId function gets the file descriptor from SSL object. The file descriptor will typically be the socket file
* descriptor of a network connection.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* 
* @retval SEC_INT On success returns file descriptor [SEC_SOCK|N/A]
* @retval SEC_INT If the input is invalid [SEC_ERROR|N/A]                    
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setSockId.
*/

SSLLINKDLL SEC_SOCK SSL_getSockId ( const SSL_S *pstSSL);

/*
    Func Name: SSL_setCipherList
*/

/**
* @defgroup SSL_setCipherList
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setCipherList (SSL_S *pstSSL, 
* const SEC_INT aiCiphers[], 
* const SEC_INT iCipherNum);
* @endcode
* 
* @par Purpose
* This is used to set the list of available ciphers for SSL_S.
* 
* @par Description
* SSL_setCipherList function sets the list of available ciphers for SSL_S object using the list of ciphers passed.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] aiCiphers Array of ciphers. [N/A]
* @param[in] iCipherNum Number of ciphers in the array. [N/A]
* 
* @retval SEC_INT If any of the ciphers is set. [TLS_SUCCESS|N/A]
* @retval SEC_INT If none of the ciphers are set. [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* If SSL_CTRL_BEHAV_RESTRICT_TLS12_CIPHERS_TO_TLS12_VERSION is enabled, then all TLS 1.2 ciphers will be 
* filtered from the list of ciphers passed to this API, if the SSL method version is specific to SSL 2, SSL 3, TLS 1.0 
* or TLS 1.1.
* \n
* 
* @par Related Topics
* SSL_addCipherToList,\n
* SSL_ctxSetCipherList,\n
* SSL_getCiphers,\n
* SSL_getCipherList,\n
* SSL_getCurrentCipher,\n
* SSL_getSharedCiphers.
*/

SSLLINKDLL SEC_INT  SSL_setCipherList (SSL_S *pstSSL, 
                           const SEC_INT aiCiphers[], 
                           const SEC_INT iCipherNum);


/*
    Func Name: SSL_addCipherToList
*/

/**
* @defgroup SSL_addCipherToList
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_addCipherToList (SSL_S *pstSSL,
* const SEC_INT iCipher);
* @endcode
* 
* @par Purpose
* This is used to add the given cipher to the SSL object with top priority.
* 
* @par Description
* SSL_addCipherToList function adds the given cipher to the SSL object with top priority to the existing cipher list.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] iCipher New cipher. [N/A]
* 
* @retval SEC_INT If the cipher is set. [TLS_SUCCESS|N/A]
* @retval SEC_INT If the cipher could not be set. [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* If SSL_CTRL_BEHAV_RESTRICT_TLS12_CIPHERS_TO_TLS12_VERSION is enabled, then all TLS 1.2 ciphers will be 
* removed from the final list of ciphers if the SSL method version is specific to SSL 2, SSL 3, TLS 1.0 or TLS 1.1.
* \n
* 
* @par Related Topics
* SSL_setCipherList.
*/

SSLLINKDLL SEC_INT SSL_addCipherToList (SSL_S *pstSSL, 
                             const SEC_INT iCipher);


/*
    Func Name:   SSL_setReadAhead
*/

/**
* @defgroup SSL_setReadAhead
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setReadAhead(SSL_S *pstSSL, SEC_INT yes);
* @endcode
* 
* @par Purpose
* This is used to set a value to the read-ahead flag in the SSL structure.
* 
* @par Description
* SSL_setReadAhead function sets a value (int yes) to the read-ahead flag in the SSL structure. In order to turn on the
* flag, a non-zero value must be set. This flag is set for reading as many input bytes as possible for socket reads.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] yes In order to set non zero value must be set. [N/A]
* 
* @retval SEC_INT On Success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL Pointer). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. When the flag is being set, SSL will read as many input bytes as possible in each socket reading event, which means
*    SSL may fetch several SSL records into SSL buffer in one SSL_read call. But still it will return only one ssl record
*    at most to the application for each SSL_read call.\n\n
* 2. SSL_pending() cannot work properly if the flag is being set.
* 
* @par Related Topics
* SSL_getReadAhead,\n
* SSL_pending,\n
* SSL_read.
*/

SSLLINKDLL SEC_INT SSL_setReadAhead(SSL_S *pstSSL, SEC_INT yes);


/*
    Func Name:   SSL_getVerifyMode
*/

/**
* @defgroup SSL_getVerifyMode
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_getVerifyMode (const SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the verification mode currently set in the SSL structure.
* 
* @par Description
* SSL_getVerifyMode function returns the verification mode currently set in SSL structure. The value that is returned can be one of
* the following or combination of these flags. The flags are:\n
* SSL_VERIFY_NONE,\n
* SSL_VERIFY_PEER,\n
* SSL_VERIFY_FAIL_IF_NO_PEER_CERT,\n
* SSL_VERIFY_CLIENT_ONCE (Depracated. Not to be used).
* 
* @param[in] pstSSL SSL structure. [N/A]
* 
* @retval SEC_INT Returns the flag that is set used during certificate verification. [Flag set during certificate
* verification|N/A]
* @retval SEC_INT If the input is invalid(NULL pointer is passed). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getVerifyDepth,\n
* SSL_getVerify_cb,\n
* SSL_setVerify,\n
* SSL_setVerifyDepth.
*/

SSLLINKDLL SEC_INT SSL_getVerifyMode (const SSL_S *pstSSL);


/*
    Func Name:  SSL_getVerifyDepth
*/
 
/**
* @defgroup SSL_getVerifyDepth
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_getVerifyDepth (const SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the verification depth using which the certificate validation will be done.
* 
* @par Description
* SSL_getVerifyDepth function gets the depth using which the certificate validation would be performed. The depth is set
* to the pstParam field of the SSL object.
* 
* @param[in] pstSSL Pointer to SSL_S object. [N/A]
* 
* @retval SEC_INT If input is NULL. [SEC_ERROR|N/A]
* @retval SEC_INT Returns the value of depth on success. [Value of depth|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getVerifyMode,\n
* SSL_getVerify_cb,\n
* SSL_setVerify,\n
* SSL_setVerifyDepth.
*/

SSLLINKDLL SEC_INT SSL_getVerifyDepth (const SSL_S *pstSSL);


/*
    Func Name:   SSL_getVerify_cb
*/

/**
* @defgroup SSL_getVerify_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT (*SSL_getVerify_cb ( const SSL_S *pstSSL))(SEC_INT iOK, X509_STORE_CTX_S *pstStoreCtx);
* @endcode
* 
* @par Purpose
* This is used to get the verification callback currently set in the SSL object.
* 
* @par Description
* SSL_getVerify_cb function returns a function pointer to the verification callback pfVerify_cb currently set in SSL
* object. If no callback was explicitly set, the NULL pointer is returned.
* 
* @param[in] pstSSL Structure from which the pointer to callback function has to be returned. [N/A]
* 
* @retval cb Callback function ((SEC_INT)(*)(SEC_INT iOK, X509_STORE_CTX_S *pstStoreCtx))\n
* or\n
* SEC_NULL in following condidtions:\n
* 1. If the input is invalid (NULL pointer is passed as input)\n
* 2. If pointer to the callback function is not set. [Pointer to callback function or SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getVerifyMode,\n
* SSL_getVerifyDepth,\n
* SSL_setVerify,\n
* SSL_setVerifyDepth.
*/

SSLLINKDLL  SEC_INT (*SSL_getVerify_cb ( const SSL_S *pstSSL))(SEC_INT iOK, X509_STORE_CTX_S *pstStoreCtx);



/*
    Func Name: SSL_getVerifyCBAppData
*/

/**
* @defgroup SSL_getVerifyCBAppData
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID *SSL_getVerifyCBAppData(SSL_S *pstSSL)
* @endcode
* 
* @par Purpose
* This is used to get the verify callback application data from SSL object.\n
* 
* @par Description
* SSL_getVerifyCBAppData function gets the verify callback application
* data from SSL object. SSL library will not do any validation or memory 
* allocation/deallocation for the application data. \n 
*
* @param[in] pstSSL Pointer to SSL object [N/A|N/A]
* 
* @retval SEC_VOID* Pointer to application data will be returned [N/A]
* or\n
* SEC_NULL will be returned in following conditions: \n
* 1. If the input is invalid (NULL pointer is passed as input)\n
* 2. If pointer to the application data is not set. 
* [Pointer to application data or SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
* 
* @par Note
* \n
* NA
*
* @par Related Topics
* SSL_setVerifyCBAppData \n
* SSL_ctxSetVerifyCBAppData \n
* SSL_ctxGetVerifyCBAppData
*/

SSLLINKDLL SEC_VOID *SSL_getVerifyCBAppData(SSL_S *pstSSL);



/*
    Func Name:  SSL_setVerify
*/
 
/**
* @defgroup SSL_setVerify
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setVerify(SSL_S *pstSSL, 
* SEC_INT iMode,
* SEC_INT (*pfCallback) (SEC_INT iOk,X509_STORE_CTX_S *pstStoreContext));
* @endcode
* 
* @par Purpose
* This is used to set the mode and callback function to the SSL object.
* 
* @par Description
* SSL_setVerify function sets the Verification Mode and the callback function pointer to SSL structure.
* 
* @param[in] pstSSL Pointer to SSL_S in which the iVerifyMode and pfVerify_cb fields are set. [N/A]
* @param[in] iMode The verification of certificates can be controlled by a set of logically OR'ed mode flags. Please
* refer to the description in SSL_ctxSetverify.  [N/A]
* @param[in] pfCallback Function pointer callback to verify the certificates. [N/A]
* 
* @retval SEC_INT On success. [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL Pointer is passed). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getVerifyMode,\n
* SSL_getVerifyDepth,\n
* SSL_getVerify_cb,\n
* SSL_setVerifyDepth.
*/

SSLLINKDLL SEC_INT SSL_setVerify(SSL_S *pstSSL, 
                          SEC_INT iMode,
                          SEC_INT (*pfCallback) (SEC_INT iOk,X509_STORE_CTX_S *pstStoreContext));

/*
    Func Name: SSL_setVerifyCBAppData
*/

/**
* @defgroup SSL_setVerifyCBAppData
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setVerifyCBAppData(SSL_S *pstSSL, SEC_VOID *pAppData)
* @endcode
* 
* @par Purpose
* This is used to set the verify callback application data in SSL object.\n
* 
* @par Description
* SSL_setVerifyCBAppData function sets the verify callback application
* data in SSL object. SSL library will not do any validation or memory 
* allocation/deallocation for the application data. \n 
*
* @param[in] pstSSL Pointer to SSL object [N/A|N/A]
* @param[in] pAppData Pointer to verify callback application data [N/A|N/A]
* 
* @retval SEC_INT On success. [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL SSL Pointer is passed). 
* [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
* 
* @par Note
* \n
* NA
*
* @par Related Topics
* SSL_ctxSetVerifyCBAppData \n
* SSL_getVerifyCBAppData \n
* SSL_ctxGetVerifyCBAppData
*/

SSLLINKDLL SEC_INT SSL_setVerifyCBAppData(SSL_S *pstSSL, SEC_VOID *pAppData);



/*
    Func Name:  SSL_setVerifyDepth
*/
 
/**
* @defgroup SSL_setVerifyDepth
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setVerifyDepth (SSL_S *pstSSL,
* SEC_INT iDepth);
* @endcode
* 
* @par Purpose
* This is used the set the verification depth.
* 
* @par Description
* SSL_setVerifyDepth function sets the depth to which the certificate validation has to be performed. The depth is set
* to the pstParam field of the SSL object.
* 
* @param[in] pstSSL Pointer to SSL_S in which the iDepth is set. [N/A]
* @param[in] iDepth Number indicating the depth to which the certificate validation had to be performed. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid(NULL Pointer is passed). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* SSL_ctxSetVerifyDepth or SSL_setVerifyDepth function should be called to set the reasonable verify depth for
* non-anonymous authentication. The default verify depth is -1.
* 
* @par Related Topics
* SSL_getVerifyMode,\n
* SSL_getVerifyDepth,\n
* SSL_getVerify_cb,\n
* SSL_setVerify.
*/

SSLLINKDLL SEC_INT SSL_setVerifyDepth (SSL_S *pstSSL,
                            SEC_INT iDepth);

#ifndef SSL_NO_RSA
/*
    Func Name:  SSL_useRSAPrivateKey
*/
 
/**
* @defgroup SSL_useRSAPrivateKey
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_useRSAPrivateKey (SSL_S *pstSSL,
* SEC_PKEY_S *pRSAKey);
* @endcode
* 
* @par Purpose
* This is used to add the RSA private key to the SSL object.
* 
* @par Description
* SSL_useRSAPrivateKey function adds the RSA private key as private key to SSL.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] pRSAKey The private key. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. SSL_usePrivateKey() can also be used to load the RSA private key. So usually we should call SSL_usePrivateKey
*    function instead of SSL_useRSAPrivateKey().\n\n
* 2. When a private key is being set, SSL library will check if a certificate has already been set. Then SSL library will
*    check whether they are pair. If not, the private key is set but the certificate will be unloaded and the API returns
*    0. If the application wants to switch certificate/private key pair, it should first switch the certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT  SSL_useRSAPrivateKey (SSL_S *pstSSL, SEC_PKEY_S *pRSAKey);
#endif /* SEC_NO_RSA */


/*
    Func Name:  SSL_usePrivateKey
*/
 
/**
* @defgroup SSL_usePrivateKey
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_usePrivateKey (SSL_S *pstSSL,
* SEC_PKEY_S *pkey);
* @endcode
* 
* @par Purpose
* This is used to add the specified key as private key to the SSL object.
* 
* @par Description
* SSL_usePrivateKey function adds pkey as private key to SSL object.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] pkey The private key. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* When a private key is being set, SSL library will check if a certificate has already been set or not.
* Then it will check whether they are pair or not. If not, the private key is set but the certificate will be
* unloaded and the API returns 0. If the application wants to switch certificate/private key pair, it should first
* switch to certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n 
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_usePrivateKey (SSL_S *pstSSL, 
                           SEC_PKEY_S *pkey);


/*
    Func Name:  SSL_useCertificate
*/
 
/**
* @defgroup SSL_useCertificate
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_useCertificate (SSL_S *pstSSL,
* X509_CERT_EXTENDED_S *pstX509Cert);
* @endcode
* 
* @par Purpose
* This is used to add the extended certificate structure to the SSL object.
* 
* @par Description
* SSL_useCertificate function adds the extended certificate structure to the SSL object. The certificate that is passed
* is stored in the CERT structure within the StoreContext.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] pstX509Cert The extended certificate structure. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* When a certificate is set, SSL library will check if a private key is already set or not. Then SSL library will check
* whether they are pair or not. If not, the certificate is set but the private key is unloaded and the API returns 1.
* If the application wants to switch certificate/private key pair, it should first switch to certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_useCertificate (SSL_S *pstSSL, 
                            X509_CERT_EXTENDED_S *pstX509Cert);



/*
    Func Name:  SSL_useRSAPrivateKeyFile
*/
 
/**
* @defgroup SSL_useRSAPrivateKeyFile
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_useRSAPrivateKeyFile (SSL_S *pstSSL, 
* const SEC_CHAR *pcFile, 
* SEC_INT iType);
* @endcode
* 
* @par Purpose
* This is used to add the RSA private key found in a file to SSL object.
* 
* @par Description
* SSL_useRSAPrivateKeyFile function adds the first private RSA key found in pcFile to SSL. The formatting type of the
* certificate must be specified from the known types SSL_FILETYPE_ASN1.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] pcFile The path of the filename. [N/A]
* @param[in] iType The formatting type could be one of the following:\n
* SSL_FILETYPE_ASN1,\n
* SSL_FILETYPE_PEM,\n
* SSL_FILETYPE_PFX. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_ERROR or SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1) If file type is SSL_FILETYPE_PFX, the PFX file should be created with encrypted password mode only. Also if file type
*    is SSL_FILETYPE_PEM, the key should be of type PEM_OBJTYPE_P8_PRIVATEKEY only.\n\n
* 2) If we are using SSL_FILETYPE_PEM, the file should not be encoded in
*    MIC_CLEAR proc mode since complete file cannot be saved in MIC_CLEAR mode.\n\n
* 3. SSL_usePrivateKeyFile function can also be used to load the RSA private key. So usually we should call
*    SSL_usePrivateKeyFile() instead of SSL_useRSAPrivateKeyFile().\n\n
* 4. When a private key is being set, SSL library will check if a certificate has already been set. Then SSL library will
*    check whether they are pair. If not, the private key is set but the certificate will be unloaded and the API returns
*    0. If the application wants to switch certificate/private key pair, it should first switch the certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_useRSAPrivateKeyFile (SSL_S *pstSSL, 
                                  const SEC_CHAR *pcFile, 
                                  SEC_INT iType);

/*
    Func Name:  SSL_usePrivateKeyBuffer
*/
 
/**
* @defgroup SSL_usePrivateKeyBuffer
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_usePrivateKeyBuffer (SSL_S *pstSSL, 
* SEC_UCHAR* pucBuf, 
* SEC_UINT32 ulLen, 
* SEC_INT iType);
* @endcode
* 
* @par Purpose
* This is used to add the first private key found in a buffer to the SSL context.
* 
* @par Description
* SSL_usePrivateKeyBuffer function adds the first private key found in buffer to SSL context. The buffer type of the key
* must be specified from the known types SSL_FILETYPE_PEM, SSL_FILETYPE_PFX, and SSL_FILETYPE_ASN1.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the private key has to be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* @param[in] iType The formatting type could be one of the following\n
* SSL_FILETYPE_ASN1\n
* SSL_FILETYPE_PEM\n
* SSL_FILETYPE_PFX. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid(NULL pointer is passed). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If buffer type is SSL_FILETYPE_PFX, the PFX file should be created with encrypted password mode only. Also if buffer
*    type is SSL_FILETYPE_PEM, the key should be of type PEM_OBJTYPE_P8_PRIVATEKEY only.\n\n
* 2. If we are using SSL_FILETYPE_PEM, the buffer should not be encoded in MIC_CLEAR proc mode since buffer from complete
*    file cannot be saved in MIC_CLEAR mode.\n\n
* 3. When a private key is being set, SSL library will check if a certificate has already been set. Then SSL library will
*    check whether they are pair. If not, the private key is set but the certificate will be unloaded and the API returns
*    0. If the application wants to switch certificate/private key pair, it should first switch the certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT  SSL_usePrivateKeyBuffer (SSL_S *pstSSL, 
                                   SEC_UCHAR* pucBuf, 
                                   SEC_UINT32 ulLen, 
                                    SEC_INT iType);


/*
    Func Name:  SSL_usePrivateKeyFile
*/
 
/**
* @defgroup SSL_usePrivateKeyFile
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_usePrivateKeyFile (SSL_S *pstSSL,
* const SEC_CHAR *pcFile, 
* SEC_INT iType);
* @endcode
* 
* @par Purpose
* This is used to add the first private key found in a file to SSL object.
* 
* @par Description
* SSL_usePrivateKeyFile function adds the first private key found in pcFile to SSL object. The formatting type of the
* private key must be specified from the known types SSL_FILETYPE_PEM, SSL_FILETYPE_PFX, and SSL_FILETYPE_ASN1.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] pcFile The path of filename. [N/A]
* @param[in] iType The formatting type could be one of the following\n
* SSL_FILETYPE_ASN1\n
* SSL_FILETYPE_PEM\n
* SSL_FILETYPE_PFX. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure, if input is/are NULL [SEC_ERROR|N/A]
* @retval SEC_INT On failure, if reading from the file failed [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If file type is SSL_FILETYPE_PFX, the PFX file should be created with encrypted password mode only. Also if file type
*    is SSL_FILETYPE_PEM, the key should be of type PEM_OBJTYPE_P8_PRIVATEKEY only.\n\n
* 2. If we are using SSL_FILETYPE_PEM, the file should not be encoded in MIC_CLEAR proc mode since complete file cannot
*    be saved in MIC_CLEAR mode.\n\n
* 3. When a private key is being set, SSL library will check if a certificate has already been set. Then SSL library will
*    check whether they are pair. If not, the private key is set but the certificate will be unloaded and the API returns
*    0. If the application wants to switch certificate/private key pair, it should first switch the certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT  SSL_usePrivateKeyFile (SSL_S *pstSSL,
                               const SEC_CHAR *pcFile, 
                               SEC_INT iType);

/*
    Func Name:  SSL_useCertificateBuffer
*/
 
/**
* @defgroup SSL_useCertificateBuffer
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_useCertificateBuffer (SSL_S *pstSSL,
* SEC_UCHAR* pucBuf, 
* SEC_UINT32 ulLen, 
* SEC_INT iType);
* @endcode
* 
* @par Purpose
* This is used to add the first certificate found in a buffer to the SSL object.
* 
* @par Description
* SSL_useCertificateBuffer function adds the first certificate found in buffer to SSL object. The format of the
* certificate must be specified from the known types SSL_FILETYPE_PEM, SSL_FILETYPE_ASN1, and SSL_FILETYPE_PFX.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the certificate has to be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* @param[in] iType The formatting type could be one of the following\n
* SSL_FILETYPE_ASN1\n
* SSL_FILETYPE_PEM\n
* SSL_FILETYPE_PFX. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If buffer type is SSL_FILETYPE_PFX, the PFX file should be created with encrypted password mode only. Also if we are
*    using SSL_FILETYPE_PEM, the buffer should not be encoded in MIC_CLEAR proc mode since buffer from complete file
*    cannot be saved in MIC_CLEAR mode.\n\n
* 2. When a certificate is set, SSL library will check if a private key is already set or not. Then SSL library will check
*    whether they are pair or not. If not, the certificate is set but the private key is unloaded and the API returns 1.
*    If the application wants to switch certificate/private key pair, it should first switch to certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_useCertificateBuffer (SSL_S *pstSSL,
                                   SEC_UCHAR* pucBuf, 
                                   SEC_UINT32 ulLen, 
                                   SEC_INT iType);

/*
    Func Name:  SSL_useCertificateFile
*/
 
/**
* @defgroup SSL_useCertificateFile
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_useCertificateFile (SSL_S *pstSSL,
* const SEC_CHAR *pcFile, 
* SEC_INT iType);
* @endcode
* 
* @par Purpose
* This is used to add the first certificate found in a file to SSL object.
* 
* @par Description
* SSL_useCertificateFile function adds the first certificate found in pcFile to ssl. The format of the certificate must
* be specified from the known types SSL_FILETYPE_PEM, SSL_FILETYPE_ASN1, and SSL_FILETYPE_PFX.
* 
* @param[in] pstSSL Pointer to SSL object. [N/A]
* @param[in] pcFile The path of filename. [N/A]
* @param[in] iType The formatting type could be one of the following\n
* SSL_FILETYPE_ASN1\n
* SSL_FILETYPE_PEM\n
* SSL_FILETYPE_PFX. [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid(NULL pointer is passed). [SEC_ERROR|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If file type is SSL_FILETYPE_PFX, the PFX file should be created with encrypted password mode only. Also if we
*    are using SSL_FILETYPE_PEM, the file should not be encoded in MIC_CLEAR proc mode since complete file cannot be
*    saved in MIC_CLEAR mode.\n\n
* 2. When a certificate is set, SSL library will check if a private key is already set or not. Then SSL library will check
*    whether they are pair or not. If not, the certificate is set but the private key is unloaded and the API returns 1.
*    If the application wants to switch certificate/private key pair, it should first switch to certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT  SSL_useCertificateFile (SSL_S *pstSSL,
                                const SEC_CHAR *pcFile, 
                                SEC_INT iType);


/*
    Func Name:  SSL_ctxUseRSAPrivateKeyFile
*/
 



 SSLLINKDLL SEC_INT SSL_ctxUseRSAPrivateKeyFile (SSL_CTX_S *pstContext, 
                                     const SEC_CHAR *pcFile, 
                                     SEC_INT iType);


/*
    Func Name:  SSL_ctxUsePrivateKeyBuffer
*/
 


SSLLINKDLL SEC_INT  SSL_ctxUsePrivateKeyBuffer (SSL_CTX_S *pstContext, 
                                   SEC_UCHAR* pucBuf, 
                                   SEC_UINT32 ulLen, 
                                    SEC_INT iType);

/*
    Func Name:  SSL_ctxUsePrivateKeyFile
*/
 


SSLLINKDLL SEC_INT  SSL_ctxUsePrivateKeyFile (SSL_CTX_S *pstContext, 
                                  const SEC_CHAR *pcFile, 
                                  SEC_INT iType);

/*
    Func Name:  SSL_ctxUseCertificateBuffer
*/

/**
* @defgroup SSL_ctxUseCertificateBuffer
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxUseCertificateBuffer (SSL_CTX_S *pstContext, 
* SEC_UCHAR* pucBuf, 
* SEC_UINT32 ulLen, 
* SEC_INT iType);
* @endcode
* 
* @par Purpose
* This is used to load the certificate found in a specified buffer to the SSL context.
* 
* @par Description
* SSL_ctxUseCertificateBuffer function loads the certificate into pstContext. It may be either client or server
* (End Entity) certificate. The data in the buffer may be any of the following formats:\n
* SSL_FILETYPE_PFX\n
* SSL_FILETYPE_PEM\n
* SSL_FILETYPE_ASN1.
* 
* @param[in] pstContext SSL Context structure to which the list of certificate has to be stored. This can be used by
* either the server or the client. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the certificates has to be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* @param[in] iType Type in which the certificates are stored in the buffer. The formats in which certificates are stored
* is one of the following SSL_FILETYPE_PFX, SSL_FILETYPE_PEM, SSL_FILETYPE_ASN1. [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT On successful execution. [TLS_SUCCESS|N/A]
* @retval SEC_INT On all failure conditions.  The failure can be when decoding of certificate fails. [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. This API does not support loading of end entity certificate dynamically.
*    Application code should not call this API in any parallel operation with
*    either SSL Object (SSL_S) or SSL context(SSL_CTX_S) operations.
*    If used, application will lead to core dump.\n\n
* 2. If buffer type is SSL_FILETYPE_PFX, the PFX buffer should be created with encrypted password mode only. Also if
*    we are using SSL_FILETYPE_PEM, the buffer should not be encoded in MIC_CLEAR proc mode since buffer from the
*    complete file cannot be saved in MIC_CLEAR mode.\n\n
* 3. When a certificate is set, SSL library will check if a private key is already set or not. Then SSL library will check
*    whether they are pair or not. If not, the certificate is set but the private key is unloaded and the API returns 1.
*    If the application wants to switch certificate/private key pair, it should first switch to certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_ctxUseCertificateBuffer (SSL_CTX_S *pstContext, 
                                   SEC_UCHAR* pucBuf, 
                                   SEC_UINT32 ulLen, 
                                   SEC_INT iType);


/*
    Func Name:  SSL_ctxUseCertificateFile
*/

/**
* @defgroup SSL_ctxUseCertificateFile
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxUseCertificateFile (SSL_CTX_S *pstContext, 
* const SEC_CHAR *pcFile, 
* SEC_INT iType);
* @endcode
* 
* @par Purpose
* This is used to load the certificate from a file to the SSL context.
* 
* @par Description
* SSL_ctxUseCertificateFile function loads the certificate into pstContext. It may be either client or server
* (End Entity) certificate. The file may be any of the following formats:\n
* SSL_FILETYPE_PFX\n
* SSL_FILETYPE_PEM\n
* SSL_FILETYPE_ASN1.
* 
* @param[in] pstContext SSL Context structure to which the list of certificate has to be stored. This can be used by
* either the server or the client. [N/A]
* @param[in] pcFile The name of the file from which the certificates has to be loaded. [N/A]
* @param[in] iType Type in which the certificates are stored in the file. The formats in which certificates are stored
* is one of the following: SSL_FILETYPE_PFX, SSL_FILETYPE_PEM, SSL_FILETYPE_ASN1. [N/A]
* 
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT On successful execution. [TLS_SUCCESS|N/A]
* @retval SEC_INT On all failure conditions.  The failure can be when file cannot be opened, or decoding of certificate
* fails. [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. This API does not support loading of end entity certificate dynamically.
*    Application code should not call this API in any parallel operation with
*    either SSL Object (SSL_S) or SSL context(SSL_CTX_S) operations.
*    If used, application will lead to core dump.\n\n
* 2. This API does not support loading of end entity certificate dynamically.
*    Application code should not call this API in any parallel operation with
*    either SSL Object (SSL_S) or SSL context(SSL_CTX_S) operations.
*    If used, this will lead to core dump.\n\n
* 3. If file type is SSL_FILETYPE_PFX, the PFX file should be created
*    with encrypted password mode only. Also if we are using
*    SSL_FILETYPE_PEM, the file should not be encoded in MIC_CLEAR proc
*    mode since complete file cannot be saved in MIC_CLEAR mode.\n\n
* 4. When a certificate is set, SSL library will check if a private key is
*    already set or not. Then SSL library will check whether they are pair
*    or not. If not, the certificate is set but the private key is unloaded
*    and the API returns 1. If the application wants to switch
*    certificate/private key pair, it should first switch to certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_ctxUseCertificateFile (SSL_CTX_S *pstContext, 
                                   const SEC_CHAR *pcFile, 
                                   SEC_INT iType);

/*
    Func Name:  SSL_ctxUseCertificateChainBuffer
*/

/**
* @defgroup SSL_ctxUseCertificateChainBuffer
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxUseCertificateChainBuffer (SSL_CTX_S *pstContext, 
* SEC_UCHAR* pucBuf, 
* SEC_UINT32 ulLen);
* @endcode
* 
* @par Purpose
* This is used to load the certificate chain found in a buffer to the SSL context.
* 
* @par Description
* SSL_ctxUseCertificateChainBuffer function reads a buffer that contains a Client/Server certificate in "PEM" format
* possibly followed by a sequence of CA certificates that should be sent to the peer during the Authentication and sets
* them to the SSL context.
* 
* @param[in] pstContext Pointer to SSL_CTX_S of either client OR server. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the certificates has to be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a Certificate or List of Certificates are set to Context. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. This API does not support loading of certificate chain dynamically.
*    Application code should not call this API in any parallel operation with
*    either SSL Object (SSL_S) or SSL context (SSL_CTX_S) operations.
*    If used, application will lead to core dump.\n\n
* 2. There should not be any duplicate Certificates in the PEM file. \n\n
* 3. This API is deprecated from TLS1.2 version and should not be used. \n\n
* 4. This function will allow only version 3 CA certficate to load, and it 
*    allows any verison of root certificate and end entity certificate.
*
* @par Related Topics
* SSL_ctxUsePrivateKey \n
* SSL_ctxUsePrivateKeyFile \n
* SSL_ctxUsePrivateKeyBuffer \n
* SSL_ctxUseRSAPrivateKey \n
* SSL_ctxUseRSAPrivateKeyFile \n
* SSL_usePrivateKey \n
* SSL_usePrivateKeyFile \n
* SSL_usePrivateKeyBuffer \n
* SSL_useRSAPrivateKey \n
* SSL_useRSAPrivateKeyFile \n
* \n
* SSL_ctxUseCertificate \n
* SSL_ctxUseCertificateFile \n
* SSL_ctxUseCertificateBuffer \n
* SSL_useCertificate \n
* SSL_useCertificateFile \n
* SSL_useCertificateBuffer \n
* \n
* SSL_ctxLoadPFXStore \n
* SSL_ctxLoadPFXStoreBuffer \n
* SSL_LoadPFXStore \n
* SSL_LoadPFXStoreBuffer \n
* \n
* SSL_ctxUseCertificateChainFile \n
* \n
* SSL_ctxLoadCACertificateFile \n
* SSL_ctxLoadCACertificateBuffer \n
* \n
* SSL_ctxLoadCrl \n
* SSL_ctxLoadCrlBuffer \n
* \n
* SSL_loadClientCAFile \n
* \n
* SSL_ctxSetDefaultPasswd_cb \n
* \n
* SSL_ctxCheckPrivateKey \n
* SSL_checkPrivateKey
*/

SSLLINKDLL SEC_INT SSL_ctxUseCertificateChainBuffer (SSL_CTX_S *pstContext, 
                                   SEC_UCHAR* pucBuf, 
                                   SEC_UINT32 ulLen);

/*
    Func Name:  IPSI_SSL_ctxLoadCertificateChainAndKey
*/
/**
* @defgroup IPSI_SSL_ctxLoadCertificateChainAndKey
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxLoadCertificateChainAndKey( SSL_CTX_S *pstCtx,
*                                           const SEC_CHAR *pstCertChainfile,
*                                           const SEC_CHAR *pcPvtKeyfile,
*                                           SEC_INT iPvtKeytype);
* @endcode
*
* @par Purpose
* This is used to load the certificate chain file, Certificate and private key
* to the SSL context.
*
* @par Description
* IPSI_SSL_ctxLoadCertificateChainAndKey reads the certificate chain from
* the file, verifies if the end entity certificate and the private key is
* a match. If the certificate and the key pair matches then Certificate,
* private and certificate chain will be loaded in the context.
* Also the certificate chain should be in the PEM format.
*
*
* @param[in] pstContext Specifies pointer to SSL_CTX_S of either client or server. [NA/NA]
* @param[in] pstCertChainfile Specifies certificate chain file in PEM format. [NA/NA]
* @param[in] pcPvtKeyfile Specifies private key file. [NA/NA]
* @param[in] iPvtKeytype Specifies private key type, where the type
* should be PEM, ASN, or PFX. [NA/NA]
*
* @retval SEC_INT If the input is invalid(NULL pointer)or Loading fails. [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a Certificate or List of Certificates are set to context. [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. This API does not support loading of certificate chain and private key
*   dynamically. Application code should not call this API in any parallel
*   operation with either SSL Object (SSL_S) or SSL context (SSL_CTX_S)
*   operations. If used, application will lead to core dump. \n\n
* 2. There should not be any duplicate Certificates in the PEM file. \n\n
* 3. This API is deprecated from TLS1.2 version and should not be used. \n\n
* 4. This function will allow only version 3 CA certficate to load, and it 
*    allows any verison of root certificate and end entity certificate.
* @par Related Topics
* None
*/


SSLLINKDLL SEC_INT IPSI_SSL_ctxLoadCertificateChainAndKey (SSL_CTX_S *pstCtx,
                                           const SEC_CHAR *pstCertChainfile,
                                           const SEC_CHAR *pcPvtKeyfile,
                                           SEC_INT iPvtKeytype);
/*
    Func Name:  IPSI_SSL_ctxRemoveCertChainAndPrivKey
*/
/**
* @defgroup IPSI_SSL_ctxRemoveCertChainAndPrivKey
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxRemoveCertChainAndPrivKey (SSL_CTX_S *pstCtx);
* @endcode
*
* @par Purpose
* This is used to remove the certificate chain file, Certificate and private key
* from the SSL context.
*
* @par Description
* IPSI_SSL_ctxRemoveCertChainAndPrivKey removes the certificate chain,
* End entity certificate and the private key from the context.
*
* @param[in] pstContext Pointer to SSL_CTX_S  either for client OR server. [NA/NA]
*
* @retval SEC_INT If the input is invalid(NULL pointer)or loading fails. [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a certificate chain, end entity certificate and private
* key are removed from the context[TLS_SUCCESS|N/A].
*
* @par Required Header File
* ssl.h
* @par Note
* \n
*	- This API does not support removing of certificate chain and private key
*     dynamically. Application code should not call this API in any parallel
*     operation with either SSL Object (SSL_S) or SSL context(SSL_CTX_S)
*     operations. If used, application will lead to core dump.
*/


SSLLINKDLL SEC_INT IPSI_SSL_ctxRemoveCertChainAndPrivKey (SSL_CTX_S *pstCtx);
/*
    Func Name:  SSL_ctxUseCertificateChainFile
*/

/**
* @defgroup SSL_ctxUseCertificateChainFile
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxUseCertificateChainFile (SSL_CTX_S *pstContext,
* const SEC_CHAR *pcFile);
* @endcode
* 
* @par Purpose
* This is used to load the certificate chain file to the SSL context.
* 
* @par Description
* SSL_ctxUseCertificateChainFile function reads a file that contains a Client/Server 
* certificate in "PEM" format possibly followed by a sequence of CA certificates 
* that should be sent to the peer during the Authentication and sets
* them to the SSL Context.
* 
* @param[in] pstContext Pointer to SSL_CTX_S of either client or server. [N/A]
* @param[in] pcFile Specifies the file name. [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a Certificate or list of Certificates are set to context. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. This API does not support loading of certificate chain
*    dynamically. Application code should not call this API in any parallel
*    operation with either SSL Object (SSL_S) or SSL context (SSL_CTX_S)
*    operations. If used, application will lead to core dump. \n\n
* 2. There should not be any duplicate Certificates in the PEM file.  \n\n
* 3. This API is deprecated from TLS1.2 version and should not be used.  \n\n
* 4. This function will allow only version 3 CA certficate to load, and it 
*    allows any verison of root certificate and end entity certificate.
*
* @par Related Topics
* SSL_ctxUsePrivateKey \n
* SSL_ctxUsePrivateKeyFile \n
* SSL_ctxUsePrivateKeyBuffer \n
* SSL_ctxUseRSAPrivateKey \n
* SSL_ctxUseRSAPrivateKeyFile \n
* SSL_usePrivateKey \n
* SSL_usePrivateKeyFile \n
* SSL_usePrivateKeyBuffer \n
* SSL_useRSAPrivateKey \n
* SSL_useRSAPrivateKeyFile \n
* \n
* SSL_ctxUseCertificate \n
* SSL_ctxUseCertificateFile \n
* SSL_ctxUseCertificateBuffer \n
* SSL_useCertificate \n
* SSL_useCertificateFile \n
* SSL_useCertificateBuffer \n
* \n
* SSL_ctxLoadPFXStore \n
* SSL_ctxLoadPFXStoreBuffer \n
* SSL_LoadPFXStore \n
* SSL_LoadPFXStoreBuffer \n
* \n
* SSL_ctxUseCertificateChainBuffer \n
* \n
* SSL_ctxLoadCACertificateFile \n
* SSL_ctxLoadCACertificateBuffer \n
* \n
* SSL_ctxLoadCrl \n
* SSL_ctxLoadCrlBuffer \n
* \n
* SSL_loadClientCAFile \n
* \n
* SSL_ctxSetDefaultPasswd_cb \n
* \n
* SSL_ctxCheckPrivateKey \n
* SSL_checkPrivateKey
*/

SSLLINKDLL SEC_INT SSL_ctxUseCertificateChainFile (SSL_CTX_S *pstContext, 
                                        const SEC_CHAR *pcFile);


/*
    Func Name:  SSL_ctxLoadCACertificateBuffer
*/

/**
* @defgroup SSL_ctxLoadCACertificateBuffer
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxLoadCACertificateBuffer(SSL_CTX_S *pstContext, 
* SEC_UCHAR* pucBuf, 
* SEC_UINT32 ulLen,
* SEC_INT type);
* @endcode
* 
* @par Purpose
* This is used to load the CA certificate found in a buffer to the SSL context.
* 
* @par Description
* SSL_ctxLoadCACertificateBuffer function reads a buffer that contains the certificate in 
* "PEM","PFX", or "DER"format. To verify user certificate during the authentication, we 
* should set it to the SSL Context.
* 
* @param[in] pstContext Pointer to SSL_CTX_S of either client OR server. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the certificates has to be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* @param[in] type Type in which the certificates are stored in the buffer. The formats in which certificates are
* stored is one of the following:\n
* SSL_FILETYPE_PFX \n
* SSL_FILETYPE_PEM \n
* SSL_FILETYPE_ASN1 [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a Cert or List of Certs are set to Context. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If there are several CA certificates stored in the buffer, all these certificates will be loaded. 
* \n\n
* 2. This function can be called multiple times to load CA certificate from multiple buffers. However, if the same
*    certificate is loaded twice, the function will return SEC_NULL and SSL_getLastError will return
*    SSL_R_EXISTING_CA_CERT.
* \n\n
* 3. This function will allow only version 3 CA certficate to load, and it 
*    allows any verison of root certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey \n
* SSL_ctxUsePrivateKeyFile \n
* SSL_ctxUsePrivateKeyBuffer \n
* SSL_ctxUseRSAPrivateKey \n
* SSL_ctxUseRSAPrivateKeyFile \n
* SSL_usePrivateKey \n
* SSL_usePrivateKeyFile \n
* SSL_usePrivateKeyBuffer \n
* SSL_useRSAPrivateKey \n
* SSL_useRSAPrivateKeyFile \n
* \n
* SSL_ctxUseCertificate \n
* SSL_ctxUseCertificateFile \n
* SSL_ctxUseCertificateBuffer \n
* SSL_useCertificate \n
* SSL_useCertificateFile \n
* SSL_useCertificateBuffer \n
* \n
* SSL_ctxLoadPFXStore \n
* SSL_ctxLoadPFXStoreBuffer \n
* SSL_LoadPFXStore \n
* SSL_LoadPFXStoreBuffer \n
* \n
* SSL_ctxUseCertificateChainFile \n
* SSL_ctxUseCertificateChainBuffer \n
* \n
* SSL_ctxLoadCACertificateFile \n
* \n
* SSL_ctxLoadCrl \n
* SSL_ctxLoadCrlBuffer \n
* \n
* SSL_loadClientCAFile \n
* \n
* SSL_ctxSetDefaultPasswd_cb \n
* \n
* SSL_ctxCheckPrivateKey \n
* SSL_checkPrivateKey
*/
                                                       
SSLLINKDLL SEC_INT SSL_ctxLoadCACertificateBuffer(SSL_CTX_S *pstContext, 
                                   SEC_UCHAR* pucBuf, 
                                   SEC_UINT32 ulLen,
                                   SEC_INT type);


/*
    Func Name:  SSL_ctxLoadCACertificateFile
*/

/**
* @defgroup SSL_ctxLoadCACertificateFile
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxLoadCACertificateFile(SSL_CTX_S *pstContext,
* const SEC_CHAR *CAfile,
* SEC_INT type);
* @endcode
* 
* @par Purpose
* This is used to load the CA certificate into the SSL context.
* 
* @par Description
* SSL_ctxLoadCACertificateFile function reads a file that contains the certificate in "PEM","PFX", 
* or "DER" format. To verify user certificate during the authentication, 
* we should set it to the SSL context.
* 
* @param[in] pstContext Pointer to SSL_CTX_S of either client or server. [N/A]
* @param[in] CAfile FileName. [N/A]
* @param[in] type The formatting type could be one of the following:\n
* SSL_FILETYPE_ASN1 \n
* SSL_FILETYPE_PEM \n
* SSL_FILETYPE_PFX [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a Cert or List of Certs are set to Context. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If there are several CA certificates stored in the buffer, all these certificates will be loaded.
* \n\n
* 2. This function can be called multiple times to load CA certificate from multiple buffers. However, if the same
*    certificate is loaded twice, the function will return SEC_NULL and SSL_getLastError will return
*    SSL_R_EXISTING_CA_CERT. 
* \n\n
* 3. This function will allow only version 3 CA certficate to load, and it 
*    allows any verison of root certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey \n
* SSL_ctxUsePrivateKeyFile \n
* SSL_ctxUsePrivateKeyBuffer \n
* SSL_ctxUseRSAPrivateKey \n
* SSL_ctxUseRSAPrivateKeyFile \n
* SSL_usePrivateKey \n
* SSL_usePrivateKeyFile \n
* SSL_usePrivateKeyBuffer \n
* SSL_useRSAPrivateKey \n
* SSL_useRSAPrivateKeyFile \n
* \n
* SSL_ctxUseCertificate \n
* SSL_ctxUseCertificateFile \n
* SSL_ctxUseCertificateBuffer \n
* SSL_useCertificate \n
* SSL_useCertificateFile\n
* SSL_useCertificateBuffer \n
* \n
* SSL_ctxLoadPFXStore \n
* SSL_ctxLoadPFXStoreBuffer \n
* SSL_LoadPFXStore \n
* SSL_LoadPFXStoreBuffer \n
* \n
* SSL_ctxUseCertificateChainFile \n
* SSL_ctxUseCertificateChainBuffer \n
* \n
* SSL_ctxLoadCACertificateBuffer \n
* \n
* SSL_ctxLoadCrl \n
* SSL_ctxLoadCrlBuffer \n
* \n
* SSL_loadClientCAFile \n
* \n
* SSL_ctxSetDefaultPasswd_cb \n
* \n
* SSL_ctxCheckPrivateKey \n
* SSL_checkPrivateKey
*/
                                                       
SSLLINKDLL SEC_INT SSL_ctxLoadCACertificateFile(SSL_CTX_S *pstContext, const SEC_CHAR *CAfile, SEC_INT type);

/*
    Func Name:  SSL_ctxLoadCrlBuffer
*/

/**
* @defgroup SSL_ctxLoadCrlBuffer
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxLoadCrlBuffer(SSL_CTX_S *pstContext, 
* SEC_UCHAR* pucBuf, 
* SEC_UINT32 ulLen,
* SEC_INT type, 
* SEC_UINT32 flags);
* @endcode
* 
* @par Purpose
* This is used to load the CRL found in a buffer to the SSL context.  Also updated CRL 
* file also can be loaded
* 
* @par Description
* SSL_ctxLoadCrlBuffer function reads a buffer that contains a CRL (Certificate Revocation List) in "PEM",or "DER"
* format. To verify user certificate during the authentication, we should set it to the SSL Context.
* If SSL_OP_REM_EXP_CRL option is set,then the API will not allow to load the expired CRL.Moreover all the
* expired CRLs will be removed from the context store.
* 
* @param[in] pstContext Pointer to SSL_CTX_S of either client OR server. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the CRL has to be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* @param[in] type The formatting type could be one of the following:\n
* SSL_FILETYPE_ASN1.\n
* SSL_FILETYPE_PEM. [N/A]
* @param[in] flags The flag that is supported. It can be one of the following:\n
* X509_V_FLAG_CRL_CHECK,\n
* X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If the CRL is set to Context. [TLS_SUCCESS|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* This function can be called multiple times to load CRL from multiple buffers. 
* The function will return SEC_NULL: \n
* 1) if decoding of CRL certificate fails or bad CRL. 
* SSL_getLastError will return SSL_R_BAD_CRL.\n 
* 2) if the same CRL is loaded twice. 
* SSL_getLastError will return SSL_R_EXISTING_CRL.\n 
* 3) if the CRL is found to be expired, 
* SSL_getLastError will return SSL_R_EXPIRED_CRL.\n 
* 4) In case of some malloc failure or internal errors. 
* SSL_getLastError will return SSL_R_INTERNAL_ERROR.\n 
* It is recommended that crl dates are verified before loading the same.
*
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_ctxLoadCrlBuffer(SSL_CTX_S *pstContext, 
                                            SEC_UCHAR* pucBuf, 
                                            SEC_UINT32 ulLen,
                                            SEC_INT type, 
                                            SEC_UINT32 flags);


/*
    Func Name:  SSL_ctxLoadCrl
*/

/**
* @defgroup SSL_ctxLoadCrl
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxLoadCrl(SSL_CTX_S *pstContext,
* const SEC_CHAR *CRLfile,
* SEC_INT type,
* SEC_UINT32 flags);
* @endcode
* 
* @par Purpose
* This is used to load the CRL file to the SSL context. Also updated CRL 
* file also can be loaded
* 
* @par Description
* SSL_ctxLoadCrl function reads a file that contains a CRL (Certificate Revocation List) in "PEM",or "DER" format.
* To verify user certificate during the authentication, we should set it to the SSL Context.
* If SSL_OP_REM_EXP_CRL option is set,then the API will not allow to load the expired CRL.Moreover all the
* expired CRLs will be removed from the context store.
*
* @param[in] pstContext Pointer to SSL_CTX_S of either client OR server. [N/A]
* @param[in] CRLfile FileName. [N/A]
* @param[in] type The formatting type could be one of the following:\n
* SSL_FILETYPE_ASN1\n
* SSL_FILETYPE_PEM. [N/A]
* @param[in] flags The flag that is supported. It can be one of the following:\n
* X509_V_FLAG_CRL_CHECK,\n
* X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If the CRL is set to Context. [TLS_SUCCESS|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* This function can be called multiple times to load CRL from multiple files. 
* The function will return SEC_NULL: \n
* 1) if decoding of CRL certificate fails or bad CRL. 
* SSL_getLastError will return SSL_R_BAD_CRL.\n
* 2) if the same CRL is loaded twice. 
* SSL_getLastError will return SSL_R_EXISTING_CRL. \n
* 3) if the CRL is found to be expired, 
* SSL_getLastError will return SSL_R_EXPIRED_CRL.\n 
* 4) In case of some malloc failure or internal errors. 
* SSL_getLastError will return SSL_R_INTERNAL_ERROR. \n
* It is recommended that crl dates are verified before loading the same. 
*
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/
                                                       
SSLLINKDLL SEC_INT SSL_ctxLoadCrl(SSL_CTX_S *pstContext, const SEC_CHAR *CRLfile, SEC_INT type, SEC_UINT32 flags);

/*
    Func Name:  SSL_ctxLoadPFXStoreBuffer
*/

/**
* @defgroup SSL_ctxLoadPFXStoreBuffer
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxLoadPFXStoreBuffer(SSL_CTX_S *pstContext, 
* SEC_UCHAR* pucBuf, 
* SEC_UINT32 ulLen,
* SEC_UCHAR *macPassword, 
* SEC_INT macPasswordLen, 
* SEC_UCHAR *enPassword, 
* SEC_INT enPasswordLen);
* @endcode
* 
* @par Purpose
* This is used to load the certificate and private key in PFX format found in a buffer to the SSL context.
* 
* @par Description
* SSL_ctxLoadPFXStoreBuffer function reads a PFX store buffer that contains a certificate and a private key. To verify
* user certificate during the authentication, we should set it to the SSL_CTX_S  Context.
* 
* @param[in] pstContext Pointer to SSL_CTX_S of either client OR server. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the PFX store has to be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* @param[in] macPassword The Mac password of PKCS12 format. [N/A]
* @param[in] macPasswordLen The length of macPassword. [N/A]
* @param[in] enPassword The password for encrypt of PKCS12 format. [N/A]
* @param[in] enPasswordLen The length of enPassword. [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT User certificate and privatekey set into SSL_CTX_S. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/
                                                       

SSLLINKDLL SEC_INT SSL_ctxLoadPFXStoreBuffer(SSL_CTX_S *pstContext, 
                                            SEC_UCHAR* pucBuf, 
                                            SEC_UINT32 ulLen,
                                             SEC_UCHAR *macPassword, 
                                             SEC_INT macPasswordLen, 
                                             SEC_UCHAR *enPassword, 
                                             SEC_INT enPasswordLen);


/*
    Func Name:  SSL_ctxLoadPFXStore
*/

/**
* @defgroup SSL_ctxLoadPFXStore
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxLoadPFXStore(SSL_CTX_S *ctx,
* SEC_CHAR *pcFileName,
* SEC_UCHAR *macPassword, 
* SEC_INT macPasswordLen, 
* SEC_UCHAR *enPassword,
* SEC_INT enPasswordLen);
* @endcode
* 
* @par Purpose
* This is used to load the certificate and private key in PFX format to the SSL context.
* 
* @par Description
* SSL_ctxLoadPFXStore function reads a PFX store file that contains a certificate and a private key. To verify user
* certificate during the authentication, we should set it to the SSL_CTX_S  Context.
* 
* @param[in] ctx Pointer to SSL_CTX_S of either client OR server. [N/A]
* @param[in] pcFilename FileName. [N/A]
* @param[in] macPassword The Mac password of PKCS12 format. [N/A]
* @param[in] macPasswordLen The length of macPassword. [N/A]
* @param[in] enPassword The password for encrypt of PKCS12 format. [N/A]
* @param[in] enPasswordLen The length of enPassword. [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT User certificate and privatekey set into SSL_CTX_S. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/
                                                       

SSLLINKDLL SEC_INT SSL_ctxLoadPFXStore(SSL_CTX_S *ctx, SEC_CHAR *pcFileName, SEC_UCHAR *macPassword, 
                            SEC_INT macPasswordLen, SEC_UCHAR *enPassword, SEC_INT enPasswordLen);


/*
    Func Name:  SSL_LoadPFXStoreBuffer
*/

/**
* @defgroup SSL_LoadPFXStoreBuffer
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_LoadPFXStoreBuffer(SSL_S *ssl, 
* SEC_UCHAR* pucBuf, 
* SEC_UINT32 ulLen,
* SEC_UCHAR *macPassword, 
* SEC_INT macPasswordLen, 
* SEC_UCHAR *enPassword, 
* SEC_INT enPasswordLen);
* @endcode
* 
* @par Purpose
* This is used to load the certificate and private key in PFX format found in a buffer to the SSL object.
* 
* @par Description
* SSL_LoadPFXStoreBuffer function reads a PFX store buffer that contains a certificate and a private key. To verify
* user certificate during the authentication, we should set it to the SSL_S  Context.
* 
* @param[in] ssl Pointer to SSL_S of either client OR server. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the PFX store has to be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* @param[in] macPassword The Mac password of PKCS12 format. [N/A]
* @param[in] macPasswordLen The length of macPassword. [N/A]
* @param[in] enPassword The password for encrypt of PKCS12 format. [N/A]
* @param[in] enPasswordLen The length of enPassword. [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT User certificate and privatekey set into SSL_S. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/
                                                       
SSLLINKDLL SEC_INT SSL_LoadPFXStoreBuffer(SSL_S *ssl, 
                                            SEC_UCHAR* pucBuf, 
                                            SEC_UINT32 ulLen,
                                             SEC_UCHAR *macPassword, 
                                             SEC_INT macPasswordLen, 
                                             SEC_UCHAR *enPassword, 
                                             SEC_INT enPasswordLen);


/*
    Func Name:  SSL_LoadPFXStore
*/

/**
* @defgroup SSL_LoadPFXStore
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_LoadPFXStore(SSL_S *ssl,
* SEC_CHAR *pcFileName,
* SEC_UCHAR *macPassword, 
* SEC_INT macPasswordLen,
* SEC_UCHAR *enPassword,
* SEC_INT enPasswordLen);
* @endcode
* 
* @par Purpose
* This is used to load the certificate and private key in PFX format to the SSL object.
* 
* @par Description
* SSL_LoadPFXStore function reads a PFX store file that contains a certificate and a private key. To verify user
* certificate during the authentication, we should set it to the SSL_S Context.
* 
* @param[in] ssl Pointer to SSL_S of either client OR server. [N/A]
* @param[in] pcFilename FileName. [N/A]
* @param[in] macPassword The Mac password of PKCS12 format. [N/A]
* @param[in] macPasswordLen The length of macPassword. [N/A]
* @param[in] enPassword The password for encrypt of PKCS12 format. [N/A]
* @param[in] enPasswordLen The length of  enPassword. [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT User certificate and privatekey set into SSL_S. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/
                                                       
SSLLINKDLL SEC_INT SSL_LoadPFXStore(SSL_S *ssl, SEC_CHAR *pcFileName, SEC_UCHAR *macPassword, 
                            SEC_INT macPasswordLen, SEC_UCHAR *enPassword, SEC_INT enPasswordLen);



/*
    Func Name:  SSL_loadClientCAFile
*/

/**
* @defgroup SSL_loadClientCAFile
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_List_S *SSL_loadClientCAFile (const SEC_CHAR *pcFile,
* SEC_CHAR * pcPassword);
* @endcode
* 
* @par Purpose
* This is used to load the Clients CA name.
* 
* @par Description
* SSL_loadClientCAFile function is used to load the CA name (subject name from the certs) from the given input file.
* It is assumed that the list of certs are stored in the PEM format.
* 
* @param[in] pcFile Path to file from which the list of certs has to be loaded. [N/A]
* @param[in] pcPassword Password to read file. [N/A]
* 
* @retval SEC_List_S* Returns the list of Subject names of the certs present in the file specified. [Pointer to SEC_List_S|N/A]
* @retval SEC_List_S* If the input is invalid (NULL pointers passed). [SEC_NULL|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey,\n
* \n
* SSL_ctxSetClientCAList,\n
* SSL_setClientCAList.
*/

SSLLINKDLL SEC_List_S *SSL_loadClientCAFile (const SEC_CHAR *pcFile,
                                  SEC_CHAR * pcPassword);


/*
    Func Name: SSL_loadErrorStrings
*/

/**
* @defgroup SSL_loadErrorStrings
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_VOID SSL_loadErrorStrings (SEC_VOID);
* @endcode
* 
* @par Purpose
* This is used to load the errors generated by SSL library.
* 
* @par Description
* SSL_loadErrorStrings function loads the errors generated by SSL library.
* 
* @par Parameters
* N/A
* 
* @retval SEC_VOID This function does not return any value. [N/A|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* Usually, it is not required to call this function directly, for it has already been called by
* SSL_libraryInit internally.
* 
* @par Related Topics
* N/A
*/

SSLLINKDLL SEC_VOID SSL_loadErrorStrings (SEC_VOID);


/*
    Func Name: SSL_stateString
*/
/**
* @defgroup SSL_stateString
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_stateString (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to indicate the current state of the SSL object.
*
* @par Description
* SSL_stateString function returns a short string indicating the current state of the SSL_S object.
*
* @param[in] pstSSL Pointer to SSL_S structure. [N/A]
*
* @retval SEC_CHAR* String indicating current state is returned. [String indicating current state|N/A]
* @retval SEC_CHAR* If the input is invalid.(NULL pointer is passed) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_rstateStringLong,\n
* SSL_rstateString,\n
* SSL_stateStringLong.
*/

SSLLINKDLL const SEC_CHAR *SSL_stateString  (const SSL_S *pstSSL);


/*
    Func Name: SSL_stateStringLong
*/
/**
* @defgroup SSL_stateStringLong
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_stateStringLong (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to return a string that indicates the current state of SSL object.
*
* @par Description
* SSL_stateStringLong function returns a long string indicating the current state of the SSL_S object.
*
* @param[in] pstSSL SSL_S [N/A]
*
* @retval SEC_CHAR* String indicating current state is returned. [String indicating current state|N/A]
* @retval SEC_CHAR* If the input is invalid(NULL pointer is passed). [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_rstateStringLong,\n
* SSL_rstateString,\n
* SSL_stateString.
*/

SSLLINKDLL const SEC_CHAR *SSL_stateStringLong  (const SSL_S *pstSSL);


/*
    Func Name: SSL_rstateString
*/
/**
* @defgroup SSL_rstateString
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_rstateString (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to indicate the current read state of the SSL object. 
*
* @par Description
* SSL_rstateString function returns a string indicating the current read state of the SSL_S object.
*
* @param[in] pstSSL pointer to SSL_S structure. [N/A]
*                                                                               
* @retval SEC_CHAR* The header of the record is being evaluated [RH|N/A]
* @retval SEC_CHAR* The body of the record is being evaluated [RB|N/A]
* @retval SEC_CHAR* The record has been completely processed [RD|N/A]
* @retval SEC_CHAR* The read state is unknown. This should never happen [unknown|N/A]
* @retval SEC_CHAR* If the input is invalid (NULL pointer is passed) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_rstateStringLong,\n
* SSL_stateStringLong,\n
* SSL_stateString.
*/

SSLLINKDLL const SEC_CHAR *SSL_rstateString  (const SSL_S *pstSSL);


/*
    Func Name: SSL_rstateStringLong
*/
/**
* @defgroup SSL_rstateStringLong
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_rstateStringLong (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is to indicate the current read state of the SSL object. 
*
* @par Description
* SSL_rstateStringLong function returns a string indicating the current read state of the SSL_S object.
*
* @param[in] pstSSL Pointer to SSL_S [N/A]
*
* @retval SEC_CHAR The header of the record is being evaluated [read header|N/A]
* @retval SEC_CHAR The body of the record is being evaluated [read body|N/A]
* @retval SEC_CHAR The record has been completely processed [read done|N/A]
* @retval SEC_CHAR The read state is unknown. This should never happen [unknown|N/A]
* @retval SEC_CHAR If the input is invalid (NULL pointer is passed) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_rstateString,\n
* SSL_stateStringLong,\n
* SSL_stateString
*/

SSLLINKDLL const SEC_CHAR *SSL_rstateStringLong  (const SSL_S *pstSSL);


/*
    Func Name:  SSL_sessionGetTime
*/
/**
* @defgroup SSL_sessionGetTime
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_sessionGetTime (const SSL_SESSION_S *pstSession);
* @endcode
*
* @par Purpose
* This is used to get the time at which the session was established. 
*
* @par Description
* SSL_sessionGetTime function returns the time at which the session had been established. The time is stored in seconds.
* It is the number of seconds elapsed since midnight (00:00:00), January 1, 1970.
*
* @param[in] pstSession Pointer to SSL Session [N/A]
*
* @retval SEC_INT32 On Success [Session Established Time set in SSL Session|N/A]
* @retval SEC_INT32 In case of NULL input [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionSetTimeout,\n
* SSL_sessionGetTimeout,\n
* SSL_sessionSetTime,\n
* SSL_ctxSetTimeout,\n
* SSL_ctxGetTimeout.
*/

SSLLINKDLL SEC_INT32 SSL_sessionGetTime  (const SSL_SESSION_S *pstSession);



/*
    Func Name:  SSL_sessionSetTime
*/
/**
* @defgroup SSL_sessionSetTime
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_sessionSetTime (SSL_SESSION_S *pstSession,
* SEC_INT32 lTime);
* @endcode
*
* @par Purpose
* This is used to replace the creation time of the session with the chosen value.
*
* @par Description
* SSL_sessionSetTime function replaces the creation time of the session pstSession with the chosen value lTime.
*
* @param[in] pstSession Pointer to Session whose time to be reset [N/A]
* @param[in] lTime Resetting time [N/A]
*
* @retval SEC_INT32 On success [TLS_SUCCESS|N/A]
* @retval SEC_INT32 In case of error [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionSetTimeout,\n
* SSL_sessionGetTimeout,\n
* SSL_sessionGetTime,\n
* SSL_ctxSetTimeout,\n
* SSL_ctxGetTimeout.
*/

SSLLINKDLL SEC_INT32 SSL_sessionSetTime (SSL_SESSION_S *pstSession, 
                              SEC_INT32 lTime);


/*
    Func Name:   SSL_sessionGetTimeout
*/
/**
* @defgroup SSL_sessionGetTimeout
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_sessionGetTimeout (const SSL_SESSION_S *pstSession);
* @endcode
*
* @par Purpose
* This is used to get the timeout value set for a session.
*
* @par Description
* SSL_sessionGetTimeout function returns the timeout value set for session in seconds.          
*
* @param[in] pstSession Pointer to Session for which session time out is required [N/A]
*
* @retval SEC_INT32 On success [Time out value set at the pstSession|N/A]
* @retval SEC_INT32 In case of error [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionSetTimeout,\n
* SSL_sessionSetTime,\n
* SSL_sessionGetTime,\n
* SSL_getDefaultTimeout,\n
* SSL_ctxSetTimeout,\n
* SSL_ctxGetTimeout.
*/

SSLLINKDLL SEC_INT32 SSL_sessionGetTimeout (const SSL_SESSION_S *pstSession);


/*
    Func Name:  SSL_sessionSetTimeout
*/
/**
* @defgroup SSL_sessionSetTimeout
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_sessionSetTimeout (SSL_SESSION_S *pstSession,
* SEC_INT32 lTimeOut);
* @endcode
*
* @par Purpose
* This is used to set the timeout value for a session.
*
* @par Description
* SSL_sessionSetTimeout function sets the timeout value for session pstSession in seconds to lTimeOut.
*
* @param[in] pstSession Pointer to Session whose time out to be changed [N/A]
* @param[in] lTimeOut Time to be set [N/A]
*
* @retval SEC_INT32 On success [TLS_SUCCESS|N/A]
* @retval SEC_INT32 If the input is invalid (NULL pointers) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If this function is not called, the session’s timeout value will be inherited from SSL Context.\n\n
* 2. If lTimeOut<0, then the session can not be resumed.\n\n
*    If lTimeOut=0, then the session will never be timeout. Only when the session cache reaches its maximum size,
*    the session will be flushed out.\n\n
* 3. If we set the session’s timeout to -1, SSL_ sessionGetTimeout will return -1. It is the same as SEC_ERROR.
*    We should avoid using this timeout value.
* 
* @par Related Topics
* SSL_sessionGetTimeout,\n
* SSL_sessionSetTime,\n
* SSL_sessionGetTime,\n
* SSL_getDefaultTimeout,\n
* SSL_ctxSetTimeout,\n
* SSL_ctxGetTimeout.
*/

SSLLINKDLL SEC_INT32 SSL_sessionSetTimeout (SSL_SESSION_S *pstSession, 
                                   SEC_INT32 lTimeOut);

/*
    Func Name:  SSL_copySessionId
*/
/**
* @defgroup SSL_copySessionId
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_copySessionId (SSL_S *pstDestSesstion,
* const SSL_S *pstSrcSesstion);
* @endcode
*
* @par Purpose
* This is used to copy a session from one SSL structure to another SSL structure. 
*
* @par Description
* SSL_copySessionId function copies an SSL session from SSL structure pstSrcSession and to SSL structure pstDestSession.
* The function will not change the reference count of pstSrcSession->pstSession. It also copies the
* certificate/private key and session ID context from pstSrcSession.
*
* @param[in] pstDestSesstion Destination [N/A]
* @param[in] pstSrcSesstion Source [N/A]
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionHash,\n
* SSL_sessionCompare,\n
* SSL_sessionCompare,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID,\n
* SSL_getSession,\n
* SSL_getSessionEx,\n
* SSL_setSession.
*/

SSLLINKDLL SEC_VOID SSL_copySessionId (SSL_S *pstDestSesstion,
                               const SSL_S *pstSrcSesstion);


/*
    Func Name:  SSL_sessionNew
*/
/**
* @defgroup SSL_sessionNew
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_SESSION_S* SSL_sessionNew (SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to create a new session.
*
* @par Description
* SSL_sessionNew function creates an SSL_SESSION_S structure and returns an address of the structure. 60*5+4 is set to
* timeout value of a newly created SSL_SESSION_S structure.
*
* @par Parameters
* N/A
*
* @retval SSL_SESSION_S* On Success [Pointer to new SSL_SESSION_S structure|N/A]
* @retval SSL_SESSION_S* If operation failed [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionHash,\n
* SSL_sessionCompare,\n
* SSL_sessionCompare,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID.
*/

SSLLINKDLL SSL_SESSION_S *SSL_sessionNew (SEC_VOID);


/*
    Func Name:  SSL_sessionHash
*/
/**
* @defgroup SSL_sessionHash
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_sessionHash (const SSL_SESSION_S *pstSession);
* @endcode
*
* @par Purpose
* This returns a session id.
*
* @par Description
* SSL_sessionHash function returns a session ID formatted as an unsigned long (32-bit).
*
* @param[in] pstSession Session structure whose hash is required [N/A]
*
* @retval SEC_UNIT32 On success [A session ID formatted as an unsigned long (32-bit)|N/A]
* @retval SEC_UNIT32 If the input is invalid(NULL pointers) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionCompare,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID.
*/

 SSLLINKDLL SEC_UINT32 SSL_sessionHash  (const SSL_SESSION_S *pstSession);


/*
    Func Name:  SSL_sessionCompare
*/
/**
* @defgroup SSL_sessionCompare
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_sessionCompare (const SSL_SESSION_S *pstSessionA, 
* const SSL_SESSION_S *pstSessionB);
* @endcode
*
* @par Purpose
* This is used to compare sessions.
*
* @par Description
* SSL_sessionCompare function compares the two input sessions.
*
* @param[in] pstSessionA Session to be compared [N/A]
* @param[in] pstSessionB Session to be compared [N/A]
*
* @retval SEC_INT On success If sessions are NOT equal [TLS_SUCCESS|N/A]
* @retval SEC_INT On success If sessions are equal [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid.(NULL pointers are passed as inputs) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionNew,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID.
*/

SSLLINKDLL SEC_INT  SSL_sessionCompare  (const SSL_SESSION_S *pstSessionA, 
                             const SSL_SESSION_S *pstSessionB);


/*
    Func Name:  SSL_sessionGetID
*/
/**
* @defgroup SSL_sessionGetID
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const SEC_UCHAR *SSL_sessionGetID (const SSL_SESSION_S *pstSession,
* SEC_UINT *puiLen);
* @endcode
*
* @par Purpose
* This is used to get the session id.
*
* @par Description
* SSL_sessionGetID function gets the Session ID from the SSL Session.
*
* @param[in] pstSession From which the session id needs to be retrieved [N/A]
* @param[out] puiLen Session ID Length [N/A]
*
* @retval SEC_UCHAR* On success [The session ID|N/A]
* @retval SEC_UCHAR* If the input is invalid (NULL pointers are passed as inputs) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionPrint,\n
* SSL_sessionFree,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID.
*/

SSLLINKDLL const SEC_UCHAR *SSL_sessionGetID  (const SSL_SESSION_S *pstSession, 
                                    SEC_UINT *puiLen);


/*
    Func Name:  SSL_sessionPrint
*/
/**
* @defgroup SSL_sessionPrint
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_sessionPrint(const SSL_SESSION_S *pstSession);
* @endcode
*
* @par Purpose
* This is used to print the details of SSL_SESSION_S structure.
*
* @par Description
* SSL_sessionPrint function prints the details of SSL_SESSION_S structure to a terminal.
*
* @param[in] pstSession Session to be printed [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* This function internally uses printf to print the session information in the console. Users are advised NOT to
* use this function in C++ based adapter codes as it may have a conflict with std::cout.
* 
* @par Related Topics
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionFree,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID.
*/

SSLLINKDLL SEC_INT  SSL_sessionPrint(const SSL_SESSION_S *pstSession);


/*
    Func Name:  SSL_sessionFree
*/
/**
* @defgroup SSL_sessionFree
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_sessionFree (SSL_SESSION_S *pstSession);
* @endcode
*
* @par Purpose
* This is used to free an SSL_SESSION_S structure.
*
* @par Description
* SSL_sessionFree function frees an allocated SSL_SESSION_S structure.
*
* @param[in] pstSession Session to be freed [N/A]
*
* @retval SEC_VOID This function does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID,\n
* SSL_getSessionEx.
*/

SSLLINKDLL SEC_VOID SSL_sessionFree (SSL_SESSION_S *pstSession);


/*
    Func Name:  SSL_sessionEncode
*/
/**
* @defgroup SSL_sessionEncode
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_UCHAR* SSL_sessionEncode (SSL_SESSION_S *pstSession,
* SEC_UINT32 *pulLen);
* @endcode
*
* @par Purpose
* This is used to encode a session in DER format.
*
* @par Description
* SSL_sessionEncode function encodes pstSession.
*
* @param[in] pstSession Pointer to SSL Session to be encoded [N/A]
* @param[out] pulLen Pointer onto which the encoded Session length is to be added [N/A]
*
* @retval SEC_UCHAR* On success [Returns the buffer containing encoded session|N/A]
* @retval SEC_UCHAR* If the input is invalid (NULL pointers) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionDecode.
*/

SSLLINKDLL SEC_UCHAR* SSL_sessionEncode (SSL_SESSION_S *pstSession, 
                              SEC_UINT32 *pulLen);

/*
    Func Name:  SSL_setSession
*/
/**
* @defgroup SSL_setSession
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setSession (SSL_S *pstSSL,
* SSL_SESSION_S *pstSession);
* @endcode
*
* @par Purpose
* This is used to set the session to be used when the TLS/SSL connection is to be established.
*
* @par Description
* SSL_setSession function sets session to be used when the TLS/SSL connection is to be established and is only useful for
* TLS/SSL clients. When the session is set, the reference count of session is incremented by 1. If the session is not
* reused, the reference count is decremented again during SSL_connect. Whether the session was reused can be queried
* with the SSL_SESSION_REUSED call. If there is already a session set inside ssl (because it was set with
* SSL_setSession before or because the same SSL was already used for a connection), SSL_sessionFree() will be
* called for that session.
*
* @param[in] pstSSL Pointer to SSL_S [N/A]
* @param[in] pstSession Pointer to SSL_SESSION_S [N/A]
*
* @retval SEC_INT On Success [TLS_SUCCESS|N/A]
* @retval SEC_INT On Failure [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxRemoveSession,\n
* SSL_ctxAddSession,\n
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID,\n
* SSL_getSession,\n
* SSL_getSessionEx.
*/

SSLLINKDLL SEC_INT  SSL_setSession (SSL_S *pstSSL, 
                        SSL_SESSION_S *pstSession);


/*
    Func Name:  SSL_ctxAddSession
*/
/**
* @defgroup SSL_ctxAddSession
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxAddSession (SSL_CTX_S *pstCtx,
* SSL_SESSION_S *pstSession);
* @endcode
*
* @par Purpose
* This is used to add the specified session to the SSL context object.
*
* @par Description
* SSL_ctxAddSession function adds the session pstSession to the context pstCtx. The reference count for session
* pstSession is incremented by 1. If a session with the same session id already exists, the old session is removed by
* calling SSL_sessionFree.
*
* @param[in] pstCtx Pointer to Context [N/A]
* @param[in] pstSession Pointer to Session [N/A]
*
* @retval SEC_INT On success. [TLS_SUCCESS|N/A]
* @retval SEC_INT On success. If a session with the same session id already exists, then new session will replace
* the old session [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input), or the Extensions are supported by the
* session passed, but not supported by the context and vice versa [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxRemoveSession,\n
* SSL_setSession,\n
* SSL_sessionFree,\n
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree,\n
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID.
*/

SSLLINKDLL SEC_INT  SSL_ctxAddSession  (SSL_CTX_S *pstCtx, 
                            SSL_SESSION_S *pstSession);


/*
    Func Name: SSL_ctxRemoveSession
*/
/**
* @defgroup SSL_ctxRemoveSession
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxRemoveSession  (SSL_CTX_S* pstCtx,
* SSL_SESSION_S *pstSession);
* @endcode
*
* @par Purpose
* This is used to remove the specified session from the SSL context object.
*
* @par Description
* SSL_ctxRemoveSession function removes the session 'pstSession' from the SSL context 'pstCtx'.
*
* @param[in] pstCtx SSL_CTX_S context structure from which the session has to be removed [N/A]
* @param[in] pstSession Session that has to be removed [N/A]
*                                                                               
* @retval SEC_INT If the operation succeeded [TLS_SUCCESS|N/A]
* @retval SEC_INT If the session was not found in the cache [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxAddSession,\n
* SSL_setSession,\n
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree.
*/

SSLLINKDLL SEC_INT  SSL_ctxRemoveSession  (SSL_CTX_S* pstCtx, 
                               SSL_SESSION_S *pstSession);


/*
    Func Name: SSL_ctxSetGenerateSessionID
*/
/**
* @defgroup SSL_ctxSetGenerateSessionID
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetGenerateSessionID (SSL_CTX_S *pstContext,
* pfGenSession_cb cb);
* @endcode
*
* @par Purpose
* This is used to set the callback function for generating new session ids.
*
* @par Description
* SSL_ctxSetGenerateSessionID function sets the callback function for generating new session ids for TLS sessions
* for SSL context to be cb.
*
* @param[in] pstContext Pointer to SSL_CTX_S [N/A]
* @param[in] cb Callback function [N/A]
*
* @retval SEC_INT After setting the callback Function to SSL context [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid(NULL pointers is being passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_hasMatchingSessionID,\n
* SSL_setGenerateSessionID.
*/

SSLLINKDLL SEC_INT  SSL_ctxSetGenerateSessionID  (SSL_CTX_S *pstContext, 
                                      pfGenSession_cb cb);

/*
    Func Name: SSL_setGenerateSessionID
*/
/**
* @defgroup SSL_setGenerateSessionID
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setGenerateSessionID (SSL_S *pstSSL,
* pfGenSession_cb cb);
* @endcode
*
* @par Purpose
* This is used to set the callback function for generating the new session ids.
*
* @par Description
* SSL_setGenerateSessionID function sets the callback function for generating new session ids for TLS sessions
* for SSL_S object to be cb.
*
* @param[in] pstSSL Pointer to SSL_S [N/A]
* @param[in] cb Callback function [N/A]
*
* @retval SEC_INT After setting the callback Function to SSL object [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid(NULL pointers is being passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_hasMatchingSessionID,\n
* SSL_ctxSetGenerateSessionID,\n
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree.
*/

SSLLINKDLL SEC_INT  SSL_setGenerateSessionID (SSL_S *pstSSL, 
                                  pfGenSession_cb cb);

/*
    Func Name: SSL_hasMatchingSessionID
*/
/**
* @defgroup SSL_hasMatchingSessionID
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_hasMatchingSessionID (const SSL_S *pstSSL, 
* const SEC_UCHAR *pucID,
* SEC_UINT uiIdLen);
* @endcode
*
* @par Purpose
* This is used to check whether a session id is already contained in the internal session cache.
*
* @par Description
* SSL_hasMatchingSessionID function checks, whether a session with id 'pucID' of length 'uiIdLen' is already contained
* in the internal session cache of the parent context of SSL.
*
* @param[in] pstSSL Pointer to  SSL_S object [N/A]
* @param[in] pucID Session ID that has to be matched [N/A]
* @param[in] uiIdLen Length of the session ID [N/A]
*
* @retval SEC_INT If the same session-id is already present in the session cache [TLS_SUCCESS|N/A] 
* @retval SEC_INT If the session-id is not present in the session cache [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setGenerateSessionID,\n
* SSL_ctxSetGenerateSessionID,\n
* SSL_sessionNew,\n
* SSL_sessionCompare,\n
* SSL_sessionHash,\n
* SSL_copySessionId,\n
* SSL_sessionGetID,\n
* SSL_sessionPrint,\n
* SSL_sessionFree.
*/

SSLLINKDLL SEC_INT  SSL_hasMatchingSessionID  (const SSL_S *pstSSL, 
                                   const SEC_UCHAR *pucID, 
                                   SEC_UINT uiIdLen);


/*
    Func Name:  SSL_sessionDecode
*/
/**
* @defgroup SSL_sessionDecode
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_SESSION_S* SSL_sessionDecode (const SEC_UCHAR *pucEncSession,
* SEC_UINT32 ulEncLength,
* SEC_UINT32 * pulDecLength);
* @endcode
*
* @par Purpose
* This is used to decode a session information which has been encoded in a DER format using the SSL_sessionEncode function.
*
* @par Description
* SSL_sessionDecode function decodes the pucEncSession.
*
* @param[in] pucEncSession Pointer to Encoded session [N/A]
* @param[in] ulEncLength Encoded length of the Session [N/A]
* @param[out] pulDecLength Pointer to length of the Decoded Session [N/A]
*
* @retval SSL_SESSION_S* On success [Pointer to decoded SSL Session|N/A]
* @retval SSL_SESSION_S* If the input is invalid(NULL pointers is being passed as input) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_sessionEncode.
*/

SSLLINKDLL SSL_SESSION_S* SSL_sessionDecode (const SEC_UCHAR *pucEncSession,
                                  SEC_UINT32 ulEncLength,
                                  SEC_UINT32 * pulDecLength);


/*
    Func Name: SSL_getPeerCertificate
*/
/**
* @defgroup SSL_getPeerCertificate
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* X509_CERT_EXTENDED_S* SSL_getPeerCertificate (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to get a pointer to the X509 certificate which the peer presented.
*
* @par Description
* SSL_getPeerCertificate function returns a pointer to the X509 certificate the peer presented. If the peer did not
* present a certificate, NULL is returned.
*
* @param[in] pstSSL SSL_S object [N/A]
*
* @retval X509_CERT_EXTENDED_S* If peer certificate is present [Pointer to the X509 certificate the peer presented|N/A]
* @retval X509_CERT_EXTENDED_S* If peer certificate is absent [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* X509_freeCertExtended function should be called after the certificate is used. Otherwise some memory leakage will be
* there.
* 
* @par Related Topics
* SSL_getPeerCertChain,\n
* SSL_getPeerIssuerCertificate.
*/

SSLLINKDLL X509_CERT_EXTENDED_S *   SSL_getPeerCertificate  (const SSL_S *pstSSL);

/*
    Func Name: SSL_getPeerIssuerCertificate
*/
/**
* @defgroup SSL_getPeerIssuerCertificate
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* X509_CERT_EXTENDED_S* SSL_getPeerIssuerCertificate (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to get a pointer to the X509 certificate which the peer's issuer presented.
*
* @par Description
* SSL_getPeerIssuerCertificate function returns a pointer to the X509 certificate the peer's issuer presented. If the
* peer's Issuer did not present a certificate, NULL is returned.
*
* @param[in] pstSSL SSL_S object [N/A]
*
* @retval X509_CERT_EXTENDED_S* If peer issuer certificate is present [Pointer to the X509 certificate the peer's issuer
* presented|N/A]
* @retval X509_CERT_EXTENDED_S* If peer issuer certificate is absent [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getPeerCertChain,\n
* SSL_getPeerCertificate.
*/

SSLLINKDLL X509_CERT_EXTENDED_S *   SSL_getPeerIssuerCertificate  (const SSL_S *pstSSL);


/*
    Func Name: SSL_getPeerCertChain
*/
/**
* @defgroup SSL_getPeerCertChain
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_List_S *SSL_getPeerCertChain (SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to get a pointer to list of certificates forming the certificate chain of the peer.
*
* @par Description
* SSL_getPeerCertChain function returns a pointer to list of certificates forming the certificate chain of the peer. If
* called on the client side, the list also contains the peer's certificate; if called on the server side, the peer's
* certificate must be obtained separately using SSL_getPeerCertificate. If the peer did not present a certificate,
* NULL is returned.
*
* @param[in] pstSSL SSL_S object [N/A]
*
* @retval SEC_List_S* If peer certificate chain is present [Pointer to list of certificates forming the chan of the peer|N/A]
* @retval SEC_List_S* If peer certificate chain is absent [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getPeerIssuerCertificate,\n
* SSL_getPeerCertificate.
*/

SSLLINKDLL SEC_List_S *SSL_getPeerCertChain (SSL_S *pstSSL);


/*
    Func Name: SSL_ctxGetVerifyMode
*/
/**
* @defgroup SSL_ctxGetVerifyMode
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxGetVerifyMode (const SSL_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This returns the verification mode set in the SSL context.
*
* @par Description
* SSL_ctxGetVerifyMode function returns the verification mode currently set in SSL context.
*
* @param[in] pstContext SSL_CTX_S context [N/A]
*
* @retval SEC_INT On success [Verification mode set in the SSL context|N/A]
* @retval SEC_INT If the input is invalid(NULL pointers is passed as input) [SEC_ERROR|N/A]         
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetVerify,\n
* SSL_ctxGetVerifyDepth,\n
* SSL_ctxGetVerifyCallback.
*/
 
SSLLINKDLL SEC_INT SSL_ctxGetVerifyMode (const SSL_CTX_S *pstContext);

/*
    Func Name: SSL_ctxGetVerifyDepth
*/
/**
* @defgroup SSL_ctxGetVerifyDepth
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxGetVerifyDepth (const SSL_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This returns the validation depth currently set in the SSl context.
*
* @par Description
* SSL_ctxGetVerifyDepth function returns the Certificate Chain Validation Depth currently set in SSL context.
*
* @param[in] pstContext SSL_CTX_S context [N/A]
*
* @retval SEC_INT On success [Returns the Certificate Chain Validation Depth set in SSL context|N/A]
* @retval SEC_INT If the input is invalid(NULL pointers is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetVerifyDepth,\n
* SSL_ctxGetVerifyMode.
*/

SSLLINKDLL SEC_INT SSL_ctxGetVerifyDepth (const SSL_CTX_S *pstContext);


/*
    Func Name: SSL_ctxGetVerifyCallback
*/
/**
* @defgroup SSL_ctxGetVerifyCallback
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT (*SSL_ctxGetVerifyCallback ( const SSL_CTX_S *pstContext)) (SEC_INT iOK, X509_STORE_CTX_S * pstStoreCtx);
* @endcode
*
* @par Purpose
* This returns the verification callback currently set in the SSL context.
*
* @par Description 
* SSL_ctxGetVerifyCallback function returns a function pointer to the verification callback currently set in ctx. If no
* callback was explicitly set, the NULL pointer is returned and the default callback will be used.
*
* @param[in] pstContext From which the pointer to application specific verification function is returned [N/A]
*           
* @retval cb callback function SEC_INT (*)(SEC_INT,X509_STORE_CTX_S *) is returned on success\n
* or\n
* SEC_NULL in the following conditions:\n
* 1. If the input is invalid (NULL pointer is passed as input)\n
* 2. If pointer to the callback function is not set [Pointer to verification callback function set in SSL context or SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetCertVerify_cb,\n
* SSL_ctxSetVerifyDepth,\n
* SSL_ctxSetVerify,\n
* SSL_ctxGetVerifyMode.
*/

 SSLLINKDLL SEC_INT (*SSL_ctxGetVerifyCallback ( const SSL_CTX_S *pstContext))(SEC_INT iOK, X509_STORE_CTX_S * pstStoreCtx);


/*
    Func Name: SSL_ctxGetVerifyCBAppData
*/

/**
* @defgroup SSL_ctxGetVerifyCBAppData
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_VOID *SSL_ctxGetVerifyCBAppData(SSL_CTX_S *pstSSLCtx)
* @endcode
* 
* @par Purpose
* This is used to get the verify callback application data from SSL Context. \n
* 
* @par Description
* SSL_ctxGetVerifyCBAppData function gets the verify callback application
* data from SSL context. SSL library will not do any validation or memory 
* allocation/deallocation for the application data.\n 
*
* @param[in] pstSSLCtx Pointer to SSL context [N/A|N/A]
* 
* @retval SEC_VOID* Pointer to application data will be returned [N/A]
* or\n
* SEC_NULL will be returned in following conditions: \n
* 1. If the input is invalid (NULL pointer is passed as input) \n
* 2. If pointer to the application data is not set.
* [Pointer to application data or SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
* 
* @par Note
* \n
* NA
*
* @par Related Topics
* SSL_setVerifyCBAppData \n
* SSL_ctxSetVerifyCBAppData \n
* SSL_getVerifyCBAppData
*/

SSLLINKDLL SEC_VOID *SSL_ctxGetVerifyCBAppData(SSL_CTX_S *pstSSLCtx);


/*
    Func Name:  SSL_ctxSetVerify
*/
/**
* @defgroup SSL_ctxSetVerify
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetVerify ( SSL_CTX_S *pstContext,
* SEC_INT iMode,
* SEC_INT (*pfCallback)(SEC_INT, X509_STORE_CTX_S *));
* @endcode
*
* @par Purpose
* This is used to set the verification flags for SSL context and specifies the verify callback function to be used.
*
* @par Description 
* SSL_ctxSetVerify function sets the verification flags for pstContext to be iMode and specifies the verify callback
* function to be used. If no callback function shall be specified, the NULL pointer can be used for verify callback.
*
* @param[in] pstContext Pointer to SSL Context [N/A]
* @param[in] iMode The verification of certificates can be controlled by a set of logically or'ed mode flags:\n\n
* SSL_VERIFY_NONE:\n
* Server mode:The server will not send a client certificate request to the client, so the client will not send a
* certificate.\n
* Client mode:If not using an anonymous cipher (by default disabled), the server will send a certificate which will be
* checked. The result of the certificate verification process can be checked after the SSL handshake using the
* SSL_getVerifyResult() function. The handshake will be continued regardless of the verification result.\n\n
* SSL_VERIFY_PEER:\n
* Server mode:The server sends a client certificate request to the client. The certificate returned (if any) is checked.
* If the verification process fails, the SSL handshake is immediately terminated with an alert message containing the
* reason for the verification failure. The behavior can be controlled by the additional SSL_VERIFY_FAIL_IF_NO_PEER_CERT
* flags.\n
* Client mode:The server certificate is verified. If the verification process fails, the TLS/SSL handshake is immediately
* terminated with an alert message containing the reason for the verification failure. If no server certificate is sent,
* because an anonymous cipher is used, SSL_VERIFY_PEER is ignored.\n\n
* SSL_VERIFY_FAIL_IF_NO_PEER_CERT:\n
* Server mode:If the client did not return a certificate, the SSL handshake is immediately terminated with a "handshake
* failure" alert. This flag must be used together with SSL_VERIFY_PEER.\n
* Client mode:Ignored.\n\n
* SSL_VERIFY_CLIENT_ONCE:\n
* This option is deprecated & should not be used.\n
* Exactly one of the mode flags SSL_VERIFY_NONE and SSL_VERIFY_PEER must be set at any time. [N/A]
*                 
* @param[in] pfCallback The callback function is used to control the behavior when the SSL_VERIFY_PEER flag is set. It
* must be supplied by the application and receives two arguments: first one is of type SEC_INT indicates, whether the
* verification of the certificate in question was passed (1) or not(0). X509_STORE_CTX_S * is a pointer to the complete context
* used for the certificate chain verification. [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetCertVerify_cb,\n
* SSL_ctxSetVerifyDepth,\n
* SSL_ctxGetVerifyCallback,\n
* SSL_ctxGetVerifyMode.
*/

SSLLINKDLL SEC_INT SSL_ctxSetVerify ( SSL_CTX_S *pstContext,
                            SEC_INT iMode,
                            SEC_INT (*pfCallback)(SEC_INT, X509_STORE_CTX_S *));


/*
    Func Name: SSL_ctxSetVerifyCBAppData
*/

/**
* @defgroup SSL_ctxSetVerifyCBAppData
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetVerifyCBAppData(SSL_CTX_S *pstSSLCtx, SEC_VOID *pAppData)
* @endcode
* 
* @par Purpose
* This is used to set the verify callback application data in SSL context. \n
* 
* @par Description
* SSL_ctxSetVerifyCBAppData function sets the verify callback application
* data in SSL context. SSL library will not do any validation or memory 
* allocation/deallocation for the application data.\n 
*
* @param[in] pstSSLCtx Pointer to SSL context [N/A|N/A]
* @param[in] pAppData Pointer to verify callback application data[N/A|N/A]
* 
* @retval SEC_INT On success. [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL SSL Context Pointer is passed).
* [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
* 
* @par Note
* \n
* NA
*
* @par Related Topics
* SSL_setVerifyCBAppData \n
* SSL_getVerifyCBAppData \n
* SSL_ctxGetVerifyCBAppData
*/

SSLLINKDLL SEC_INT SSL_ctxSetVerifyCBAppData(SSL_CTX_S *pstSSLCtx,
                                                        SEC_VOID *pAppData);


/*
    Func Name: SSL_ctxSetVerifyDepth
*/
/**
* @defgroup SSL_ctxSetVerifyDepth
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT  SSL_ctxSetVerifyDepth (SSL_CTX_S *pstContext,
* SEC_INT iDepth);
* @endcode
*
* @par Purpose
* This is used to set the validation depth in SSL context.
*
* @par Description 
* SSL_ctxSetVerifyDepth function sets the Certificate Chain Validation Depth in SSL context.
*
* @param[in] pstContext Pointer to SSL_CTX_S [N/A]
* @param[in] iDepth Certificate Chain Validation Depth to be set in SSL context [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid(NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* SSL_ctxSetVerifyDepth or SSL_setVerifyDepth function should be called to set the reasonable verify depth for
* non-anonymous authentication. The default verify depth is -1.
* 
* @par Related Topics
* SSL_ctxSetCertVerify_cb,\n
* SSL_ctxSetVerify,\n
* SSL_ctxGetVerifyCallback,\n
* SSL_ctxGetVerifyDepth.
*/

SSLLINKDLL SEC_INT SSL_ctxSetVerifyDepth (SSL_CTX_S *pstContext,
                                SEC_INT iDepth);

/*
    Func Name:  SSL_ctxSetCertVerify_cb
*/
/**
* @defgroup SSL_ctxSetCertVerify_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetCertVerify_cb (SSL_CTX_S *pstContext,
* SEC_INT (*cb)(X509_STORE_CTX_S *,SEC_VOID *), SEC_VOID *pArg);
* @endcode
*
* @par Purpose
* This is used to set the verification callback function for SSL context.
*
* @par Description 
* SSL_ctxSetCertVerify_cb function sets the verification callback function for pstContext. SSL objects that are created
* from pstContext inherit the setting  valid at the time SSL_new() is called. Whenever a certificate is verified during a
* TLS handshake, a verification function is called. If the application does not explicitly specify a verification callback
* function, the built-in verification function is used. If a verification callback is specified through
* SSL_ctxSetCertVerify_cb(), the supplied callback function is called instead.\n
* By setting callback to NULL, the default behavior is restored.
*
* @param[in] cb pointer to callback function.[N/A]
* @param[in] pArg pointer to arguments.[N/A]
* @param[in] pstContext Pointer to SSL context object.[N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid(NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetVerify,\n
* SSL_ctxSetVerifyDepth,\n
* SSL_ctxGetVerifyCallback.
*/

SSLLINKDLL SEC_INT SSL_ctxSetCertVerify_cb (SSL_CTX_S *pstContext,
                                  SEC_INT (*cb)(X509_STORE_CTX_S *,SEC_VOID *), 
                                  SEC_VOID *pArg);

#ifndef SSL_NO_RSA
/*
    Func Name:  SSL_ctxUseRSAPrivateKey
*/
/**
* @defgroup SSL_ctxUseRSAPrivateKey
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxUseRSAPrivateKey (SSL_CTX_S *pstContext,
* SEC_PKEY_S *pstRSAKey);
* @endcode
*
* @par Purpose
* This is used to add the private key of type RSA to the SSL context
*
* @par Description 
* SSL_ctxUseRSAPrivateKey function adds the private key pstRSAKey of type RSA to pstContext.
*
* @param[in] pstContext Pointer to SSL Context [N/A]
* @param[in] pstRSAKey Structure to hold a private key [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_ERROR or SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. This API does not support loading of private key
*    dynamically. Application code should not call this API in any parallel
*    operation with either SSL Object (SSL_S) or SSL context(SSL_CTX_S)
*    operations. If used, application will lead to core dump.\n\n
* 2. SSL_ctxUsePrivateKey can also be used to load the RSA private key. So usually we should call SSL_ctxUsePrivateKey
*    instead of SSL_ctxUseRSAPrivateKey.\n\n
* 3. When a private key is being set, SSL library will check if a certificate has already been set. Then SSL library will
*    check whether they are pair. If not, the private key is set but the certificate will be unloaded and the API returns
*    0. If the application wants to switch certificate/private key pair, it should first switch the certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_ctxUseRSAPrivateKey  ( SSL_CTX_S *pstContext, SEC_PKEY_S *pstRSAKey);
#endif



/*
    Func Name:  SSL_ctxUsePrivateKey
*/
/**
* @defgroup SSL_ctxUsePrivateKey
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxUsePrivateKey (SSL_CTX_S *pstContext,
* SEC_PKEY_S *pstPKey);
* @endcode
*
* @par Purpose
* This is used to add the private key to SSL context.
*
* @par Description
* SSL_ctxUsePrivateKey function adds pstPKey as private key to pstContext.
*
* @param[in] pstContext Pointer to SSL Context [N/A]
* @param[in] pstPKey Structure to hold a private key [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. This API does not support loading of certificate chain
*    dynamically. Application code should not call this API in any parallel
*    operation with either SSL Object (SSL_S) or SSL context(SSL_CTX_S)
*    operations. If used, application will lead to core dump.\n\n
* 2. When a private key is being set, SSL library will check
*    if a certificate has already been set or not.
*    Then it will check whether they are pair or not.
*    If not, the private key is set but the certificate will be
*    unloaded and the API returns 0.
*    If the application wants to switch certificate/private key pair,
*    it should first switch to certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_ctxUsePrivateKey ( SSL_CTX_S *pstContext, SEC_PKEY_S *pstPKey);


/*
    Func Name:  SSL_ctxUseCertificate
*/
/**
* @defgroup SSL_ctxUseCertificate
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxUseCertificate (SSL_CTX_S *pstContext,
* X509_CERT_EXTENDED_S *pstExtndCert);
* @endcode
*
* @par Purpose
* This is used to add the extended certificate structure to the SSL context.
*
* @par Description
* SSL_ctxUseCertificate function adds pstExtndCert as Certificate to pstContext.
*
* @param[in] pstContext Pointer to SSL Context [N/A]
* @param[in] pstExtndCert Structure to hold an Extended Certificate [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On all failure conditions. The failure can be when decoding of certificate fails. [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer). [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. When a certificate is set, SSL library will check if a private key
*    is already set or not. Then SSL library will check whether they are
*    pair or not. If not, the certificate is set but the private key is
*    unloaded and the API returns 1. If the application wants to switch
*    certificate/private key pair, it should first switch to certificate.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_ctxUseCertificate (SSL_CTX_S *pstContext, 
                               X509_CERT_EXTENDED_S *pstExtndCert);


/*
    Func Name:  SSL_ctxSetDefaultPasswd_cb
*/
/**
* @defgroup SSL_ctxSetDefaultPasswd_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetDefaultPasswd_cb (SSL_CTX_S *pstContext,
* SEC_CHAR *pcDefaultPwdcallback);
* @endcode
*
* @par Purpose
* This is used to set the default password into the SSL context.
*
* @par Description
* SSL_ctxSetDefaultPasswd_cb function sets the default password, which is used during loading/storing a PFX
* certificate/private key with encryption or PEM private key with encryption.
*
* @param[in] pstContext Pointer to SSL_CTX_S [N/A]
* @param[in] pcDefaultPwdcallback Pointer to password to be set [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid(NULL pointers is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* The memory pointed by pcDefaultPwdcallback should not be free when we call other api using the password, such as
* SSL_ctxUsePrivateKeyFile function. Otherwise the application will crash.
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_ctxSetDefaultPasswd_cb (SSL_CTX_S *pstContext, SEC_CHAR *pcDefaultPwdcallback);

/*
    Func Name:  SSL_ctxSetDefaultPasswdUserdata_cb
*/
/**
* @defgroup SSL_ctxSetDefaultPasswdUserdata_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT  SSL_ctxSetDefaultPasswdUserdata_cb (SSL_CTX_S *pstContext,
* SEC_VOID *pstPasswd);
* @endcode
*
* @par Purpose
* This is kept for backward compatibility. Do not use.
*
* @par Description
* This is kept for backward compatibility. Do not use.
*
* @param[in] pstContext Pointer to SSL_CTX_S [N/A]
* @param[in] pstPasswd Pointer to char . password to be set [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid(NULL pointers is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetDefaultPasswd_cb.
*/

SSLLINKDLL SEC_INT SSL_ctxSetDefaultPasswdUserdata_cb (SSL_CTX_S *pstContext, SEC_VOID *pstPasswd);


/*
    Func Name:  SSL_ctxCheckPrivateKey
*/
/**
* @defgroup SSL_ctxCheckPrivateKey
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxCheckPrivateKey ( const SSL_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This is used to check the consistency of a private key with the corresponding certificate.
*
* @par Description
* SSL_ctxCheckPrivateKey function checks the consistency of a private key with the corresponding certificate loaded into
* SSL context. If more than one key/certificate pair (RSA/DSA) is installed, the last item installed will be checked.
*
* @param[in] pstContext Pointer to SSL context [N/A]
*
* @retval SEC_INT On successful execution [SEC_SUCCESS|N/A]
* @retval SEC_INT On failure conditions [Non-zero|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT SSL_ctxCheckPrivateKey ( const SSL_CTX_S *pstContext);

/*
    Func Name:  SSL_checkPrivateKey
*/
/**
* @defgroup SSL_checkPrivateKey
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_checkPrivateKey ( const SSL_S *pstContext);
* @endcode
*
* @par Purpose
* This is used to check the consistency of a private key with the corresponding certificate loaded into SSL_S object.
*
* @par Description
* SSL_checkPrivateKey function checks the consistency of a private key with the corresponding certificate loaded into
* SSL_S object. If more than one key/certificate pair (RSA/DSA) is installed, the last item installed will be checked.
*
* @param[in] pstContext Pointer to SSL object [N/A]
*
* @retval SEC_INT On successful execution [SEC_SUCCESS|N/A]
* @retval SEC_INT On failure conditions [Non-zero|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyFile,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey.
*/

 SSLLINKDLL SEC_INT SSL_checkPrivateKey ( const SSL_S *pstContext);


/*
    Func Name:  SSL_ctxSetSessionIDContext
*/
/**
* @defgroup SSL_ctxSetSessionIDContext
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetSessionIDContext (SSL_CTX_S *pstContext,
* const SEC_UCHAR *pucSidCtx,
* SEC_UINT uiSidCtxLen);
* @endcode
*
* @par Purpose
* This is used to set the session ID into the SSL context.
*
* @par Description
* SSL_ctxSetSessionIDContext function sets the context pucSidCtx of length uiSidCtxLen within which a session can be
* reused for the SSL context (server side only).
*
* @param[in] pstContext Pointer to SSL Context [N/A]
* @param[in] pucSidCtx Pointer to SessionID Context [N/A]
* @param[in] uiSidCtxLen SessionID Context Length [N/A]
*
* @retval SEC_INT On successful execution [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input length exceeds SSL_MAX_SSL_SESSION_ID_LENGTH [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointers are passed as inputs) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. Sessions are generated within a certain context. During exporting/importing sessions, it would be possible to
*    re-import a session generated from another context (e.g. another application), which might lead to malfunctions.
*    Therefore each application must set its own session id context pucSidCtx, which is used to distinguish the contexts
*    and is stored in exported sessions. The pucSidCtx can be any kind of binary data with a given length, it is therefore
*    possible to use, for example, the name of the application and/or the hostname and/or service name.\n\n
* 2. The session id context becomes part of the session. The session id context is set by the SSL/TLS server. The
*    SSL_ctxSetSessionIDContext() and SSL_setSessionIDContext() functions are therefore only useful on the server side.\n\n
* 3. If the session id context is not set on an SSL/TLS server and client certificates are used, stored sessions will not
*    be reused but a fatal error will be flagged and the handshake will fail.
* 
* @par Related Topics
* SSL_setSessionIDContext.
*/

 SSLLINKDLL SEC_INT SSL_ctxSetSessionIDContext (SSL_CTX_S *pstContext,
                                    const SEC_UCHAR *pucSidCtx, 
                                    SEC_UINT uiSidCtxLen);


/*
    Func Name:  SSL_setSessionIDContext
*/
/**
* @defgroup SSL_setSessionIDContext
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setSessionIDContext(SSL_S *pstSSL,
* const SEC_UCHAR *pucSidCtx,
* SEC_UINT uiSidCtxLen);
* @endcode
*
* @par Purpose
* This is used to set the session ID into the SSL_S object.
*
* @par Description
* SSL_setSessionIDContext function sets the context pucSidCtx of length uiSidCtxLen within which a session can be reused
* for the SSL_S object (server side only).
*  
* @param[in] pstSSL Pointer to SSL object [N/A]  
* @param[in] pucSidCtx Pointer to SessionID Context [N/A]
* @param[in] uiSidCtxLen SessionID Context Length [N/A]
*
* @retval SEC_INT On successful execution [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input length exceeds SSL_MAX_SSL_SESSION_ID_LENGTH [SEC_NULL|N/A]
* @retval SEC_INT If the invalid input (NULL pointers) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. Sessions are generated within a certain context. During exporting/importing sessions, it would be possible to
*    re-import a session generated from another context (e.g. another application), which might lead to malfunctions.
*    Therefore each application must set its own session id context pucSidCtx, which is used to distinguish the contexts
*    and is stored in exported sessions. The pucSidCtx can be any kind of binary data with a given length, it is therefore
*    possible to use, for example, the name of the application and/or the hostname and/or service name.\n\n
* 2. The session id context becomes part of the session. The session id context is set by the SSL/TLS server. The
*    SSL_ctxSetSessionIDContext() and SSL_setSessionIDContext() functions are therefore only useful on the server side.\n\n
* 3. If the session id context is not set on an SSL/TLS server and client certificates are used, stored sessions will not
*    be reused but a fatal error will be flagged and the handshake will fail.
* 
* @par Related Topics
* SSL_ctxSetSessionIDContext.
*/

 SSLLINKDLL SEC_INT SSL_setSessionIDContext(SSL_S *pstSSL,
                                const SEC_UCHAR *pucSidCtx, 
                                SEC_UINT uiSidCtxLen);

/*
    Func Name:  SSL_new
*/
/**
* @defgroup SSL_new
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_S* SSL_new(SSL_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This is used to create a new SSL object.
*
* @par Description
* SSL_new function creates the new SSL object. This function extracts the configuration parameters from
* the SSL context which is passed as a input parameter.
*
* @param[in] pstContext Pointer to SSL context [N/A]
*
* @retval SSL_S* On successful execution [The new SSL object|N/A]
* @retval SSL_S* On failure conditions [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_free,\n
* SSL_ctxExNew,\n
* SSL_ctxNew,\n
* SSL_clear.
*/

 SSLLINKDLL SSL_S * SSL_new ( SSL_CTX_S *pstContext);


/*
    Func Name:  SSL_free
*/
/**
* @defgroup SSL_free
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_free(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to free an SSL object.
*
* @par Description
* SSL_free function frees an SSL object.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_new,\n
* SSL_clear.
*/

 SSLLINKDLL SEC_VOID SSL_free(SSL_S *pstSSL);


/*
    Func Name:  SSL_accept
*/
/**
* @defgroup SSL_accept
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_accept(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to wait for a TLS/SSL client to initiate the TLS/SSL handshake.
*
* @par Description
* SSL_accept function waits for a TLS/SSL client to initiate the TLS/SSL handshake. The communication channel
* must already have been set and assigned to the ssl by setting an underlying BIO.
*           
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SEC_INT The TLS/SSL handshake was successfully completed, a TLS/SSL connection has been established
* [TLS_SUCCESS|N/A]
* @retval SEC_INT The TLS/SSL handshake was not successful but was shut down controlled and by the specifications of
* the TLS/SSL protocol. Call SSL_getError function with the return value ret to find the reason [SEC_NULL|N/A]
* @retval SEC_INT The TLS/SSL handshake was not successful because a fatal error occurred either at the protocol level
* or a connection failure occurred. The shutdown was not clean. It can also occur if action is needed to continue
* the operation for non-blocking BIOs. Call the SSL_getError() function with the return value ret to find the
* reason [Lesser than Zero|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. The behavior of SSL_accept() depends on the underlying socket.\n\n
* 2. If the underlying socket is blocking, SSL_accept() will only return once the handshake has been finished or an error
*    occurred.\n\n
* 3. If the underlying socket is non-blocking, SSL_accept() will also return when the underlying socket could not satisfy
*    the needs of SSL_accept() to continue the handshake, indicating the problem by the return value -1. In this case a
*    call to SSL_getError() with the return value of SSL_accept() will yield SSL_ERROR_WANT_READ or SSL_ERROR_WANT_WRITE.
*    The calling process then must repeat the call after taking appropriate action to satisfy the needs of SSL_accept().
*    The action depends on the underlying socket. When using a non-blocking socket, nothing is to be done, but select()
*    can be used to check for the required condition.
* 4. For DTLS connections the Non-Blocking sockets Behave like Blocking Sockets during the handshake(because of Timers
* and retransmission). If the behaviours needs to be changed it must be changed in the OSAL.
* 
* @par Related Topics
* SSL_write,\n
* SSL_peek,\n
* SSL_read,\n
* SSL_connect,\n
* SSL_doHandshake.
*/

 SSLLINKDLL SEC_INT SSL_accept(SSL_S *pstSSL);

/*
    Func Name:  SSL_connect
*/
/**
* @defgroup SSL_connect
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_connect(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to initiate connection from a TLS/SSL client in the TLS/SSL handshake.
*
* @par Description
* SSL_connect function initiates connection from a TLS/SSL client in the TLS/SSL handshake. The communication
* channel must already have been set and assigned to the ssl by setting an underlying socket.
*           
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SEC_INT The TLS/SSL handshake was successfully completed, a TLS/SSL connection has been established
* [TLS_SUCCESS|N/A]
* @retval SEC_INT The TLS/SSL handshake was not successful but was shut down controlled and by the specifications of
* the TLS/SSL protocol. Call SSL_getError() with the return value ret to find the reason [SEC_NULL|N/A]
* @retval SEC_INT The TLS/SSL handshake was not successful because a fatal error occurred either at the protocol level
* or a connection failure occurred. The shutdown was not clean. It can also occur if action is needed to continue
* the operation for non-blocking sockets. Call the SSL_getError() function with the return value ret to find the
* reason [Lesser than Zero|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. The behavior of SSL_connect() depends on the underlying socket.\n\n
* 2. If the underlying socket is blocking, SSL_connect() will only return once the handshake has been finished or an
*    error occurred.\n\n
* 3. If the underlying socket is non-blocking, SSL_connect() will also return when the underlying socket could not satisfy
*    the needs of SSL_connect() to continue the handshake, indicating the problem by the return value -1. In this case a
*    call to SSL_getError() with the return value of SSL_connect() will yield SSL_ERROR_WANT_READ or SSL_ERROR_WANT_WRITE.
*    The calling process then must repeat the call after taking appropriate action to satisfy the needs of SSL_connect().
*    The action depends on the underlying socket. When using a non-blocking socket, nothing is to be done, but select()
*    can be used to check for the required condition.
* 4. For DTLS connections the Non-Blocking sockets Behave like Blocking Sockets during the handshake(because of Timers
* and retransmission). If the behaviours needs to be changed it must be changed in the OSAL.
* 
* @par Related Topics
* SSL_write,\n
* SSL_peek,\n
* SSL_read,\n
* SSL_accept,\n
* SSL_doHandshake.
*/

 SSLLINKDLL SEC_INT SSL_connect(SSL_S *pstSSL);


/*
    Func Name:  SSL_read
*/
/**
* @defgroup SSL_read
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_read(SSL_S *pstSSL,
* SEC_VOID *pBuf,
* SEC_INT iNum);
* @endcode
*
* @par Purpose
* This is used to read data from the SSL connection.
*
* @par Description
* SSL_read function tries to read iNum bytes from the specified ssl into the buffer pBuf. The SSL_read() is based
* on the SSL/TLS records. The data are received in records.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
* @param[in] iNum The number of bytes to be read [N/A]
* @param[out] pBuf Which holds the SSL data [N/A]
*
* @retval SEC_INT The read operation was successful. The return value is the number of bytes actually read from the
* TLS/SSL connection [Greater than Zero|N/A]
* @retval SEC_INT The read operation was not successful. The reason may either be a clean shutdown due to a
* "close notify" alert sent by the peer (in which case the SSL_RECEIVED_SHUTDOWN flag in the ssl shutdown state is
* set (see SSL_shutdown(), SSL_setShutdown())). It is also possible, that the peer simply shut down the underlying
* transport and the shutdown is incomplete. Call SSL_getError() with the return value ret to find out whether an error
* occurred or the connection was shut down cleanly (SSL_ERROR_ZERO_RETURN).\n
* SSLv2 (deprecated) does not support a shutdown alert protocol, so it can only be detected whether the underlying
* connection was closed. It cannot be checked whether the closure was initiated by the peer or by something else
* [Zero|N/A]
* @retval SEC_INT The read operation was not successful, because either an error occurred or an action must be taken
* by the calling process. Call SSL_getError() with the return value ret to find out the reason [Less than Zero|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If necessary, SSL_read() will negotiate a TLS/SSL session, if not already explicitly performed by SSL_connect() or
*    SSL_accept(). If the peer requests a re-negotiation, it will be performed transparently during the SSL_read()
*    operation. The behavior of SSL_read() depends on the underlying sockstream.\n\n
* 2. For the transparent negotiation to succeed, the ssl must have been initialized to client or server mode. This is
*    being done by calling SSL_setConnectState() or SSL_setAcceptState() before the first call to an SSL_read() or
*    SSL_write() function.\n\n
* 3. SSL_read() works based on the SSL/TLS records. The data are received in records (with a maximum record size of 16kB
*    for SSLv3/TLSv1). Only when a record has been completely received, it can be processed (decryption and check of
*    integrity). Therefore data that was not retrieved at the last call of SSL_read() can still be buffered inside the
*    SSL layer and will be retrieved on the next call to SSL_read(). If iNum is higher than the number of bytes buffered,
*    SSL_read() will return with the bytes buffered. If no more bytes are in the buffer, SSL_read() will trigger the
*    processing of the next record. Only when the record has been received and processed completely, SSL_read() will
*    return reporting success. At most the contents of the record will be returned. As the size of an SSL/TLS record may
*    exceed the maximum packet size of the underlying transport (e.g. TCP), it may be necessary to read several packets
*    from the transport layer before the record is complete and SSL_read() can succeed.\n\n
* 4. If the underlying socket is blocking, SSL_read() will only return, once the read operation has been finished or an
*    error occurred, except when a renegotiation takes place, in which case a SSL_ERROR_WANT_READ may occur. This
*    behavior can be controlled with the SSL_MODE_AUTO_RETRY flag of the SSL_CTX_SET_MODE() macro call.\n\n
* 5. If the underlying socket is non-blocking, SSL_read() will also return when the underlying socket could not satisfy
*    the needs of SSL_read() to continue the operation. In this case a call to SSL_getError() with the return value of
*    SSL_read() will yield SSL_ERROR_WANT_READ or SSL_ERROR_WANT_WRITE. As at any time a re-negotiation is possible, a
*    call to SSL_read() can also cause write operations. The calling process then must repeat the call after taking
*    appropriate action to satisfy the needs of SSL_read(). The action depends on the underlying socket. When using a
*    non-blocking socket, nothing is to be done, but select() can be used to check for the required condition.
* 6. Renegotiation requested by peer can be rejected and send fatal handshake failure or no renegotiation warning alert
*    to peer side by enabling SSL_CTRL_BEHAV_NORENEG_FATAL or SSL_CTRL_BEHAV_NORENEG_WARN option. At this case
*    return value will be SEC_ERROR. If warning alert is send, then the connection can be continued if peer side 
*    allowed it.
* 
* @par Related Topics
* SSL_write,\n
* SSL_peek,\n
* SSL_connect,\n
* SSL_accept,\n
* SSL_getReadAhead,\n
* SSL_setReadAhead.
*/

 SSLLINKDLL SEC_INT SSL_read(SSL_S *pstSSL,SEC_VOID *pBuf,SEC_INT iNum);


/*
    Func Name:  SSL_peek
*/
/**
* @defgroup SSL_peek
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_peek(SSL_S *pstSSL,
* SEC_VOID *pBuf,
* SEC_INT iNum);
* @endcode
*
* @par Purpose
* This is used to copy the data in the SSL buffer into the buffer passed to this API.
*
* @par Description
* SSL_peek function copies the data in the SSL buffer into the buffer passed to this API. The SSL_peek() copies iNum bytes
* from the specified SSL into the buffer. In contrast to the SSL_read function, the data in the SSL buffer is
* unmodified after the SSL_peek function operation. 
*
* @param[in] pstSSL Pointer to SSL object [N/A]
* @param[in] iNum The number of bytes to be copied [N/A]
* @param[out] pBuf Which holds the SSL data [N/A]
*
* @retval SEC_INT The peek operation was successful. The return value is the number of bytes actually copied from the
* TLS/SSL connection [Greater than Zero|N/A]
* @retval SEC_INT The peek operation was not successful. The SSL connection was closed by the peer by sending a "close
* notify'' alert. The SSL_RECEIVED_SHUTDOWN flag in the SSL shutdown state is set. (See SSL_shutdown(), SSL_setShutdown()).
* Call SSL_getError() with the return value ret to determine whether an error occurred or the connection was shut down
* cleanly (SSL_ERROR_ZERO_RETURN).\n
* SSLv2 (deprecated) does not support a shutdown alert protocol, so it can only be detected, whether the underlying
* connection was closed. It cannot be checked, whether the closure was initiated by the peer or by something else
* [Zero|N/A]
* @retval SEC_INT The peek operation was not successful, because either an error occurred or action must be taken by the
* calling process. Call SSL_getError() with the return value ret to find out the reason [Lesser than Zero|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_write,\n
* SSL_read,\n
* SSL_connect,\n
* SSL_accept.
*/

 SSLLINKDLL SEC_INT SSL_peek(SSL_S *pstSSL,SEC_VOID *pBuf,SEC_INT iNum);


/*
    Func Name:  SSL_write
*/
/**
* @defgroup SSL_write
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_write(SSL_S *pstSSL,
* const SEC_VOID *pBuf,
* SEC_INT iNum);
* @endcode
*
* @par Purpose
* This is used to write the  data into the SSL connection.
*
* @par Description
* SSL_write function tries to write iNum bytes to the specified ssl from the buffer pBuf. The SSL_write() is based
* on the SSL/TLS records. The data are sent in records.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
* @param[in] iNum The number of bytes to be written [N/A]
* @param[out] pBuf Which holds the data [N/A]
*
* @retval SEC_INT If write operation is successful, the return value is the number of bytes actually written to the
* TLS/SSL connection [Greater than Zero|N/A]
* @retval SEC_INT If write operation is not successful. Probably the underlying connection is closed. Call SSL_getError()
* with the return value ret to find out, whether an error occurred or the connection was shut down cleanly
* (SSL_ERROR_ZERO_RETURN).\n
* SSLv2 (deprecated) does not support a shutdown alert protocol, so it can only be detected whether the underlying
* connection was closed. It cannot be checked, why the closure happened [Zero|N/A]
* @retval SEC_INT If write operation is not successful. It is because, either an error occurred or action must be taken
* by the calling process. Call SSL_getError() with the return value ret to find out the reason [Lesser than Zero|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If necessary, SSL_write function will negotiate a TLS/SSL session, if not already explicitly performed by 
*    SSL_connect or SSL_accept function. If the peer requests a re-negotiation, it will be performed transparently during
*    the SSL_write operation. The behavior of  SSL_write depends on the underlying socket stream.\n\n
* 2. For the transparent negotiation to succeed, the SSL must have been initialized to client or server mode. This is
*    being done by calling SSL_setConnectState or SSL_setAcceptState before the first call to an SSL_read or
*    SSL_write function.\n\n
* 3. If the underlying socket is blocking, SSL_write will only return once the write operation has been finished or an
*    error occurred, except when a renegotiation takes place, in which case a SSL_ERROR_WANT_READ may occur. This behavior
*    can be controlled with the SSL_MODE_AUTO_RETRY flag of the SSL_CTX_SET_MODE macro call.\n\n
* 4. If the underlying socket is non-blocking, SSL_write will also return when the underlying socket could not satisfy
*    the needs of SSL_write to continue the operation. In this case a call to SSL_getError with the return value of
*    SSL_write will yield SSL_ERROR_WANT_READ or SSL_ERROR_WANT_WRITE. As at any time a re-negotiation is possible, a
*    call to SSL_write can also cause read operations. The calling process then must repeat the call after taking
*    appropriate action to satisfy the needs of SSL_write. The action depends on the underlying socket. When using a
*    non-blocking socket, nothing is to be done, but select can be used to check for the required condition.\n\n
* 5. SSL_write will only return with success, when the complete contents of  buf of length iNum has been written. This
*    default behavior can be changed with the SSL_MODE_ENABLE_PARTIAL_WRITE option of SSL_CTX_SET_MODE. When this flag
*    is set, SSL_write will also return with success, when a partial write has been successfully completed. In this case
*    the SSL_write() operation is considered as completed. The bytes are sent and a new SSL_write() operation with a new
*    buffer (with the already sent bytes removed) must be started. A partial write is performed with the size of a message
*    block, which is 16kB for SSLv3/TLSv1. 
* 6). For DTLS connection SSL_write Fails if application data is more than 
*   (mtu - IPSI_DTLS1_MAX_RECORD_OVERHEAD(65)). In this case
*   SSL_getLastError will return error SSL_R_APP_DATA_GT_MTU.
* 
* @par Related Topics
* SSL_peek,\n
* SSL_read,\n
* SSL_connect,\n
* SSL_accept.
*/

 SSLLINKDLL SEC_INT SSL_write(SSL_S *pstSSL,const SEC_VOID *pBuf,SEC_INT iNum);


/*
    Func Name:  SSL_ctrl
*/
/**
* @defgroup SSL_ctrl
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctrl(SSL_S *pstSSL,SEC_INT iCmd,
* SEC_INT32 lArg,
* SEC_VOID *pArg);
* @endcode
*
* @par Purpose
* This is used to manipulate the settings of the SSL_CTX_S and SSL_S objects.
*
* @par Description
* SSL_*_ctrl family of functions is used to manipulate the settings of the SSL_CTX_S and SSL_S objects.
* Depending on the command iCmd the arguments lArg, pArg are evaluated. These functions should never be called directly.
* All functionalities needed are made available via other functions or macros. This function is NOT to be used directly.
*
* @param[in] pstSSL pointer to SSL object [N/A]
* @param[in] iCmd The action to perform [N/A]
* @param[in] lArg optional argument [N/A]
* @param[in] pArg optional argument[N/A]
*
* @retval SEC_INT32 Return value depends on the iCmd ex: if iCmd is SSL_CTRL_GET_READ_AHEAD it returns number of bytes
* [Depends on iCmd|N/A]
* @retval SEC_INT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxCallbackCtrl,\n
* SSL_ctxCtrl,\n
* SSL_callbackCtrl.
*/

 SSLLINKDLL SEC_INT32 SSL_ctrl(SSL_S *pstSSL,SEC_INT iCmd, SEC_INT32 lArg, SEC_VOID *pArg);


/*
    Func Name:  SSL_callbackCtrl
*/
/**
* @defgroup SSL_callbackCtrl
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_callbackCtrl(SSL_S *pstSSL,
* SEC_INT iCmd,
* SEC_VOID (*pfCallback)(SEC_VOID));
* @endcode
* 
* @par Purpose
* This is used to manipulate the settings of the SSL objects with respect to callback functions.
*
* @par Description
* SSL_callbackCtrl function manipulates the settings of the SSL objects with respect to callback functions.
* Currently it is only used to set message callbacks.
*
* @param[in] pstSSL pointer to SSL object.[N/A]
* @param[in] iCmd The action to perform.[N/A]
* @param[in] pfCallback callback function pointer.[N/A]
*
* @retval SEC_INT32 On successful execution [TLS_SUCCESS|N/A]
* @retval SEC_INT32 If pstSSL is NULL [SEC_ERROR|N/A]
* @retval SEC_INT32 On failure conditions [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If NULL is passed as function pointer for SSL_CTRL_SET_MSG_CALLBACK, then this API fails with SEC_ERROR as 
* return value.\n
* 
* @par Related Topics
* SSL_ctxCallbackCtrl,\n
* SSL_ctxCtrl,\n
* SSL_ctrl.
*/

 SSLLINKDLL SEC_INT32 SSL_callbackCtrl(SSL_S *pstSSL, SEC_INT iCmd, SEC_VOID (*pfCallback)(SEC_VOID));


/*
    Func Name:  SSL_ctxCtrl
*/
/**
* @defgroup SSL_ctxCtrl
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxCtrl (SSL_CTX_S *pstContext,
* SEC_INT iCmd,
* SEC_INT32 lArg,
* SEC_VOID *pArg);
* @endcode
*
* @par Purpose
* This is used to manipulate the settings of the SSL context.
*
* @par Description
* SSL_ctxCtrl family of functions is used to manipulate settings of the SSL_CTX_S. Depending on the iCmd
* parameter, the arguments lArg, pArg are evaluated. These functions should never be called directly. All functionalities
* needed are made available via other functions or macros. DO NOT use this directly. 
*
* @param[in] pstContext Pointer to SSL context [N/A]
* @param[in] iCmd Command [N/A]
* @param[in] lArg Integer argument to the command [N/A]
* @param[in] pArg Pointer argument to the command [N/A]
*
* @retval SEC_INT32 Return value depends on the iCmd suppose if iCmd is of type SSL_CTRL_GET_READ_AHEAD it returns the
* number of bytes. [Depends on iCmd|N/A]
* @retval SEC_INT32 If pstContext is SEC_NULL [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxCallbackCtrl,\n
* SSL_callbackCtrl,\n
* SSL_ctrl.
*/

 SSLLINKDLL SEC_INT32 SSL_ctxCtrl (SSL_CTX_S *pstContext,
                         SEC_INT iCmd, 
                         SEC_INT32 lArg, 
                         SEC_VOID *pArg);

/*
    Func Name:  SSL_ctxCallbackCtrl
*/
/**
* @defgroup SSL_ctxCallbackCtrl
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxCallbackCtrl ( SSL_CTX_S *pstContext,
* SEC_INT iAction, 
* SEC_VOID (*cb)(SEC_VOID));
* @endcode
*
* @par Purpose
* This is used to manipulate the settings of the SSL_CTX_S objects with respect to callback functions.
*
* @par Description
* SSL_ctxCallbackCtrl function manipulates the settings of the SSL_CTX_S objects with respect to callback
* functions. Currently it is only used to set message callbacks.
*
* @param[in] pstContext pointer to SSL context object.[N/A]
* @param[in] iAction The action to perform.[N/A]
* @param[in] cb callback function pointer.[N/A]
*
* @retval SEC_INT32 On successful execution [TLS_SUCCESS|N/A]
* @retval SEC_INT32 On failure conditions [SEC_NULL|N/A]
* @retval SEC_INT32 If the input is invalid(NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If NULL is passed as function pointer for SSL_CTRL_SET_MSG_CALLBACK, then this API fails with SEC_ERROR as 
* return value.\n
* 
* @par Related Topics
* SSL_ctxCtrl,\n
* SSL_callbackCtrl,\n
* SSL_ctrl.
*/

 SSLLINKDLL SEC_INT32 SSL_ctxCallbackCtrl ( SSL_CTX_S *pstContext, SEC_INT iAction, 
                                  SEC_VOID (*cb)(SEC_VOID));


/*
    Func Name: SSL_getError
*/
/**
* @defgroup SSL_getError
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_getError (const SSL_S *pstSSL,
* SEC_INT iRetCode);
* @endcode
*
* @par Purpose
* This returns a result code (suitable for the C "switch" statement) for a preceding call to SSL_connect, SSL_accept,
* SSL_doHandshake, SSL_read, SSL_peek, or SSL_write on ssl.
*
* @par Description
* SSL_getError function returns a result code (suitable for the C "switch" statement) for a preceding call to
* SSL_connect, SSL_accept, SSL_doHandshake, SSL_read, SSL_peek, or SSL_write on ssl. The value returned by that
* TLS/SSL I/O function must be passed to SSL_getError in parameter ret.
*
* @param[in] pstSSL The SSL object [N/A]
* @param[in] iRetCode It is the return value of preceding call to SSL_connect, SSL_accept, SSL_doHandshake, SSL_read,
* SSL_peek, or SSL_write on pstSSL. [N/A]
*
* @retval SEC_INT The TLS/SSL I/O operation completed. This result code is returned if and only
* if iRetCode is greater than zero [SSL_ERROR_NONE|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
* @retval SEC_INT The TLS/SSL connection has been closed. If the protocol version is SSL 3.0 or TLS 1.0, this result
* code is returned only if a closure alert has occurred in the protocol, i.e. if the connection has been closed cleanly.
* Note that in this case SSL_ERROR_ZERO_RETURN does not necessarily indicate that the underlying transport has been
* closed.[SSL_ERROR_ZERO_RETURN|N/A]
* @retval SEC_INT The operation did not complete because an application callback set by SSL_CTX_SET_CLIENT_CERT_URL_CB()
* has asked to be called again. The TLS/SSL I/O function should be called again later.  Details depend on the
* application [SSL_ERROR_WANT_X509_LOOKUP|N/A]
* @retval SEC_INT If some I/O error occurred [SSL_ERROR_SYSCALL|N/A]
* @retval SEC_INT A failure in the SSL library occurred, usually a protocol error [SSL_ERROR_SSL|N/A]
* @retval SEC_INT If SSL failed on write or read [SSL_ERROR_WANT_READ/SSL_ERROR_WANT_WRITE|N/A]
* @retval SEC_INT If rejected renegotiation initiated by peer or accepted the renegotiation rejection by peer which was self initiated.[SSL_ERROR_RENEGOTIATION_REJECTED|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If SSL_getError function return SSL_ERROR_SSL, call SSL_getLastError, or SSL_peekLastError function to get the real
*    problem for SSL error. And call SSL_getVerifyResult function to get the certificate chain verify result.\n\n
* 2. In case of SSL I/O APIs (SSL_Connect/SSL_Accept/SSL_write/SSL_read/SSL_doHandshake), if error occurs then we should
*    call SSL_getError function first followed by SSL_getLastError. If SSL_getLastError function is called first without
*    calling SSL_getError, the information returned might be incorrect.\n\n
* 3. SSL_getError will give return value SSL_ERROR_RENEGOTIATION_REJECTED only once. If called again immediately,
*    it will not give same error as the error SSL_ERROR_RENEGOTIATION_REJECTED will be propagated only once.
*    This is only applicable for SSL_ERROR_RENEGOTIATION_REJECTED.
* @par Related Topics
* SSL_getLastError,\n
* SSL_peekLastError,\n
* SSL_getVerifyResult.
*/

 SSLLINKDLL SEC_INT SSL_getError ( const SSL_S *pstSSL, SEC_INT iRetCode);

/*
    Func Name: SSL_getVersion
*/
/**
* @defgroup SSL_getVersion
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_getVersion ( const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to get the SSL version.
*
* @par Description
* SSL_getVersion function gets the SSL version as string.
*
* @param[in] pstSSL The structure from which the version has to be retrieved [N/A]
*
* @retval SEC_CHAR* Returns the protocol version as string. [One of the following protocol versions is returned as string:\n
* TLSv1.1,\n
* TLSv1,\n
* SSLv2,\n
* SSLv3|N/A]
*
* @retval SEC_CHAR* If the input is invalid (NULL pointers is passed as input) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod,\n
* SSL_version.
*/

 SSLLINKDLL const SEC_CHAR *SSL_getVersion ( const SSL_S *pstSSL);

/* This sets the 'default' SSL_S version that SSL_new() will create */

/*
    Func Name:  SSL_ctxSetSSLVersion
*/
/**
* @defgroup SSL_ctxSetSSLVersion
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetSSLVersion ( SSL_CTX_S *pstContext,
* SSL_METHOD_S *pstMethod);
* @endcode
*
* @par Purpose
* This is used to set a new default SSL method for SSL objects newly created from this SSl context.
*
* @par Description
* SSL_ctxSetSSLVersion function sets a new default SSL method for SSL objects newly created from this SSL context. SSL
* objects already created with SSL_new are not affected, except when SSL_clear function is being called. 
*
* @param[in] pstContext Pointer to SSL Context [N/A]
* @param[in] pstMethod Pointer to the server or client methods [N/A]
*
* @retval SEC_INT If the new choice failed, check the error stack to find out the reason [SEC_NULL|N/A]
* @retval SEC_INT If the operation is succeeded [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointers are passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_getVersion,\n
* SSL_setSSLMethod,\n
* SSL_version,\n
* SSL_getVersion.
*/

 SSLLINKDLL SEC_INT SSL_ctxSetSSLVersion (SSL_CTX_S *pstContext, SSL_METHOD_S *pstMethod);


/*
    Func Name:  SSLv2_method
*/
/**
* @defgroup SSLv2_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S* SSLv2_method(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a constructor for SSLv2 SSL_METHOD_S structure for combined client and server.
*
* @par Description
* SSLv2_method function acts as a Constructor for the SSLv2 SSL_METHOD_S structure for combined client and server.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned
* which holds all methods supported by SSLv2 server and client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *SSLv2_method(SEC_VOID);       /* SSLv2 */


/*
    Func Name:  SSLv2_serverMethod
*/
/**
* @defgroup SSLv2_serverMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *SSLv2_serverMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the SSLv2 SSL_METHOD_S structure for a dedicated server which supports SSLv2.
*
* @par Description
* SSLv2_serverMethod function acts as a Constructor for the SSLv2 SSL_METHOD_S structure for a dedicated server which
* supports SSLv2.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned
* which holds all methods supported by SSLv2 server [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S* SSLv2_serverMethod(SEC_VOID); /* SSLv2 */


/*
    Func Name:  SSLv2_clientMethod
*/
/**
* @defgroup SSLv2_clientMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *SSLv2_clientMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the SSLv2 SSL_METHOD_S structure for a dedicated client which supports SSLv2.
*
* @par Description
* SSLv2_clientMethod function acts as a Constructor for the SSLv2 SSL_METHOD_S structure for a dedicated client which
* supports SSLv2.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned
* which holds all methods supported by SSLv2 client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *SSLv2_clientMethod(SEC_VOID); /* SSLv2 */


/*
    Func Name:  SSLv3_method
*/
/**
* @defgroup SSLv3_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *SSLv3_method(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the SSLv3 SSL_METHOD_S structure for combined client and server.
*
* @par Description
* SSLv3_method function acts as a Constructor for the SSLv3 SSL_METHOD_S structure for combined client and server.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned
* which holds all methods supported by SSLv3 server and client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *SSLv3_method(SEC_VOID);       /* SSLv3 */


/*
    Func Name:  SSLv3_serverMethod
*/
/**
* @defgroup SSLv3_serverMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *SSLv3_serverMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the SSLv3 SSL_METHOD_S structure for a dedicated server which supports SSLv3.
*
* @par Description
* SSLv3_serverMethod function acts as a Constructor for the SSLv3 SSL_METHOD_S structure for a dedicated server which
* supports SSLv3.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned which holds all
* methods supported by SSLv3 server [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *SSLv3_serverMethod(SEC_VOID); /* SSLv3 */


/*
    Func Name:  SSLv3_clientMethod
*/
/**
* @defgroup SSLv3_clientMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *SSLv3_clientMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the SSLv3 SSL_METHOD_S structure for a dedicated client which supports SSLv3.
*
* @par Description
* SSLv3_clientMethod function acts as a Constructor for the SSLv3 SSL_METHOD_S structure for a dedicated client which
* supports SSLv3.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S  structure is returned which holds all methods
* supported by SSLv3 client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *SSLv3_clientMethod(SEC_VOID); /* SSLv3 */

/*
    Func Name:  SSL_method
*/
/**
* @defgroup SSL_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *SSL_method(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the SSLv3, SSLv2, TLS1, TLS1.1 and TLS 1.2 SSL_METHOD_S structure for a combined client and server
* which supports all versions.
*
* @par Description
* SSL_method function acts as a Constructor for the SSLv3, SSLv2, TLS1 ,TLS1.1 and TLS 1.2 SSL_METHOD_S structure for a combined
* client and server server which supports all versions.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned which holds all methods
* supported by SSL server and client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *SSL_method(SEC_VOID);     

/*
    Func Name:  SSL_serverMethod
*/
/**
* @defgroup SSL_serverMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *SSL_serverMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a generic constructor for all the SSL versions.
*
* @par Description
* SSL_serverMethod function acts as a generic constructor for all the SSL versions.
*
* @par Parameters
* None
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned
* which holds all methods supported by SSL server [Pointer to SSL_METHOD_S|NA]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|NA]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* None
* 
* @par Related Topics
* SSL_getSSLMethod \n
* SSL_ctxNew \n
* SSL_ctxExNew
*/

 SSLLINKDLL SSL_METHOD_S *SSL_serverMethod(SEC_VOID);   

/*
    Func Name:  SSL_clientMethod
*/
/**
* @defgroup SSL_clientMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *SSL_clientMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a generic constructor for all the SSL versions.
*
* @par Description
* SSL_clientMethod function acts as a generic Constructor for the SSL, that is, it supports all versions of SSL (SSLv2,
* SSLv23, SSLv3, TLS1, TLS1.1, and TLS 1.2 ).
*
* @par Parameters
* None
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned
* which holds all methods supported by SSL client [Pointer to SSL_METHOD_S|NA]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|NA]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* None
* 
* @par Related Topics
* SSL_getSSLMethod \n
* SSL_ctxNew \n
* SSL_ctxExNew \n
* SSL_ctxSetSSLVersion \n
* SSL_setSSLMethod
*/

 SSLLINKDLL SSL_METHOD_S *SSL_clientMethod(SEC_VOID);   

/*
    Func Name:  TLSv1_method
*/
/**
* @defgroup TLSv1_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv1_method(SEC_VOID);
* @endcode
* 
* @par Purpose
* This acts as a constructor for the TLSv1 SSL_METHOD_S structure for combined client and server.
*
* @par Description
* TLSv1_method function acts as a constructor for the TLSv1 SSL_METHOD_S structure for combined client and server.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S  structure is returned
* which holds all methods supported by TLSv1 server and client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *TLSv1_method(SEC_VOID);       /* TLSv1.0 */


/*
    Func Name:  TLSv1_serverMethod
*/
/**
* @defgroup TLSv1_serverMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv1_serverMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the TLSv1 SSL_METHOD_S structure for a dedicated server which supports TLSv1.
*
* @par Description
* TLSv1_serverMethod function acts as a Constructor for the TLSv1  SSL_METHOD_S structure for a dedicated server which
* supports TLSv1.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S On successful execution a pointer to SSL_METHOD_S structure is returned
* which holds all methods supported by TLSv1 server [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *TLSv1_serverMethod(SEC_VOID); /* TLSv1.0 */


/*
    Func Name:  TLSv1_clientMethod
*/
/**
* @defgroup TLSv1_clientMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv1_clientMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the TLSv1  SSL_METHOD_S structure for a dedicated client which supports TLSv1.
*
* @par Description
* TLSv1_clientMethod function acts as a Constructor for the TLSv1  SSL_METHOD_S structure for a dedicated client which
* supports TLSv1.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned
* which holds all methods supported by TLSv1 client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *TLSv1_clientMethod(SEC_VOID); /* TLSv1.0 */


/*
    Func Name:  TLSv11_method
*/
/**
* @defgroup TLSv11_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv11_method(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the TLSv1.1 SSL_METHOD_S structure for combined client and server.
*
* @par Description
* TLSv11_method function acts as a Constructor for the TLSv1.1 SSL_METHOD_S structure for combined client and server.                                           
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S  structure is returned which holds all methods
* supported by TLSv1.1 server and client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *TLSv11_method(SEC_VOID);      /* TLSv1.1 */

/*
    Func Name:  TLSv12_method
*/
/**
* @defgroup TLSv12_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv12_method(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the TLSv1.2 SSL_METHOD_S structure for 
* combined client and server.
*
* @par Description
* TLSv12_method function acts as a Constructor for the TLSv1.2 SSL_METHOD_S 
* structure for combined client and server.
*
* @par Parameters
* None
*
* @retval SSL_METHOD_S* On successful execution, a pointer to SSL_METHOD_S  
* structure is returned which holds all methods supported by TLSv1.1 server 
* and client [Indicates pointer to SSL_METHOD_S|NA]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|NA]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* None
* 
* @par Related Topics
* SSL_getSSLMethod \n
* SSL_ctxNew \n
* SSL_ctxExNew \n
* SSL_ctxSetSSLVersion \n
* SSL_setSSLMethod
*/
#ifndef IPSI_NO_TLS12

 SSLLINKDLL SSL_METHOD_S *TLSv12_method(SEC_VOID);      /* TLSv1.2 */
#endif

/*
    Func Name:  TLSv11_serverMethod
*/
/**
* @defgroup TLSv11_serverMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv11_serverMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the TLSv1.1 SSL_METHOD_S structure for a dedicated server which supports TLSv1.1.
*
* @par Description
* TLSv11_serverMethod function acts as a Constructor for the TLSv1.1 SSL_METHOD_S structure for a dedicated server which
* supports TLSv1.1.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned which holds all methods
* supported by TLSv1.1 server [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *TLSv11_serverMethod(SEC_VOID);    /* TLSv1.1 */

/*
    Func Name:  TLSv12_serverMethod
*/
/**
* @defgroup TLSv12_serverMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv12_serverMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the TLSv1.2 SSL_METHOD_S structure for a 
* dedicated server which supports TLSv1.2.
*
* @par Description
* TLSv12_serverMethod function acts as a Constructor for the TLSv1.2 
* SSL_METHOD_S structure for a dedicated server which supports TLSv1.2.
*
* @par Parameters
* None
*
* @retval SSL_METHOD_S* On successful execution, a pointer to SSL_METHOD_S 
* structure is returned which holds all methods supported by TLSv1.2 server 
* [Specifies pointer to SSL_METHOD_S|NA]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|NA]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* None
* 
* @par Related Topics
* SSL_getSSLMethod \n
* SSL_ctxNew \n
* SSL_ctxExNew \n
* SSL_ctxSetSSLVersion \n
* SSL_setSSLMethod
*/
#ifndef IPSI_NO_TLS12
 SSLLINKDLL SSL_METHOD_S *TLSv12_serverMethod(SEC_VOID);    /* TLSv1.2 */
#endif


/*
    Func Name:  TLSv11_clientMethod
*/
/**
* @defgroup TLSv11_clientMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv11_clientMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the TLSv1.1  SSL_METHOD_S structure for a dedicated client which supports TLSv1.1.
*
* @par Description
* TLSv11_clientMethod function acts as a Constructor for the TLSv1.1  SSL_METHOD_S structure for a dedicated client
* which supports TLSv1.1.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S structure is returned which holds all methods
* supported by TLSv1.1 client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *TLSv11_clientMethod(SEC_VOID);    /* TLSv1.1 */

/*
    Func Name:  TLSv12_clientMethod
*/
/**
* @defgroup TLSv12_clientMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *TLSv12_clientMethod(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the TLSv1.2 SSL_METHOD_S structure for a 
* dedicated client which supports TLSv1.2.
*
* @par Description
* TLSv12_clientMethod function acts as a Constructor for the TLSv1.2 
* SSL_METHOD_S structure for a dedicated client which supports TLSv1.2.
*
* @par Parameters
* None
*
* @retval SSL_METHOD_S* On successful execution, a pointer to SSL_METHOD_S 
* structure is returned which holds all methods supported by TLSv1.2 client 
* [Pointer to SSL_METHOD_S|NA]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|NA]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* None
* 
* @par Related Topics
* SSL_getSSLMethod \n
* SSL_ctxNew \n
* SSL_ctxExNew \n
* SSL_ctxSetSSLVersion \n
* SSL_setSSLMethod
*/
#ifndef IPSI_NO_TLS12

SSLLINKDLL SSL_METHOD_S *TLSv12_clientMethod(SEC_VOID);    /* TLSv1.2 */

#endif


#ifndef IPSI_SSL_NO_DTLS

/*
    Func Name:  IPSI_DTLSv1_method*/
/**
* @defgroup IPSI_DTLSv1_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *IPSI_DTLSv1_method(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the DTLSv1 SSL_METHOD_S structure for 
* combined client and server.
*
* @par Description
* IPSI_DTLSv1_method function acts as a Constructor for the DTLSv1 SSL_METHOD_S 
* structure for combined client and server.                                           
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S  
* structure is returned which holds all methods
* supported by DTLSv1 server and client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod \n
* SSL_ctxNew \n
* SSL_ctxExNew \n
* SSL_ctxSetSSLVersion \n
* SSL_setSSLMethod
*/

 SSLLINKDLL SSL_METHOD_S *IPSI_DTLSv1_method(SEC_VOID);      /* DTLSv1 */


/*
    Func Name:  IPSI_DTLSv1_server_method
*/
/**
* @defgroup IPSI_DTLSv1_server_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *IPSI_DTLSv1_server_method(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the DTLSv1 SSL_METHOD_S structure for a 
dedicated server which supports DTLSv1.
*
* @par Description
* IPSI_DTLSv1_server_method function acts as a Constructor for the DTLSv1 
SSL_METHOD_S structure for a dedicated server which
* supports DTLSv1.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S 
structure is returned which holds all methods
* supported by DTLSv1 server [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *IPSI_DTLSv1_server_method(SEC_VOID);


/*
    Func Name:  IPSI_DTLSv1_client_method
*/
/**
* @defgroup IPSI_DTLSv1_client_method
* @ingroup sslFunctions
* @par Prototype
* @code
* SSL_METHOD_S *IPSI_DTLSv1_client_method(SEC_VOID);
* @endcode
*
* @par Purpose
* This acts as a Constructor for the DTLSv1  SSL_METHOD_S structure for a 
dedicated client which supports DTLSv1.
*
* @par Description
* IPSI_DTLSv1_client_method function acts as a Constructor for the DTLSv1  
SSL_METHOD_S structure for a dedicated client
* which supports DTLSv1.
*
* @par Parameters
* N/A
*
* @retval SSL_METHOD_S* On successful execution a pointer to SSL_METHOD_S 
structure is returned which holds all methods
* supported by DTLSv1 client [Pointer to SSL_METHOD_S|N/A]
* @retval SSL_METHOD_S* On failure conditions [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_ctxNew,\n
* SSL_ctxExNew,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod.
*/

 SSLLINKDLL SSL_METHOD_S *IPSI_DTLSv1_client_method(SEC_VOID); 

#endif

/*
    Func Name:  SSL_getCiphers
*/
/**
* @defgroup SSL_getCiphers
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_List_S *SSL_getCiphers(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to get the list of cipher suites available with the SSL object.
*
* @par Description
* SSL_getCiphers function returns the list of cipher suites available with the SSL object.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SEC_List_S* On successful execution [List of cipher suites|N/A]
* @retval SEC_List_S* On failure conditions [NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetCipherList,\n
* SSL_setCipherList,\n
* SSL_getCipherList,\n
* SSL_getCurrentCipher,\n
* SSL_getSharedCiphers.
*/


 SSLLINKDLL SEC_List_S *SSL_getCiphers(SSL_S *pstSSL);


/*
    Func Name:  SSL_doHandshake
*/
/**
* @defgroup SSL_doHandshake
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_doHandshake(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This will wait for a SSL/TLS handshake to take place.
*
* @par Description
* SSL_doHandshake function waits for a SSL/TLS handshake to take place. If the connection is in client mode, the handshake
* will be started. The handshake routines may have to be explicitly set in advance using either SSL_setConnectState
* or SSL_setAcceptState.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SEC_INT The TLS/SSL handshake was successfully completed, a TLS/SSL connection has been established
* [TLS_SUCCESS|N/A]
* @retval SEC_INT The TLS/SSL handshake was not successful but was shut down controlled and by the specifications of the
* TLS/SSL protocol. Call SSL_getError with the return value ret to find out the reason [SEC_NULL|N/A]
* @retval SEC_INT The TLS/SSL handshake was not successful because a fatal error occurred either at the protocol level or
* a connection failure occurred. The shutdown was not clean. It can also occur due to action needed to continue the
* operation for non-blocking sockets. Call SSL_getError with the return value ret to find out the reason [Lesser than
* Zero|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. The behavior of SSL_doHandshake depends on the underlying socket.\n\n
* 2. If the underlying socket is blocking, SSL_do_handshake will only return once the handshake has been finished or an
*    error occurred.\n\n
* 3. If the underlying socket is non-blocking, SSL_doHandshake will also return when the underlying socket could not
*    satisfy the needs of SSL_doHandshake to continue the handshake. In this case a call to SSL_getError with the
*    return value of SSL_doHandshake will yield SSL_ERROR_WANT_READ or SSL_ERROR_WANT_WRITE. The calling process then
*    must repeat the call after taking appropriate action to satisfy the needs of SSL_doHandshake. The action depends
*    on the underlying socket. When using a non-blocking socket, nothing is to be done, but select can be used to check
*    for the required condition.
* 4. If the requested renegotiation is rejected by peer with No renegotiation warning alert, then the existing 
*    connection can be continued by enabling SSL_CTRL_BEHAV_ACCEPT_RENEG_REJECTION option.
* 
* @par Related Topics
* SSL_renegotiate_pending,\n
* SSL_renegotiate,\n
* SSL_connect,\n
* SSL_accept,\n
* SSL_setConnectState,\n
* SSL_setAcceptState.
*/

 SSLLINKDLL SEC_INT SSL_doHandshake(SSL_S *pstSSL);


/*
    Func Name:  SSL_renegotiate
*/
/**
* @defgroup SSL_renegotiate
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_renegotiate(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to turn on flags for renegotiation so that renegotiation will happen.
*
* @par Description
* SSL_renegotiate function turn on flags for renegotiation so that renegotiation will happen. The renegotiation
* may happen at the next I/O operation provided that client/server are ready for renegotiation.                     
*
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SEC_INT On successful execution [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure conditions(if the input parameter is NULL) [SEC_ERROR|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. Before calling this API user should check whether any readable data are buffered in SSL object. If so user should
*     read that data before calling this API. User can call the SSL_pending API to get the remaining readable
*     data available in SSL object.\n
* 2. SSLv2 does not support renegotiation.\n
* 
* @par Related Topics
* SSL_renegotiate_pending,\n
* SSL_doHandshake.\n
* SSL_pending
*/

 SSLLINKDLL SEC_INT SSL_renegotiate(SSL_S *pstSSL);

/*
    Func Name:  SSL_renegotiate_pending
*/
/**
* @defgroup SSL_renegotiate_pending
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_renegotiate_pending(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to indicate the status of the renegotiation request.
*
* @par Description
* SSL_renegotiate_pending function returns true when negotiation is requested and false when handshake is finished.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SEC_INT negotiation is requested [TLS_SUCCESS|N/A]
* @retval SEC_INT Handshake has finished [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_renegotiate,\n
* SSL_doHandshake.
*/

 SSLLINKDLL SEC_INT SSL_renegotiate_pending(SSL_S *pstSSL);


/*
    Func Name:  SSL_shutdown
*/
/**
* @defgroup SSL_shutdown
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_shutdown(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to shutdown an SSL connection.
*
* @par Description
* The shutdown procedure consists of 2 steps:\n 
* 1. The sending of the "close notify" shutdown alert. \n
* 2. The reception of the peer's "close notify" shutdown alert.\n
* According to the TLS standard, it is acceptable for an application to only send its shutdown alert and then close
* the underlying connection without waiting for the peer's response (this way resources can be saved, as the process
* can already terminate or serve another connection). When the underlying connection shall be used for more communications,
* the complete shutdown procedure (bidirectional "close notify" alerts) must be performed, so that the peers stay synchronized.
*
* @param[in] pstSSl Pointer to SSL object [N/A]
*
* @retval SEC_INT when both the sending and receiving of "close notify" are successful, or 
* we set quiet shutdown mode. [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure conditions [SEC_ERROR|N/A]
* @retval SEC_INT when just sent the "close notify" but "close notify" not received, or when we called this API, but in
* fact "close notify", has not been sentout out due to TCP congestion. [SEC_NULL|N/A]       
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. Call SSL_shutdown the first time, it will only send the "close notify". Then call it again, it will try to receive
*    the peer's "close notify". So, usually, call SSL_shutdown first time will return 0. Then call it again, if
*    "close notify" is received, it will return 1. If "close notify" still is not received, it still return 0.\n\n
* 2. Sometimes, before you call SSL_shutdown, you have called SSL_read and received "close notify". 
*    Then even call SSL_shutdown first time, and it will return 1.\n\n
* 3. If the SSL version is SSLv2, the first call to SSL_Shutdown itself will return 1 as SSLv2 does not support
*    "close_notify" alert.\n\n
* 4. If the SSL is set to quiet shutdown mode by calling the SSL_setQuietShutdown or SSL_ctxSetQuietShutdown, then the
*    first call to SSL_shutdown itself will return 1.
*
* @par Related Topics
* SSL_getShutdown,\n
* SSL_setShutdown,\n
* SSL_getQuietShutdown,\n
* SSL_setQuietShutdown,\n
* SSL_ctxSetQuietShutdown,\n
* SSL_ctxGetQuietShutdown,\n
* SSL_clear.
*/

 SSLLINKDLL SEC_INT SSL_shutdown(SSL_S *pstSSL);


/*
    Func Name:  IPSI_SSL_shutdown_ex
*/
/**
* @defgroup IPSI_SSL_shutdown_ex
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_shutdown_ex(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to shutdown an SSL connection.
*
* @par Description
* The SSL shutdown procedure consists of 2 steps:\n 
* 1. The sending of the "close notify" shutdown alert. \n
* 2. The reception of the peer's "close notify" shutdown alert.\n
* According to the TLS standard, it is acceptable for an application to only send its shutdown alert and then close
* the underlying connection without waiting for the peer's response (this way resources can be saved, as the process
* can already terminate or serve another connection). When the underlying connection shall be used for more communications,
* the complete shutdown procedure (bidirectional "close notify" alerts) must be performed, so that the peers stay synchronized.
*
* @param[in] pstSSl Pointer to SSL object [N/A]
*
* @retval SEC_INT when both the sending and receiving of "close notify" are successful, or 
* we set quiet shutdown mode. [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure conditions. This value can be returned if non-blocking error happens.[SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. Sometimes, before you call IPSI_SSL_shutdown_ex, you have called SSL_read and received "close notify". 
*    Then even call IPSI_SSL_shutdown_ex first time, and it will return 1.\n\n
* 2. If the SSL version is SSLv2, the first call to IPSI_SSL_shutdown_ex itself will return 1 as SSLv2 does not support
*    "close_notify" alert.\n\n
* 3. If the SSL is set to quiet shutdown mode by calling the SSL_setQuietShutdown or SSL_ctxSetQuietShutdown, then the
*    first call to IPSI_SSL_shutdown_ex itself will return 1.
* 4. When sending/receiving a "close notify" message, a non-block error can happen if the socket 
* registered with SSL object, is used in non-blocking mode. The user can call SSL_getError() API to 
* to check the type of non-blocking error(SSL_ERROR_WANT_WRITE or SSL_ERROR_WANT_READ).
*. If it is a non-blocking error, then the user has to call the IPSI_SSL_shutdown_ex again to 
*. complete SSL shutdown process.
*
* @par Related Topics
* SSL_shutdown,\n
* SSL_getShutdown,\n
* SSL_setShutdown,\n
* SSL_getQuietShutdown,\n
* SSL_setQuietShutdown,\n
* SSL_ctxSetQuietShutdown,\n
* SSL_ctxGetQuietShutdown,\n
* SSL_clear.
*/

 SSLLINKDLL SEC_INT IPSI_SSL_shutdown_ex(SSL_S *pstSSL);

/*
    Func Name:  SSL_getSSLMethod
*/
/**
* @defgroup SSL_getSSLMethod
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_METHOD_S* SSL_getSSLMethod(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to return the method stored in SSL
*
* @par Description
* SSL_getSSLMethod function returns the method stored in SSL. This SSL Method holds functions for SSLv2/SSLv3/TLSv1
* /TLSv1.1 functions.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SSL_METHOD_S* On success [Valid pointer to SSL_METHOD_S structure|N/A]
* @retval SSL_METHOD_S* If the method is not set using SSL_setSSLMethod [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setSSLMethod,\n
* SSL_getVersion,\n
* SSL_ctxSetSSLVersion,\n
* SSL_version,\n
* SSL_getVersion.
*/

 SSLLINKDLL SSL_METHOD_S* SSL_getSSLMethod(SSL_S *pstSSL);


/*
    Func Name:  SSL_setSSLMethod
*/
/**
* @defgroup SSL_setSSLMethod
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setSSLMethod(SSL_S *pstSSL,
* SSL_METHOD_S *pstMethod);
* @endcode
*
* @par Purpose
* This is used to set the SSL method to SSL object.
*
* @par Description
* SSL_setSSLMethod function sets the SSL method to SSL object. 
*
* @param[in] pstSSL Pointer to SSL_S onto which the method is set [N/A]
* @param[in] pstMethod Pointer to SSL_METHOD_S [N/A]
* 
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSSLMethod,\n
* SSL_version,\n
* SSL_getVersion.
*/

 SSLLINKDLL SEC_INT SSL_setSSLMethod(SSL_S *pstSSL, SSL_METHOD_S *pstMethod);


/*
    Func Name:    SSL_alertTypeStringLong
*/
/**
* @defgroup SSL_alertTypeStringLong
* @ingroup sslFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_alertTypeStringLong(SEC_INT iValue);
* @endcode
*
* @par Purpose
* This returns string indicating the type of alert.
*
* @par Description
* SSL_alertTypeStringLong function returns a string indicating the type of the alert specified by value.
*           
* @param[in] iValue Alert value [N/A]
*
* @retval SEC_CHAR* If the input is SSL3_AL_WARNING, then to indicate the severity of the alert message W(Warning) will be 
* returned. [warning|N/A]
* @retval SEC_CHAR* If the input is SSL3_AL_FATAL, then to indicate the severity of the alert message F(Fatal) will be 
* returned. [fatal|N/A]
* @retval SEC_CHAR* If the input is none of the above then to indicate the severity of the alert message U(Unknown) will
* be returned. [unknown|N/A]                                                   
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_alertDescString,\n
* SSL_alertDescStringLong,\n
* SSL_alertTypeString.
*/

 SSLLINKDLL const SEC_CHAR *SSL_alertTypeStringLong(SEC_INT iValue);


/*
    Func Name:   SSL_alertTypeString
*/
/**
* @defgroup SSL_alertTypeString
* @ingroup sslFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_alertTypeString(SEC_INT iValue);
* @endcode
*
* @par Purpose
* This returns a one letter string indicating the type of the alert.
*
* @par Description
* SSL_alertTypeString function returns a one letter string indicating the type of the alert specified by value.
*           
* @param[in] iValue Alert value [N/A]
*
* @retval SEC_CHAR* If the input is SSL3_AL_WARNING, then to indicate the severity of the alert message W(Warning) will be 
* returned. [W|N/A]
* @retval SEC_CHAR* If the input is SSL3_AL_FATAL, then to indicate the severity of the alert message F(Fatal) will be 
* returned. [F|N/A]
* @retval SEC_CHAR* If the input is none of the above then to indicate the severity of the alert message U(Unknown) will
* be returned. [U|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_alertDescString,\n
* SSL_alertDescStringLong,\n
* SSL_alertTypeStringLong.
*/

 SSLLINKDLL const SEC_CHAR *SSL_alertTypeString(SEC_INT iValue);


/*
    Func Name:  SSL_alertDescStringLong
*/
/**
* @defgroup SSL_alertDescStringLong
* @ingroup sslFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_alertDescStringLong(SEC_INT iValue);
* @endcode
*
* @par Purpose
* This returns message strings about SSL alerts.
*
* @par Description
* SSL_alertDescStringLong function returns message strings about SSL alerts.
*           
* @param[in] iValue Alert value [N/A]
*
* @retval SEC_CHAR* Success case [Returns the string which describes the alert message, for example, if value is
* SSL3_AD_CLOSE_NOTIFY this function returns "close notify" as output.|N/A]
* @retval SEC_CHAR* Failure case [Returns "unknown"|N/A]
*           
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* For complete list of alert messages refer Alert Codes.
* 
* @par Related Topics
* SSL_alertDescString,\n
* SSL_alertTypeString,\n
* SSL_alertTypeStringLong.
*/

 SSLLINKDLL const SEC_CHAR *SSL_alertDescStringLong(SEC_INT iValue);


/*
    Func Name:   SSL_alertDescString
*/
/**
* @defgroup SSL_alertDescString
* @ingroup sslFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_alertDescString (SEC_INT iValue);
* @endcode
*
* @par Purpose
* This returns two-letter strings indicating SSL alerts.
*
* @par Description
* SSL_alertDescString function returns two-letter strings indicating SSL alerts.
*           
* @param[in] iValue Error value [N/A]
*
* @retval SEC_CHAR* Success case [Returns the string which describes the alert message, for example, if value is
* SSL3_AD_CLOSE_NOTIFY, this function returns "CN" as output.|N/A]
* @retval SEC_CHAR* Failure case [Returns "UK" (unknown)|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* For complete list of alert messages refer Alert Codes.
* 
* @par Related Topics
* SSL_alertDescStringLong,\n
* SSL_alertTypeString,\n
* SSL_alertTypeStringLong.
*/

 SSLLINKDLL const SEC_CHAR *SSL_alertDescString (SEC_INT iValue);


/*
    Func Name: SSL_setClientCAList
*/
/**
* @defgroup SSL_setClientCAList
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setClientCAList (SSL_S *pstSSL,
* SEC_List_S *pCANameList);
* @endcode
*
* @par Purpose
* This is used to set the list of CAs sent to the client when requesting a client certificate.
*
* @par Description
* SSL_setClientCAList function sets the list of CAs sent to the client when requesting a client certificate for SSL_S
* object.
*
* @param[in] pstSSL Pointer to SSL_S [N/A]
* @param[in] pCANameList Names of supported CAs [N/A]
*                                                                               
* @retval SEC_INT On success [TLS_SUCCESS|N/A] 
* @retval SEC_INT If the input parameter is invalid(NULL pointer is being passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxAddClientCA,\n
* SSL_addClientCA,\n
* SSL_ctxGetClientCAList,\n
* SSL_getClientCAList,\n
* SSL_ctxSetClientCAList,\n
* SSL_loadClientCAFile.
*/

 SSLLINKDLL SEC_INT SSL_setClientCAList (SSL_S *pstSSL, 
                             SEC_List_S *pCANameList);/* list to hold X509_name */


/*
    Func Name:  SSL_ctxSetClientCAList
*/
/**
* @defgroup SSL_ctxSetClientCAList
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetClientCAList (SSL_CTX_S *pstCtx,
* SEC_List_S *pstNameList);
* @endcode
*
* @par Purpose
* This identifies the list of certificate authorities (CAs) that will be sent to the remote client application when
* requesting the client certificate.
*
* @par Description
* SSL_ctxSetClientCAList function identifies the list of certificate authorities (CAs) that will be sent to
* the remote client application when requesting the client certificate for any SSL session associated with a specific
* context structure. The client application should provide a certificate that was signed by one of the CAs in the list.
*
* @param[in] pstCtx Pointer to SSL Context [N/A]
* @param[in] pstNameList A pointer to a list of CA names. The datatype of CA names should be only SEC_NAME_S [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input parameter is invalid(NULL pointer is being passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxAddClientCA,\n
* SSL_addClientCA,\n
* SSL_ctxGetClientCAList,\n
* SSL_getClientCAList,\n
* SSL_setClientCAList,\n
* SSL_loadClientCAFile.
*/

 SSLLINKDLL SEC_INT SSL_ctxSetClientCAList (SSL_CTX_S *pstCtx, 
                                 SEC_List_S *pstNameList);


/*
    Func Name:  SSL_getClientCAList
*/
/**
* @defgroup SSL_getClientCAList
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_List_S *SSL_getClientCAList (const SSL_S *pstSSL );
* @endcode
*
* @par Purpose
* This returns the list of client CAs.
*
* @par Description
* SSL_getClientCAList function returns the list of client CAs explicitly set for ssl using SSL_setClientCAList or
* ssl's SSL_CTX_S object with SSL_ctxSetClientCAList, when in server mode. In client mode, SSL_getClientCAList
* returns the list of client CAs sent from the server, if any.
*
* @param[in] pstSSL Pointer to SSL context [N/A]
*
* @retval SEC_List_S* On success [List of CAs|N/A]
* @retval SEC_List_S* On failure [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxAddClientCA,\n
* SSL_addClientCA,\n
* SSL_ctxGetClientCAList,\n
* SSL_ctxSetClientCAList,\n
* SSL_setClientCAList.
*/

 SSLLINKDLL SEC_List_S *SSL_getClientCAList(const SSL_S *pstSSL );


/*
    Func Name:  SSL_ctxGetClientCAList
*/
/**
* @defgroup SSL_ctxGetClientCAList
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_List_S *SSL_ctxGetClientCAList (const SSL_CTX_S *pstCtx);
* @endcode
*
* @par Purpose
* This returns the list of client CAs explicitly set for SSL context using the SSL_ctxSetClientCAList function.
*
* @par Description
* SSL_ctxGetClientCAList function returns the list of client CAs explicitly set for SSL context using the
* SSL_ctxSetClientCAList function.
*
* @param[in] pstCtx Pointer to SSL context [N/A]
*
* @retval SEC_List_S* On success [List of CA|N/A]
* @retval SEC_List_S* On failure [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxAddClientCA,\n
* SSL_addClientCA,\n
* SSL_getClientCAList,\n
* SSL_ctxSetClientCAList,\n
* SSL_setClientCAList.
*/

 SSLLINKDLL SEC_List_S *SSL_ctxGetClientCAList (const SSL_CTX_S *pstCtx);


/*
    Func Name:  SSL_addClientCA
*/
/**
* @defgroup SSL_addClientCA
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_addClientCA (SSL_S *pstSSL,
* X509_CERT_EXTENDED_S *pstExtndCert);
* @endcode
*
* @par Purpose
* This is used to add the subject name of the input certificate to the client CA list of the SSL object.
*
* @par Description
* SSL_addClientCA function adds the subject name of the input certificate to the client CA list of the SSL object.
*           
* @param[in] pstSSL Pointer to SSL object [N/A]
* @param[in] pstExtndCert Pointer to Extended certificate [N/A]
*
* @retval SEC_INT On successful operation [TLS_SUCCESS|N/A]
* @retval SEC_INT A failure while manipulating the list of x509 name object occurred
* or the x509 name object could not be extracted from CA certificate. Check the error stack to find the reason
* [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxAddClientCA,\n
* SSL_ctxGetClientCAList,\n
* SSL_getClientCAList,\n
* SSL_ctxSetClientCAList,\n
* SSL_setClientCAList.
*/

 SSLLINKDLL SEC_INT SSL_addClientCA (SSL_S *pstSSL,
                         X509_CERT_EXTENDED_S *pstExtndCert);


/*
    Func Name:  SSL_ctxAddClientCA
*/
/**
* @defgroup SSL_ctxAddClientCA
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxAddClientCA (SSL_CTX_S *pstContext, 
* X509_CERT_EXTENDED_S *pstExtndCert);
* @endcode
*
* @par Purpose
* This is used to add the subject name of the input certificate to the client CA list of the SSL context.
*
* @par Description
* SSL_ctxAddClientCA function adds the subject name of the input certificate to the client CA list of the SSL context. 
*
* @param[in] pstContext Pointer to SSL_CTX_S object [N/A]
* @param[in] pstExtndCert Pointer to X509_CERT_EXTENDED_S certificate [N/A]
*
* @retval SEC_INT On successful execution [TLS_SUCCESS|N/A]
* @retval SEC_INT On failure conditions [SEC_NULL|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_addClientCA,\n
* SSL_ctxGetClientCAList,\n
* SSL_getClientCAList,\n
* SSL_ctxSetClientCAList,\n
* SSL_setClientCAList.
*/

 SSLLINKDLL SEC_INT SSL_ctxAddClientCA (SSL_CTX_S *pstContext, 
                            X509_CERT_EXTENDED_S *pstExtndCert);


/*
    Func Name:  SSL_setConnectState
*/
/**
* @defgroup SSL_setConnectState
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT  SSL_setConnectState (SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to set SSL to work in client mode.
*
* @par Description
* SSL_setConnectState function sets SSL to work in client mode. When using the SSL_connect or SSL_accept routines,
* the correct handshake routines are automatically set. When performing a transparent negotiation using SSL_write
* or SSL_read, the handshake routines must be explicitly set in advance using either SSL_setConnectState
* or SSL_setAcceptState. 
*
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setAcceptState,\n
* SSL_doHandshake.
*/

 SSLLINKDLL SEC_INT  SSL_setConnectState (SSL_S *pstSSL);


/*
    Func Name: SSL_setAcceptState
*/
/**
* @defgroup SSL_setAcceptState
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setAcceptState (SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to set SSL to work in server mode.
*
* @par Description
* SSL_setAcceptState function sets SSL to work in server mode. When using the SSL_connect or SSL_accept routines,
* the correct handshake routines are automatically set. When performing a transparent negotiation using SSL_write or
* SSL_read, the handshake routines must be explicitly set in advance using either SSL_setConnectState or
* SSL_setAcceptState function.
*
* @param[in] pstSSL Pointer to SSL_S object [N/A]
*                                                                               
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setConnectState,\n
* SSL_doHandshake.
*/  

 SSLLINKDLL SEC_INT SSL_setAcceptState (SSL_S *pstSSL);

/*
    Func Name: SSL_getDefaultTimeout
*/
/**
* @defgroup SSL_getDefaultTimeout
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_getDefaultTimeout (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns the default timeout value assigned to SSL_SESSION_S objects.
*
* @par Description
* SSL_get_default_timeout function returns the default timeout value assigned to SSL_SESSION_S objects negotiated for
* the protocol valid for ssl. For SSLv2, it is 5 minutes. For others, it is 2 hours.
*
* @param[in] pstSSL SSL object [N/A]
*
* @retval SEC_INT32 On success [The timeout value|N/A]
* @retval SEC_INT32 On failure [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxGetTimeout,\n
* SSL_ctxSetTimeout,\n
* SSL_sessionGetTimeout,\n
* SSL_sessionSetTimeout.
*/  

 SSLLINKDLL SEC_INT32 SSL_getDefaultTimeout (const SSL_S *pstSSL);


/*
    Func Name: SSL_libraryInit
*/
/**
* @defgroup SSL_libraryInit
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_INT SSL_libraryInit(SEC_VOID);
* @endcode
*
* @par Purpose
* This is used to initialize the SSL library.
*
* @par Description
* SSL_libraryInit function registers the available ciphers and digests and registers the error strings required by
* SSL library.
*
* @par Parameters
* N/A
*
* @retval SEC_INT After initializing [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* This function should be called only in main thread at the beginning
* of the application.
* 
* @par Related Topics
* SSL_libraryFini.
*/  

 SSLLINKDLL SEC_INT SSL_libraryInit(SEC_VOID);


/*
    Func Name:  SSL_cipherDescription
*/
/**
* @defgroup SSL_cipherDescription
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_CHAR *SSL_cipherDescription(SSL_CIPHER_S *pstCipher, 
* SEC_CHAR *pcBuf,
* SEC_INT iSize);
* @endcode
*
* @par Purpose
* This returns a human readable description of cipher.
*
* @par Description
* SSL_cipherDescription function Writes a string to pcBuf (with a maximum size of iSize) containing a human readable
* description of cipher.
*
* @param[in] pstCipher Pointer to SSL_CIPHER_S object [N/A]
* @param[in] iSize Maximum size of a string to be written [N/A]
* @param[out] pcBuf Output parameter which holds the human readable form of cipher description [N/A]
*
* @retval SEC_CHAR* On successful execution [Buffer containing human readable form of cipher description|N/A]
* @retval SEC_CHAR* On failure conditions [String "unknown"|N/A]
* @retval SEC_CHAR* If input is null [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* N/A
*/

 SSLLINKDLL SEC_CHAR *SSL_cipherDescription(SSL_CIPHER_S *pstCipher, 
                                SEC_CHAR *pcBuf,
                                SEC_INT iSize);


/*
    Func Name:  SSL_dup
*/
/**
* @defgroup SSL_dup
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_S* SSL_dup (SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This function returns an SSL object which is an exact copy of the supplied parameter. \n
* \n
*
* @par Description
* SSL_dup function returns an SSL object which is an exact copy of the supplied parameter.
* - SSL_dup function should not be called inside multithreading. \n
* - SSL_dup function should be used only before ssl connection. \n
* - SSL_dup function should not be used in case of SSL version 2. \n
* - Socket id and read, write, callbacks should not be copied 
* to the duplicated object. \n
* - Internal parameters like buffer, SSL state, cryptographic parameters,
* internal errors, verify result, client version, and DTLS informations 
* are not copied to the duplicated object. \n
* \n
*
* @param[in] pstSSL Pointer to SSL_S object [N/A]
*
* @retval SSL_S* On successful execution [New SSL object|N/A]
* @retval SSL_S* On failure conditions [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_new
*/

 SSLLINKDLL SSL_S *SSL_dup (SSL_S *pstSSL);


/*
    Func Name:  SSL_getCertificate
*/
/**
* @defgroup SSL_getCertificate
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* X509_CERT_EXTENDED_S *SSL_getCertificate (const SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This returns an X509 certificate loaded in the SSL_S structure.
*
* @par Description
* SSL_getCertificate function returns an X509 certificate loaded in the SSL structure. Before calling this
* function, an X509 certificate must be loaded into the SSL structure with another API.
*
* @param[in] pstSSL Pointer to SSL_S object [N/A]
*
* @retval X509_CERT_EXTENDED_S* On successful execution [Certificate|N/A]
* @retval X509_CERT_EXTENDED_S* On failure conditions [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getPrivatekey
*/

 SSLLINKDLL X509_CERT_EXTENDED_S *SSL_getCertificate (const SSL_S *pstSSL);


/*
    Func Name:  SSL_getPrivatekey
*/
/**
* @defgroup SSL_getPrivatekey
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_PKEY_S *SSL_getPrivatekey(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns a pointer to a private-key loaded in the SSL_S structure.
*
* @par Description
* SSL_getPrivatekey function returns a pointer to a private key loaded in the SSL structure. Before calling this
* function, a private key must be loaded into the SSL structure.
*
* @param[in] pstSSL Pointer to SSL_S object [N/A]
*
* @retval SEC_PKEY_S* On successful execution [Private key|N/A]
* @retval SEC_PKEY_S* On failure conditions [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getCertificate.
*/

 SSLLINKDLL SEC_PKEY_S *SSL_getPrivatekey(SSL_S *pstSSL);


/*
    Func Name:  SSL_ctxSetQuietShutdown
*/

/**
* @defgroup SSL_ctxSetQuietShutdown
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetQuietShutdown (SSL_CTX_S *pstContext,
* SEC_INT iMode);
* @endcode
*
* @par Purpose
* This is used to set the "quiet shutdown" flag for SSL context to be the specified mode.
*
* @par Description
* SSL_ctxSetQuietShutdown function sets the "quiet shutdown" flag for SSL context to be mode. SSL objects created from
* context inherit the mode valid at the time SSL_new is called. mode may be 0 or 1.
*
* @param[in] pstContext Pointer to SSL Context [N/A]
* @param[in] iMode mode may be 0(not quiet shutdown) or 1(quiet shutdown) [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is being passed) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getShutdown,\n
* SSL_setShutdown,\n
* SSL_getQuietShutdown,\n
* SSL_setQuietShutdown,\n
* SSL_ctxGetQuietShutdown,\n
* SSL_shutdown.
*/

 SSLLINKDLL SEC_INT SSL_ctxSetQuietShutdown (SSL_CTX_S *pstContext,
                                 SEC_INT iMode);


/*
    Func Name: SSL_ctxGetQuietShutdown
*/
/**
* @defgroup SSL_ctxGetQuietShutdown
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxGetQuietShutdown (const SSL_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This is used to get the value of the quiet-shutdown flag.
*
* @par Description
* SSL_ctxGetQuietShutdown function gets the value of the quiet shutdown flag in the SSL_CTX_S structure. It is either
* 0 or 1. 
*             
* @param[in] pstContext SSL_CTX_S context structure [N/A]
*                                                                               
* @retval SEC_INT If quiet shutdown flag of the SSL_CTX_S structure is turned off [SEC_NULL|N/A]
* @retval SEC_INT If quiet shutdown flag of the SSL_CTX_S structure is turned on [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is being passed) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getShutdown,\n
* SSL_setShutdown,\n
* SSL_getQuietShutdown,\n
* SSL_setQuietShutdown,\n
* SSL_ctxSetQuietShutdown,\n
* SSL_shutdown.
*/

 SSLLINKDLL SEC_INT SSL_ctxGetQuietShutdown (const SSL_CTX_S *pstContext);


/*
    Func Name:   SSL_setQuietShutdown
*/
/**
* @defgroup SSL_setQuietShutdown
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setQuietShutdown (SSL_S *pstSSL,
* SEC_INT iMode);
* @endcode
*
* @par Purpose
* This is used to set a mode of quiet shutdown to the SSL_S structure.
*
* @par Description
* SSL_setQuietShutdown function sets a mode of quiet shutdown to the ssl structure. To turn on the quiet
* shutdown, mode == 1 needs to be passed. The mode == 0 turns off the quiet shutdown flag of the ssl structure. When
* SSL_new creates an ssl structure, the value of the quiet-shutdown flag inherits from the quiet-shutdown flag in
* the  SSL_CTX_S data structure. For more detail, please refer to Shutting Down SSL.
*           
* @param[in] pstSSL Pointer to SSL object [N/A]
* @param[in] iMode modes '0' / '1' as described in description [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is being passed) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getShutdown,\n
* SSL_setShutdown,\n
* SSL_getQuietShutdown,\n
* SSL_ctxGetQuietShutdown,\n
* SSL_ctxSetQuietShutdown,\n
* SSL_shutdown.
*/

 SSLLINKDLL SEC_INT SSL_setQuietShutdown (SSL_S *pstSSL, 
                              SEC_INT iMode);


/*
    Func Name: SSL_getQuietShutdown
*/
/**
* @defgroup SSL_getQuietShutdown
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_getQuietShutdown (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns the QuietShutDown value set in the SSL_S structure.
*
* @par Description
* SSL_getQuietShutdown function returns the QuietShutDown value set in the SSL_S structure. If this flag is set, the
* shutdown packets  should not be sent.
*
* @param[in] pstSSL The structure from which the value has to be extracted [N/A]
*
* @retval SEC_INT On success, and quiet shutdown mode [T|N/A]
* @retval SEC_INT On success, and not quiet shutdown mode [SEC_NULL|N/A]
* @retval SEC_INT If the SSL_setQuietShutdown is not called or the field is not in SSL [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getShutdown,\n
* SSL_setShutdown,\n
* SSL_setQuietShutdown,\n
* SSL_ctxGetQuietShutdown,\n
* SSL_ctxSetQuietShutdown,\n
* SSL_shutdown.
*/

 SSLLINKDLL SEC_INT SSL_getQuietShutdown (const SSL_S *pstSSL);


/*
    Func Name: SSL_setShutdown
*/
/**
* @defgroup SSL_setShutdown
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setShutdown (SSL_S *pstSSL,
* SEC_INT iMode);
* @endcode
*
* @par Purpose
* This is used to set the shutdown state of ssl to the specified mode.
*
* @par Description
* SSL_setShutdown function sets the shutdown state of ssl to the mode. The shutdown state of an ssl connection is a
* bitmask of: 0, SSL_SENT_SHUTDOWN or SSL_RECEIVED_SHUTDOWN.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
* @param[in] iMode Shutdown mode which needs to be set [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getShutdown,\n
* SSL_getQuietShutdown,\n
* SSL_setQuietShutdown,\n
* SSL_ctxGetQuietShutdown,\n
* SSL_ctxSetQuietShutdown,\n
* SSL_shutdown,\n
* SSL_clear.
*/

 SSLLINKDLL SEC_INT SSL_setShutdown (SSL_S *pstSSL, 
                         SEC_INT iMode);


/*
    Func Name: SSL_getShutdown
*/
/**
* @defgroup SSL_getShutdown
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_getShutdown ( const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns the shutdown state of the SSL.
*
* @par Description
* SSL_getShutdown function returns the state of the SSL. The state can be a bitmask of: 0, SSL_SENT_SHUTDOWN or
* SSL_RECEIVED_SHUTDOWN.
*
* @param[in] pstSSL The structure to which the shutdown state is obtained [N/A]
*
* @retval SEC_INT On successful conditions [a bitmask of: 0, SSL_SENT_SHUTDOWN or SSL_RECEIVED_SHUTDOWN|N/A]
* @retval SEC_INT If input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]       
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setShutdown,\n
* SSL_getQuietShutdown,\n
* SSL_setQuietShutdown,\n
* SSL_ctxGetQuietShutdown,\n
* SSL_ctxSetQuietShutdown,\n
* SSL_shutdown.
*/

 SSLLINKDLL SEC_INT SSL_getShutdown ( const SSL_S *pstSSL);


/*
    Func Name: SSL_version
*/
/**
* @defgroup SSL_version
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_version (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to get the SSL version.
*
* @par Description
* SSL_version function gets the SSL version.
*
* @param[in] pstSSL The structure from which the version has to be retrieved [N/A]
*
* @retval SEC_INT On success [Returns one of the following  protocol version:\n
* SSL2_VERSION\n,
* SSL3_VERSION\n,
* TLS1_VERSION\n,
* TLS11_VERSION.|N/A]
* @retval SEC_INT If the input is invalid (NULL pointers are passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getVersion,\n
* SSL_ctxSetSSLVersion,\n
* SSL_setSSLMethod,\n
* SSL_getSSLMethod.
*/

 SSLLINKDLL SEC_INT SSL_version ( const SSL_S *pstSSL);


/*
    Func Name: SSL_getSession
*/
/**
* @defgroup SSL_getSession
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_SESSION_S* SSL_getSession (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns a pointer to the SSL_SESSION_S actually used in SSL_S.
*
* @par Description
* SSL_getSession function returns a pointer to the SSL_SESSION_S actually used in ssl and contains all information
* required to reestablish the connection without a new handshake. 
*
* @param[in] pstSSL Pointer to SSL_S object from which session is to be extracted [N/A]
*
* @retval SSL_SESSION* On success [Pointer to session|N/A]
* @retval SSL_SESSION* If the input is invalid (NULL pointers are passed as input) [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getSessionEx,\n
* SSL_setSession,\n
* SSL_copySessionId.
*/

 SSLLINKDLL SSL_SESSION_S* SSL_getSession ( const SSL_S *pstSSL);

/*
    Func Name: SSL_getSessionEx
*/
/**
* @defgroup SSL_getSessionEx
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_SESSION_S* SSL_getSessionEx (SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns a pointer to the SSL_SESSION_S actually used in SSL_S.
* 
* @par Description
* SSL_getSessionEx function is same as the SSL_getSession function, but the reference count of the SSL_SESSION_S is
* incremented by one.
*
* @param[in] pstSSL Pointer to SSL_S from which session is to be extracted [N/A]
*
* @retval SSL_SESSION_S* On success [Valid pointer to SSL_SESSION_S structure|N/A]
* @retval SSL_SESSION_S* If the input is invalid [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* SSL_sessionFree function should be called to free the session obtained using this function.
* 
* @par Related Topics
* SSL_getSession,\n
* SSL_sessionFree,\n
* SSL_setSession,\n
* SSL_copySessionId.
*/

 SSLLINKDLL SSL_SESSION_S* SSL_getSessionEx ( SSL_S *pstSSL); /* obtain a reference count */


/*
    Func Name:   SSL_getSSLCtx
*/
/**
* @defgroup SSL_getSSLCtx
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SSL_CTX_S* SSL_getSSLCtx (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns the ssl context of the SSL object.
*
* @par Description
* SSL_getSSLCtx function returns the SSL context of the SSL object.
*
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval SSL_CTX_S* If present [SSL_CTX_S* object|N/A]
* @retval SSL_CTX_S* If not present [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* N/A
*/                                                                 

 SSLLINKDLL SSL_CTX_S* SSL_getSSLCtx ( const SSL_S *pstSSL);


/*
    Func Name:   SSL_setInfo_cb
*/
/**
* @defgroup SSL_setInfo_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setInfo_cb(SSL_S *pstSSL,
* SEC_VOID (*cb) ( const SSL_S *pstSSL,SEC_INT iType,SEC_INT val));
* @endcode
*
* @par Purpose
* This is used to set the callback function, that can be used to obtain state information for ssl during connection
* setup and use.
*
* @par Description
* SSL_setInfo_cb function sets the callback function, that can be used to obtain state information for ssl during
* connection setup and use. When callback is NULL, the callback setting currently valid for SSL context is used. 
*       
* @param[in] pstSSL Pointer to SSL structure into which the callback function which needs to be set [N/A]
* @param[in] cb Callback function which needs to be set [N/A]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSLgetInfo_cb.
*/

 SSLLINKDLL SEC_INT SSL_setInfo_cb(SSL_S *pstSSL,
               SEC_VOID (*cb) ( const SSL_S *pstSSL,SEC_INT iType,SEC_INT val));


/*
    Func Name:   SSLgetInfo_cb
*/
/**
* @defgroup SSLgetInfo_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID (*SSLgetInfo_cb (const SSL_S *pstSSL)) (const SSL_S *pstSSL,SEC_INT iType,SEC_INT val);
* @endcode
*
* @par Purpose
* This returns a pointer to the currently set information callback function.
*
* @par Description
* SSLgetInfo_cb function returns a pointer to the currently set information callback function for SSL.
*       
* @param[in] pstSSL SSL structure from which the callback function need to be retrieved [N/A]
*
* @retval cb Callback function ((SEC_VOID)(*)( const SSL_S *pstSSL,SEC_INT iType,SEC_INT val))\n
* or\n
* SEC_NULL in the following conditions:\n
* 1. If the input is invalid (NULL pointer is passed as input)\n
* 2. If pointer to the callback function is not set. [Pointer to the callback function or SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setInfo_cb.
*/

SSLLINKDLL SEC_VOID (*SSLgetInfo_cb ( const SSL_S *pstSSL)) ( const SSL_S *pstSSL,SEC_INT iType,SEC_INT val);

/*
    Func Name:   SSL_state
*/
/**
* @defgroup SSL_state
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_state (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns the current state of the connection.
*
* @par Description
* SSL_state function returns the current state of the connection.
*           
* @param[in] pstSSL Pointer to SSL object [N/A]
*                                                   
* @retval SEC_INT On success [The current state|N/A]
* @retval SEC_INT On failure [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* N/A
*/

 SSLLINKDLL SEC_INT SSL_state ( const SSL_S *pstSSL);


/*
    Func Name:   SSL_setVerifyResult
*/
/**
* @defgroup SSL_setVerifyResult
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setVerifyResult(SSL_S *pstSSL,
* SEC_INT32 lVerifyResult);
* @endcode
*
* @par Purpose
* This is used to set the verify result of the SSL object.
*
* @par Description
* SSL_setVerifyResult function sets the verify result of the SSL object to be the result of the verification
* of the X509 certificate presented by the peer, if any.
*
* @param[in] pstSSL Pointer to SSL structure [N/A]
* @param[in] lVerifyResult Verification result [N/A]
*                                                           
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_verifyResultDescString,\n
* SSL_getVerifyResult.
*/              

 SSLLINKDLL SEC_INT SSL_setVerifyResult(SSL_S *pstSSL, SEC_INT32 lVerifyResult);


/*
    Func Name:   SSL_getVerifyResult
*/
/**
* @defgroup SSL_getVerifyResult
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_getVerifyResult (const SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to get verify result from the SSL object.
*
* @par Description
* SSL_getVerifyResult function gets iVerifyResult from the SSL object. The value will be one of a X509_V_ERR_ * macros,
* which are called verify result codes. A list of all the verify result codes is provided in the section, Error Codes.
*
* @param[in] pstSSL Pointer to SSL structure [N/A]
*
* @retval SEC_INT32 On success [Verify result|N/A]
* @retval SEC_INT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_verifyResultDescString,\n
* SSL_setVerifyResult.
*/

 SSLLINKDLL SEC_INT32 SSL_getVerifyResult ( const SSL_S *pstSSL);

/*
    Func Name: SSL_verifyResultDescString
*/
/**
* @defgroup SSL_verifyResultDescString
* @ingroup sslFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_verifyResultDescString(SEC_INT32 iValue);
* @endcode
*
* @par Purpose
* This is used to get message strings about certificate verification result.
*
* @par Description
* SSL_verifyResultDescString function gets message strings about certificate verification result.
*
* @param[in] iValue Certificate verification result value [N/A]
*
* @retval SEC_CHAR* Returns the message strings about certificate verification result [certificate validation result|N/A]
* @retval SEC_CHAR* If input is invalid ["error number iValue"|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getVerifyResult,\n
* SSL_setVerifyResult.
*/

 SSLLINKDLL const SEC_CHAR *SSL_verifyResultDescString(SEC_INT32 iValue);

/*  Sets the size of the internal session cache of SSL context ctx to t */
#define SSL_CTX_SESS_SETCACHESIZE(ctx,t) \
    SSL_ctxCtrl(ctx,SSL_CTRL_SET_SESS_CACHE_SIZE,t,SEC_NULL)

/* Returns the currently valid session cache size */
#define SSL_CTX_SESS_GETCACHESIZE(ctx) \
    SSL_ctxCtrl(ctx,SSL_CTRL_GET_SESS_CACHE_SIZE,0,SEC_NULL)
 /** The user can use SSL_CTX_SETSESSIONCACHEMODE to close the session resume 
function in the server side. If the server call SSL_CTX_SETSESSIONCACHEMODE(ctx,SSL_SESS_CACHE_OFF),
then the client will get session_id which is equal to zero each time.*/ 
#define SSL_CTX_SETSESSIONCACHEMODE(ctx,m) \
    SSL_ctxCtrl(ctx,SSL_CTRL_SET_SESS_CACHE_MODE,m,SEC_NULL)

/* Returns the currently set cache mode. It can be :
        SSL_SESS_CACHE_OFF, 
        SSL_SESS_CACHE_CLIENT,
        SSL_SESS_CACHE_SERVER, 
        SSL_SESS_CACHE_BOTH, 
        SSL_SESS_CACHE_NO_AUTO_CLEAR, 
        SSL_SESS_CACHE_NO_INTERNAL_LOOKUP. 
        The default mode is SSL_SESS_CACHE_SERVER  */
#define SSL_CTX_GETSESSIONCACHEMODE(ctx) \
    SSL_ctxCtrl(ctx,SSL_CTRL_GET_SESS_CACHE_MODE,0,SEC_NULL)

/** SSL_CTX_GETREADAHEAD gets the  ReadAhead Flag value set in the context structure. 
    This flag is set for reading as many input bytes as possible for non-blocking reads */
#define SSL_CTX_GETREADAHEAD(ctx) \
    SSL_ctxCtrl(ctx,SSL_CTRL_GET_READ_AHEAD,0,SEC_NULL)

/** SSL_CTX_SETREADAHEAD sets the  ReadAhead Flag value in the  context structure. 
    This flag is set for reading as many input bytes as possible for non-blocking reads */
#define SSL_CTX_SETREADAHEAD(ctx,m) \
    SSL_ctxCtrl(ctx,SSL_CTRL_SET_READ_AHEAD,m,SEC_NULL)

#define SSL_CTX_GET_DEFAULT_READ_AHEAD(ctx)     SSL_CTX_GETREADAHEAD(ctx)
#define SSL_CTX_SET_DEFAULT_READ_AHEAD(ctx,m)   SSL_CTX_SETREADAHEAD(ctx,m)

/** Returns the maximum size allowed for the peer's certificate chain for all 
    SSL objects created from ctx */
#define SSL_CTX_GETMAXCERTLIST(ctx) \
    SSL_ctxCtrl(ctx,SSL_CTRL_GET_MAX_CERT_LIST,0,SEC_NULL)

/** Sets the maximum size allowed for the peer's certificate chain for all 
    SSL objects created from ctx to be m bytes */
/** Interface will fail and returns SEC_ERROR, if user tries to set zero or any negative values  */
#define SSL_CTX_SETMAXCERTLIST(ctx,m) \
    SSL_ctxCtrl(ctx,SSL_CTRL_SET_MAX_CERT_LIST,m,SEC_NULL)

/** Returns the maximum size allowed for the peer's certificate chain for  
    SSL */
#define SSL_GETMAXCERTLIST(ssl) \
    SSL_ctrl(ssl,SSL_CTRL_GET_MAX_CERT_LIST,0,SEC_NULL)

/** Sets the maximum size allowed for the peer's certificate chain for 
    SSL object to be m bytes */
/** Interface will fail and returns SEC_ERROR, if user tries to set zero or any negative values */
#define SSL_SETMAXCERTLIST(ssl,m) \
    SSL_ctrl(ssl,SSL_CTRL_SET_MAX_CERT_LIST,m,SEC_NULL)

 /* NB: the keylength is only applicable when is_export is true */
#ifndef SSL_NO_RSA
/*
    Func Name:   SSL_ctxSetTempRSA_cb
*/
/**
* @defgroup SSL_ctxSetTempRSA_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxSetTempRSA_cb (SSL_CTX_S *pstContext,
* SEC_PKEY_S *(*cb)(SSL_S *pstSSL,SEC_INT iIsExport,SEC_INT iKeyLength));
* @endcode
*
* @par Purpose
* This is used to set the callback function for SSL context to be used when a temporary/ephemeral RSA key is required.
*
* @par Description
* SSL_ctxSetTempRSA_cb function sets the callback function for SSL context to be used when a temporary/ephemeral RSA
* key is required, to cb. The callback is inherited by all SSL objects newly created from context with SSL_new.
* Already created SSL objects are not affected.
*
* @param[in] pstContext Pointer to SSL context (SSL_CTX_S structure) [N/A]
* @param[in]  cb Pointer to Call back function [N/A]
*
* @retval SEC_UNIT32 On success [TLS_SUCCESS|N/A]
* @retval SEC_UNIT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setTempRSA_cb,\n
* SSL_setTempDH_cb,\n
* SSL_ctxSetTempDH_cb.
*/

 SSLLINKDLL SEC_INT32 SSL_ctxSetTempRSA_cb (SSL_CTX_S *pstContext,
                               SEC_PKEY_S *(*cb)(SSL_S *pstSSL,SEC_INT iIsExport,SEC_INT iKeyLength));

/*
    Func Name:   SSL_setTempRSA_cb
*/
/**
* @defgroup SSL_setTempRSA_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_setTempRSA_cb (SSL_S *pstSSL,
* SEC_PKEY_S *(*cb)(SSL_S *pstSSL,SEC_INT iIsExport,SEC_INT iKeyLength));
* @endcode
*
* @par Purpose
* This is used to set the callback function for SSL_S object to be used when a temporary/ephemeral RSA key is required.
*
* @par Description
* SSL_setTempRSA_cb function sets the callback function for SSL object to be used when a temporary/ephemeral RSA key is
* required, to cb.
*   
* @param[in] pstSSL Pointer to SSL (SSL_S structure) [N/A]
* @param[in] cb Pointer to Call back function [N/A]
*
* @retval SEC_UNIT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_UNIT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetTempRSA_cb,\n
* SSL_setTempDH_cb,\n
* SSL_ctxSetTempDH_cb.
*/

 SSLLINKDLL SEC_INT32 SSL_setTempRSA_cb (SSL_S *pstSSL,
                            SEC_PKEY_S *(*cb)(SSL_S *pstSSL,SEC_INT iIsExport,SEC_INT iKeyLength));
#endif

#ifndef SSL_NO_DH

/*
    Func Name:   SSL_ctxSetTempDH_cb
*/
/**
* @defgroup SSL_ctxSetTempDH_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxSetTempDH_cb (SSL_CTX_S *pstContext,
* SEC_PKEY_S *(*dh)(SSL_S *pstSSL,SEC_INT iIsExport,SEC_INT iKeyLength));
* @endcode
*
* @par Purpose
* This is used to set the callback function for SSL context to be used when DH parameters are required.
*
* @par Description
* SSL_ctxSetTempDH_cb function sets the callback function for SSL context to be used when DH parameters are required, to
* dh. The callback is inherited by all ssl objects created from context.
*
* @param[in] pstContext Pointer to SSL_CTX_S [N/A]
* @param[in] dh Pointer to Call back function [N/A]
*
* @retval SEC_INT32 On success [TLS_SUCCESS|N/A]
* @retval SEC_INT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setTempDH_cb \n
* SSL_setTempRSA_cb \n
* SSL_ctxSetTempRSA_cb
*/

 SSLLINKDLL SEC_INT32 SSL_ctxSetTempDH_cb (SSL_CTX_S *pstContext,
                              SEC_PKEY_S *(*dh)(SSL_S *pstSSL,SEC_INT iIsExport,SEC_INT iKeyLength));


/*
    Func Name:   SSL_setTempDH_cb
*/
/**
* @defgroup SSL_setTempDH_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_setTempDH_cb (SSL_S *pstSSL,
* SEC_PKEY_S *(*dh)(SSL_S *pstSSL,SEC_INT iIsExport,SEC_INT iKeyLength));
* @endcode
*
* @par Purpose
* This is used to set the callback function for SSL object to be used when DH parameters are required.
*
* @par Description
* SSL_setTempDH_cb function sets the callback function for SSL object to be used when DH parameters are required, to dh.
*
* @param[in] pstSSL Pointer to SSL_S [N/A]
* @param[in] dh Pointer to callback function [N/A]
*
* @retval SEC_INT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_ctxSetTempDH_cb \n
* SSL_setTempRSA_cb \n
* SSL_ctxSetTempRSA_cb
*/

 SSLLINKDLL SEC_INT32 SSL_setTempDH_cb (SSL_S *pstSSL,
                           SEC_PKEY_S *(*dh)(SSL_S *pstSSL,SEC_INT iIsExport,SEC_INT iKeyLength));

#ifndef IPSI_NO_TLS12


/*
    Func Name:   SSL_ctxSetVerDH_cb
*/
/**
* @defgroup SSL_ctxSetVerDH_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_ctxSetVerDH_cb (SSL_CTX_S *pstContext,
* SEC_INT (*ver_dh)(SSL_S *pstSSL,SEC_PKEY_S * pDHKey));
* @endcode
*
* @par Purpose
* This function is used to set the callback function for SSL context to be used when 
* DH parameters received from the server are required to be verified in the client side.
*
* @par Description
* SSL_ctxSetVerDH_cb function sets the callback function for SSL context to be used when 
* DH parameters are required to be verified. The callback is inherited by all ssl 
* objects created from context.
*
* @param[in] pstContext Specifies pointer to SSL_CTX_S [N/A]
* @param[in] ver_dh Specifies pointer to callback function. The callback function 
* will be called with SSL object and server DH public key. If the server public
* key is validated to be successful, returns SEC_SUCCESS. Else, 
* returns SEC_ERROR.[N/A]
*
* @retval SEC_INT32 On success [TLS_SUCCESS|N/A]
* @retval SEC_INT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* The callback set by this function will be called only on the client side.
* This callback will be called only for TLS1.2 version.
*
* @par Related Topics
* SSL_setVerDH_cb
*/

 SSLLINKDLL SEC_INT32 SSL_ctxSetVerDH_cb (SSL_CTX_S *pstContext,
                              SEC_INT (*ver_dh)(SSL_S *pstSSL,SEC_PKEY_S * pDHKey));


/*
    Func Name:   SSL_setVerDH_cb
*/
/**
* @defgroup SSL_setVerDH_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT32 SSL_setVerDH_cb (SSL_S *pstSSL,
* SEC_INT (*ver_dh)(SSL_S *pstSSL,SEC_PKEY_S * pDHKey));
* @endcode
*
* @par Purpose
* This function is used to set the callback function for SSL object to be used when DH 
* parameters received from the server are required to be verified in the client side.
*
* @par Description
* SSL_setVerDH_cb function sets the callback function for SSL object to be used 
* when DH parameters are required to be verified.
*
* @param[in] pstSSL Specifies pointer to SSL_S [N/A]
* @param[in] ver_dh Specifies pointer to callback function. The callback function 
* will be called with SSL object and server DH public key. If the server public
* key is validated to be successful, returns SEC_SUCCESS. Else, 
* returns SEC_ERROR.[N/A]
*
* @retval SEC_INT32 On success [SEC_SUCCESS|N/A]
* @retval SEC_INT32 If the input is invalid (NULL pointer is passed as input) [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* The callback set by this function will be called only on the client side.
* This callback will be called only for TLS1.2 version.
* 
* @par Related Topics
* SSL_ctxSetVerDH_cb
*/

 SSLLINKDLL SEC_INT32 SSL_setVerDH_cb (SSL_S *pstSSL,
                           SEC_INT (*ver_dh)(SSL_S *pstSSL,SEC_PKEY_S * pDHKey));


#endif
#endif


/*
    Func Name:   SSL_getCurrentCompression
*/
/**
* @defgroup SSL_getCurrentCompression
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const COMP_METHOD_S *SSL_getCurrentCompression(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns the compression method set in the ssl structure.
*
* @par Description
* SSL_getCurrentCompression function returns the compression method set in the ssl structure.
*           
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval COMP_METHOD_S* If compression method is not set [SEC_NULL|N/A]
* @retval COMP_METHOD_S* If compression method is set [Pointer to that compression method|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_compGetCompressionMethods \n
* SSL_compAddCompressionMethod \n
* SSL_compGetName \n
* SSL_getCurrentExpansion
*/

 SSLLINKDLL const COMP_METHOD_S *SSL_getCurrentCompression(SSL_S *pstSSL);

/*
    Func Name:   SSL_getCurrentExpansion
*/
/**
* @defgroup SSL_getCurrentExpansion
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* const COMP_METHOD_S *SSL_getCurrentExpansion(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This returns the decompression method set in the ssl structure.
*
* @par Description
* SSL_getCurrentExpansion function returns the decompression method set in the ssl structure.
*           
* @param[in] pstSSL Pointer to SSL object [N/A]
*
* @retval COMP_METHOD_S* If decompression method is not set [SEC_NULL|N/A]
* @retval COMP_METHOD_S* If decompression method is set[Pointer to that decompression method|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_compGetCompressionMethods \n
* SSL_compAddCompressionMethod \n
* SSL_compGetName \n
* SSL_getCurrentCompression
*/

 SSLLINKDLL const COMP_METHOD_S *SSL_getCurrentExpansion(SSL_S *pstSSL);

/*
    Func Name:   SSL_compGetName
*/
/**
* @defgroup SSL_compGetName
* @ingroup sslFunctions
* @par Prototype
* @code
* const SEC_CHAR *SSL_compGetName(const COMP_METHOD_S *pstCompMethod);
* @endcode
*
* @par Purpose
* This returns the name of the compression method set in the given compression method structure.
*
* @par Description
* SSL_compGetName function returns the name of the compression method set in the given compression method structure.
*           
* @param[in] pstCompMethod pointer to the compression method structure[N/A]
*
* @retval SEC_CHAR* If compression method name is not set [SEC_NULL|N/A]
* @retval SEC_CHAR* If compression method name is set [Pointer to the compression method name|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_compGetCompressionMethods,\n
* SSL_compAddCompressionMethod,\n
* SSL_getCurrentExpansion,\n
* SSL_getCurrentCompression.
*/

 SSLLINKDLL const SEC_CHAR* SSL_compGetName(const COMP_METHOD_S *pstCompMethod);

/*
    Func Name: SSL_compGetCompressionMethods
*/
/**
* @defgroup SSL_compGetCompressionMethods
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_List_S *SSL_compGetCompressionMethods(SEC_VOID);
* @endcode
*
* @par Purpose
* This returns the list of compression methods loaded.
*
* @par Description
* SSL_compGetCompressionMethods function returns the list of compression methods loaded.
*           
* @par Parameters
* N/A
*
* @retval SEC_List_S* If compression methods are not set [SEC_NULL|N/A]
* @retval SEC_List_S* Pointer to the list of compression methods [SEC_List_S*|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_compAddCompressionMethod,\n
* SSL_compGetName,\n
* SSL_getCurrentExpansion,\n
* SSL_getCurrentCompression.
*/

 SSLLINKDLL SEC_List_S* SSL_compGetCompressionMethods(SEC_VOID);

/*
    Func Name: SSL_compAddCompressionMethod
*/
/**
* @defgroup SSL_compAddCompressionMethod
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_INT SSL_compAddCompressionMethod (SEC_INT iID,
* COMP_METHOD_S *pstCompMethod);
* @endcode
*
* @par Purpose
* This is used to add the compression method with the specified identifier to the list of available compression methods.
*
* @par Description
* SSL_compAddCompressionMethod function adds the compression method 'pstCompMethod' with the identifier 'id' to the list
* of available compression methods. This list is globally maintained for all SSL operations within the application.
*           
* @param[in] iID  Identifier of the compression method [N/A]
* @param[in] pstCompMethod Pointer to the COMP_METHOD_S structure [N/A]
*
* @retval SEC_INT If the operation is failed [SEC_NULL|N/A]
* @retval SEC_INT If the operation is succeeded [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_compGetCompressionMethods,\n
* SSL_compGetName,\n
* SSL_getCurrentExpansion,\n
* SSL_getCurrentCompression.
*/

 SSLLINKDLL SEC_INT SSL_compAddCompressionMethod (SEC_INT iID,
                                      COMP_METHOD_S *pstCompMethod);


#ifndef IPSI_SSL_NO_SSL

/*
    Func Name: SEC_readSocket
*/
/**
* @defgroup SEC_readSocket
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SEC_readSocket (SSL_S *ssl,
* SEC_SOCK sd,
* SEC_INT8 *data,
* SEC_INT len);
* @endcode
*
* @par Purpose
* This reads from a socket into a buffer.
*
* @par Description
* SEC_readSocket reads from a socket into a buffer
*
* @param[in] ssl pointer to the ssl structure [N/A]
* @param[in] sd the socket descriptor [N/A]
* @param[in] len the number bytes to be read from the socket [N/A]
* @param[out] data the buffer into which data read from socket has been filled [N/A]
*
* @retval SEC_INT On success [Number of bytes read from the socket|N/A]
* @retval SEC_INT If the input buffer is NULL or an error occurred [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* This function reads the data from the socket directly. It is called by SSL_read internally. Usually the
* application should not call it.
* 
* @par Related Topics
* SEC_writeSocket,\n
* SEC_closeSocket,\n
* SSL_setSockRead_cb,\n
* SSL_setSockWrite_cb.
*/

 SSLLINKDLL SEC_INT SEC_readSocket (SSL_S *ssl, SEC_SOCK sd, SEC_INT8 *data, SEC_INT len);


/*
    Func Name:   SEC_writeSocket
*/
/**
* @defgroup SEC_writeSocket
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SEC_writeSocket (SSL_S *ssl,
* SEC_SOCK sd,
* const SEC_INT8 *data,
* SEC_INT len);
* @endcode
*
* @par Purpose
* This is used to write into a socket from a buffer.
*
* @par Description
* SEC_writeSocket function writes into a socket from a buffer.
*
* @param[in] ssl pointer to the ssl structure. [N/A]
* @param[in] sd the socket descriptor. [N/A]
* @param[in] data the buffer from which data will be written into a socket. [N/A]
* @param[in] len the number of bytes to be written into the socket. [N/A]
*
* @retval SEC_INT On success [Number of bytes written into the socket|N/A]
* @retval SEC_INT If the input buffer is NULL or an error occurred [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* This function writes the data into the socket directly. It is called by SSL_write internally. Usually the
* application should not call it.
* 
* @par Related Topics
* SEC_readSocket,\n
* SEC_closeSocket,\n
* SSL_setSockRead_cb,\n
* SSL_setSockWrite_cb.
*/

 SSLLINKDLL SEC_INT SEC_writeSocket (SSL_S *ssl, SEC_SOCK sd, const SEC_INT8 *data, SEC_INT len);


/*
    Func Name:   SEC_closeSocket
*/
/**
* @defgroup SEC_closeSocket
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_INT SEC_closeSocket (SEC_SOCK sd);
* @endcode
*
* @par Purpose
* This is used to close a socket.
*
* @par Description
* SEC_closeSocket function closes a socket.
*
* @param[in] sd The socket descriptor [N/A]
*
* @retval SEC_INT If close succeeds [SEC_SUCCESS|N/A]
* @retval SEC_INT If error occurred [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SEC_readSocket,\n
* SEC_writeSocket,\n
* SSL_setSockRead_cb,\n
* SSL_setSockWrite_cb.
*/

 SSLLINKDLL SEC_INT SEC_closeSocket (SEC_SOCK sd);

/* Add by Shiva */
/*
    Func Name:   SSL_setIpsiSockRead_cb
*/
/**
* @defgroup SSL_setIpsiSockRead_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setIpsiSockRead_cb (SSL_S *ssl,
* IPSISSLSOCKREAD_CB pfIpsiSslSockRead_cb);
* @endcode
*
* @par Purpose
* This is used to set the callback which will be used to read from a socket and the facility has been provided to set a userdata in the callback.
*
* @par Description
* SSL_setIpsiSockRead_cb function sets the callback which will be used to read from a socket and the facility has been provided to set a userdata in the callback.
*
* @param[in] ssl The ssl descriptor [N/A]
* @param[in] pfIpsiSslSockRead_cb A pointer to callback function [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If the read callback returns a value which is more than the length of the buffer passed by us, then our lib API 
* which invokes this callback like SSL_accept, SSL_connect, SSL_read etc will return SEC_ERROR. SSL_getError will 
* return SSL_ERROR_SSL and SSL_getLastError will return SSL_R_IPSI_UNEXPECTED_SOCKET_BEHAVIOUR. 
* Since, this case does not exactly match with any of the defined system call errors, it has been categorized under 
* SSL Error though it pertains to invalid behavior of callback or system calls.\n
* 
* @par Related Topics
* SSL_setIpsiSockWrite_cb,\n
* SEC_readSocket,\n
* SEC_writeSocket.
*/
SSLLINKDLL SEC_VOID SSL_setIpsiSockRead_cb(SSL_S *ssl, IPSISSLSOCKREAD_CB pfIpsiSslSockRead_cb);

/*
    Func Name:   SSL_setIpsiSockWrite_cb
*/
/**
* @defgroup SSL_setIpsiSockWrite_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setIpsiSockWrite_cb (SSL_S *ssl,
* IPSISSLSOCKWRITE_CB pfIpsiSslSockWrite_cb);
* @endcode
* @par Purpose
* This is used to set the callback which will be used to write into a socket and the facility has been provided to set a userdata in the callback.
*
* @par Description
* SEC_setSockWrite_cb function sets the callback which will be used to write into a socket and the facility has been provided to set a userdata in the callback.
*
* @param[in] ssl The SSL descriptor [N/A]
* @param[in] pfIpsiSslSockWrite_cb A pointer to callback function [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If the write callback returns a value which is more than the length of the buffer passed by us, then our lib API 
* which invokes this callback like SSL_accept, SSL_connect, SSL_write etc will return SEC_ERROR. SSL_getError will 
* return SSL_ERROR_SSL and SSL_getLastError will return SSL_R_IPSI_UNEXPECTED_SOCKET_BEHAVIOUR. 
* Since, this case does not exactly match with any of the defined system call errors, it has been categorized under 
* SSL Error though it pertains to invalid behavior of callback or system calls.\n
* 
* @par Related Topics
* SSL_setIpsiSockRead_cb,\n
* SEC_readSocket,\n
* SEC_writeSocket.
*/

SSLLINKDLL SEC_VOID SSL_setIpsiSockWrite_cb(SSL_S *ssl, IPSISSLSOCKWRITE_CB pfIpsiSslSockWrite_cb);

/*
    Func Name:   SSL_setIpsiSockReadCb_AppData
*/
/**
* @defgroup SSL_setIpsiSockReadCb_AppData
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setIpsiSockReadCb_AppData(SSL_S *ssl, SEC_VOID *IpsiReadAppdata);
* @endcode
*
* @par Purpose
* This is used to set Application data for Socket Read callback(SSL_setIpsiSockRead_cb).
*
* @par Description
* SSL_setIpsiSockReadCb_AppData function sets the Application data for Socket Read callback(SSL_setIpsiSockRead_cb).
*
* @param[in] ssl The SSL descriptor [N/A]
* @param[in] IpsiReadAppdata The application that needs to be set [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setIpsiSockRead_cb,\n
* SEC_readSocket,\n.
*/
SSLLINKDLL SEC_VOID SSL_setIpsiSockReadCb_AppData(SSL_S *ssl, SEC_VOID *IpsiReadAppdata);

/*
    Func Name:   SSL_setIpsiSockWriteCb_AppData
*/
/**
* @defgroup SSL_setIpsiSockWriteCb_AppData
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setIpsiSockWriteCb_AppData(SSL_S *ssl, SEC_VOID *IpsiWriteAppdata);
* @endcode
* @par Purpose
* This is used to set Application data for Socket Write callback(SSL_setIpsiSockWrite_cb).
*
* @par Description
* SSL_setIpsiSockWriteCb_AppData function sets the Application data for Socket Write callback(SSL_setIpsiSockWrite_cb).
*
* @param[in] ssl The SSL descriptor [N/A]
* @param[in] IpsiWriteAppdata The application that needs to be set [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_setIpsiSockWrite_cb,\n
* SEC_writeSocket.
*/

SSLLINKDLL SEC_VOID SSL_setIpsiSockWriteCb_AppData(SSL_S *ssl, SEC_VOID *IpsiWriteAppdata);

/* End by Shiva */
/*
    Func Name:   SSL_setSockRead_cb
*/
/**
* @defgroup SSL_setSockRead_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setSockRead_cb (SSL_S *ssl,
* SSLSOCKREAD_CB pfSslSockRead_cb);
* @endcode
*
* @par Purpose
* This is used to set the callback which will be used to read from a socket.
*
* @par Description
* SEC_setSockRead_cb function sets the callback which will be used to read from a socket.
*
* @param[in] ssl The ssl descriptor [N/A]
* @param[in] pfSslSockRead_cb A pointer to callback function [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If the read callback returns a value which is more than the length of the buffer passed by us, then our lib API 
* which invokes this callback like SSL_accept, SSL_connect, SSL_read etc will return SEC_ERROR. SSL_getError will 
* return SSL_ERROR_SSL and SSL_getLastError will return SSL_R_IPSI_UNEXPECTED_SOCKET_BEHAVIOUR. 
* Since, this case does not exactly match with any of the defined system call errors, it has been categorized under 
* SSL Error though it pertains to invalid behavior of callback or system calls.\n
* 
* @par Related Topics
* SSL_setSockWrite_cb,\n
* SEC_readSocket,\n
* SEC_writeSocket.
*/

// SEC_VOID SSL_setSockRead_cb (SSL_S *ssl, SEC_INT(*pfSslSockRead_cb)(SEC_SOCK, SEC_INT8 *, SEC_INT, SEC_INT));
 SSLLINKDLL SEC_VOID SSL_setSockRead_cb (SSL_S *ssl, SSLSOCKREAD_CB pfSslSockRead_cb);


/*
    Func Name:   SSL_setSockWrite_cb
*/
/**
* @defgroup SSL_setSockWrite_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_setSockWrite_cb (SSL_S *ssl,
* SSLSOCKWRITE_CB pfSslSockWrite_cb);
* @endcode
* @par Purpose
* This is used to set the callback which will be used to write into a socket.
*
* @par Description
* SEC_setSockWrite_cb function sets the callback which will be used to write into a socket.
*
* @param[in] ssl The SSL descriptor [N/A]
* @param[in] pfSslSockWrite_cb A pointer to callback function [N/A]
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If the write callback returns a value which is more than the length of the buffer passed by us, then our lib API 
* which invokes this callback like SSL_accept, SSL_connect, SSL_write etc will return SEC_ERROR. SSL_getError will 
* return SSL_ERROR_SSL and SSL_getLastError will return SSL_R_IPSI_UNEXPECTED_SOCKET_BEHAVIOUR. 
* Since, this case does not exactly match with any of the defined system call errors, it has been categorized under 
* SSL Error though it pertains to invalid behavior of callback or system calls.\n
* 
* @par Related Topics
* SSL_setSockRead_cb,\n
* SEC_readSocket,\n
* SEC_writeSocket.
*/

// SEC_VOID SSL_setSockWrite_cb (SSL_S *ssl, SEC_INT(*pfSslSockWrite_cb)(SEC_SOCK, const SEC_INT8 *, SEC_INT, SEC_INT));
 SSLLINKDLL SEC_VOID SSL_setSockWrite_cb (SSL_S *ssl, SSLSOCKWRITE_CB pfSslSockWrite_cb);


#endif // IPSI_SSL_NO_SSL


/*
    Func Name:   SSL_getLastError
*/
/** 
* @defgroup SSL_getLastError
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_INT SSL_getLastError ();
* @endcode
*
* @par Purpose
* This is used to get the details about the errors that occurred during an SSL session.
*
* @par Description
* SSL_getLastError function can be used to get details about the errors that occurred during an SSL session. The errors
* are maintained in an error queue. This function returns the earliest error in the error queue; that is among the list
* of errors that have occurred in the course of the session, it will return the first error that occurred and also
* removes it from the error queue. This function can be called repeatedly until there are no more error codes to return.
* The value will be one of a SSL_R_* or ERR_R_* macros, which are called reason codes. A list of all the error codes
* that will arise in SSL is provided in the section, Error Codes.
*           
* @par Parameters
* N/A
*
* @retval SEC_INT On success [One of the reason code|N/A]
* @retval SEC_INT On failure condition that is, if no error happened [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_peekLastError,\n
* ERR_get_error.
*/

 SSLLINKDLL SEC_INT SSL_getLastError (SEC_VOID);


/*
    Func Name:   SSL_peekLastError
*/

/**
* @defgroup SSL_peekLastError
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_INT SSL_peekLastError ();
* @endcode
*
* @par Purpose
* This is used to get the details about the errors that occurred during an SSL session without removing them from
* the queue.
*
* @par Description
* SSL_peekLastError function can be used to get details about the errors that occurred during an SSL session.
* The errors are maintained in an error queue. This function returns the earliest error in the error queue; that is
* among the list of errors that have occurred in the course of the session, it will return the first error that occurred.
* The value will be one of a SSL_R_* or ERR_R_* macros, which are called reason codes. A list of all the error codes
* that will arise in SSL is provided in the section, Error Codes. The error will not be removed from the error queue,
* hence it will remain accessible.
*           
* @par Parameters
* N/A                                                   
*
* @retval SEC_INT On success [One of the reason code|N/A]
* @retval SEC_INT On failure condition that is, if no error happened [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getLastError,\n
* ERR_peek_error.
*/

 SSLLINKDLL SEC_INT SSL_peekLastError (SEC_VOID);

/*
    Func Name:   SSL_threadCleanup
*/
/**
* @defgroup SSL_threadCleanup
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_VOID SSL_threadCleanup();
* @endcode
*
* @par Purpose
* This is used to clean up the thread related data.
*
* @par Description
* SSL_threadCleanup function cleans up the thread related data.
*
* @par Parameters
* N/A
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* For each thread except the main thread, we should call this function.
* 
* @par Related Topics
* SSL_libraryFini,\n
* SSL_freeMultiThread.
*/

 SSLLINKDLL SEC_VOID SSL_threadCleanup(SEC_VOID);


/*
    Func Name:   SSL_libraryFini
*/

/** 
* @defgroup SSL_libraryFini
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_VOID SSL_libraryFini();
* @endcode
*
* @par Purpose
* This is used to perform the final cleanup of the SSL library.
*
* @par Description
* SSL_libraryFini function does the final clean up of the SSL library.
*
* @par Parameters
* N/A
*
* @retval SEC_VOID This does not return any value [N/A|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* This function should be called only in main thread at the end
* of the application.
* 
* @par Related Topics
* SSL_libraryInit,\n
* SSL_threadCleanup,\n
* SSL_freeMultiThread.
*/

 SSLLINKDLL SEC_VOID SSL_libraryFini(SEC_VOID);

 /*
    Func Name:   SSL_setPSKParameter
*/

/** 
* @defgroup SSL_setPSKParameter
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setPSKParameter(SSL_S *ssl,
* const char *pPskId, 
* SEC_INT iPskIdLen,
* const unsigned char *pPsk,
* SEC_INT iPskLen);
* @endcode
*
* @par Purpose
* This is used to copy the 4 PSK parameters, that is, the pPskID, iPskIdLen, pPsk and iPskLen 
* into the SSL->stPSKInfo structure.
*
* @par Description
* SSL_setPSKParameter function copies the 4 PSK parameters, that is, the pPskID, iPskIdLen, pPsk and iPskLen into the
* SSL->stPSKInfo structure. Thus the stPSKInfo structure inside each SSL_S object is initialized using this API.
*
* @param[in] ssl This is the SSL object for this particular session. The PSK parameters will be updated into the 
* ssl->pPskStore_S structure. [N/A] 
* @param[in] pPskId This is the PSK Identity. [N/A]
* @param[in] iPskIdLen This is the length of the PSK Identity. [N/A]
* @param[in] pPsk This is the PSK (pre-shared key). [N/A]
* @param[in] iPskLen This is the length of the pre-shared key. [N/A]
                    
* @retval SEC_INT on successful completion of copying contents to the SSL_S structure [SEC_SUCCESS|N/A]
* @retval SEC_INT Error in parameters passed to the function.\n
* Initialization of the PSK store was not successful [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* Usage of this API is depreciated.\n
* N/A
* 
* @par Related Topics
* N/A
*/

 SSLLINKDLL SEC_INT SSL_setPSKParameter(SSL_S *ssl,const char *pPskId, \
            SEC_INT iPskIdLen, const unsigned char *pPsk, SEC_INT iPskLen);


/**
* @defgroup SSL_ctxRemoveCertAndPrivKey
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxRemoveCertAndPrivKey( SSL_CTX_S *pstContext);
* @endcode
*
* @par Purpose
* This function is used to remove the certificate along with the key
* from the ssl context.
*
* @par Description
* SSL_ctxRemoveCertAndPrivKey function removes the certificate and private 
* key from the ssl context. If only one of them is loaded, certificate
* or key will be removed.
*
* @param[in] pstContext Pointer to SSL context.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On in all cases except invalid input. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* N/A
*/

SSLLINKDLL SEC_INT SSL_ctxRemoveCertAndPrivKey(SSL_CTX_S *pstContext);


/**
* @defgroup SSL_RemoveCertAndPrivKey
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_RemoveCertAndPrivKey( SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This function is used to remove the certificate and private 
* key from the ssl object.
*
* @par Description
* SSL_RemoveCertAndPrivKey function removes the certificate along with the key
* from the ssl object. If only one of them is loaded, certificate
* or key will be removed.
*
* @param[in] pstSSL Pointer to SSL object. [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On in all cases except invalid input. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
*
* @par Required Header File
* ssl.h
*
* @par Note
* The Certificate and private keys acquired from the context will 
* continue to remain in the context. The certificate and
* private key will only be removed from the object.
* Once SSL_ctxRemoveCertAndPrivKey or SSL_ctxFree
* is called the same will be removed from the memory. \n
* N/A
* 
* @par Related Topics
* N/A
*/
SSLLINKDLL SEC_INT SSL_RemoveCertAndPrivKey(SSL_S *pstSSL);

/**
* @defgroup SSL_ctxRemoveTrustedCA
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxRemoveTrustedCA( SSL_CTX_S *pstContext,
*                               SEC_NAME_S *pstIssuerName,
*                               SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove the Trusted CA certificates from the 
* ssl context.
*
* @par Description
* SSL_ctxRemoveTrustedCA function removes the Trusted CA certificate from 
* the ssl context based on the Issuer name and the Serial number of 
* the CA certificate
*
* @param[in] pstContext Pointer to SSL context.
* Issuer name and serial number are unique identifier in RFC.[NA/NA]
* @param[in] pstIssuerName Issuer name of the CA.[NA/NA]
* @param[in] pstSerialNum Serial Number of the CA.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* If SEC_NULL is returned 
* 1) SSL_getLastError will return SSL_R_TRUST_CA_CERT_NOT_FOUND 
* if certificate was not found
* 2) SSL_getLastError will return SSL_R_INTERNAL_ERROR
* on all internal error\n
* N/A
* 
* @par Related Topics
* N/A
*/
SSLLINKDLL SEC_INT SSL_ctxRemoveTrustedCA(SSL_CTX_S *pstContext,
                               SEC_NAME_S *pstIssuerName,
                               SEC_BIGINT_S *pstSerialNum);


/**
* @defgroup SSL_ctxRemoveCrl
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxRemoveCrl( SSL_CTX_S *pstContext,
*                           SEC_NAME_S *pstIssuerName,
                            SEC_BIGINT_S *pstExtnCRLNum);
* @endcode
*
* @par Purpose
* This function is used to remove the crl from the 
* ssl context.
*
* @par Description
* SSL_ctxRemoveCrl function removes the crl from 
* the ssl context based on the Issuer name and the
* CRL Number 
*
* @param[in] pstContext Pointer to SSL context
* Issuer name and crl number are unique identifier in RFC.[NA/NA]
* @param[in] pstIssuerName Issuer name of the CRL.[NA/NA]
* @param[in] pstExtnCRLNum CRL number of the CRL certificate 
* to be removed[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
*	- If the user inputs only Issuer Name then all the matching CRL(S) 
* and Delta CRL(S) will be removed.
*	- If the user inputs both the Issuer Name and the CRL number then all 
* the matching CRL(S) and Delta CRL(S) will be removed.
* The flags set during SSL_ctxLoadCRL are not removed during 
* SSL_ctxRemoveCrl. And hence must be removed by the user 
* if needed.
* 
* If SEC_NULL is returned 
* 1) SSL_getLastError will return SSL_R_CRL_CERT_NOT_FOUND 
* if certificate was not found
* 2) SSL_getLastError will return SSL_R_INTERNAL_ERROR
* on all internal error\n
* N/A
* 
* @par Related Topics
* N/A
*/
SSLLINKDLL SEC_INT SSL_ctxRemoveCrl(SSL_CTX_S *pstContext,
                               SEC_NAME_S *pstIssuerName,
                               SEC_BIGINT_S *pstExtnCRLNum);



/**
* @defgroup IPSI_SSL_ctxRemoveExpiredCRL
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxRemoveExpiredCRL( SSL_CTX_S *pstContext,
* SEC_UINT uiCrlType);
* @endcode
*
* @par Purpose
* This function is used to remove the expired crls from the
* ssl context.
*
* @par Description
* IPSI_SSL_ctxRemoveExpiredCRL function removes the expired crls from 
* the ssl context. This API is multithread safe. This API can be used 
* in parallel with handshake.
*
* @param[in] pstContext Pointer to SSL context. [NA/NA]
* @param[in] uiCrlType The Type of the CRL to be removed. 
* Reserved for future use.The user can pass 0 for this parameter. 
* This parameter will not be validated. [NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT On successful execution. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
* @retval SEC_INT If any internal error occurs. [0|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
*	- If X509_V_FLAG_USE_CHECK_TIME flag is set, then 
*     the time validity of the CRL will be compared with the customized time
*     present in the context.Otherwise the system time will be used for comparison.
*	- The API doesnot report any error if no CRLs are present in the context
*     store.
*	- The API doesnot report any error if no CRLs are expired.
*
* If SEC_NULL is returned\n
* 1) SSL_getLastError will return SSL_R_INTERNAL_ERROR
*    on all internal error\n
* 2) SSL_getLastError will return SSL_R_DATE_CMP_FAILED
*    if Date Comparison fails\n
* N/A
*
* @par Related Topics
* N/A
*/
SSLLINKDLL SEC_INT IPSI_SSL_ctxRemoveExpiredCRL(SSL_CTX_S *pstContext,
                                            SEC_UINT uiCrlType);


/**
* @defgroup SSL_ctxLoadCrossCACertificateBuffer
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxLoadCrossCACertificateBuffer (SSL_CTX_S *pstContext,
*                                           SEC_CHAR *pcCertBuf,
*                                           SEC_UINT uCertBufLen,
*                                           SEC_INT iType);
* @endcode
*
 @par Purpose
* This is used to load the Cross CA certificate found in a buffer to 
* the SSL context.
* 
* @par Description
* SSL_ctxLoadCrossCACertificateBuffer function reads a buffer that contains
* the certificate in "PEM","PFX" or "DER"format.
* To verify user certificate during the authentication, we should set it
* to the SSL Context.
* 
* @param[in] pstContext Pointer to SSL_CTX_S of either client OR server. [N/A]
* @param[in] pucBuf Pointer to the buffer from which the certificates has to
* be loaded. [N/A]
* @param[in] ulLen The length of the buffer. [N/A]
* @param[in] type Type in which the certificates are stored in the buffer.
* The formats in which certificates are stored is one of the following:\n
* SSL_FILETYPE_PFX \n
* SSL_FILETYPE_PEM \n
* SSL_FILETYPE_ASN1 [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a Cert or List of Certs are set to Context. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* - If a buffer contains more than one certificate, other than X509 V3 end 
* entity certificate and self signed certificates, all other certificates
* will be loaded.
* - In case of buffer length, validation is done only for the value of zero.
* (Value zero is considered to be invalid). Any value other than the actual
* buffer length API behaviour is undefined.
* - For PFX file type, zero password length is not supported.
* - If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
* - For the PEM file type, stack does not support MIC_CLEAR mode.
* - If the same certificate is being loaded twice, loading will be
* failed and continues to load other certificates if there are more than one
* certificate in the buffer.
* - If the same certiifcate is being loaded which is already available in
* store, it returns SEC_NULL with error SSL_R_EXISTING_CA_CERT, if buffer
* has only one certificate.
* - This function will allow only version 3 CA certficate to load, and it 
* allows any verison of root certificate.
*
* @par Related Topics
* SSL_ctxUsePrivateKey \n
* SSL_ctxUsePrivateKeyFile \n
* SSL_ctxUsePrivateKeyBuffer \n
* SSL_ctxUseRSAPrivateKey \n
* SSL_ctxUseRSAPrivateKeyFile \n
* SSL_usePrivateKey \n
* SSL_usePrivateKeyFile \n
* SSL_usePrivateKeyBuffer \n
* SSL_useRSAPrivateKey \n
* SSL_useRSAPrivateKeyFile \n
* \n
* SSL_ctxUseCertificate \n
* SSL_ctxUseCertificateFile \n
* SSL_ctxUseCertificateBuffer \n
* SSL_useCertificate \n
* SSL_useCertificateFile \n
* SSL_useCertificateBuffer \n
* \n
* SSL_ctxLoadPFXStore \n
* SSL_ctxLoadPFXStoreBuffer \n
* SSL_LoadPFXStore \n
* SSL_LoadPFXStoreBuffer \n
* \n
* SSL_ctxUseCertificateChainFile \n
* SSL_ctxUseCertificateChainBuffer \n
* \n
* SSL_ctxLoadCACertificateFile \n
* \n
* SSL_ctxLoadCrl \n
* SSL_ctxLoadCrlBuffer \n
* \n
* SSL_loadClientCAFile \n
* \n
* SSL_ctxSetDefaultPasswd_cb \n
* \n
* SSL_ctxCheckPrivateKey \n
* SSL_checkPrivateKey \n
* SSL_ctxLoadCACertificateBuffer \n
* SSL_ctxLoadCACertificateFile
*/

SSLLINKDLL SEC_INT SSL_ctxLoadCrossCACertificateBuffer (SSL_CTX_S *pstContext,
                                           SEC_CHAR *pcCertBuf,
                                           SEC_UINT uCertBufLen,
                                           SEC_INT iType);

/**
* @defgroup SSL_ctxLoadCrossCACertificateFile
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxLoadCrossCACertificateFile (SSL_CTX_S *pstContext, 
*                                           const SEC_CHAR *CAfile,
*                                           SEC_INT type);
* @endcode
*
 @par Purpose
* This is used to load the Cross CA certificate found in a file to 
* the SSL context.
* 
* @par Description
* SSL_ctxLoadCrossCACertificateFile function reads a file that contains
* the certificate in "PEM","PFX" or "DER"format.
* To verify user certificate during the authentication, we should set it
* to the SSL Context.
* 
* @param[in] pstContext Pointer to SSL_CTX_S of either client OR server. [N/A]
* @param[in] CAfile Pointer to the file from which the certificates has to
* be loaded. [N/A]
* @param[in] type Type in which the certificates are stored in the buffer.
* The formats in which certificates are stored is one of the following:\n
* SSL_FILETYPE_PFX,\n
* SSL_FILETYPE_PEM,\n
* SSL_FILETYPE_ASN1. [N/A]
* 
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a Cert or List of Certs are set to Context. [TLS_SUCCESS|N/A]
* 
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* - If a file contains more than one certificate, other than X509 V3 end 
* entity certificate and self signed certificates, all other certificates
* will be loaded.
* - For PFX file type, zero password length is not supported.
* - If the file type is PFX, the PFX file should be created with encrypted
* password mode only.
* - For the PEM file type, stack does not support MIC_CLEAR mode.
* - If the same certificate is being loaded twice, loading will be
* failed and continues to load other certificates if there are more than one
* certificate in the buffer.
* - If the same certiifcate is being loaded which is already available in the
* store, it returns SEC_NULL with error SSL_R_EXISTING_CA_CERT, if file
* has only one certificate.
* - This function will allow only version 3 CA certficate to load, and it 
* allows any verison of root certificate.
*
* @par Related Topics
* SSL_ctxUsePrivateKey \n
* SSL_ctxUsePrivateKeyFile \n
* SSL_ctxUsePrivateKeyBuffer \n
* SSL_ctxUseRSAPrivateKey \n
* SSL_ctxUseRSAPrivateKeyFile \n
* SSL_usePrivateKey \n
* SSL_usePrivateKeyFile \n
* SSL_usePrivateKeyBuffer \n
* SSL_useRSAPrivateKey \n
* SSL_useRSAPrivateKeyFile \n
* \n
* SSL_ctxUseCertificate \n
* SSL_ctxUseCertificateFile \n
* SSL_ctxUseCertificateBuffer \n
* SSL_useCertificate \n
* SSL_useCertificateFile \n
* SSL_useCertificateBuffer \n
* \n
* SSL_ctxLoadPFXStore \n
* SSL_ctxLoadPFXStoreBuffer \n
* SSL_LoadPFXStore \n
* SSL_LoadPFXStoreBuffer \n
* \n
* SSL_ctxUseCertificateChainFile \n
* SSL_ctxUseCertificateChainBuffer \n
* \n
* SSL_ctxLoadCACertificateFile \n
* \n
* SSL_ctxLoadCrl \n
* SSL_ctxLoadCrlBuffer \n
* \n
* SSL_loadClientCAFile \n
* \n
* SSL_ctxSetDefaultPasswd_cb \n
* \n
* SSL_ctxCheckPrivateKey \n
* SSL_checkPrivateKey \n
* SSL_ctxLoadCACertificateBuffer \n
* SSL_ctxLoadCACertificateFile \n
* SSL_ctxLoadCrossCACertificateBUffer
*/

SSLLINKDLL SEC_INT SSL_ctxLoadCrossCACertificateFile (SSL_CTX_S *pstContext, 
                                           const SEC_CHAR *CAfile,
                                           SEC_INT type);

/**
* @defgroup SSL_ctxRemoveCrossCA
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxRemoveCrossCA(SSL_CTX_S *pstContext,
*                               SEC_NAME_S *pstIssuerName,
*                               SEC_BIGINT_S *pstSerialNum);
* @endcode
*
* @par Purpose
* This function is used to remove the cross certificate from the 
* ssl context.
*
* @par Description
* SSL_ctxRemoveCrossCA function removes the cross certificate from 
* the ssl context.
*
* @param[in] pstContext Pointer to SSL context.
* issuer name and serial number are unique identifier in RFC[NA/NA]
* @param[in] pstIssuerName Issuer name of the cross CA.[NA/NA]
* @param[in] pstSerialNum Serial Number of the cross CA.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval int On successful execution [TLS_SUCCESS|NA]
* @retval int On all failure conditions [SEC_ERROR|NA]
*
* @par Note
* 
* If SEC_NULL is returned 
* 1) SSL_getLastError will return SSL_R_CROSS_CA_CERT_NOT_FOUND 
* if certificate was not found
* 2) SSL_getLastError will return SSL_R_INTERNAL_ERROR
* on all internal error\n
* N/A
* 
* @par Related Topics
* N/A
*/
SSLLINKDLL SEC_INT SSL_ctxRemoveCrossCA(SSL_CTX_S *pstContext,
                               SEC_NAME_S *pstIssuerName,
                               SEC_BIGINT_S *pstSerialNum);



/*
    Func Name:  SSL_getX509Certificate
*/
/**
* @defgroup SSL_getX509Certificate
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_getX509Certificate (SSL_S *pstSSL,
*                                           X509_CERT_S ** dpstCert)
* @endcode
* 
* @par Purpose
* This function provides an X509 certificate latest loaded in the SSL_S
* structure 
* as output parameter 
*
* @par Description
* SSL_getX509Certificate function provides an X509 certificate latest loaded 
* in the SSL structure. Before calling this function, an X509 certificate
* must be loaded into the SSL structure with another API.
*
* @param[in] pstSSL Pointer to SSL_S object [N/A]
* @param[out] dpstCert  double Pointer to X509_CERT_S [N/A]
*
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If certificate is retrived succesfully from 
* SSL_S object. [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Memory Handling
* ipsi will allocate the memory for the dpstCert. To free this memory 
* application has to call the X509_freeCert
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getPrivatekey,\n
* SSL_getCertificate,\n
* SSL_useCertificate,\n
* SSL_RemoveCertAndPrivKey
*/

SSLLINKDLL SEC_INT SSL_getX509Certificate (SSL_S *pstSSL,
                                            X509_CERT_S ** dpstCert);


/*
    Func Name:  SSL_getX509Certificate
*/
/**
* @defgroup SSL_ctxGetX509Certificate
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxGetX509Certificate (SSL_CTX_S *pstContext,
*                                           X509_CERT_S ** dpstCert);
* @endcode
* 
* @par Purpose
* This function provides an X509 certificate loaded in the SSL context 
* as output parameter 
*
* @par Description
* SSL_ctxGetX509Certificate function provides an X509 certificate latest 
* loaded in the SSL context. Before calling this function, an X509 certificate
* must be loaded into the SSL context with another API.
*
* @param[in] pstContext Pointer to SSL_CTX_S context [N/A]
* @param[out] dpstCert  double Pointer to X509_CERT_S [N/A]
*
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If certificate is retrived succesfully from 
* SSL context. [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Memory Handling
* ipsi will allocate the memory for the dpstCert. To free this memory 
* application has to call the X509_freeCert
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
* SSL_getPrivatekey,\n
* SSL_getCertificate,\n
*.SSL_ctxUseCertificate,\n
* SSL_ctxRemoveCertAndPrivKey
*/
SSLLINKDLL SEC_INT SSL_ctxGetX509Certificate (SSL_CTX_S *pstContext,
                                            X509_CERT_S ** dpstCert);



/*
    Func Name:  SSL_ctxGetAllTrustCA
*/
/**
* @defgroup SSL_ctxGetAllTrustCA
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxGetAllTrustCA(SSL_CTX_S *pstContext,
*                            SEC_List_S **dpOutCertList);
* @endcode
* 
* @par Purpose
* This function retrive all loaded trusted CA from SSL context 
*
* @par Description
* SSL_ctxGetAllTrustCA retrive all loaded trusted CA from SSL context 
*
* @param[in] pstContext Pointer to SSL_CTX_S context [N/A]
* @param[out] dpOutCertList List which contains all the CA.
* dpOutCertList is a list which holds elements of type X509_CERT_S[NA/NA]
*
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If CAs are retrived successfully from SSL_CTX_S 
* context. [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
* @par Memory Handling
* ipsi will allocate the memory for the dpOutCertList (the list may contain one
* or more entries), to free this memory application has to call the
* SEC_LIST_FREE ,with the free function as X509_freeCert.
*
* @par Note
* \n
* N/A
* @par Related Topics
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
*.SSL_ctxRemoveTrustedCA
*/

SSLLINKDLL SEC_INT SSL_ctxGetAllTrustCA(SSL_CTX_S *pstContext,
                            SEC_List_S **dpOutCertList);


/*
    Func Name:  SSL_ctxGetAllTrustCrossCA
*/
/**
* @defgroup SSL_ctxGetAllTrustCrossCA
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxGetAllTrustCrossCA(SSL_CTX_S *pstContext,
*                           SEC_List_S **dpOutCrossCAList);
* @endcode
* 
* @par Purpose
* This function retrive all loaded trusted cross CA from SSL context 
*
* @par Description
* SSL_ctxGetAllTrustCrossCA retrive all loaded trusted cross CA from 
* SSL context 
*
* @param[in] pstContext Pointer to SSL_CTX_S context [N/A]
* @param[out] dpOutCrossCAList List which contains all the cross CA.
* dpOutCrossCAList is a list which holds elements of type
* X509_CERT_S[NA/NA]
*
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If cross CAs are retrived successfully from SSL_CTX_S
* context. [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Memory Handling
* ipsi will allocate the memory for the dpOutCrossCAList ( the list may 
* contain one or more entries), to free this memory application has to 
* call the SEC_LIST_FREE ,with the free function as X509_freeCert.
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_ctxLoadCrossCACertificateFile,\n
* SSL_ctxLoadCrossCACertificateBuffer,\n
*.SSL_ctxRemoveCrossCA
*/

SSLLINKDLL SEC_INT SSL_ctxGetAllTrustCrossCA(SSL_CTX_S *pstContext,
                            SEC_List_S **dpOutCrossCAList);


/*
    Func Name:  SSL_ctxGetAllCRL
*/
/**
* @defgroup SSL_ctxGetAllCRL
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxGetAllCRL(SSL_CTX_S *pstContext,
*                          SEC_List_S **dpOutCRLList);
* @endcode
* 
* @par Purpose
* This function retrive all loaded trusted cross CRL from SSL context 
*
* @par Description
* SSL_ctxGetAllCRL retrive all loaded trusted cross CA from 
* SSL context 
*
* @param[in] pstContext Pointer to SSL_CTX_S context [N/A]
* @param[out] dpOutCRLList List which contains all the CRL.
* dpOutCRLList is a list which holds elements of type
* X509_CRL_S[NA/NA]
*
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If any internal error occurs. [SEC_NULL|N/A]
* @retval SEC_INT If a CRLs are retrived successfully from SSL_CTX_S
* context. [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Memory Handling
* ipsi will allocate the memory for the dpOutCRLList ( the list may contain one
* or more entries), to free this memory application has to call the
* SEC_LIST_FREE,with the free function as X509CRL_free.
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
*.SSL_ctxRemoveCrl
*/
SSLLINKDLL SEC_INT SSL_ctxGetAllCRL(SSL_CTX_S *pstContext,
                         SEC_List_S **dpOutCRLList);

#ifndef __IPSI_VISP_RELEASE__
/*
    Func Name:  IPSI_SSL_ctxLoadCertificateKeyFile
*/

/**
* @defgroup IPSI_SSL_ctxLoadCertificateKeyFile
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxLoadCertificateKeyFile(SSL_CTX_S *ctx,
* const SEC_CHAR *pcCertFile,
* SEC_INT iCertFileType,
* const SEC_CHAR *pcKeyFile,
* SEC_INT iKeyFileType);
* @endcode
*
* @par Purpose
* This is used to load the certificate from a file and private key from
* a file to the SSL context.
*
* @par Description
* IPSI_SSL_ctxLoadCertificateKeyFile function adds certificate from a file
* and private key from a file to ctx. The file types must be
* specified from the known types SSL_FILETYPE_PEM, SSL_FILETYPE_PFX,
* and SSL_FILETYPE_ASN1.
*
* @param[in] ctx Pointer to SSL Context. [NA/NA]
* @param[in] pcCertFile The path of the certificate filename. [NA/NA]
* @param[in] iCertFileType The formatting type of certificate could be one
* of the following\n
* SSL_FILETYPE_ASN1\n
* SSL_FILETYPE_PEM\n
* SSL_FILETYPE_PFX. [NA/NA]
* @param[in] pcKeyFile The path of the pvtkey filename. [NA/NA]
* @param[in] iKeyFileType The formatting type of pvtkey could be one of
* the following\n
* SSL_FILETYPE_ASN1\n
* SSL_FILETYPE_PEM\n
* SSL_FILETYPE_PFX. [NA/NA]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On all failure conditions [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1. If file type is SSL_FILETYPE_PFX, the PFX file should be created with
*    encrypted password mode only. Also if file type
*    is SSL_FILETYPE_PEM, the key should be of type
*    PEM_OBJTYPE_P8_PRIVATEKEY only.\n\n
* 2. If we are using SSL_FILETYPE_PEM, the file should not be encoded
*    in MIC_CLEAR proc mode since complete file cannot
*    be saved in MIC_CLEAR mode.\n\n
* 3. If certificate and private key both are of type PFX, then both should 
*    have same password. That should be set in the context using callback\n\n
* 4. This API does not support loading of certificate and private key
*    dynamically. Application code should not call this API in any parallel
*    operation with either SSL Object (SSL_S) or SSL context(SSL_CTX_S)
*    operations. If used, application will lead to core dump.
*
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/

SSLLINKDLL SEC_INT  IPSI_SSL_ctxLoadCertificateKeyFile(SSL_CTX_S *ctx,
                                 const SEC_CHAR *pcCertFile,
                                 SEC_INT iCertFileType,
                                 const SEC_CHAR *pcKeyFile,
                                 SEC_INT iKeyFileType);

#endif // __IPSI_VISP_RELEASE__

/*
    Func Name: IPSI_SSL_ctxLoadCertificateKeyFile_withPasswd
*/

/**
* @defgroup IPSI_SSL_ctxLoadCertificateKeyFile_withPasswd
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxLoadCertificateKeyFile_withPasswd(
*                            SSL_CTX_S *pstCtx,
*                            IPSI_SSL_CERTKEY_FILE_CONF_S *pstCertKeyConf);
* @endcode
*
* @par Purpose
* This is used to load the certificate from a file and private key from
* a file to the SSL context.
*
* @par Description
* IPSI_SSL_ctxLoadCertificateKeyFile_withPasswd function adds certificate
* from a file and private key from a file to SSL context.
* The file types must be specified from the known types SSL_FILETYPE_PEM,
* SSL_FILETYPE_PFX, and SSL_FILETYPE_ASN1.
*
* @param[in] ctx Pointer to SSL Context. [NA/NA]
* @param[in] pstCertKeyConf Pointer to certificate and private key
* configurations structure. [NA/NA]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On invalid input parameters [SEC_ERROR|N/A]
* @retval SEC_INT On any internal error happens [0|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
*	- A file can contain both the certificate and key, in such a case same file
*     name should be given as input to pcCertFile and pcKeyFile.\n
*	- A file should not contain more than one end entity certificate.\n
*	- In case of file having multiple certificates, first certificate will be
*     considered as end entity certificate.
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
*         present in PFX.
*		- Enc password - Used for encrypting the baglist or 
*         the key before storing into bag. Cert can be encrypted 
*         only by encrypting the baglist. But, key can be encrypted 
*         by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		- Same file containing both the certificate and private key 
*         whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different for respective files.
*		- If a file has multiple encrypted or unencrypted baglists.
*         Then the first certificate from the first encrypted baglist will be taken
*         for checking. If the certificate is not present in the first encrypted 
*         baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
*         baglists, the first private key from the first encrypted/unencrypted 
*         baglist is taken.
*         If the privatekey is not present in the first baglist, then 
*         the privatekey is searched in the other baglists. If the 
*         private key is not present in any of the baglists,
*         then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
*     password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits for all types.
*   - For PFX type, the certificate MAC password and encryption password
*     should be same. In the same way, the private key MAC password and
*     encryption password should be same.
*
*   - This API can be used in multiple threads with the same SSL Context 
*     used across the threads. The multithread scenarios can be as below:\n

*     a. We can call this API with same SSL context in 
*        multiple threads. There will not be any undefined behavior. The 
*        certificate/private key which is loaded last will be updated
*        in the context.\n\n

*     b. If certificate/private key are loaded using this API in SSL context,
*        then all the SSL objects created from SSL context will 
*        be holding those certficate/private keys.  So if SSL connection
*        is being established using these SSL objects and in another thread
*        a new set of certificate/private key is loaded then it will not affect
*        the existing SSL objects nor the SSL connection that is being
*        established. Newly loaded certificates/private keys into SSL context
*        will not reflected in already created SSL objectes.But once if a new
*        set of certificate/private key is loaded into the SSL Context then the
*        subsequent SSL objects created will use the newly loaded
*        certificate/private key for establishing SSL connection.

*
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey.
*/
SSLLINKDLL SEC_INT IPSI_SSL_ctxLoadCertificateKeyFile_withPasswd(
                            SSL_CTX_S *pstCtx,
                            IPSI_SSL_CERTKEY_FILE_CONF_S *pstCertKeyConf);


/*
    Func Name: IPSI_SSL_ctxLoadCertificateKeyBuffer_withPasswd
*/

/**
* @defgroup IPSI_SSL_ctxLoadCertificateKeyBuffer_withPasswd
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxLoadCertificateKeyBuffer_withPasswd(
*                            SSL_CTX_S *pstCtx,
*                            IPSI_SSL_CERTKEY_BUF_CONF_S *pstCertKeyConf);
* @endcode
*
* @par Purpose
* This is used to load the certificate from a buffer and private key from
* a buffer to the SSL context.
*
* @par Description
* IPSI_SSL_ctxLoadCertificateKeyBuffer_withPasswd function adds certificate
* from a buffer and private key from a buffer to SSL context.
* The file types must be specified from the known types SSL_FILETYPE_PEM,
* SSL_FILETYPE_PFX and SSL_FILETYPE_ASN1.
*
* @param[in] ctx Pointer to SSL Context. [NA/NA]
* @param[in] pstCertKeyConf Pointer to certificate and private key
* configurations structure. [NA/NA]
*
* @retval SEC_INT On success [TLS_SUCCESS|N/A]
* @retval SEC_INT On invalid input parameters [SEC_ERROR|N/A]
* @retval SEC_INT On any internal error happens [0|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
*	- The terms used in PFX format are:
*		- Bag - Contains certificate / crl / key
*		- Baglist - List of bags
*		- Authsafe - List of Baglists
		- PFX - Encoded authsafe
*		- Mac password - Used for integrity check on the encoded data 
*         present in PFX.
*		- Enc password - Used for encrypting the baglist or 
*         the key before storing into bag. Cert can be encrypted 
*         only by encrypting the baglist. But, key can be encrypted 
*         by encrypting baglist or storing encrypted key in bag.
*	- In PFX format,the following type of file(s) are supported:
*		- Same file containing both the certificate and private key 
*         whose encryption and mac passwords are same.
*		- Certificate and keyfiles are different whose mac and encryption 
*         password are also different.
*		- If a file has multiple encrypted or unencrypted baglists.
*         Then the first certificate from the first encrypted baglist will be taken
*         for checking. If the certificate is not present in the first encrypted 
*         baglist, then the API returns failure.
*		- If a file has multiple encrypted or unencrypted 
*         baglists, the first private key from the first encrypted/unencrypted 
*         baglist is taken.
*         If the privatekey is not present in the first baglist, then 
*         the privatekey is searched in the other baglists. If the 
*         private key is not present in any of the baglists,
*         then the API returns failure.
*	- For PFX file type, zero password length is not supported.
*	- If the file type is PFX, the PFX file should be created with encrypted
*     password mode only.
*	- For the PEM file type, we will not support MIC_CLEAR mode.
*	- The supported key size ranges from 512 to 4096 bits.
*
*   - This API can be used in multiple threads with the same SSL Context 
*     used across the threads. The multithread scenarios can be as below:

*     a. We can call this API with same SSL context in 
*        multiple threads. There will not be any undefined behavior. The 
*        certificate/private key which is loaded last will be updated
*        in the context.

*     b. If certificate/private key are loaded using this API in SSL context,
*        then all the SSL objects created from SSL context will 
*        be holding those certficate/private keys.  So if SSL connection
*        is being established using these SSL objects and in another thread
*        a new set of certificate/private key is loaded then it will not affect
*        the existing SSL objects nor the SSL connection that is being
*        established. Newly loaded certificates/private keys into SSL context
*        will not reflected in already created SSL objectes.But once if a new
*        set of certificate/private key is loaded into the SSL Context then the
*        subsequent SSL objects created will use the newly loaded
*        certificate/private key for establishing SSL connection.
*
* @par Related Topics
* SSL_ctxUsePrivateKey,\n
* SSL_ctxUsePrivateKeyBuffer,\n
* SSL_ctxUseRSAPrivateKey,\n
* SSL_ctxUseRSAPrivateKeyFile,\n
* SSL_usePrivateKey,\n
* SSL_usePrivateKeyFile,\n
* SSL_usePrivateKeyBuffer,\n
* SSL_useRSAPrivateKey,\n
* SSL_useRSAPrivateKeyFile,\n
* \n
* SSL_ctxUseCertificate,\n
* SSL_ctxUseCertificateFile,\n
* SSL_ctxUseCertificateBuffer,\n
* SSL_useCertificate,\n
* SSL_useCertificateFile,\n
* SSL_useCertificateBuffer,\n
* \n
* SSL_ctxLoadPFXStore,\n
* SSL_ctxLoadPFXStoreBuffer,\n
* SSL_LoadPFXStore,\n
* SSL_LoadPFXStoreBuffer,\n
* \n
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
* \n
* SSL_ctxLoadCACertificateFile,\n
* SSL_ctxLoadCACertificateBuffer,\n
* \n
* SSL_ctxLoadCrl,\n
* SSL_ctxLoadCrlBuffer,\n
* \n
* SSL_loadClientCAFile,\n
* \n
* SSL_ctxSetDefaultPasswd_cb,\n
* \n
* SSL_ctxCheckPrivateKey,\n
* SSL_checkPrivateKey,\n
* IPSI_SSL_ctxLoadCertificateKeyFile_withPasswd
*/
SSLLINKDLL SEC_INT IPSI_SSL_ctxLoadCertificateKeyBuffer_withPasswd(
                            SSL_CTX_S *pstCtx,
                            IPSI_SSL_CERTKEY_BUF_CONF_S *pstCertKeyConf);


/*
    Func Name:  IPSI_SSL_ctxRemoveCertChain
*/

/**
* @defgroup IPSI_SSL_ctxRemoveCertChain
* @ingroup sslContextFunctions
* @par Prototype
* @code
* IPSI_SSL_ctxRemoveCertChain(SSL_CTX_S *ctx);
* @endcode
*
* @par Purpose
* This is used to remove the certificate chain from the SSL context.
*
* @par Description
* IPSI_SSL_ctxRemoveCertChain function removes the certificate chain
* from the ctx. It may be either client or server certificate chain.
* 
* @param[in] ctx SSL Context structure from which the certificate chain
* has to be removed. [NA/NA]
*
* @retval SEC_INT On successful execution. [TLS_SUCCESS|N/A]
* @retval SEC_INT On all failure conditions, the failure can be when the context
* is null. [SEC_ERROR|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
*   - This API does not support removing of certificate chain
*     dynamically. Application code should not call this API in any parallel
*     operation with either SSL Object (SSL_S) or SSL context(SSL_CTX_S)
*     operations. If used, application will lead to core dump.
* @par Related Topics
* SSL_ctxUseCertificateChainFile,\n
* SSL_ctxUseCertificateChainBuffer,\n
*/

SSLLINKDLL SEC_INT IPSI_SSL_ctxRemoveCertChain(SSL_CTX_S *ctx);

/*
    Func Name:  IPSI_SSL_ctxRemoveCertAndKeyByAlgID
*/

/**
* @defgroup IPSI_SSL_ctxRemoveCertAndKeyByAlgID
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxRemoveCertAndKeyByAlgID( SSL_CTX_S *pstCtx,
*                                             SEC_INT iAlgID);
* @endcode
*
* @par Purpose
* This function is used to remove the certificate along with the key 
* from the ssl context based on the algorithm ID.
* @par Description
* IPSI_SSL_ctxRemoveCertAndKeyByAlgID function removes the certificate 
* and private key from the ssl context based on the algorithm ID.
* If only certificate or key is loaded, the same will be removed.
* Valid AlgID's are SSL_PKEY_RSA_ENC to remove RSA certificate, Key 
* and SSL_PKEY_DSA_SIGN to remove DSA certificate and Key.
*
* @param[in] pstCtx Pointer to SSL context.[NA/NA]
* @param[in] iAlgID Algorithm ID for which certificate and key
* needs to be freed. They are SSL_PKEY_RSA_ENC for RSA,
* and SSL_PKEY_DSA_SIGN for DSA.[NA/NA]
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT In all the cases except invalid input. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
*
* @par Required Header File
* \n
* ssl.h
*
* @par Note
*   - This API does not support removing of certificate and private key
*     dynamically. Application code should not call this API in any parallel
*     operation with either SSL Object (SSL_S) or SSL context(SSL_CTX_S)
*     operations. If used, application will lead to core dump.
*
* @par Related Topics
* \n
* N/A
*/

SSLLINKDLL SEC_INT IPSI_SSL_ctxRemoveCertAndKeyByAlgID(SSL_CTX_S *pstCtx,
                                                            SEC_INT iAlgID);



#ifndef IPSI_SSL_NO_DTLS

/*
    Func Name:  SSL_setAIO
*/
/**
* @defgroup SSL_setAIO
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setAIO(SSL_S *pstSsl,
* IPSI_AIO_S *pstReadAio,IPSI_AIO_S *pstWriteAio);
* @endcode
* 
* @par Purpose
* This function Sets read and write aio to SSL object
*
* @par Description
* SSL_setAIO Sets read and write aio to SSL object
*
* @param[in] pstSsl Pointer to SSL_S object [N/A]
* @param[in] pstReadAio Read aio
* @param[in] pstWriteAio Write aio
*
* @retval SEC_INT If the input is invalid(NULL pointer). [SEC_ERROR|N/A]
* @retval SEC_INT If setting of aio to SSL object Successful [TLS_SUCCESS|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* ipsi_aio_free should not be called for freeing pstReadAio and pstWriteAio
* after setting the same aio in SSL_setAIO, as it will be freed in SSL_free.
*
* @par Related Topics
* NA
*/

SSLLINKDLL SEC_INT SSL_setAIO(SSL_S *pstSsl,
IPSI_AIO_S *pstReadAio,IPSI_AIO_S *pstWriteAio);


/*
    Func Name:  SSL_getReadAIO
*/
/**
* @defgroup SSL_getReadAIO
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* IPSI_AIO_S * SSL_getReadAIO(SSL_S *pstSsl);
* @endcode
* 
* @par Purpose
* This function gets readaio from SSL object
*
* @par Description
* SSL_getReadAIO gets readaio from SSL object
*
* @param[in] pstSsl Pointer to SSL_S object [N/A]
* @param[out] NA
*
* @retval  SEC_NULL If the input is invalid(NULL pointer). [N/A]
* @retval pointer to IPSI_AIO_SSEC_INT If Success [|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* NA
*/

SSLLINKDLL IPSI_AIO_S * SSL_getReadAIO(const SSL_S *pstSsl);

/*
    Func Name:  SSL_getWriteAIO
*/
/**
* @defgroup SSL_getWriteAIO
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* IPSI_AIO_S * SSL_getWriteAIO(SSL_S *pstSsl);
* @endcode
* 
* @par Purpose
* This function gets writeaio from SSL object
*
* @par Description
* SSL_getWriteAIO gets writeaio from SSL object
*
* @param[in] pstSsl Pointer to SSL_S object [N/A]
* @param[out] NA
*
* @retval  SEC_NULL If the input is invalid(NULL pointer). [N/A]
* @retval pointer to IPSI_AIO_SSEC_INT If Success [|N/A]
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
*
* @par Related Topics
* NA
*/

SSLLINKDLL IPSI_AIO_S * SSL_getWriteAIO(const SSL_S *pstSsl);

/*
    Func Name:  SSL_ctxSetCookieGenerate_cb
*/
/**
* @defgroup SSL_ctxSetCookieGenerate_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_VOID SSL_ctxSetCookieGenerate_cb(SSL_CTX_S *ctx,
* SEC_INT (*app_gen_cookie_cb)
* (SSL_S *ssl, SEC_UCHAR *cookie, SEC_UINT *cookie_len));
* @endcode
* 
* @par Purpose
* This function sets callback for cookie generate to SSL context
*
* @par Description
* SSL_ctxSetCookieGenerate_cb set coockie generation callback to SSL context
*
* @param[in] pstCtx Pointer to SSL context [N/A]
* @param[in] app_gen_cookie_cb function pointer for cookie generate fn [N/A]
* @param[in] pAppData Pointer to application data [N/A]
* @param[out] NA
*
* @retval  NA
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* app_gen_cookie_cb - callback function takes 4 arguments
* pstSsl pointer to ssl object
* pcCookie buffer for generated cookie
* pCookieLen stores generated cookie length
* pAppData void pointer which contains application data.
* app_gen_cookie_cb function returns 0 if it fails to generate cookie
* 1 if it success
*
* @par Related Topics
* NA
*/

SSLLINKDLL SEC_VOID SSL_ctxSetCookieGenerate_cb(
SSL_CTX_S *pstCtx,SEC_INT (*app_gen_cookie_cb)(SSL_S *pstSsl,
SEC_UCHAR *pcCookie, SEC_UINT *pCookieLen,SEC_VOID *pAppData),
SEC_VOID *pAppData);

/*
    Func Name:  SSL_ctxSetCookieVerify_cb
*/
/**
* @defgroup SSL_ctxSetCookieVerify_cb
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_VOID SSL_ctxSetCookieVerify_cb(SSL_CTX_S *pstCtx,
* SEC_INT (*app_verify_cookie_cb)(SSL_S *pstSsl,
* SEC_UCHAR *pcCookie, SEC_UINT iCookieLen,SEC_VOID *pAppData),
* SEC_VOID *pAppData);

* @endcode
* 
* @par Purpose
* This function sets callback for cookie verify to SSL context
*
* @par Description
* SSL_ctxSetCookieVerify_cb sets callback for cookie verify to SSL context
*
* @param[in] pstCtx Pointer to SSL context [N/A]
* @param[in] app_verify_cookie_cb function pointer for cookie verify fn N/A
* @param[in] pAppData Pointer to application data [N/A]

* @param[out] NA
*
* @retval  NA
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* app_verify_cookie_cb - callback function takes 4 arguments
* pstSsl pointer to ssl object
* pcCookie cookie buffer
* iCookieLen length of cookie
* pAppData void pointer which contains application data.

* app_verify_cookie_cb function returns 0 if it fails to verify cookie
* 1 if it success
*
* @par Related Topics
* NA
*/

SSLLINKDLL SEC_VOID SSL_ctxSetCookieVerify_cb(SSL_CTX_S *pstCtx,
SEC_INT (*app_verify_cookie_cb)(SSL_S *pstSsl,
SEC_UCHAR *pcCookie, SEC_UINT iCookieLen,SEC_VOID *pAppData),
SEC_VOID *pAppData);

/*
    Func Name:  SSL_SetCookieGenerate_cb
*/
/**
* @defgroup SSL_SetCookieGenerate_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_SetCookieGenerate_cb(SSL_S *ssl,
* SEC_INT (*app_gen_cookie_cb)
* (SSL_S *ssl, SEC_UCHAR *cookie, SEC_UINT *cookie_len));
* @endcode
* 
* @par Purpose
* This function sets callback for cookie generate to SSL object
*
* @par Description
* SSL_ctxSetCookieGenerate_cb sets callback for cookie generate to SSL object
*
* @param[in] pstCtx Pointer to SSL object [N/A]
* @param[in] app_gen_cookie_cb function pointer for cookie generate fn [N/A]
* @param[in] pAppData Pointer to application data [N/A]

* @param[out] NA
*
* @retval  NA
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* app_gen_cookie_cb - callback function takes 4 arguments
* pstSsl pointer to ssl object
* pcCookie buffer for generated cookie
* pCookieLen stores generated cookie length
* pAppData void pointer which contains application data.
* app_gen_cookie_cb function returns 0 if it fails to generate cookie
* 1 if it success

*
* @par Related Topics
* NA
*/

SSLLINKDLL SEC_VOID SSL_SetCookieGenerate_cb(SSL_S *pstSsl,
SEC_INT (*app_gen_cookie_cb)(SSL_S *pstSsl,
SEC_UCHAR *pcCookie, SEC_UINT *pCookielen,SEC_VOID *pAppData),
SEC_VOID *pAppData);

/*
    Func Name: SSL_SetCookieVerify_cb
*/
/**
* @defgroup SSL_SetCookieVerify_cb
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_VOID SSL_SetCookieVerify_cb(SSL_S *pstSsl,
* SEC_INT (*app_verify_cookie_cb)(SSL_S *pstSsl, SEC_UCHAR *pcCookie,
* SEC_UINT iCookieLen,SEC_VOID *pAppData),SEC_VOID *pAppData);
* @endcode
* 
* @par Purpose
* This function sets callback for cookie verify to SSL object
*
* @par Description
* SSL_ctxSetCookieVerify_cb sets callback for cookie verify to SSL object
*
* @param[in] ctx Pointer to SSL object [N/A]
* @param[in] app_verify_cookie_cb function pointer for cookie verify fn [N/A]
* @param[in] pAppData Pointer to application data [N/A]

* @param[out] NA
*
* @retval  NA
*
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* app_verify_cookie_cb - callback function takes 4 arguments
* pstSsl pointer to ssl object
* pcCookie cookie buffer
* iCookieLen length of cookie
* pAppData void pointer which contains application data.

* app_verify_cookie_cb function returns 0 if it fails to verify cookie
* 1 if it success

*
* @par Related Topics
* NA
*/

SSLLINKDLL SEC_VOID SSL_SetCookieVerify_cb(SSL_S *pstSsl,
SEC_INT (*app_verify_cookie_cb)(SSL_S *pstSsl, SEC_UCHAR *pcCookie,
SEC_UINT iCookieLen,SEC_VOID *pAppData),SEC_VOID *pAppData);

#endif

/* Reason codes. */
#define SSL_R_APP_DATA_IN_HANDSHAKE                             100
#define SSL_R_ATTEMPT_TO_REUSE_SESSION_IN_DIFFERENT_CONTEXT     272
#define SSL_R_BAD_ALERT_RECORD                                  101
#define SSL_R_BAD_AUTHENTICATION_TYPE                           102
#define SSL_R_BAD_CHANGE_CIPHER_SPEC                            103
#define SSL_R_BAD_CHECKSUM                                      104
#define SSL_R_BAD_DATA_RETURNED_BY_CALLBACK                     106
#define SSL_R_BAD_DECOMPRESSION                                 107
#define SSL_R_BAD_DH_G_LENGTH                                   108
#define SSL_R_BAD_DH_PUB_KEY_LENGTH                             109
#define SSL_R_BAD_DH_P_LENGTH                                   110
#define SSL_R_BAD_DIGEST_LENGTH                                 111
#define SSL_R_BAD_DSA_SIGNATURE                                 112
#define SSL_R_BAD_ECC_CERT                                      1117
#define SSL_R_BAD_ECDSA_SIGNATURE                               352
#define SSL_R_BAD_ECPOINT                                       356
#define SSL_R_BAD_HELLO_REQUEST                                 105
#define SSL_R_BAD_LENGTH                                        271
#define SSL_R_BAD_MAC_DECODE                                    113
#define SSL_R_BAD_MESSAGE_TYPE                                  114
#define SSL_R_BAD_PACKET_LENGTH                                 115
#define SSL_R_BAD_PROTOCOL_VERSION_NUMBER                       116
#define SSL_R_BAD_RESPONSE_ARGUMENT                             117
#define SSL_R_BAD_RSA_DECRYPT                                   118
#define SSL_R_BAD_RSA_ENCRYPT                                   119
#define SSL_R_BAD_RSA_E_LENGTH                                  120
#define SSL_R_BAD_RSA_MODULUS_LENGTH                            121
#define SSL_R_BAD_RSA_SIGNATURE                                 122
#define SSL_R_BAD_SIGNATURE                                     123
#define SSL_R_BAD_SSL_FILETYPE                                  124
#define SSL_R_BAD_SSL_SESSION_ID_LENGTH                         125
#define SSL_R_BAD_STATE                                         126
#define SSL_R_BAD_WRITE_RETRY                                   127
#define SSL_R_BLOCK_CIPHER_PAD_IS_WRONG                         129
#define SSL_R_BN_LIB                                            130
#define SSL_R_CA_DN_LENGTH_MISMATCH                             131
#define SSL_R_CA_DN_TOO_LONG                                    132
#define SSL_R_CCS_RECEIVED_EARLY                                133
#define SSL_R_CERTIFICATE_VERIFY_FAILED                         134
#define SSL_R_CERT_LENGTH_MISMATCH                              135
#define SSL_R_CHALLENGE_IS_DIFFERENT                            136
#define SSL_R_CIPHER_CODE_WRONG_LENGTH                          137
#define SSL_R_CIPHER_OR_HASH_UNAVAILABLE                        138
#define SSL_R_CIPHER_TABLE_SRC_ERROR                            139
#define SSL_R_COMPRESSED_LENGTH_TOO_LONG                        140
#define SSL_R_COMPRESSION_FAILURE                               141
#define SSL_R_COMPRESSION_ID_NOT_WITHIN_PRIVATE_RANGE           1120
#define SSL_R_COMPRESSION_LIBRARY_ERROR                         142
#define SSL_R_CONNECTION_ID_IS_DIFFERENT                        143
#define SSL_R_CONNECTION_TYPE_NOT_SET                           144
#define SSL_R_COOKIE_MISMATCH                                   355
#define SSL_R_DATA_BETWEEN_CCS_AND_FINISHED                     145
#define SSL_R_DATA_LENGTH_TOO_LONG                              146
#define SSL_R_DECRYPTION_FAILED                                 147
#define SSL_R_DECRYPTION_FAILED_OR_BAD_RECORD_MAC               1109
#define SSL_R_DH_PUBLIC_VALUE_LENGTH_IS_WRONG                   148
#define SSL_R_DIGEST_CHECK_FAILED                               149
#define SSL_R_DUPLICATE_COMPRESSION_ID                          1121
#define SSL_R_ECGROUP_TOO_LARGE_FOR_CIPHER                      1119
#define SSL_R_ENCRYPTED_LENGTH_TOO_LONG                         150
#define SSL_R_ERROR_GENERATING_TMP_RSA_KEY                      1092
#define SSL_R_ERROR_IN_RECEIVED_CIPHER_LIST                     151
#define SSL_R_EXCESSIVE_MESSAGE_SIZE                            152
#define SSL_R_EXTRA_DATA_IN_MESSAGE                             153
#define SSL_R_GOT_A_FIN_BEFORE_A_CCS                            154
#define SSL_R_HTTPS_PROXY_REQUEST                               155
#define SSL_R_HTTP_REQUEST                                      156
#define SSL_R_ILLEGAL_PADDING                                   351
#define SSL_R_INAPPROPRIATE_FALLBACK                            373
#define SSL_R_INVALID_CHALLENGE_LENGTH                          158
#define SSL_R_INVALID_COMMAND                                   280
#define SSL_R_INVALID_PURPOSE                                   278
#define SSL_R_INVALID_TRUST                                     279
#define SSL_R_KEY_ARG_TOO_LONG                                  353
#define SSL_R_LENGTH_MISMATCH                                   159
#define SSL_R_LENGTH_TOO_SHORT                                  160
#define SSL_R_LIBRARY_BUG                                       274
#define SSL_R_LIBRARY_HAS_NO_CIPHERS                            161
#define SSL_R_MASTER_KEY_TOO_LONG                               354
#define SSL_R_MESSAGE_TOO_LONG                                  357
#define SSL_R_MISSING_DH_DSA_CERT                               162
#define SSL_R_MISSING_DH_KEY                                    163
#define SSL_R_MISSING_DH_RSA_CERT                               164
#define SSL_R_MISSING_DSA_SIGNING_CERT                          165
#define SSL_R_MISSING_EXPORT_TMP_DH_KEY                         166
#define SSL_R_MISSING_EXPORT_TMP_RSA_KEY                        167
#define SSL_R_MISSING_RSA_CERTIFICATE                           168
#define SSL_R_MISSING_RSA_ENCRYPTING_CERT                       169
#define SSL_R_MISSING_RSA_SIGNING_CERT                          170
#define SSL_R_MISSING_TMP_DH_KEY                                171
#define SSL_R_MISSING_TMP_ECDH_KEY                              358
#define SSL_R_MISSING_TMP_RSA_KEY                               172
#define SSL_R_MISSING_TMP_RSA_PKEY                              173
#define SSL_R_MISSING_VERIFY_MESSAGE                            174
#define SSL_R_NON_SSLV2_INITIAL_PACKET                          175
#define SSL_R_NO_CERTIFICATES_RETURNED                          176
#define SSL_R_NO_CERTIFICATE_ASSIGNED                           177
#define SSL_R_NO_CERTIFICATE_RETURNED                           178
#define SSL_R_NO_CERTIFICATE_SET                                179
#define SSL_R_NO_CERTIFICATE_SPECIFIED                          180
#define SSL_R_NO_CIPHERS_AVAILABLE                              181
#define SSL_R_NO_CIPHERS_PASSED                                 182
#define SSL_R_NO_CIPHERS_SPECIFIED                              183
#define SSL_R_NO_CIPHER_LIST                                    184
#define SSL_R_NO_CIPHER_MATCH                                   185
#define SSL_R_NO_CLIENT_CERT_RECEIVED                           186
#define SSL_R_NO_COMPRESSION_SPECIFIED                          187
#define SSL_R_NO_METHOD_SPECIFIED                               188
#define SSL_R_NO_PRIVATEKEY                                     189
#define SSL_R_NO_PRIVATE_KEY_ASSIGNED                           190
#define SSL_R_NO_PROTOCOLS_AVAILABLE                            191
#define SSL_R_NO_PUBLICKEY                                      192
#define SSL_R_NO_SHARED_CIPHER                                  193
#define SSL_R_NO_VERIFY_CALLBACK                                194
#define SSL_R_NULL_SSL_CTX                                      195
#define SSL_R_NULL_SSL_METHOD_PASSED                            196
#define SSL_R_OLD_SESSION_CIPHER_NOT_RETURNED                   197
#define SSL_R_PACKET_LENGTH_TOO_LONG                            198
#define SSL_R_PATH_TOO_LONG                                     270
#define SSL_R_PEER_DID_NOT_RETURN_A_CERTIFICATE                 199
#define SSL_R_PEER_ERROR                                        200
#define SSL_R_PEER_ERROR_CERTIFICATE                            201
#define SSL_R_PEER_ERROR_NO_CERTIFICATE                         202
#define SSL_R_PEER_ERROR_NO_CIPHER                              203
#define SSL_R_PEER_ERROR_UNSUPPORTED_CERTIFICATE_TYPE           204
#define SSL_R_PRE_MAC_LENGTH_TOO_LONG                           205
#define SSL_R_PROBLEMS_MAPPING_CIPHER_FUNCTIONS                 206
#define SSL_R_PROTOCOL_IS_SHUTDOWN                              207
#define SSL_R_PUBLIC_KEY_ENCRYPT_ERROR                          208
#define SSL_R_PUBLIC_KEY_IS_NOT_RSA                             209
#define SSL_R_PUBLIC_KEY_NOT_RSA                                210
#define SSL_R_READ_WRONG_PACKET_TYPE                            212
#define SSL_R_RECORD_LENGTH_MISMATCH                            213
#define SSL_R_RECORD_TOO_LARGE                                  214
#define SSL_R_RECORD_TOO_SMALL                                  1093
#define SSL_R_REQUIRED_CIPHER_MISSING                           215
#define SSL_R_REUSE_CERT_LENGTH_NOT_ZERO                        216
#define SSL_R_REUSE_CERT_TYPE_NOT_ZERO                          217
#define SSL_R_REUSE_CIPHER_LIST_NOT_ZERO                        218
#define SSL_R_SESSION_ID_CONTEXT_UNINITIALIZED                  277
#define SSL_R_SHORT_READ                                        219
#define SSL_R_SIGNATURE_FOR_NON_SIGNING_CERTIFICATE             220
#define SSL_R_SSL23_DOING_SESSION_ID_REUSE                      221
#define SSL_R_SSL2_CONNECTION_ID_TOO_LONG                       359
#define SSL_R_SSL3_SESSION_ID_TOO_LONG                          360
#define SSL_R_SSL3_SESSION_ID_TOO_SHORT                         222
#define SSL_R_SSLV3_ALERT_BAD_CERTIFICATE                       1042
#define SSL_R_SSLV3_ALERT_BAD_RECORD_MAC                        1020
#define SSL_R_SSLV3_ALERT_CERTIFICATE_EXPIRED                   1045
#define SSL_R_SSLV3_ALERT_CERTIFICATE_REVOKED                   1044
#define SSL_R_SSLV3_ALERT_CERTIFICATE_UNKNOWN                   1046
#define SSL_R_SSLV3_ALERT_DECOMPRESSION_FAILURE                 1030
#define SSL_R_SSLV3_ALERT_HANDSHAKE_FAILURE                     1040
#define SSL_R_SSLV3_ALERT_ILLEGAL_PARAMETER                     1047
#define SSL_R_SSLV3_ALERT_NO_CERTIFICATE                        1041
#define SSL_R_SSLV3_ALERT_PEER_ERROR_CERTIFICATE                223
#define SSL_R_SSLV3_ALERT_PEER_ERROR_NO_CERTIFICATE             224
#define SSL_R_SSLV3_ALERT_PEER_ERROR_NO_CIPHER                  225
#define SSL_R_SSLV3_ALERT_PEER_ERROR_UNSUPPORTED_CERTIFICATE_TYPE 226
#define SSL_R_SSLV3_ALERT_UNEXPECTED_MESSAGE                    1010
#define SSL_R_SSLV3_ALERT_UNKNOWN_REMOTE_ERROR_TYPE             227
#define SSL_R_SSLV3_ALERT_UNSUPPORTED_CERTIFICATE               1043
#define SSL_R_SSL_CTX_HAS_NO_DEFAULT_SSL_VERSION                228
#define SSL_R_SSL_HANDSHAKE_FAILURE                             229
#define SSL_R_SSL_LIBRARY_HAS_NO_CIPHERS                        230
#define SSL_R_SSL_SESSION_ID_CALLBACK_FAILED                    1102
#define SSL_R_SSL_SESSION_ID_CONFLICT                           1103
#define SSL_R_SSL_SESSION_ID_CONTEXT_TOO_LONG                   273
#define SSL_R_SSL_SESSION_ID_HAS_BAD_LENGTH                     1101
#define SSL_R_SSL_SESSION_ID_IS_DIFFERENT                       231
#define SSL_R_TLSV1_ALERT_ACCESS_DENIED                         1049
#define SSL_R_TLSV1_ALERT_DECODE_ERROR                          1050
#define SSL_R_TLSV1_ALERT_DECRYPTION_FAILED                     1021
#define SSL_R_TLSV1_ALERT_DECRYPT_ERROR                         1051
#define SSL_R_TLSV1_ALERT_EXPORT_RESTRICTION                    1060
#define SSL_R_TLSV1_ALERT_INAPPROPRIATE_FALLBACK                1086
#define SSL_R_TLSV1_ALERT_INSUFFICIENT_SECURITY                 1071
#define SSL_R_TLSV1_ALERT_INTERNAL_ERROR                        1080
#define SSL_R_TLSV1_ALERT_NO_RENEGOTIATION                      1100
#define SSL_R_TLSV1_ALERT_PROTOCOL_VERSION                      1070
#define SSL_R_TLSV1_ALERT_RECORD_OVERFLOW                       1022
#define SSL_R_TLSV1_ALERT_UNKNOWN_CA                            1048
#define SSL_R_TLSV1_ALERT_USER_CANCELLED                        1090
#define SSL_R_TLS_CLIENT_CERT_REQ_WITH_ANON_CIPHER              232
#define SSL_R_TLS_PEER_DID_NOT_RESPOND_WITH_CERTIFICATE_LIST    233
#define SSL_R_TLS_RSA_ENCRYPTED_VALUE_LENGTH_IS_WRONG           234
#define SSL_R_TRIED_TO_USE_UNSUPPORTED_CIPHER                   235
#define SSL_R_UNABLE_TO_DECODE_DH_CERTS                         236
#define SSL_R_UNABLE_TO_DECODE_ECDH_CERTS                       1115
#define SSL_R_UNABLE_TO_EXTRACT_PUBLIC_KEY                      237
#define SSL_R_UNABLE_TO_FIND_DH_PARAMETERS                      238
#define SSL_R_UNABLE_TO_FIND_ECDH_PARAMETERS                    1116
#define SSL_R_UNABLE_TO_FIND_PUBLIC_KEY_PARAMETERS              239
#define SSL_R_UNABLE_TO_FIND_SSL_METHOD                         240
#define SSL_R_UNABLE_TO_LOAD_SSL2_MD5_ROUTINES                  241
#define SSL_R_UNABLE_TO_LOAD_SSL3_MD5_ROUTINES                  242
#define SSL_R_UNABLE_TO_LOAD_SSL3_SHA1_ROUTINES                 243
#define SSL_R_UNEXPECTED_MESSAGE                                244
#define SSL_R_UNEXPECTED_RECORD                                 245
#define SSL_R_UNINITIALIZED                                     276
#define SSL_R_UNKNOWN_ALERT_TYPE                                246
#define SSL_R_UNKNOWN_CERTIFICATE_TYPE                          247
#define SSL_R_UNKNOWN_CIPHER_RETURNED                           248
#define SSL_R_UNKNOWN_CIPHER_TYPE                               249
#define SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE                         250
#define SSL_R_UNKNOWN_PKEY_TYPE                                 251
#define SSL_R_UNKNOWN_PROTOCOL                                  252
#define SSL_R_UNKNOWN_REMOTE_ERROR_TYPE                         253
#define SSL_R_UNKNOWN_SSL_VERSION                               254
#define SSL_R_UNKNOWN_STATE                                     255
#define SSL_R_UNSUPPORTED_CIPHER                                256
#define SSL_R_UNSUPPORTED_COMPRESSION_ALGORITHM                 257
#define SSL_R_UNSUPPORTED_ELLIPTIC_CURVE                        1118
#define SSL_R_UNSUPPORTED_OPTION                                1091
#define SSL_R_UNSUPPORTED_PROTOCOL                              258
#define SSL_R_UNSUPPORTED_SSL_VERSION                           259
#define SSL_R_UNABLE_TO_WRITE_TO_SOCKET                         260
#define SSL_R_WRONG_CIPHER_RETURNED                             261
#define SSL_R_WRONG_MESSAGE_TYPE                                262
#define SSL_R_WRONG_NUMBER_OF_KEY_BITS                          263
#define SSL_R_WRONG_SIGNATURE_LENGTH                            264
#define SSL_R_WRONG_SIGNATURE_SIZE                              265
#define SSL_R_WRONG_SSL_VERSION                                 266
#define SSL_R_WRONG_VERSION_NUMBER                              267
#define SSL_R_X509_LIB                                          268
#define SSL_R_X509_VERIFICATION_SETUP_PROBLEMS                  269

#ifndef SSL_NO_TLSEXT
/* Added for TLS Extensions*/
#define SSL_R_TLSV1_ALERT_UNSUPPORTED_EXTENSION                 1110
#define SSL_R_TLSV1_ALERT_CERTIFICATE_UNOBTAINABLE              1111
#define SSL_R_TLSV1_ALERT_UNRECOGNIZED_NAME                     1112
#define SSL_R_TLSV1_ALERT_BAD_CERTIFICATE_STATUS_RESPONSE       1113
#define SSL_R_TLSV1_ALERT_BAD_CERTIFICATE_HASH_VALUE            1114

#define SSL_R_ADD_SERVER_NAME_EXTN                              3005
#define SSL_R_ADD_MAX_FRAG_LEN_EXTN                             3006
#define SSL_R_ADD_TRUSTED_CA_EXTN                               3007
#define SSL_R_ADD_STATUS_REQ_EXTN                               3008
#define SSL_R_ENCODE_CERT_URL_LIST                              3009
#define SSL_R_DECODE_SERVER_NAME_EXTN_ERR                       3010
#define SSL_R_INVALID_MAX_FRAG_LEN                              3011
#define SSL_R_DECODE_TRUSTED_CA_EXTN_ERR                        3012
#define SSL_R_DECODE_STATUS_REQ_EXTN_ERR                        3013
#define SSL_R_DECODE_CERT_URL_MESSAGE                           3014
#define SSL_R_UNACCEPTED_MANDATORY_EXTN                         3015
#define SSL_R_UNABLE_TO_DECODE_CERT_STATUS                      3016
#define SSL_R_EXTENSION_DATA_EMPTY                              3017
#define SSL_R_UNSUPPORTED_STATUS_REQ_TYPE                       3018
#define SSL_R_CALLBACK_NOT_DEFINED                              3019

#define SSL_R_INVALID_CAIDENTIFIER_TYPE                         3020
#define SSL_R_LIST_OPERATION_FAILED                             3022
#define SSL_R_INVALID_CERTCHAIN_TYPE                            3023
#define SSL_R_INVALID_STATUS_REQ_TYPE                           3024
#define SSL_R_INVALID_STATUS_RESP_TYPE                          3025

#define SSL_R_URL_LIST_TYPE_ERROR                               3026
#define SSL_R_DECODE_CERT_ERROR                                 3027
#define SSL_R_DECODE_CERT_CHAIN_ERROR                           3028
#define SSL_R_NO_EXTN_SUPPORT_FOR_SESSION                       3029
#define SSL_R_NO_EXTN_SUPPORT_FOR_SSL                           3030
#endif
#define SSL_R_INVALID_INPUT_PARAMETER                           3021

#if  (!defined(SSL_NO_PSK) || !defined(SSL_NO_DH_PSK))
#define SSL_R_TLSV1_ALERT_PSK_UNKNOWN_PSK_IDENTITY              1115
#define SSL_R_PSK_NO_CALLBACK_FUNCTION_FOR_GETPSKBYPSKID        556
#define SSL_R_PSK_INFO_NOT_CORRECT                              557
#define SSL_R_PSK_DECODE_HANDSHAKE_MESSAGE_IS_WRONG             558
#define SSL_R_BAD_PSK_IDENTITY_HINT_LENGTH                      559
#define SSL_R_PSK_NO_CLIENT_CB                                  560
#define SSL_R_PSK_IDENTITY_NOT_FOUND                            561
#endif

//New error codes added for SSL_ctxLoadCACertificateFile Function
#define SSL_R_BAD_CA_CERT                                       281
#define SSL_R_EXISTING_CA_CERT                                  282

//New error codes added for SSL_ctxLoadCRL Function
#define SSL_R_BAD_CRL                                           283
#define SSL_R_EXISTING_CRL                                      284
                                                                             
#define SSL_R_GET_CERT_FROM_PFXSTORE_ERROR                             285
#define SSL_R_GET_PRIVKEY_FROM_PFXSTORE_ERROR                       286

//New error codes added for SSL_ctxLoadCRL Function(Addition of Updated CRL)
#define SSL_R_NEWER_CRL_EXISTS                                  287
#define SSL_R_DATE_CMP_FAILED                                   288
#define SSL_R_INTERNAL_ERROR                                    289

//Error Codes added for the function SSL_ctxRemoveTrustedCA,
//SSL_ctxRemoveCrl and SSL_ctxRemoveCrossCA
#define SSL_R_TRUST_CA_CERT_NOT_FOUND                             290
#define SSL_R_CRL_CERT_NOT_FOUND                                       291

// Error code for retrive all crl , CA , cross CA
#define SSL_R_EMPTY_CRL_STORE                                      292
#define SSL_R_EMPTY_CA_STORE                                       293
#define SSL_R_EMPTY_CROSS_CA_STORE                                 294

#define SSL_R_CROSS_CA_CERT_NOT_FOUND                             295

#define SSL_R_CTX_NO_CERT_LOADED                                  296
#define SSL_R_OBJ_NO_CERT_LOADED                                  297


//Added error codes for load cross CA
#define SSL_R_GET_CERT_LIST_FAILED                              298
#define SSL_R_CREAT_EXTND_CERT_FAILED                          299
#define SSL_R_UNSUPPORTED_KEY_SIZE                              300

#ifndef IPSI_SSL_NO_DTLS
#define SSL_R_AIO_NOT_SET                                       301
#define SSL_R_APP_DATA_GT_MTU                               302
#define SSL_R_GEN_COOKIE_FAIL                                  303
#define SSL_R_READ_TIMEOUT_EXPIRED                              304
#define SSL_R_RETRANSMISSION_FAILED                              305
#define SSL_R_START_TIMER_FAILED                              306
#define SSL_R_IPSI_CLOCK_FAILED 307
#endif

#define SSL_R_SCSV_RECEIVED_WHEN_RENEGOTIATING                   308
#define SSL_R_NO_RENEGOTIATION                                   309
#define SSL_R_RENEGOTIATE_EXT_TOO_LONG                           310
#define SSL_R_RENEGOTIATION_ENCODING_ERR                         311
#define SSL_R_RENEGOTIATION_MISMATCH                             312
#define SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED               313
#define SSL_R_HANDSHAKE_DISABLED_FOR_LEGACY_SERVER_BY_CLIENT     314
#define SSL_R_HANDSHAKE_DISABLED_FOR_LEGACY_CLIENT_BY_SERVER     315

#define SSL_R_UNABLE_TO_EXTRACT_EXTND_CERT          316
#define SSL_R_UNABLE_TO_EXTRACT_PKEY                        317
#define SSL_R_CERT_KEY_MISMATCH                                 318
#define SSL_R_READ_BUF_FROM_FILE_FAILED                 319
#define SSL_R_EXT_CERT_CHAIN_BUILD_FAILED              320
#define SSL_R_READ_CERT_FROM_BUF_FAILED                 321
#define SSL_R_UNABLE_TO_RETRIEVE_FROM_LIST               322



#define SSL_R_IPSI_CTX_NEW_FAILED							323
#define SSL_R_IPSI_DUP_CIPHER_LIST_FAILED					324
#define SSL_R_IPSI_DUP_CERT_STORE_FAILED					325
#define SSL_R_IPSI_DUP_SESSION_FAILED						326
#define SSL_R_IPSI_DUP_EXTRA_CERT_LIST_FAILED				327
#define SSL_R_IPSI_DUP_CA_NAME_LIST_FAILED					328
#define SSL_R_IPSI_DUP_TLS_EXT_FAILED						329
#define SSL_R_IPSI_DUP_DFLT_PSWD_FAILED						330
#define SSL_R_IPSI_DUP_CERT_FAILED							331
#define SSL_R_IPSI_DUP_PSK_HINT_FAILED						332

#define SSL_R_EXPIRED_CRL						            333

#define SSL_R_CLIENT_VERIFY_DATA_MISMATCH                   334
#define SSL_R_SERVER_VERIFY_DATA_MISMATCH                   335

#ifndef IPSI_NO_TLS12

#define SSL_R_UNSUPPORTED_SIGN_HASH_EXTNS                   336

#define SSL_R_UNKNOWN_DIGEST                                337
#define SSL_R_SIGNATURE_ALGORITHMS_ERROR                    338
#define SSL_R_SERVER_DHKEY_VERIFICATION_FAILURE             339

#endif

#define SSL_R_NOT_A_X509_V3_CA_CERTIFICATE                  340
#define SSL_R_IPSI_MULTIPLE_SGC_RESTARTS                    346

#define SSL_R_IPSI_RENEGOTIATION_REJECTED                   347
#define SSL_R_IPSI_UNEXPECTED_SOCKET_BEHAVIOUR              349
#define SSL_R_ILLEGAL_EXPORTER_LABEL                    350




#ifndef SSL_NO_PSK

/*
    Func Name:   IPSI_SSL_setPskIdentityHint
*/
/**
* @defgroup IPSI_SSL_setPskIdentityHint
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_setPskIdentityHint(SSL_S *pstSSL,
*                               const SEC_UCHAR *identityHint,
*                               SEC_UINT hintLen);
* @endcode
*
* @par Purpose
* This is used to set PSK Identity hint to SSL object.
*
* @par Description
* IPSI_SSL_setPskIdentityHint function sets PSK Identity hint to SSL object.
*
* @param[in] pstSSL SSL object to which hint to be set [N/A]
* @param[in] identityHint Hint value to be set [N/A]
* @param[in] hintLen Hint length
*
* @retval SEC_INT If success [TLS_SUCCESS|N/A]
* @retval SEC_INT If input is invalid (NULL parameters) [SEC_ERROR|N/A]
* @retval SEC_INT If internal error happened [SEC_NULL|N/A]
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* N/A
* 
* @par Related Topics
*/

SSLLINKDLL SEC_INT IPSI_SSL_setPskIdentityHint(SSL_S *pstSSL,
                                const SEC_UCHAR *identityHint,
                                SEC_UINT hintLen);

#endif


#ifndef IPSI_SSL_NO_DTLS

/*
    Func Name:   ipsi_dtlsv1_handle_timeout
*/
/**
* @defgroup ipsi_dtlsv1_handle_timeout
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT ipsi_dtlsv1_handle_timeout(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This is used to handle timeout for DTLS functionalities. This function will retransmitt the previous handshake 
* flight messages if internal timer expired. This API should not be used if SSL_MODE_DTLS_EXTERNAL_TIMER
* mode is set, if its used it will return SEC_NULL without doing anything.
*
* @par Description
* ipsi_dtlsv1_handle_timeout function performs retransmission if timer is expired.
*
* @param[in] pstSSL SSL object [N/A]
*
* @retval SEC_INT If success [TLS_SUCCESS|N/A]
* @retval SEC_INT If input is invalid (NULL parameters) [SEC_ERROR|N/A]
* @retval SEC_INT If internal error happened [SEC_NULL|N/A]
* @par Required Header File
* ssl.h
*
* @par Note
* This API is deprecated and it is not supported to use by application. As for DTLS connection with blocking socket,
* internal timer can take care of retransmission. And for DTLS connection with nonblocking socket 
* ipsi_dtls1_retransmit_buffered_messages() can take care it.
* N/A
* 
* @par Related Topics
*/


SSLLINKDLL SEC_INT ipsi_dtlsv1_handle_timeout(SSL_S *pstSSL);




/*
    Func Name:   ipsi_dtls1_retransmit_buffered_messages
*/

/**
* @defgroup ipsi_dtls1_retransmit_buffered_messages
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT ipsi_dtls1_retransmit_buffered_messages(SSL_S *s);
* @endcode
*
* @par Purpose
* This is used to retransmitt previous handshake messages if user is running DTLS on nonblocking UDP socket layer. 
* This should not be used for blocking socket.
*
* @par Description
* ipsi_dtls1_retransmit_buffered_messages retransmitts previous handshake messages without checking internal timer,
* as this API is used only if external timer is used in application with nonblocking UDP socket. If this API is used
* with blocking socket then it may send some previous handshake messages (if its buffered earlier) which may flood the
* peer entity with unwanted old messages.
*
* @param[in] pstSSL SSL object [N/A]
*
* @retval long * If retransmission of previous handshake messages succeeded [TLS_SUCCESS|N/A]
* @retval long * If any failure in retransmission or invalid input parameter [SEC_ERROR|N/A]
* @par Required Header File
* ssl.h
*
* @par Note
* 1. If this API returns SEC_ERROR, SSL_getError needs to be called to check whether non block error happened for 
* write. If so then user has to handle it with select() system call and call this API again.\n
* 2. This API returns TLS_SUCCESS if retransmission succeeds for buffered previous handshake messages.\n
* 3. This API returns TLS_SUCCESS even if there is no message available in buffer to retransmit.\n
* 
* @par Related Topics
*/

SSLLINKDLL SEC_INT ipsi_dtls1_retransmit_buffered_messages(SSL_S *s);

#endif

#ifndef __IPSI_VISP_RELEASE__

/*
    Func Name:   IPSI_SSL_ctxDup
*/
/**
* @defgroup IPSI_SSL_ctxDup
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SSL_CTX_S* IPSI_SSL_ctxDup(SSL_CTX_S *pstCtx);
* @endcode
*
* @par Purpose
* This function is used to clone the ssl context and return the same to user.
* \n
*
* @par Description
* IPSI_SSL_ctxDup makes a copy of input SSL context and returns the new context 
* to the application. \n
* - This function should not be called inside multithreading \n
* - This function should be used only before connection \n
* - This function should not be used incase of SSL version 2 \n
* - Session related informations (including session id context) are not copied
* \n
*
* @param[in] pstCtx Pointer to SSL context [N/A]
*
* @retval SSL_CTX_S* If success [Pointer to the SSL context|N/A]
* @retval SSL_CTX_S* If input is invalid [SEC_NULL|N/A]
* @retval SSL_CTX_S* If internal error happened [SEC_NULL|N/A]
* @par Required Header File
* ssl.h
*
* @par Note
* \n
* 1.  Clone context will refer to the same application data which
*     is referred by orignal context.\n
* 2.  The number of connections, references, and other statistical data will
*     reset to initial value.\n
*
* @par Related Topics
* N/A
*/

SSLLINKDLL SSL_CTX_S *IPSI_SSL_ctxDup(SSL_CTX_S *pstCtx);

#endif //__IPSI_VISP_RELEASE__


/*
    Func Name:   SEC_getSSLVersion
*/
/**
* @defgroup SEC_getSSLVersion
* @ingroup sslFunctions
* @par Prototype
* @code
* SEC_CHAR* SEC_getSSLVersion();
* @endcode
*
* @par Purpose
* This function is used to get the release version of SSL library.
*
* @par Description
* SEC_getSSLVersion used to get the release version of SSL library.
* @param[in] N/A N/A [N/A]
* @param[out] N/A N/A [N/A]
*
* @retval SEC_CHAR* The version of SSL library [SEC_CHAR*|N/A]
* @par Required Header File
* ssl.h
*
* @par Note
*
* N/A
*
* @par Related Topics
* N/A
*/
SSLLINKDLL SEC_CHAR* SEC_getSSLVersion(SEC_VOID);

#ifndef IPSI_NO_TLS12

/*
    Func Name:  SSL_ctxSetTLS12Extns
*/

/**
* @defgroup SSL_ctxSetTLS12Extns
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT SSL_ctxSetTLS12Extns(SSL_CTX_S *pstCtx, TLS_EXTNS_MODE_E eMode,
*                                            SEC_UINT uiExtension);
* @endcode
*
* @par Purpose
* This function is used to set or append the TLS extensions at SSL_CTX_S level,
* that needs to be supported by TLS clients.
* @par Description
* SSL_ctxSetTLS12Extns function is used to set or append the TLS extensions at 
* SSL_CTX_S level, that needs to be supported by TLS clients. These extensions
* will be used only for TLS1.2 Client. And for other TLS versions these extensions
* will be ignored.
* \n \n
* TLS_SIGN_HASH_EXTN extension is supported by this API.
* \n \n
* By default, this extension will be enabled in TLS1.2 context.
* \n \n
* Whenever a new SSL_S object is created for that application, this extension
* value is copied in to the SSL_S level structure. If user wants to update 
* the default extension level value for some SSL_S objects, user can do it
* by calling SSL_setTLS12Extns function.
* \n \n
* If user wants to reset all the TLS 1.2 extensions supported by this API,
* user should pass 0 as extension value and mode as TLS_SET_EXTENSION.
* \n \n
* @param[in] pstCtx Pointer to SSL context.[NA/NA]
* @param[in] eMode Indicates whether to append the extension or overwrite the
* existing value.[NA/NA]
* @param[in] uiExtension TLS extension required to set, as TLS_SIGN_HASH_EXTN 
* [NA/NA]
*
* @retval SEC_INT In all the cases except invalid input. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
*
* @par Required Header File
* \n
* ssl.h
*
* @par Note
* \n
*   - By Default this extension is enabled.
*
* @par Related Topics
* SSL_setTLS12Extns \n
*/

SSLLINKDLL SEC_INT SSL_ctxSetTLS12Extns(SSL_CTX_S *pstCtx,
                                            TLS_EXTNS_MODE_E eMode,
                                            SEC_UINT uiExtension);


/*
    Func Name:  SSL_setTLS12Extns
*/

/**
* @defgroup SSL_setTLS12Extns
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT SSL_setTLS12Extns(SSL_S *pstSSL, TLS_EXTNS_MODE_E eMode,
*                                           SEC_UINT uiExtension);
* @endcode
*
* @par Purpose
* This function is used to set or append the TLS extensions at SSL_S level,
* that needs to be supported by TLS clients.
* @par Description
* SSL_setTLS12Extns function is used to set or append the TLS extensions at 
* SSL_S level, that needs to be supported by TLS clients. These extensions
* will be used only for TLS1.2 Client. And for other TLS versions these extensions
* will be ignored.
* \n \n
* TLS_SIGN_HASH_EXTN extension is supported by this API.  
* \n \n
* By default, this extension will be enabled in TLS1.2 context.
* \n \n
* If the user wants to reset all the TLS 1.2 extensions supported by this API,
* user should pass 0 as extension value and mode as TLS_SET_EXTENSION.
* @param[in] pstSSL Pointer to SSL object.[NA/NA]
* @param[in] eMode Indicates whether to append the extension or overwrite the
* existing value.[NA/NA]
* @param[in]uiExtension TLS extension required to set, as TLS_SIGN_HASH_EXTN 
* @param[out] NA NA [NA/NA]
*
* @retval SEC_INT In all the cases except invalid input. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
*
* @par Required Header File
* \n
* ssl.h
*
* @par Related Topics
* SSL_ctxSetTLS12Extns \n
*/
SSLLINKDLL SEC_INT SSL_setTLS12Extns(SSL_S *pstSSL,
                                            TLS_EXTNS_MODE_E eMode,
                                            SEC_UINT uiExtension);

/*
    Func Name:  IPSI_SSL_ctxEnableTLS12
*/

/**
* @defgroup IPSI_SSL_ctxEnableTLS12
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxEnableTLS12(SSL_CTX_S *pstCtx);
* @endcode
*
* @par Purpose
* This function is used to enable the TLS1.2 version in SSL context.
* @par Description
* IPSI_SSL_ctxEnableTLS12 function is used to enable the TLS1.2 version
* while using SSL generic methods for SSL handshake. By default,
* in generic methods, TLS1.2 version will be disabled. The highest version
* supported in generic methods by default is TLS1.1.
* \n \n
* @param[in] pstCtx Pointer to SSL context.[NA/NA]
*
* @retval SEC_INT In all the cases except invalid input. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
*
* @par Required Header File
* \n
* ssl.h
*
* @par Related Topics
* IPSI_SSL_enableTLS12 \n
*/
SSLLINKDLL SEC_INT IPSI_SSL_ctxEnableTLS12(SSL_CTX_S *pstCtx);

/*
    Func Name:  IPSI_SSL_enableTLS12
*/

/**
* @defgroup IPSI_SSL_enableTLS12
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_enableTLS12(SSL_S *pstSSL);
* @endcode
*
* @par Purpose
* This function is used to enable the TLS1.2 version in SSL object.
* @par Description
* IPSI_SSL_enableTLS12 function is used to enable the TLS1.2 version
* while using SSL generic methods for SSL handshake. By default,
* in generic methods, TLS1.2 version will be disabled. The highest version
* supported in generic methods by default is TLS1.1
* \n \n
* If TLS1.2 is enabled in SSL context by using API IPSI_SSL_ctxEnableTLS12,
* then no need to call this API again to enable the TLS1.2 in SSL object
* unless the ulOptions are modified to disable TLS1.2 explicitly.
* @param[in] pstSSL Pointer to SSL object.[NA/NA]
*
* @retval SEC_INT In all the cases except invalid input. [TLS_SUCCESS|NA]
* @retval SEC_INT On invalid input. [SEC_ERROR|NA]
*
* @par Required Header File
* \n
* ssl.h
*
* @par Related Topics
* IPSI_SSL_ctxEnableTLS12 \n
*/
SSLLINKDLL SEC_INT IPSI_SSL_enableTLS12(SSL_S *pstSSL);


#endif //IPSI_NO_TLS12


/*
    Func Name:  IPSI_SSL_ctxSetRenegManageCallback
*/

/**
* @defgroup IPSI_SSL_ctxSetRenegManageCallback
* @ingroup sslContextFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_ctxSetRenegManageCallback(SSL_CTX_S *pstCtx, IPSI_SSL_RENEG_MANAG_CB pfCallback, 
*                                                                                               SEC_VOID *pvAppData);
* @endcode
*
* @par Purpose
* This function is used to set renegotiation management callback and its application data in context.
* @par Description
* This function is used to set renegotiation management callback and its application data in context.
* There will not be any NULL check for callback function pointer and application data.
* User can pass the valid pointer or NULL pointer for callback function and application data.
* \n \n
* @param[in] pstCtx Pointer to SSL context.[NA/NA]
*
* @retval SEC_INT In all the cases except invalid context. [TLS_SUCCESS|NA]
* @retval SEC_INT If invalid context is passed. [SEC_ERROR|NA]
*
* @par Required Header File
* \n
* ssl.h
*
* @par Note
* 1. IPSI_SSL_RENEG_MANAG_CB - This callback function has to return SEC_SUCCESS if user wants to allow the 
* renegotiation. Or else it has to return SSL_CTRL_BEHAV_NORENEG_FATAL or SSL_CTRL_BEHAV_NORENEG_WARN
* for rejecting renegotiation with fatal or warning alert. Any other value returns from this callback will be considered
* as SEC_SUCCESS only. But its strongly recommended to implement this callback by returning any of these 3 values
* because in future we will be expanding the usage of this callback function for some other feature also.\n
* 2. ACESSL doesn`t supports  SSL_CTRL_BEHAV_NORENEG_WARN, so if this callback function returns
* SSL_CTRL_BEHAV_NORENEG_WARN in ACESSL, then it treats this as SSL_CTRL_BEHAV_NORENEG_FATAL only.\n
* 3. SSLv3 RFC mandates to send only fatal alert for rejecting renegotiation. So if negotiated version is SSLv3 and 
* callback returns SSL_CTRL_BEHAV_NORENEG_WARN then renegotiation will be rejected with fatal alert. But
* other versions (TLS 1.0, TLS 1.1 and TLS 1.2) can send both warning and fatal alert. \n
* 4. SSL_CTRL_BEHAV_NORENEG_FATAL and SSL_CTRL_BEHAV_NORENEG_WARN can be set as control behaviour options also using
* SSL_SET_BEHAVIOUR_OPTIONS or SSL_CTX_SET_BEHAVIOUR_OPTIONS. If both control behaviour option and this callback are
* set then only callback will be considered, control behaviour option will not be considered.\n
*
* @par Related Topics
* IPSI_SSL_setRenegManageCallback \n
*/

SSLLINKDLL SEC_INT IPSI_SSL_ctxSetRenegManageCallback(SSL_CTX_S *pstCtx, IPSI_SSL_RENEG_MANAG_CB pfCallback,
                                                                                                SEC_VOID *pvAppData);

/**
* @defgroup IPSI_SSL_setRenegManageCallback
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_setRenegManageCallback(SSL_S *pstSSL, IPSI_SSL_RENEG_MANAG_CB pfCallback, SEC_VOID *pvAppData);
* @endcode
*
* @par Purpose
* This function is used to set renegotiation management callback and its application data in object.
* @par Description
* This function is used to set renegotiation management callback and its application data in object.
* There will not be any NULL check for callback function pointer and application data.
* User can pass the valid pointer or NULL pointer for callback function and application data.
* \n \n
* @param[in] pstSSL Pointer to SSL object.[NA/NA]
*
* @retval SEC_INT In all the cases except invalid object. [TLS_SUCCESS|NA]
* @retval SEC_INT If invalid object is passed. [SEC_ERROR|NA]
*
* @par Required Header File
* \n
* ssl.h
*
* @par Note
* 1. IPSI_SSL_RENEG_MANAG_CB - This callback function has to return SEC_SUCCESS if user wants to allow the 
* renegotiation. Or else it has to return SSL_CTRL_BEHAV_NORENEG_FATAL or SSL_CTRL_BEHAV_NORENEG_WARN
* for rejecting renegotiation with fatal or warning alert. Any other value returns from this callback will be considered
* as SEC_SUCCESS only. But its strongly recommended to implement this callback by returning any of these 3 values
* because in future we will be expanding the usage of this callback function for some other feature also.\n
* 2. ACESSL doesn`t supports  SSL_CTRL_BEHAV_NORENEG_WARN, so if this callback function returns
* SSL_CTRL_BEHAV_NORENEG_WARN in ACESSL, then it treats this as SSL_CTRL_BEHAV_NORENEG_FATAL only.\n
* 3. SSLv3 RFC mandates to send only fatal alert for rejecting renegotiation. So if negotiated version is SSLv3 and 
* callback returns SSL_CTRL_BEHAV_NORENEG_WARN then renegotiation will be rejected with fatal alert. But
* other versions (TLS 1.0, TLS 1.1 and TLS 1.2) can send both warning and fatal alert. \n
* 4. SSL_CTRL_BEHAV_NORENEG_FATAL and SSL_CTRL_BEHAV_NORENEG_WARN can be set as control behaviour options also using
* SSL_SET_BEHAVIOUR_OPTIONS or SSL_CTX_SET_BEHAVIOUR_OPTIONS. If both control behaviour option and this callback are
* set then only callback will be considered, control behaviour option will not be considered.\n
*
* @par Related Topics
* IPSI_SSL_ctxSetRenegManageCallback \n
*/

SSLLINKDLL SEC_INT IPSI_SSL_setRenegManageCallback(SSL_S *pstSSL, IPSI_SSL_RENEG_MANAG_CB pfCallback, 
                                                                                            SEC_VOID *pvAppData);




#define IPSI_INTEROP_TLS12_OPENSSLBUG_EXPKEYGEN             1


/**
* @defgroup IPSI_SSL_export_keying_material
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_INT IPSI_SSL_export_keying_material(SSL_S *pstSSL, SEC_UCHAR *out, SEC_INT outLen,
*                            const SEC_UCHAR *label, SEC_INT labelLen, const SEC_UCHAR *ctx, SEC_UINT ctxLen,
*                            SEC_UINT useCtx, SEC_UINT uiAppFlag);
* @endcode
*
* @par Purpose
* This function is used to generate export keying material from TLS master secret key with provided label string as
* per RFC 5705.
* @par Description
* This function is used to generate export keying material from TLS master secret key with provided label string.
* User can pass optional context by passing non-zero value to "useCtx" variable.
* \n \n
* @param[in] pstSSL Pointer to SSL object.[NA/NA]
* @param[in] label A disambiguating label string.[NA/NA]
* @param[in] labelLen Length of label string. Should be greater than zero[NA/NA]
* @param[in] ctx Optional context value.[NA/NA]
* @param[in] ctxLen Length of context value. Can be any non-negative value. Context length zero is also allowed[NA/NA]
* @param[in] useCtx Flag which indicates context value to be used for generation of keying material.
*                              It should be non-zero value.[NA/NA]
* @param[in] outLen Length indicating how much keying material length required. Should be greater than zero[NA/NA]
* @param[in] uiAppFlag Flag to indicate use TLS 1.0 PRF instead of TLS 1.2 PRF. OpenSSL has a bug which uses PRF
*                                  function based on TLS 1.0 for TLS 1.2 version also which is wrong as per RFC 5246.
*                                  So, to interoperate with such peers, this flag is provided. Should pass
*                                  IPSI_INTEROP_TLS12_OPENSSLBUG_EXPKEYGEN to this flag to interoperate
*                                  with buggy openSSL versions.
* @param[out] out Output buffer which holds the generated keying material.[NA/NA]
*
* @retval SEC_INT In success case. [TLS_SUCCESS|NA]
* @retval SEC_INT If invalid inputs passed or internal failures. [SEC_ERROR|NA]
*
* @par Required Header File
* \n
* ssl.h
*
* @par Note
* 1. This API should be called by users only after handshake (initial handshake, resumption, renegotiation) is finished successfully.\n
* 2. It is strictly not recommended to call this API when handshake (initial handshake, resumption, renegotiation) is in progress.\n
* 3. This API should not be called in multi-thread with the same SSL object.
* 4. The output buffer should be allocated by user based on the output length required. If output buffer is less than the required length passed
*     by user in "outLen" parameter, then it may lead to undefined behavior.
*
* @par Related Topics
* NA \n
*/

SSLLINKDLL SEC_INT IPSI_SSL_export_keying_material(SSL_S *pstSSL, SEC_UCHAR *out, SEC_INT outLen,
                            const SEC_UCHAR *label, SEC_INT labelLen, const SEC_UCHAR *ctx, SEC_UINT ctxLen,
                            SEC_UINT useCtx, SEC_UINT uiAppFlag);


/*
    Func Name:  SSL_getCurrentCipherID
*/

/**
* @defgroup SSL_getCurrentCipherID
* @ingroup sslObjectFunctions
* @par Prototype
* @code
* SEC_UINT32 SSL_getCurrentCipherID(const SSL_S *pstSSL);
* @endcode
* 
* @par Purpose
* This is used to get the cipher ID negotiated in the TLS handshake process.
* 
* @par Description
* SSL_getCurrentCipherID function returns cipher ID which has been negotiated in the TLS handshake process.
* 
* @param[in] pstSSL Pointer to SSL_S object. [N/A]
* 
* @retval SEC_UINT32 On successful execution , cipher ID negotiated [NA|NA]
* @retval SEC_UINT32 On failure conditions [SEC_NULL|NA]
*
* @par Required Header File
* ssl.h
*
* @par Note
* 1. This API should be called by users only after handshake (initial handshake, resumption, renegotiation) is finished successfully.\n
* 2. It is strictly not recommended to call this API when handshake (initial handshake, resumption, renegotiation) is in progress.\n
* 3. This API should not be called in multi-thread with the same SSL object.
* 
* @par Related Topics
* SSL_getCurrentCipher.
*/
SSLLINKDLL SEC_UINT32 SSL_getCurrentCipherID(const SSL_S *pstSSL);


#ifdef  __cplusplus
}
#endif
#endif


