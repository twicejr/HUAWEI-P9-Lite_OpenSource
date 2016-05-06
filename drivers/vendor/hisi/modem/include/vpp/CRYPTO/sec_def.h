/*
 Copyright(C) 2006, Huawei Tech. Co., Ltd.
 ALL RIGHTS RESERVED
 Project Code:              iPSI
 Module Name:               Crypto Module
 Created On:                2007-08-30
 Author:                    Vinay Gudur
 Description:               This file contains macros defined for crypto lib.

 Modification History
 DATE        NAME             DESCRIPTION
Filename:sec_def.h
Version
*/

#ifndef SEC_DEF_H
#define SEC_DEF_H

#include "sec_sys.h"
#include "ipsi_file.h"

#include "ipsi_types.h"


#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup sec_def
* This section contains the sec_def Enum, Structure and Functions.
*/


/** @defgroup sec_defEnum
* @ingroup sec_def
* This section contains sec_def Enum.
*/


/** @defgroup sec_defStructure
* @ingroup sec_def
* This section contains sec_def Structure.
*/


/** @defgroup sec_defFunctions
* @ingroup sec_def
* This section contains sec_def Functions.
*/


/*
    Func Name:  SEC_vfsFopen
*/

/**
* @defgroup SEC_vfsFopen 
* @ingroup sec_defFunctions
* @par Prototype
* @code
* SEC_FILE_F* SEC_vfsFopen(const char *path, const char *mode);
* @endcode
*
* @par Purpose
* This is used to open a file.
*
* @par Description
* SEC_vfsFopen function opens a file.User has to give 
path of the file and mode(read/write) in which file needs to be
* opened.
*
* @param[in] path Path where File needs to be opened [N/A]
* @param[in] mode Mode of file opening(read/write) [N/A]
* 
* @retval SEC_FILE_F* If file opens [File pointer|N/A]
* @retval SEC_FILE_F* If file opening fails [SEC_NULL|N/A]
*
* @par Required Header File
* sec_def.h
*
* @par Note
* \n
* This function doesn't set any specific permissions to the file. Only default permissions
* based on mode will be set. 
* 
*
* @par Related Topics
* N/A
*/

CRYPTOLINKDLL SEC_FILE_F * SEC_vfsFopen(const char *path, const char *mode);

#define SEC_VFS_FOpen SEC_vfsFopen  
#define SEC_VFS_FClose ipsi_fclose
#define SEC_VFS_FRead(buffer, charsize, \
size,stream) ipsi_fread(buffer,(charsize)*(size),stream)
#define SEC_VFS_FWrite(buffer, charsize, \
size,stream) ipsi_fwrite(buffer,(charsize)*(size),stream)
#define SEC_VFS_FFlush ipsi_fflush
#define SEC_VFS_FileLength ipsi_filelength


/*
    Func Name:  SEC_GetSysTime
*/

/**
* @defgroup SEC_GetSysTime 
* @ingroup sec_defFunctions 
* @par Prototype
* @code
* SEC_UINT32 SEC_GetSysTime(DATETIME_S *pstSysTime);
* @endcode
*
* @par Purpose
* This is used to get the system time.
*
* @par Description
* SEC_GetSysTime function gets system time and stores the same in pstSysTime.

* @param[in] pstSysTime Pointer to DATETIME_S structure [N/A]
*
* @retval SEC_UINT32 If pstSysTime is NULL [SEC_ERR_INVALID_ARG|N/A]
* @retval SEC_UINT32 If gets system time [SEC_SUCCESS|N/A]
*
* @par Required Header File
* sec_def.h  
*
* @par Note
* \n
* N/A
*
* @par Related Topics
*
* N/A
*/
CRYPTOLINKDLL SEC_UINT32 SEC_GetSysTime(DATETIME_S *pstSysTime);




#ifdef __cplusplus
}
#endif

#endif


