/*******************************************************************************
* Copyright @ Huawei Technologies Co., Ltd. 1998-2014. All rights reserved.  
* File name: securec.h
* Decription: 
*             the user of this secure c library should include this header file
*             in you source code. This header file declare all supported API
*             prototype of the library, such as memcpy_s, strcpy_s, wcscpy_s,
*             strcat_s, strncat_s, sprintf_s, scanf_s, and so on.
* History:   
*     1. Date: 
*         Author:  
*         Modification: 
********************************************************************************
*/

#ifndef __SECUREC_H__5D13A042_DC3F_4ED9_A8D1_882811274C27
#define __SECUREC_H__5D13A042_DC3F_4ED9_A8D1_882811274C27

#include "securectype.h"
#include <stdarg.h>

#ifndef errno_t
typedef int errno_t;
#endif

/* for performance consideration, the following macro will the corresponding API 
* of libC for memcpy, memmove and memset
*/
#define CALL_LIBC_COR_API
/*define error code*/

/* success */
#define EOK (0)

/* invalid parameter */
#ifdef EINVAL
#undef EINVAL
#endif
#define EINVAL (22)
#define EINVAL_AND_RESET (22 | 0X80)
/* invalid parameter range */
#ifdef ERANGE
#undef ERANGE  /* to avoid redefinition */
#endif
#define ERANGE (34)
#define ERANGE_AND_RESET  (34 | 0X80)

/* A wide-character code has been detected that does not correspond to a
* valid character, or a byte sequence does not form a valid wide-character code
*/
#ifdef EILSEQ
#undef EILSEQ
#endif
#define EILSEQ (42)

#ifdef EOVERLAP_AND_RESET
#undef EOVERLAP_AND_RESET
#endif
 /*Once the buffer overlap is detected, the dest buffer must be reseted! */
#define EOVERLAP_AND_RESET (54 | 0X80)

#ifdef __cplusplus
extern "C"
{
#endif

    /* memset */
    errno_t memset_s(void* dest, size_t destMax, int c, size_t count);

    /*
    memcpy
    */
    errno_t memcpy_s(void* dest, size_t destMax, const void* src, size_t count);

    errno_t wmemcpy_s(wchar_t* dest, size_t destMax, const wchar_t* src, size_t count);

    /*
    memmove
    */

    errno_t memmove_s(void* dest, size_t destMax, const void* src, size_t count);

    errno_t wmemmove_s(wchar_t* dest, size_t destMax, const wchar_t* src, size_t count);

    /* strcpy */
    errno_t strcpy_s(char* strDest, size_t destMax, const char* strSrc);

    errno_t wcscpy_s(wchar_t* strDest, size_t destMax, const wchar_t* strSrc);

    /* strncpy */
    errno_t strncpy_s(char* strDest, size_t destMax, const char* strSrc, size_t count);

    errno_t wcsncpy_s(wchar_t* strDest, size_t destMax, const wchar_t* strSrc, size_t count);

    /* strcat */
    errno_t strcat_s(char* strDest, size_t destMax, const char* strSrc);

    errno_t wcscat_s(wchar_t* strDest, size_t destMax, const wchar_t* strSrc);

    /* strncat */
    errno_t strncat_s(char* strDest, size_t destMax, const char* strSrc, size_t count);

    errno_t wcsncat_s(wchar_t* strDest, size_t destMax, const wchar_t* strSrc, size_t count);

    /* strtok */
    char* strtok_s(char* strToken, const char* strDelimit, char** context);

    wchar_t* wcstok_s(wchar_t* strToken, const wchar_t* strDelimit, wchar_t** context);

    /* sprintf */
    int sprintf_s(char* strDest, size_t destMax, const char* format, ...);

    int swprintf_s(wchar_t* strDest, size_t destMax, const wchar_t* format, ...);

    /* vsprintf */
    int vsprintf_s(char* strDest, size_t destMax, const char* format, va_list argptr);

    int vswprintf_s(wchar_t* strDest, size_t destMax, const wchar_t* format, va_list argptr);

    int vsnprintf_s(char* strDest, size_t destMax, size_t count, const char* format, va_list arglist);

    /* snprintf */
    int snprintf_s(char* strDest, size_t destMax, size_t count, const char* format, ...);

    /* scanf */
    int scanf_s(const char* format, ...);

    int wscanf_s(const wchar_t* format, ...);

    /* vscanf */
    int vscanf_s(const char* format, va_list arglist);

    int vwscanf_s(const wchar_t* format, va_list arglist);

    /* fscanf */
    int fscanf_s(FILE* stream, const char* format, ...);

    int fwscanf_s(FILE* stream, const wchar_t* format, ...);

    /* vfscanf */
    int vfscanf_s(FILE* stream, const char* format, va_list arglist);
    
    int vfwscanf_s(FILE* stream, const wchar_t* format, va_list arglist);

    /* sscanf */
    int sscanf_s(const char* buffer, const char* format, ...);

    int swscanf_s(const wchar_t* buffer, const wchar_t* format, ...);

    /* vsscanf */
    int vsscanf_s(const char* buffer, const char* format, va_list argptr);

    int vswscanf_s(const wchar_t* buffer, const wchar_t* format, va_list arglist);

    /* gets */
    char* gets_s(char* buffer, size_t destMax);

    void getHwSecureCVersion(char* verStr, int bufSize, unsigned short* verNumber);



#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif/* __SECUREC_H__5D13A042_DC3F_4ED9_A8D1_882811274C27 */


