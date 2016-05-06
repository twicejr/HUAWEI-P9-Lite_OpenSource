/**
Copyright(C) 2007, Huawei Tech. India Pvt. Ltd.
            ALL RIGHTS RESERVED

Author     : Jayaraghavendran K
FileName     :ipsi_misc.h 
Version      :1
Date         :: 2007-01-08
Description: This file contains all the miscellaneous functions.
*/


#ifndef __IPSI_MISC_H_
#define __IPSI_MISC_H_

#include "ipsi_types.h"
#include <stdarg.h>
#ifdef  __cplusplus
extern "C" {
#endif


typedef void * ipsi_sem_handle_t;

/*Search permission is denied for the path*/
#define IPSI_ACCESS_DENIED (-2)
typedef void *ipsi_stat;

/**

    @brief          The ipsi_printf function prints the buf to standard output.

                    Passing invalid argument to this function results in
                    undefined behaviour.

    @param[in]      buf             The string to be printed.
    @retval         int             On success returns the number of
                    characters printed negative value  On Failure.
*/
IPSILINKDLL int ipsi_printf(const char format[], ...);


/**
    @brief          The ipsi_strerror function returns a string describing
                    the error code passed in the argument errnum. This
                    string must not be modified by the application, but
                    may be modified by a subsequent call to ipsi_strerror
                    or other system calls which work on this string like
                    perror of linux flavors.

    @param[in]  errnum          The error Number.
    @retval    const char*     An appropriate error description string,
                               or an unknown error message if the error
                               code is unknown.
*/
IPSILINKDLL const char *ipsi_strerror(int errnum);

/**
    @brief            ipsi_clear_sys_error function will sets the last system
                    error code to Zero.

    @param            None

    @retval            None
*/
IPSILINKDLL void ipsi_clear_sys_error(void);

/**
    @breif            ipsi_sleep function suspends the execution of the current
                    thread for a specified interval passed as parameter.
    
    @param[in]        ulTime    Unsigned long integer that specifies the
                            milliseconds

    @retval            None
*/

IPSILINKDLL void ipsi_sleep(unsigned long ulTime);

/**
    @brief          The ipsi_fprintf function Prints formatted data
                    to a stream.

    @param[in]     pFile   Pointer to file structure
    @param[in]     format  format to be printed

    @retval         number of bytes written on success.
                    negative value on failure
*/

IPSILINKDLL int ipsi_fprintf(SEC_FILE_F* pFile, const SEC_CHAR format[], ...);

/**
    @brief          The ipsi_vsprintf function Write formatted output
                    using a pointer to a list of arguments

    @param[out]     buffer   storage location for output
    @param[in]     format  format to be printed
    @param[in]     argptr Pointer to list of arguments

    @retval         number of bytes written on success.
                    negative value on failure
*/

IPSILINKDLL int ipsi_vsprintf(char *buffer, const char *format, va_list argptr);

/**
    @brief          The ipsi_vsnprintf function Write formatted output
                    using a pointer to a list of arguments

    @param[out]     buffer   storage location for output
    @param[in]     format  format to be printed
    @param[in]     argptr Pointer to list of arguments
    @param[in]     count Maximum number of bytes to write

    @retval         number of bytes written on success.
                    negative value on failure
*/

IPSILINKDLL int ipsi_vsnprintf(char *buffer, size_t count, const char *format,
                                va_list argptr);

/**
    @brief          The ipsi_snprintf function Write formatted data 
                    to string.

    @param[out]     buffer   storage location for output
    @param[in]     format  format to be printed
    @param[in]     count Maximum number of bytes to write

    @retval         number of bytes written on success.
                    negative value on failure
*/

IPSILINKDLL int ipsi_snprintf(char *buffer, size_t count,
                                const char format[],...);

/**
    @brief          The ipsi_sprintf function Write formatted data 
                    to string.

    @param[out]     buffer   storage location for output
    @param[in]     format  format to be printed

    @retval         number of bytes written on success.
                    negative value on failure
*/

IPSILINKDLL int ipsi_sprintf(char *buffer, const char format[], ...);

/**
    @brief          The ipsi_sscanf function reads formatted data from
                    string.

    @param[out]     buffer   storage location for output
    @param[in]     format  format to be printed

    @retval         number of fields successfully converted and assigned.
                    return value of 0 indicates no fields were assigned.
                    The return value is EOF for an error or if the end
                    of the string is reached before the first conversion.

*/

IPSILINKDLL int ipsi_sscanf(const char *buffer, const char format[], ...);


/**
    @brief          This function is used to convert strings to integer.

    @param[out]     NA
    @param[in]      pcPtr String to be converted.

    @retval         This function returns the int or long value produced 
                    by interpreting the input characters as a number

*/

IPSILINKDLL int ipsi_atoi(const char* pcPtr);


/**
    @brief          Convert an integer to a string.

    @param[out]     string String result
    @param[in]      value  Number to be converted
    @param[in]      radix  Base of value; must be in the range 2 to 36

    @retval         Each of these functions returns a pointer to string.
                    There is no error return.
*/
IPSILINKDLL char *ipsi_itoa(int value, char *string, int radix);

/**
    @brief          Rename a file or directory.

    @param[in]      oldname  Pointer to old name
    @param[in]      newname  Pointer to new name

    @retval         Each of these functions returns 0 if it is successful.
                    On an error, the function  returns a nonzero value 
*/
IPSILINKDLL int ipsi_rename(const char *oldname, const char *newname);

/**
    @brief          Delete a file.

    @param[in]      filename  Name of file to remove
    
    @retval         Each of these functions returns 0 if successful.
                    Otherwise, the function returns ?
*/
IPSILINKDLL int ipsi_unlink(const char *filename);

/**
    @brief          ipsi_get_stat : Get the stat of the local file

    @param          pucFileName   Local file name with path
                    pcBuff        Stat structure

    @retval         This function returns success if it gets the stat of file
                    successfully otherwise return fail
*/
IPSILINKDLL int ipsi_get_stat(const unsigned char *pucFileName,
                              ipsi_stat *pcBuff);

/**
    @brief          ipsi_assert : Assert function

    @param          bExp   The evaluate expression
                    

    @retval         This function is used for assertion
*/
IPSILINKDLL void ipsi_assert(int bExp);

/**
    @brief          ipsi_check_stat : Checks the presence of the file or dir

    @param          pucFileName   Local file name with path                    

    @retval         This function returns success if it gets the stat of file
                    successfully otherwise return fail
*/
IPSILINKDLL int ipsi_check_stat(const unsigned char *pucFileName);

/**
    @brief          ipsi_update_check_directory : Checks the given pathname
                    is directory or not after removing the trailing slashes

    @param          pucFileName   Local file name with path                    

    @retval         This function returns success if it checks the stat of dir
                    successfully otherwise return fail
*/
IPSILINKDLL int ipsi_update_check_directory(unsigned char *pucFileName);

/**
    @brief          ipsi_check_is_dir : Checks the given attribute
                    of a path belongs to directory or a file

    @param          pstFindData  The finddata structure 
                    pcFullPath  The full Path

    @retval         This function returns success if it checks the attribute
                    of dir successfully otherwise return fail
*/
IPSILINKDLL int ipsi_check_is_dir(char * pcFullPath,void * pstFindData);

/**
    @brief          ipsi_getlast_system_error : Checks the getlast error

    @param          void

    @retval         This function returns IPSI_ERROR_NO_MORE_FILES if the 
                    getlast error gives
                    No more files or return IPSI_NO_ERROR
*/
IPSILINKDLL unsigned int ipsi_getlast_system_error(void);

/**
    @brief          ipsi_interrupt_signal : The interrupt initialzing function

    @param          iSignal - The interrupt signal
                    pFuncPtr - The handler function pointer

    @retval         This function returns success if it initialized
                    successfully otherwise return fail
*/
IPSILINKDLL int ipsi_interrupt_signal(int iSignal,void * pFuncPtr);


/**
    @brief          ipsi_ignore_interrupt : The interrupt ignoring function

    @param          iSignal - The interrupt signal

    @retval         This function returns success if it ignores the interrupt
                    successfully otherwise return fail
*/
IPSILINKDLL int ipsi_ignore_interrupt(int iSignal);


/**
    @brief          ipsi_isFile : Check the stat and return true if it is file

    @param          pcBuff        Stat structure

    @retval         This function returns SEC_TRUE if it is file
                    otherwise return SEC_FALSE
*/
IPSILINKDLL SEC_BOOL ipsi_isFile(ipsi_stat pcBuff);

/**
    @brief          ipsi_check_absolute_path:Checks if the given path is 
                    absolute or not.

    @param          pcFileName   The path                    

    @retval         This function returns IPSI_SUCCESS if it succeeds
                    otherwise return IPSI_FAILURE
*/
IPSILINKDLL int ipsi_check_absolute_path(const char *pcFileName);

//The system errors are defined here
#define IPSI_ERROR_NO_MORE_FILES  18L 

#define IPSI_ERROR_ALREADY_EXISTS  183L

#define IPSI_ERROR_NO_ENTRY 2L

#define IPSI_NO_ERROR  0L

#define IPSI_OSAL_VERSION "VPP V300R003C22SPC200"

/**
    @brief          ipsi_getOSALVersion:Returns the release version string.

    @param          NA

    @retval         This function returns release version string.
*/
IPSILINKDLL SEC_CHAR* ipsi_getOSALVersion();

#ifdef  __cplusplus
}
#endif
#endif

