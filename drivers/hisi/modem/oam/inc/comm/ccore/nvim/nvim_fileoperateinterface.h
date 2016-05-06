/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: NVIM_FileOperateInterface.h                                     */
/*                                                                           */
/* Author: Jiang kaibo                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-06                                                             */
/*                                                                           */
/* Description: Announcement of NV File operate.                             */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-06                                                          */
/*    Author: Jiang kaibo                                                    */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _NVIM_FILEOPERATEINTERFACE_H
#define _NVIM_FILEOPERATEINTERFACE_H


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "comm_adapter.h"

#if ((VOS_VXWORKS == VOS_OS_VER) || (VOS_WIN32 == VOS_OS_VER))
#include <stdio.h>
#endif

#if (VOS_WIN32 == VOS_OS_VER)
#ifndef STATUS
#define STATUS    VOS_UINT32
#endif
#endif

FILE* NV_File_Open( VOS_CHAR *pcFileName, VOS_CHAR *pcAccessMode );
VOS_INT32 NV_File_Close( FILE *Fp );
VOS_INT32 NV_File_Seek( FILE *Fp,VOS_INT32 lOffset,VOS_INT32 lWhence);
VOS_INT32 NV_File_Write(VOS_VOID *pBuf,VOS_UINT32 ulSize,VOS_UINT32 ulCount,FILE *Fp);
VOS_INT32 NV_File_Tell(FILE *Fp);
VOS_CHAR *NV_GetFileAbsltPath(const VOS_CHAR        *pcFolderPath,
                                     const VOS_CHAR *pcFileName ,
                                     VOS_CHAR       *pcFilePath,
                                     VOS_UINT32      ulFilePathLen);

VOS_UINT32 NV_Printf(const VOS_CHAR *pcformat, ...);

#if ((VOS_WIN32 == VOS_OS_VER)||(VOS_VXWORKS == VOS_OS_VER)||(VOS_RTOSCK == VOS_OS_VER))

#ifndef MAX_PATH
#define MAX_PATH                        (256)
#endif

#define NV_XML_SUFFIX_STR_SIZE          (5)
#define NV_XML_FILE_MAX_NUM             (1000)

VOS_INT32 NV_File_Read(VOS_VOID *pBuf,VOS_UINT32 ulSize,VOS_UINT32 ulCount,FILE *Fp);
VOS_INT32 NV_File_Remove(VOS_CHAR *pcDir, VOS_CHAR *pcFile);
VOS_INT32 NV_File_Exist(VOS_CHAR *pcDir, VOS_CHAR *pcFile);
VOS_INT32 NV_File_Create(VOS_CHAR *pcDir, VOS_CHAR *pcFile);
VOS_INT32 NV_File_Check(VOS_CHAR *pcDir, VOS_CHAR *pcFile);

VOS_INT32 NV_Xcopy(VOS_CHAR *pcSrcDir, VOS_CHAR *pcDestDir);
VOS_INT32 NV_Mkdir(VOS_CHAR *pcDirName);

VOS_VOID NV_DeleteFilesBySuffix(VOS_CHAR *pcDirPath, VOS_CHAR *pcSuffixName);

extern int tolower(int c);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
