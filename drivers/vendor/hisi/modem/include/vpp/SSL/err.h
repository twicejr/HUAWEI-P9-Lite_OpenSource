/* crypto/err/err.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
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

#include "ipsi_ssl_build_conf.h"

#ifndef _IPSI_HEADER_ERR_H
#define _IPSI_HEADER_ERR_H

#include "ipsi_types.h"
#include "sec_sys.h"
#include "sec_def.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define ERR_free_strings IPSI_ERR_free_strings
#define ERR_error_string_n IPSI_ERR_error_string_n
#define ERR_clear_error IPSI_ERR_clear_error
#define ERR_func_error_string IPSI_ERR_func_error_string
#define ERR_lib_error_string IPSI_ERR_lib_error_string
#define ERR_get_error_line IPSI_ERR_get_error_line
#define ERR_peek_error IPSI_ERR_peek_error
#define ERR_peek_error_line IPSI_ERR_peek_error_line
#define ERR_peek_last_error_line IPSI_ERR_peek_last_error_line
#define ERR_peek_last_error IPSI_ERR_peek_last_error
#define ERR_reason_error_string IPSI_ERR_reason_error_string

/* library */
#define ERR_LIB_NONE		1
#define ERR_LIB_SYS		2
#define ERR_LIB_BN		3
#define ERR_LIB_RSA		4
#define ERR_LIB_DH		5
#define ERR_LIB_EVP		6
#define ERR_LIB_BUF		7
#define ERR_LIB_OBJ		8
#define ERR_LIB_PEM		9
#define ERR_LIB_DSA		10
#define ERR_LIB_X509		11
#define ERR_LIB_ASN1		13
#define ERR_LIB_CONF		14
#define ERR_LIB_CRYPTO		15
#define ERR_LIB_EC		16
#define ERR_LIB_SSL		20
#define ERR_LIB_PKCS7		33
#define ERR_LIB_X509V3		34
#define ERR_LIB_PKCS12		35
#define ERR_LIB_RAND		36
#define ERR_LIB_DSO		37
#define ERR_LIB_ENGINE		38
#define ERR_LIB_OCSP            39
#define ERR_LIB_UI              40
#define ERR_LIB_COMP            41
#define ERR_LIB_ECDSA		42
#define ERR_LIB_ECDH		43
#define ERR_LIB_STORE           44
#define ERR_LIB_PFX         45

#define ERR_LIB_USER		128


/* reasons */
#define ERR_R_SYS_LIB	ERR_LIB_SYS       /* 2 */
#define ERR_R_BN_LIB	ERR_LIB_BN        /* 3 */
#define ERR_R_RSA_LIB	ERR_LIB_RSA       /* 4 */
#define ERR_R_DH_LIB	ERR_LIB_DH        /* 5 */
#define ERR_R_EVP_LIB	ERR_LIB_EVP       /* 6 */
#define ERR_R_BUF_LIB	ERR_LIB_BUF       /* 7 */
#define ERR_R_OBJ_LIB	ERR_LIB_OBJ       /* 8 */
#define ERR_R_PEM_LIB	ERR_LIB_PEM       /* 9 */
#define ERR_R_DSA_LIB	ERR_LIB_DSA      /* 10 */
#define ERR_R_X509_LIB	ERR_LIB_X509     /* 11 */
#define ERR_R_ASN1_LIB	ERR_LIB_ASN1     /* 13 */
#define ERR_R_CONF_LIB	ERR_LIB_CONF     /* 14 */
#define ERR_R_CRYPTO_LIB ERR_LIB_CRYPTO  /* 15 */
#define ERR_R_EC_LIB	ERR_LIB_EC       /* 16 */
#define ERR_R_SSL_LIB	ERR_LIB_SSL      /* 20 */
#define ERR_R_PKCS7_LIB	ERR_LIB_PKCS7    /* 33 */
#define ERR_R_X509V3_LIB ERR_LIB_X509V3  /* 34 */
#define ERR_R_PKCS12_LIB ERR_LIB_PKCS12  /* 35 */
#define ERR_R_RAND_LIB	ERR_LIB_RAND     /* 36 */
#define ERR_R_DSO_LIB	ERR_LIB_DSO      /* 37 */
#define ERR_R_ENGINE_LIB ERR_LIB_ENGINE  /* 38 */
#define ERR_R_OCSP_LIB  ERR_LIB_OCSP     /* 39 */
#define ERR_R_UI_LIB    ERR_LIB_UI       /* 40 */
#define ERR_R_COMP_LIB	ERR_LIB_COMP     /* 41 */
#define ERR_R_ECDSA_LIB ERR_LIB_ECDSA	 /* 42 */
#define ERR_R_ECDH_LIB  ERR_LIB_ECDH	 /* 43 */
#define ERR_R_STORE_LIB ERR_LIB_STORE    /* 44 */
#define ERR_R_PFX_LIB   ERR_LIB_PFX     /* 45 */

#define ERR_R_NESTED_ASN1_ERROR			58
#define ERR_R_BAD_ASN1_OBJECT_HEADER		59
#define ERR_R_BAD_GET_ASN1_OBJECT_CALL		60
#define ERR_R_EXPECTING_AN_ASN1_SEQUENCE	61
#define ERR_R_ASN1_LENGTH_MISMATCH		62
#define ERR_R_MISSING_ASN1_EOS			63

/* fatal error */
#define ERR_R_FATAL				64
#define	ERR_R_MALLOC_FAILURE			(1|ERR_R_FATAL)
#define	ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED	(2|ERR_R_FATAL)
#define	ERR_R_PASSED_NULL_PARAMETER		(3|ERR_R_FATAL)
#define	ERR_R_INTERNAL_ERROR			(4|ERR_R_FATAL)
#define	ERR_R_DISABLED				(5|ERR_R_FATAL)

/* 99 is the maximum possible ERR_R_... code, higher values
 * are reserved for the individual libraries */

//#defines to solve the iMAP problem - Start
#define ERR_get_error IPSI_ERR_get_error
//#defines to solve the iMAP problem - End 

/*ERR_GET_LIB can used to extract library code in which error occurred from the error code*/
#define ERR_GET_LIB(l)		(SEC_INT)((((SEC_UINT32)l)>>24L)&0xffL)
/*ERR_GET_LIB can used to extract function code in which error occurred from the error code*/
#define ERR_GET_FUNC(l)		(SEC_INT)((((SEC_UINT32)l)>>12L)&0xfffL)
/*ERR_GET_LIB can used to extract reason code of the respective error code*/
#define ERR_GET_REASON(l)	(SEC_INT)((l)&0xfffL)

/**
* @defgroup err
* This section contains the Functions of err.h.
*/

/** 
* @defgroup errFunctions
* @ingroup err
* This section contains the Functions of err.h.
*/

/*
    Func Name: ERR_get_error                                                 
*/

/**
* @defgroup ERR_get_error
* @ingroup errFunctions
* @par Prototype
* @code
* SEC_UINT32 ERR_get_error(SEC_VOID);
* @endcode
* 
* @par Purpose
* To get the earliest error code.
*
* @par Description
* This function returns the earliest error code from the thread's error queue and removes the entry.
* This function can be called repeatedly until there are no more error codes to return.
*
* @par Parameters
* N/A
*
* @retval SEC_UINT32 Error code is returned if there is error in queue. [Error Code|N/A]
* @retval SEC_UINT32 0 is returned if there is no error in the queue. [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* Error Code returned by this API is different from the error reason returned by SSL_getLastError function. From the error code,
* the error reason can be obtained by using ERR_GET_REASON macro. It is equal to SSL_getLastError function.
*
* @par Related Topics
* SSL_getLastError.
* 
*/	
SSLLINKDLL SEC_UINT32 ERR_get_error(SEC_VOID);

/*
    Func Name: ERR_get_error_line
*/

/**
* @defgroup ERR_get_error_line
* @ingroup errFunctions
* @par Prototype
* @code
* SEC_UINT32 ERR_get_error_line(const SEC_CHAR **file,SEC_INT *line);
* @endcode
* 
* @par Purpose
* To get the earliest error code along  with line number and file name.
*
* @par Description
* This function returns the earliest error code from the thread's error queue and removes the entry. This function also 
* additionally stores the file name and line number where the error occurred in *file and *line, unless these are NULL.
* This function can be called repeatedly until there are no more error codes to return.
* 
* @param[out]  file File in which the error has occurred. [N/A]
* @param[out]  line Line number in the file where the error has occurred. [N/A]
*
* @retval SEC_UINT32 Error code is returned if there is error in queue. [Error Code|N/A]
* @retval SEC_UINT32 0 is returned if there is no error in the queue. [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/	
SSLLINKDLL SEC_UINT32 ERR_get_error_line(const SEC_CHAR **file,SEC_INT *line);

/*
    Func Name: ERR_peek_error                                                 
*/

/**
* @defgroup ERR_peek_error
* @ingroup errFunctions
* @par Prototype
* @code
* SEC_UINT32 ERR_peek_error(SEC_VOID);
* @endcode
* 
* @par Purpose
* To peek at the earliest error code.
*
* @par Description
* This function returns the earliest error code from the thread's error queue without removing the entry.
*
* @par Parameters
* N/A
*
* @retval SEC_UINT32 Error code is returned if there is error in queue. [Error Code|N/A]
* @retval SEC_UINT32 0 is returned if there is no error in the queue. [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* Error code returned by this API is different from the error reason code returned by SSL_peekLastError function.
* From the error code, the error reason can be obtained by using ERR_GET_REASON macro. It is equal to SSL_peekLastError
* function.
*
* @par Related Topics
* SSL_peekLastError.
*/	
SSLLINKDLL SEC_UINT32 ERR_peek_error(SEC_VOID);

/*
    Func Name: ERR_peek_error_line                                                 
*/

/**
* @defgroup ERR_peek_error_line
* @ingroup errFunctions
* @par Prototype
* @code
* SEC_UINT32 ERR_peek_error_line(const char **file,int *line);
* @endcode
* 
* @par Purpose
* To peek at the earliest error code along with the file name and line number.
*
* @par Description
* This function returns the earliest error code from the thread's error queue without removing the entry. This function
* also additionally stores the file name and line number where the error occurred, in file and line, unless these are NULL.
*
* @param[out] file File in which the error has occurred. [N/A]
* @param[out] line Line number in the file where the error has occurred. [N/A]
*
* @retval SEC_UINT32 Error code is returned if there is error in queue. [Error Code|N/A]
* @retval SEC_UINT32 0 is returned if there is no error in the queue. [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/	
SSLLINKDLL SEC_UINT32 ERR_peek_error_line(const SEC_CHAR **file,SEC_INT *line);

/*
    Func Name: ERR_peek_last_error                                                 
*/

/**
* @defgroup ERR_peek_last_error
* @ingroup errFunctions
* @par Prototype
* @code
* SEC_UINT32 ERR_peek_last_error(SEC_VOID);
* @endcode
* 
* @par Purpose
* To get the latest error code.
*
* @par Description
* This function returns the latest error code from the thread's error queue without removing the entry.
*
* @par parameters
* N/A
*
* @retval SEC_UINT32 Error code is returned if there is error in queue. [Error Code|N/A]
* @retval SEC_UINT32 0 is returned if there is no error in the queue. [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/	
SSLLINKDLL SEC_UINT32 ERR_peek_last_error(SEC_VOID);

/*
    Func Name: ERR_peek_last_error_line                                                 
*/

/**
* @defgroup ERR_peek_last_error_line
* @ingroup errFunctions
* @par Prototype
* @code
* SEC_UINT32 ERR_peek_last_error_line(const SEC_CHAR **file,SEC_INT *line);
* @endcode
* 
* @par Purpose
* To get the latest error code along with the file name and the line number.
*
* @par Description
* This function returns the latest error code from the thread's error queue without removing the entry. This function also 
* additionally stores the file name and line number where the error occurred, in file and line, unless these are NULL.
*
* @param[out] file File in which the error has occurred. [N/A]
* @param[out] line Line number in the file where the error has occurred. [N/A]
* 
* @retval SEC_UINT32 Error code is returned if there is error in queue. [Error Code|N/A]
* @retval SEC_UINT32 0 is returned if there is no error in the queue. [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/
SSLLINKDLL SEC_UINT32 ERR_peek_last_error_line(const SEC_CHAR **file,SEC_INT *line);

/*
    Func Name: ERR_error_string_n                                                 
*/

/**
* @defgroup ERR_error_string_n
* @ingroup errFunctions
* @par Prototype
* @code
* void ERR_error_string_n(SEC_UINT32 e, SEC_CHAR *buf, SEC_UINT len);
* @endcode
* 
* @par Purpose
* To get human-readable error string.
*
* @par Description
* This function generates a human-readable string representing the error code e, and places it at buf.
* This function writes at most "len" characters (including the terminating 0) and truncates the string if necessary.
* 
* @param[in] e The error code. [N/A]
* @param[in] len The max length written to the buf. [N/A]
* @param[out] buf The buffer in which error string is copied. [N/A]
*
* @retval void This function does not return any value [N/A|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* If Error string can not be found for the error code, the string in the buf will be:\n
* "error: error code:lib(lib code):func(func code):reason(reason code)"
*
* @par Related Topics
* N/A
*/
SSLLINKDLL void ERR_error_string_n(SEC_UINT32 e, SEC_CHAR *buf, SEC_UINT len);

/*
    Func Name: ERR_lib_error_string                                                 
*/

/**
* @defgroup ERR_lib_error_string
* @ingroup errFunctions
* @par Prototype
* @code
* const SEC_CHAR *ERR_lib_error_string(SEC_UINT32 e);
* @endcode
* 
* @par Purpose
* To return the library name.
*
* @par Description
* This function returns the library name where the error has occurred.
* 
* @param[in] e The error code. [N/A]
*
* @retval SEC_CHAR* Error string containing the library name is returned [Error string|N/A]
* @retval SEC_CHAR* If Error string can not be found for the error code [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/
SSLLINKDLL const SEC_CHAR *ERR_lib_error_string(SEC_UINT32 e);

/*
    Func Name: ERR_func_error_string                                                 
*/

/**
* @defgroup ERR_func_error_string
* @ingroup errFunctions
* @par Prototype
* @code
* const SEC_CHAR *ERR_func_error_string(SEC_UINT32 e);
* @endcode
* 
* @par Purpose
* To return function name.
*
* @par Description
* This function returns the function name of the corresponding error code.
* 
* @param[in] e The error code. [N/A]
*
* @retval SEC_CHAR* Error string containing the function name is returned. [Error string|N/A]
* @retval SEC_CHAR* If Error string can not be found for the error code [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/
SSLLINKDLL const SEC_CHAR *ERR_func_error_string(SEC_UINT32 e);

/*
    Func Name: ERR_reason_error_string                                                 
*/

/**
* @defgroup ERR_reason_error_string
* @ingroup errFunctions
* @par Prototype
* @code
* const SEC_CHAR *ERR_reason_error_string(SEC_UINT32 e);
* @endcode
* 
* @par Purpose
* To get the reason string.
*
* @par Description
* This function returns the reason string of the corresponding error code.
* 
* @param[in] e The error code. [N/A]
*
* @retval SEC_CHAR* Error string containing the reason is returned. [Error Code|N/A]
* @retval SEC_CHAR* If Error string can not be found for the error code [SEC_NULL|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/
SSLLINKDLL const SEC_CHAR *ERR_reason_error_string(SEC_UINT32 e);

/*
    Func Name: ERR_clear_error                                                 
*/

/**
* @defgroup ERR_clear_error
* @ingroup errFunctions
* @par Prototype
* @code
* void ERR_clear_error(void );
* @endcode
* 
* @par Purpose
* Clears the error queue.
*
* @par Description
* This function is used to empty the current thread's error queue.
*
* @par Parameters
* N/A
*
* @retval void This function does not return any value [N/A|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/
SSLLINKDLL void ERR_clear_error(void );

/*
    Func Name: ERR_free_strings                                                 
*/

/**
* @defgroup ERR_free_strings
* @ingroup errFunctions
* @par Prototype
* @code
* void ERR_free_strings(void);
* @endcode
* 
* @par Purpose
* Frees error strings.
*
* @par Description
* This function free all the previously loaded error strings.
*
* @par Parameters
* N/A
*
* @retval void This function does not return any value [N/A|N/A]
*
* @par Required Header File
* err.h
* 
* @par Note
* \n
* N/A
*
* @par Related Topics
* N/A
*/
SSLLINKDLL void ERR_free_strings(void);
#ifdef	__cplusplus
}
#endif

#endif // _IPSI_HEADER_ERR_H



