/***************************************************************
Copyright (C), 2004, Huawei Tech. Co., Ltd.
FileName: ipsi_string.h
Author: Ashwini A
Creation Date:2006-12-29
Version:1
Description: This file contains all the string related functions.
Function List:
ipsi_memcmp
ipsi_strncmp
ipsi_strlen
ipsi_strstr
ipsi_strrchr
ipsi_strchr
ipsi_strcmp
ipsi_strnicmp
ipsi_stricmp
ipsi_memchr
ipsi_strtouint32
ipsi_strcasecmp
ipsi_stristr
ipsi_memcpy_s
ipsi_memmove_s
ipsi_strncpy_s
ipsi_strncat_s
ipsi_snprintf_s
ipsi_sscanf_s
ipsi_memset_s
ipsi_vsnprintf_s
ipsi_sprintf_s
ipsi_vsprintf_s
ipsi_strcpy_s
ipsi_strcat_s
*****************************************************************/

#ifndef __IPSI_STRING_H_
#define __IPSI_STRING_H_

#include "ipsi_types.h"
#include <string.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
* @defgroup OSAL
* This section contains the descriptions of all APIs in OSAL.
*/

/**
* @defgroup ipsi_string_Functions
* @ingroup OSAL
* This section contains all the string related functions. .
*
*/

/**
* @defgroup ipsi_memcpy
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_memcpy(void *pDest, const void *pSrc, size_t uiCount);
* @endcode
* 
* @par Purpose
* This function is used to copy the characters between buffers.
* 
* @par Description
* ipsi_memcpy function copies characters between buffers.
*
* @param[in] pDest New buffer. [NA/NA]
* @param[in] pSrc Buffer to copy. [NA/NA]
* @param[in] uiCount Number of characters to copy. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval memcpy Returns the value of the destination. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
* 
* @par Note
* \n
* NA
*
* @par Related Topics
* NA
*/

IPSILINKDLL void *ipsi_memcpy(void *pDest, const void *pSrc, size_t uiCount);

/**
* @defgroup ipsi_memmove
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_memmove(void *pDest, const void *pSrc, size_t uiCount);
* @endcode
* 
* @par Purpose
* This function is used to move one buffer to another.
* 
* @par Description
* ipsi_memmove function moves one buffer to another.
*
* @param[in] pDest Destination. [NA/NA]
* @param[in] pSrc Source. [NA/NA]
* @param[in] uiCount Number of bytes of characters to copy. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval memmove Returns the value of the destination. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL void *ipsi_memmove(void *pDest, const void *pSrc, size_t uiCount);

/**
* @defgroup ipsi_strcpy
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strcpy(char *pDest, const char *pSrc);
* @endcode
* 
* @par Purpose
* This function is used to copy a string.
*
* @par Description
* ipsi_strcpy function copies a string.
*
* @param[in] pDest Destination string. [NA/NA]
* @param[in] pSrc Null-terminated source string. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA This functions returns the destination string. 
* No return value is reserved to indicate the error. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL char *ipsi_strcpy(char *pcDest, const char *pcSrc);

/**
* @defgroup ipsi_strcat
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strcat(char *pDest, const char *pSrc);
* @endcode
* 
* @par Purpose
* This function is used to append a string.
* 
* @par Description
* ipsi_strcat function appends a string.
*
* @param[in] pDest Null-terminated destination string. [NA/NA]
* @param[in] pSrc Null-terminated source string. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA This functions returns the destination string. 
* No return value is reserved to indicate the error. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL char *ipsi_strcat(char *pcDest, const char *pcSrc);

/**
* @defgroup ipsi_memset
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_memset(void *pDest, int iChar, size_t uiCount);
* @endcode
* 
* @par Purpose
* This function is used to set the buffers to a specified character.
*
* @par Description
* ipsi_memset function sets the buffers to a specified character.
*
* @param[in] pDest Pointer to destination. [NA/NA]
* @param[in] iChar Character to set. [NA/NA]
* @param[in] uiCount Number of characters. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval IPSI_SUCCESS On Successful Completion. [IPSI_SUCCESS | NA]
* @retval IPSI_FAILURE On Error. [IPSI_FAILURE | NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL void *ipsi_memset(void *pDest, int iCh, size_t uiCount);

/**
* @defgroup ipsi_memcmp
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_memcmp(const void *pBuf1, const void *pBuf2, size_t uiCount);
* @endcode
* 
* @par Purpose
* This function is used to compare the characters.
*
* @par Description
* ipsi_memcmp function compares the characters in two buffers.
*
* @param[in] pBuf1 First buffer. [NA/NA]
* @param[in] pBuf2 Second buffer. [NA/NA]
* @param[in] uiCount Number of characters. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA The return value indicates the relationship between the buffers 
* as follows:\n 
*   -buf1 less than buf2.\n 
*   -buf1 identical to buf2. \n
*   -buf1 greater than buf2. [NA|NA]
*  
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_memcmp(const void *pBuf1, const void 
                            *pBuf2, size_t uiCount);

/**
* @defgroup ipsi_strncmp
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strncmp(const char *pcString1, const char 
*                  *pcString2, size_t uiCount);
* @endcode
* 
* @par Purpose
* This function is used to compare the characters in two strings.
*
* @par Description
* ipsi_strncmp function compares the characters of two strings.
*
* @param[in] pcString1 String to compare. [NA/NA]
* @param[in] pcString2 String to compare. [NA/NA]
* @param[in] uiCount Number of characters. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA The return value indicates the relation between the substrings of 
* string1 and string2 as follows:\n 
*   -string1 substring is less than string2 substring. \n
*   -string1 substring is identical to string2 substring.\n
*   -string1 substring is greater than string2 substring.  [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_strncmp(const char *pcString1, const char 
                             *pcString2, size_t uiCount);

/**
* @defgroup ipsi_strlen
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* unsigned int ipsi_strlen(const char *pcString);
* @endcode
* 
* @par Purpose
* This function is used to get the length of a string.
*
* @par Description
* ipsi_strlen function gets the length of a string.
*
* @param[in] pcString Null-terminated string. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA This function returns the number of characters 
* in string, excluding the terminal NULL. No return value is 
* reserved to indicate the error. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* NA
*/

IPSILINKDLL unsigned int ipsi_strlen(const char *pcString);

/**
* @defgroup ipsi_strstr
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* const char *ipsi_strstr(const char *pcString, const char *pcStrcharset);
* @endcode
* 
* @par Purpose
* This function is used to search a string.
*
* @par Description
* ipsi_strstr function finds for a substring.
*
* @param[in] pcString Null-terminated string to search. [NA/NA]
* @param[in] pcStrcharset Null-terminated character set string to search. 
* [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA This function returns a pointer to the first 
* occurrence of Strcharset in string or NULL,
* if strCharSet does not appear in string. If Strcharset points to 
* a string of zero length, the function returns a string. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL const char *ipsi_strstr(const char *pcString, 
                                    const char *pcStrcharset);

/**
* @defgroup ipsi_stristr
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* const char *ipsi_stristr(const char *pcString,
*                           const char *pcStrcharset);
* @endcode
* 
* @par Purpose
* This function is used to search a string by ignoring the case.
*
* @par Description
* ipsi_stristr function finds for a substring by ignoring the case.
*
* @param[in] pcString Null-terminated string to search. [NA/NA]
* @param[in] pcStrcharset Null-terminated character set string to search. 
* [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA This function returns a pointer to the first 
* occurrence of Strcharset in string or NULL,
* if strCharSet does not appear in string. If Strcharset points to 
* a string of zero length, the function returns a string. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/
IPSILINKDLL const char *ipsi_stristr(const char *pcString,
                                    const char *pcStrcharset);

/**
* @defgroup ipsi_strrchr
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* char *ipsi_strrchr( const char *pcString, int iCh );
* @endcode
* 
* @par Purpose
* This function is used to scan a string for the last occurrence of a
* character.
*
* @par Description
* ipsi_strrchr function finds for last occurrence of a
* character.
*
* @param[in] pcString Null-terminated string to search. [NA/NA]
* @param[in] iCh      Character to be located.[NA/NA]
* 
* @retval This function returns a pointer to the last occurrence of iCh in 
* pcString, or NULL if iCh is not found.
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/
IPSILINKDLL char *ipsi_strrchr(const char *pcString, int iCh);

/**
* @defgroup ipsi_strchr
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* char *ipsi_strchr( const char *pcString, int iCh );
* @endcode
* 
* @par Purpose
* This function is used to scan a string for the first occurrence of a
* character.
*
* @par Description
* ipsi_strrchr function finds for first occurrence of a
* character.
*
* @param[in] pcString Null-terminated string to search. [NA/NA]
* @param[in] iCh      Character to be located.[NA/NA]
* 
* @retval This function returns a pointer to the first occurrence of iCh in 
* pcString, or NULL if iCh is not found.
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/
IPSILINKDLL char *ipsi_strchr(const char *pcString, int iCh);

/**
* @defgroup ipsi_strcmp
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strcmp(const char *pcString1, const char *pcString2);
* @endcode
* 
* @par Purpose
* This function is used to compare the characters in two strings.
*
* @par Description
* ipsi_strcmp function compares the characters of two strings.
*
* @param[in] pcString1 String to compare. [NA/NA]
* @param[in] pcString2 String to compare. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA The return value indicates the relation between the substrings of 
* string1 and string2 as follows:\n 
*   -string1 substring is less than string2 substring. \n
*   -string1 substring is identical to string2 substring.\n
*   -string1 substring is greater than string2 substring.  [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_strcmp(const char *pcString1, const char *pcString2);

/**
* @defgroup ipsi_memchr
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* void *ipsi_memchr(const void *pBuf, int character, size_t uiCount);
* @endcode
* 
* @par Purpose
* This function is used to find characters in a buffer.
*
* @par Description
* ipsi_memchr function finds characters in a buffer.
*
* @param[in] pBuf Pointer to buffer. [NA/NA]
* @param[in] character Character to look for. [NA/NA]
* @param[in] uiCount Number of characters to check [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA If successful, returns a pointer to first location of
* character in buffer. Otherwise, returns NULL.
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL void *ipsi_memchr(const void *pBuf, int character, size_t uiCount);

/**
* @defgroup ipsi_strnicmp
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strnicmp(const char *pcString1, const char *pcString2,
*                   size_t uiCount);
* @endcode
* 
* @par Purpose
* This function is used to compare characters in two strings without
* regard to case.
*
* @par Description
* ipsi_strnicmp function used to compare characters in two strings
* without regard to case.
*
* @param[in] pcString1 String to compare. [NA/NA]
* @param[in] pcString2 String to compare. [NA/NA]
* @param[in] uiCount Number of characters to compare [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA The return value indicates the relation between the 
* substrings of string1 and string2 as follows:\n 
* <0 -string1 substring is less than string2 substring. \n
* 0 -string1 substring is identical to string2 substring.\n
* >0 -string1 substring is greater than string2 substring.  [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_strnicmp(const char *pcString1,
                            const char *pcString2, size_t uiCount);

/**
* @defgroup ipsi_stricmp
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_stricmp(const char *pcString1, const char *pcString2);
* @endcode
* 
* @par Purpose
* This function is used to perform a lowercase comparison of strings.
*
* @par Description
* ipsi_stricmp function used to perform a lowercase comparison of strings.
*
* @param[in] pcString1 String to compare. [NA/NA]
* @param[in] pcString2 String to compare. [NA/NA]
* @param[out] NA NA [NA/NA]
* 
* @retval NA The return value indicates the relation between the substrings of 
* string1 and string2 as follows:\n 
* <0 -string1 substring is less than string2 substring. \n
* 0 -string1 substring is identical to string2 substring.\n
* >0 -string1 substring is greater than string2 substring.  [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_stricmp(const char *pcString1, const char *pcString2);

/**
* @defgroup ipsi_strtouint32
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* long ipsi_strtouint32(const char *string, int *piNum);
* @endcode
* 
* @par Purpose
* This function is used to convert strings to long.
*
* @par Description
* ipsi_strtouint32 function used to convert strings to long.
*
* @param[in] string String to be converted. [NA/NA]
* @param[out] piNum pointer to be updated with output. [NA/NA]
* 
* @retval NA returns 0 in case of success. -1 in case of failure.
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL long ipsi_strtouint32(const char *string, int *piNum);

/**
    @brief          ipsi_filename_comparison : used to perform a lowercase 
                        comparison of filename strings.This is because in unix
                                   the lowercase and upper case filenames are 
                                   different but in windows, those are same.

    @param          pcString1, pcString2        Strings to compare

    @retval         The return value indicates the relation of the substrings 
                    of string1 and string2 as follows.
                    < 0 string1 substring less than string2 substring 
                    0 string1 substring identical to string2 substring 
                    > 0 string1 substring greater than string2 substring 
*/

IPSILINKDLL int ipsi_filename_comparison(const char *pcString1,
                                const char *pcString2);


/**
    @brief          ipsi_strcasecmp : used to compare two strings without case.

    @param          str1 - First String to be compared
                    str2 - Second String to be compared

    @retval         returns 0 in case of match. else difference between the two.
*/
IPSILINKDLL int ipsi_strcasecmp (const char* str1, const char* str2);


/**
* @defgroup ipsi_memcpy_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_memcpy_s(void* dest, size_t destMax, const void* src, size_t count);
* @endcode
* 
* @par Purpose
* This function is used to copy the characters between buffers.
* 
* @par Description
* ipsi_memcpy_s function copies characters between buffers.
*
* @param[out] dest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] src Buffer to copy. [NA/NA]
* @param[in] count Number of characters to copy. [NA/NA]
* 
* @retval int On success. [IPSI_SUCCESS|NA]
* @retval int On failure. [IPSI_FAILURE|NA]
* 
* @par Required Header File
* ipsi_string.h
* 
* @par Note
* \n
* NA
*
* @par Related Topics
* NA
*/


IPSILINKDLL int ipsi_memcpy_s(void* dest, size_t destMax, const void* src, size_t count);


/**
* @defgroup ipsi_memmove_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_memmove_s(void* dest, size_t destMax, const void* src, size_t count);
* @endcode
* 
* @par Purpose
* This function is used to move one buffer to another.
* 
* @par Description
* ipsi_memmove_s function moves one buffer to another.
*
* @param[out] dest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] src Buffer to copy. [NA/NA]
* @param[in] count Number of characters to copy. [NA/NA]
* 
* @retval int On success. [IPSI_SUCCESS|NA]
* @retval int On failure. [IPSI_FAILURE|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_memmove_s(void* dest, size_t destMax, const void* src, size_t count);

/**
* @defgroup ipsi_strncpy_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strncpy_s(char* dest, size_t destMax, const char* src, size_t count);
* @endcode
* 
* @par Purpose
* This function is used to copy a string.
*
* @par Description
* ipsi_strncpy_s function copies a string.
*
* @param[out] dest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] src Buffer to copy. [NA/NA]
* @param[in] count Number of characters to copy. [NA/NA]
* 
* @retval int On success. [IPSI_SUCCESS|NA]
* @retval int On failure. [IPSI_FAILURE|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_strncpy_s(char* dest, size_t destMax, const char* src, size_t count);

/**
* @defgroup ipsi_strncat_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strncat_s(char* dest, size_t destMax, const char* src, size_t count);
* @endcode
* 
* @par Purpose
* This function is used to append a string.
* 
* @par Description
* ipsi_strncat_s function appends a string.
*
* @param[out] dest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] src Buffer to copy. [NA/NA]
* @param[in] count Number of characters to copy. [NA/NA]
* 
* @retval int On success. [IPSI_SUCCESS|NA]
* @retval int On failure. [IPSI_FAILURE|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_strncat_s(char* dest, size_t destMax, const char* src, size_t count);


/**
* @defgroup ipsi_snprintf_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_snprintf_s(char* strDest, size_t destMax, size_t count, const char* format, ...);
* @endcode
* 
* @par Purpose
* This function writes formatted data to string.
* 
* @par Description
* ipsi_snprintf_s writes formatted data to string.
*
* @param[out] strDest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] count Number of characters to copy. [NA/NA]
* @param[in] format Formatted string input. [NA/NA]
* 
* @retval int Number of bytes written on success. [NA|NA]
* @retval int Negative values on failure. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_snprintf_s(char* strDest, size_t destMax, size_t count, const char* format, ...);

/**
* @defgroup ipsi_sscanf_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_sscanf_s (const char* buffer, const char* format, ...);
* @endcode
* 
* @par Purpose
* This function reads formatted data to string.
* 
* @par Description
* ipsi_sscanf_s reads formatted data to string.
*
* @param[in] buffer input buffer. [NA/NA]
* @param[in] format Formatted string input. [NA/NA]
* 
* @retval int Number of fields successfully converted and assigned. [NA|NA]
* @retval int Returns 0 to indidcate no fields were assigned. [NA|NA]
* @retval int Returns EOF for any error. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_sscanf_s (const char* buffer, const char* format, ...);

/**
* @defgroup ipsi_memset_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_memset_s(void* dest, size_t destMax, int c, size_t count);
* @endcode
* 
* @par Purpose
* This function is used to set the buffers to a specified character.
*
* @par Description
* ipsi_memset_s function sets the buffers to a specified character.
*
* @param[out] strDest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] c characters to copy. [NA/NA]
* @param[in] count number of bytes to set. [NA/NA]
* 
* @retval IPSI_SUCCESS On Successful Completion. [IPSI_SUCCESS | NA]
* @retval IPSI_FAILURE On Error. [IPSI_FAILURE | NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_memset_s(void* dest, size_t destMax, int c, size_t count);

/**
* @defgroup ipsi_vsnprintf_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_vsnprintf_s(char* strDest, size_t destMax, size_t count, const char* format, va_list arglist);
* @endcode
* 
* @par Purpose
* This function writes formatted data to string.
* 
* @par Description
* ipsi_vsnprintf_s writes formatted data to string.
*
* @param[out] strDest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] count Number of characters to copy. [NA/NA]
* @param[in] format Formatted string input. [NA/NA]
* @param[in] arglist Input values as variable arguments. [NA/NA]
* 
* @retval int Number of bytes written on success. [NA|NA]
* @retval int Negative values on failure. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_vsnprintf_s(char* strDest, size_t destMax, size_t count, const char* format, va_list arglist);


/**
* @defgroup ipsi_sprintf_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_sprintf_s(char* strDest, size_t destMax, const char* format, ...);
* @endcode
* 
* @par Purpose
* This function writes formatted data to string.
* 
* @par Description
* ipsi_sprintf_s writes formatted data to string.
*
* @param[out] strDest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] format Formatted string input. [NA/NA]
* 
* @retval int Number of bytes written on success. [NA|NA]
* @retval int Negative values on failure. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_sprintf_s(char* strDest, size_t destMax, const char* format, ...);

/**
* @defgroup ipsi_vsprintf_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_vsprintf_s(char *buffer, size_t destMax, const char *format, va_list arglist);
* @endcode
* 
* @par Purpose
* This function writes formatted data to string.
* 
* @par Description
* ipsi_vsprintf_s writes formatted data to string.
*
* @param[out] strDest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] format Formatted string input. [NA/NA]
* @param[in] arglist Input values as variable arguments. [NA/NA]
* 
* @retval int Number of bytes written on success. [NA|NA]
* @retval int Negative values on failure. [NA|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_vsprintf_s(char *buffer, size_t destMax, const char *format, va_list arglist);

/**
* @defgroup ipsi_strcpy_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strcpy_s(char* dest, size_t destMax, const char* src);
* @endcode
* 
* @par Purpose
* This function is used to copy a string.
*
* @par Description
* ipsi_strcpy_s function copies a string.
*
* @param[out] dest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] src Buffer to copy. [NA/NA]
* 
* @retval int On success. [IPSI_SUCCESS|NA]
* @retval int On failure. [IPSI_FAILURE|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_strcpy_s(char* dest, size_t destMax, const char* src);

/**
* @defgroup ipsi_strcat_s
* @ingroup ipsi_string_Functions
* @par Prototype
* @code
* int ipsi_strcat_s(char* dest, size_t destMax, const char* src);
* @endcode
* 
* @par Purpose
* This function is used to append a string.
* 
* @par Description
* ipsi_strcat_s function appends a string.
*
* @param[out] dest destination buffer. [NA/NA]
* @param[in] destMax destinatio buffer size. [NA/NA]
* @param[in] src Buffer to copy. [NA/NA]
* 
* @retval int On success. [IPSI_SUCCESS|NA]
* @retval int On failure. [IPSI_FAILURE|NA]
* 
* @par Required Header File
* ipsi_string.h
*
* @par Note
* \n
* NA
* 
* @par Related Topics
* NA
*/

IPSILINKDLL int ipsi_strcat_s(char* dest, size_t destMax, const char* src);

#ifdef  __cplusplus
}
#endif

#endif


