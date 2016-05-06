/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "nvim_fileoperateinterface.h"
#include "nvim_internalfunc.h"
#include "mdrv.h"
/*lint -e451 */
#include <stdarg.h>
/*lint +e451 */
#if (VOS_RTOSCK == VOS_OS_VER)
#include "sre_shell.h"
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
/* Macro of log */
/*lint -e767 -e750 修改人:蒋开波 00105005;检视人:徐铖 51137;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_NVIM_FILEOPERATEINTERFACE_C
/*lint +e767 +e750 修改人:蒋开波 00105005;检视人:徐铖 51137; */
#endif

extern const VOS_CHAR    g_acNvLogFilePath[];

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
Function   : NV_Printf
Description: NV module print output.
Input      : pcformat - printed string.
Return     : VOS_OK: successfully, VOS_ERR: failed.
Other      :
*****************************************************************************/
/*lint -e960 */
#if (VOS_VXWORKS == VOS_OS_VER)
extern int logMsg(char *fmt, ...);
#endif

VOS_UINT32 NV_Printf(const VOS_CHAR *pcformat, ...)
/*lint +e960 */
{
    VOS_CHAR                            acOutput[NV_LOG_MAX_LEN];
    /*lint -e530 -e830 */
    va_list                             argument;
    VOS_UINT32                          ulRetLen;
#if ((VOS_WIN32 == VOS_OS_VER)||(VOS_VXWORKS == VOS_OS_VER)||(VOS_RTOSCK == VOS_OS_VER))
    FILE                               *fp;
    VOS_UINT32                          ulFileSize;
#endif

    /* 将格式化字符串和可变参数转换为字符串 */
    va_start(argument, pcformat);
    /*lint -e64 */
    ulRetLen = (VOS_UINT32)vsnprintf(acOutput, NV_LOG_MAX_LEN, pcformat, argument);
    /*lint +e64 */
    va_end(argument);
    /*lint +e530 +e830 */

    if ((NV_LOG_MAX_LEN < ulRetLen) || (0 == ulRetLen))
    {
        return VOS_ERR;
    }

#if (VOS_LINUX == VOS_OS_VER)
    printk("%s", acOutput);
#elif (VOS_VXWORKS == VOS_OS_VER)
    logMsg("%s", acOutput);
#elif (VOS_RTOSCK == VOS_OS_VER)
    /*lint -e534*/
    SRE_Printf("%s", acOutput);
    /*lint +e534*/
#endif

#if ((VOS_WIN32 == VOS_OS_VER)||(VOS_VXWORKS == VOS_OS_VER)||(VOS_RTOSCK == VOS_OS_VER))
    fp = mdrv_file_open(g_acNvLogFilePath, "a");

    if (VOS_NULL_PTR == fp)
    {
        return VOS_ERR;
    }

    mdrv_file_seek(fp, 0, NV_FILE_SEEK_END);

    ulFileSize = (VOS_UINT32)mdrv_file_tell(fp);

    /* If the log file is too large, we need empty it. */
    if (ulFileSize > NV_LOG_FILE_MAX_SIZE)
    {
        /*lint -e534*/
        mdrv_file_close(fp);
        /*lint +e534*/
        fp = mdrv_file_open(g_acNvLogFilePath, "w");

        if (VOS_NULL_PTR == fp)
        {
            return VOS_ERR;
        }
    }

    /*lint -e534*/
    mdrv_file_write(acOutput, ulRetLen, 1, fp);

    mdrv_file_close(fp);
    /*lint +e534*/

#endif

    return VOS_OK;
}


#if defined( __PS_WIN32_RECUR__ ) || defined (__DART__)
#else

/*****************************************************************************
Function   : NV_File_Open
Description: Open a file specified by name
Input      : VOS_CHAR *pcFileName -> Name of File
             VOS_CHAR *pcAccessMode -> Open Mode
Return     : FILE *
Other      :
*****************************************************************************/
FILE *NV_File_Open( VOS_CHAR *pcFileName, VOS_CHAR *pcAccessMode )
{
    FILE *fp;

    fp = mdrv_file_open(pcFileName,pcAccessMode);

    if ( VOS_NULL_PTR == fp )
    {
        NV_Printf("Open File %s fail.\r\n", pcFileName);
    }

    return fp;
}

/*****************************************************************************
Function   : NV_File_Close
Description: Close File
Input      : FILE *Fp -> File ptr
Return     : OK or ERR
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Close( FILE *Fp )
{
    VOS_INT32 lRslt = VOS_ERR;

    lRslt = mdrv_file_close(Fp);

    if ( VOS_OK != lRslt )
    {
        NV_Printf("NV:Close File fail.\r\n");
    }

    return lRslt;
}

/*****************************************************************************
Function   : NV_File_Seek
Description: Set the file position indicator
Input      : FILE *Fp -> File position
             VOS_INT32 lOffset -> Offset from lWhence
             VOS_INT32 lWhence -> Position to offset from
Return     : OK or ERR
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Seek( FILE *Fp,VOS_INT32 lOffset,VOS_INT32 lWhence)
{
    VOS_INT32 ulRslt = VOS_ERR;

    ulRslt = mdrv_file_seek(Fp,lOffset,lWhence);

    if ( VOS_OK != ulRslt )
    {
        NV_Printf("NV:Seek File fail.\r\n");
    }

    return ulRslt;
}

/*****************************************************************************
Function   : NV_File_Write
Description: Write from a specified array
Input      : VOS_VOID *pBuf -> where to copy from
             VOS_UINT32 ulSize -> Element size
             VOS_UINT32 ulCount -> No. of elements
             FILE *Fp -> File position
Return     : The number of elements successfully written
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Write(VOS_VOID *pBuf,VOS_UINT32 ulSize,VOS_UINT32 ulCount,FILE *Fp)
{
    VOS_INT32                             lRslt;

    lRslt = mdrv_file_write(pBuf,ulSize,ulCount,Fp);

    if ( lRslt != ulCount )
    {
        NV_Printf("NV:Write File fail.\r\n");
    }

    return lRslt;

}

/*****************************************************************************
Function   : NV_File_Tell
Description: Return the current value of the file position indicator
Input      : FILE *Fp -> File position
Return     : The current value of the file position indicator
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Tell(FILE *Fp)
{
    VOS_INT32 lFileSize = VOS_ERROR;

    lFileSize = mdrv_file_tell(Fp);

    if ( VOS_ERROR == lFileSize)
    {
        NV_Printf("NV:Tell File Size fail.\r\n");
    }

    return lFileSize;
}

#if ((VOS_WIN32 == VOS_OS_VER)||(VOS_VXWORKS == VOS_OS_VER)||(VOS_RTOSCK == VOS_OS_VER))
/*****************************************************************************
Function   : NV_File_Read
Description: Read data into an array
Input      : VOS_VOID *pBuf -> Where to copy data
             VOS_UINT32 ulSize -> Element size
             VOS_UINT32 ulCount -> No. of elements
             FILE *Fp -> File position
Return     : The number of elements successfully read
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Read(VOS_VOID *pBuf,VOS_UINT32 ulSize,VOS_UINT32 ulCount,FILE *Fp)
{
    VOS_INT                             lRslt;

    lRslt = mdrv_file_read(pBuf,ulSize,ulCount,Fp);

    if ( (VOS_UINT32)lRslt != ulCount )
    {
        NV_Printf("NV:Read File fail.\r\n");
    }

    return lRslt;
}

/*****************************************************************************
Function   : NV_File_Remove
Description: remove a file
Input      : VOS_CHAR *pcFileName -> File name
Return     : OK, or ERROR
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Remove(VOS_CHAR *pcDir, VOS_CHAR *pcFile)
{
    VOS_INT32                           lRslt;
    VOS_CHAR                            acFilePath[MAX_PATH] = {0};

    strncpy(acFilePath, pcDir, (MAX_PATH - 1));

    if (VOS_NULL_PTR != pcFile)
    {
        strncat(acFilePath, pcFile, (MAX_PATH - VOS_StrLen(acFilePath) - 1));
    }

    lRslt = mdrv_file_remove(acFilePath);

    if(VOS_OK != lRslt)
    {
        NV_Printf("Remove File %s fail.\r\n", acFilePath);
    }

    return lRslt;
}

/*****************************************************************************
Function   : NV_File_Exist
Description: Judge the NV file is exist.
Input      : pcDir - the directory of NV file.
             pcFile- the name of NV file.
Return     : OK, or ERROR
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Exist(VOS_CHAR *pcDir, VOS_CHAR *pcFile)
{
    VOS_INT32                           lRslt;
    VOS_CHAR                            acFilePath[MAX_PATH] = {0};

    strncpy(acFilePath, pcDir, (MAX_PATH - 1));

    if (VOS_NULL_PTR != pcFile)
    {
        strncat(acFilePath, pcFile, (MAX_PATH - VOS_StrLen(acFilePath) - 1));
    }

    lRslt = mdrv_file_access(acFilePath, NV_FILE_EXIST_OK);

    return lRslt;
}

/*****************************************************************************
Function   : NV_File_Create
Description: Create empty file.
Input      : pcDir - the directory of NV file.
             pcFile- the name of NV file.
Return     : OK, or ERROR
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Create(VOS_CHAR *pcDir, VOS_CHAR *pcFile)
{
    FILE                               *fp;
    VOS_CHAR                            acFilePath[MAX_PATH] = {0};

    strncpy(acFilePath, pcDir, (MAX_PATH - 1));

    if (VOS_NULL_PTR != pcFile)
    {
        strncat(acFilePath, pcFile, (MAX_PATH - VOS_StrLen(acFilePath) - 1));
    }

    fp = mdrv_file_open(acFilePath, NV_FILE_OPEN_MODE_NEW_RW);

    if (VOS_NULL_PTR == fp)
    {
        return VOS_ERR;
    }

    if (VOS_OK != mdrv_file_close(fp))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
Function   : NV_File_Check
Description: Check NV file's security.
Input      : pcDir - the directory of NV file.
             pcFile- the name of NV file.
Return     : OK, or ERROR
Other      :
*****************************************************************************/
VOS_INT32 NV_File_Check(VOS_CHAR *pcDir, VOS_CHAR *pcFile)
{
    VOS_CHAR                            acFilePath[MAX_PATH] = {0};

    strncpy(acFilePath, pcDir, (MAX_PATH - 1));

    if (VOS_NULL_PTR != pcFile)
    {
        strncat(acFilePath, pcFile, (MAX_PATH - VOS_StrLen(acFilePath) - 1));
    }

    return DRV_NV_FILE_SEC_CHECK(acFilePath);
}

/*****************************************************************************
Function   : NV_Mkdir
Description: make a directory
Input      : VOS_CHAR *pcDirName -> Directory name
Return     : OK, or ERROR if the directory cannot be created
Other      :
*****************************************************************************/
VOS_INT32 NV_Mkdir(VOS_CHAR *pcDirName)
{
    VOS_INT32 ulRslt;

    ulRslt = mdrv_file_mkdir(pcDirName);

    if(VOS_OK != ulRslt)
    {
        NV_Printf("Make Dir %s fail.\r\n", pcDirName);
    }

    return ulRslt;
}

#endif  /* #if defined( __PS_WIN32_RECUR__ ) || defined (__DART__) */

#if (VOS_WIN32 == VOS_OS_VER)

#ifndef OAM_UT_DEBUG
/*****************************************************************************
Function   : NV_Xcopy
Description: Copy folder operation.
Input      : pcSrcDir - the source's directory.
             pcDestDir- the destination's directory
Return     : OK, or ERROR
Other      :
*****************************************************************************/
VOS_INT32 NV_Xcopy(VOS_CHAR *pcSrcDir, VOS_CHAR *pcDestDir)
{
    VOS_INT32                           lRslt;
    SHFILEOPSTRUCT                      sfo;
    VOS_CHAR                            acSrcDir[MAX_PATH] = {0};
    VOS_CHAR                            acDestDir[MAX_PATH] = {0};
    VOS_CHAR                            acCurDir[MAX_PATH];

    GetCurrentDirectory(MAX_PATH, acCurDir);

    strcpy(acSrcDir,  acCurDir);
    strcpy(acDestDir, acCurDir);

    strcat(acSrcDir,  pcSrcDir + 1);
    strcat(acDestDir, pcDestDir + 1);

    sfo.hwnd  = NULL;
    sfo.wFunc = FO_COPY;
    sfo.pFrom = (LPCSTR)acSrcDir;
    sfo.pTo   = (LPCSTR)acDestDir;
    sfo.fFlags = FOF_NOCONFIRMATION|FOF_SIMPLEPROGRESS|FOF_NOCONFIRMMKDIR|FOF_MULTIDESTFILES;
    sfo.hNameMappings = 0;
    sfo.lpszProgressTitle="foldercopy!";

    lRslt = SHFileOperation(&sfo);

    return lRslt;
}

#endif

/*****************************************************************************
Function   : NV_DeleteFileBySuffix
Description: Delete files by file's suffix name.
Input      : pcDirName - the file's directory.
Return     : VOID
Other      :
*****************************************************************************/
VOS_VOID NV_DeleteFilesBySuffix(VOS_CHAR *pcDirPath, VOS_CHAR *pcSuffixName)
{
    return;
}

#elif ((VOS_VXWORKS == VOS_OS_VER)||(VOS_RTOSCK == VOS_OS_VER))

/*****************************************************************************
Function   : NV_Xcopy
Description: Copy folder operation.
Input      : pcSrcDir - the source's directory.
             pcDestDir- the destination's directory
Return     : OK, or ERROR
Other      :
*****************************************************************************/
VOS_INT32 NV_Xcopy(VOS_CHAR *pcSrcDir, VOS_CHAR *pcDestDir)
{
    VOS_INT32                           lRslt;

    lRslt = mdrv_file_xcopy(pcSrcDir, pcDestDir);

    return lRslt;
}

/*****************************************************************************
Function   : NV_DeleteFileBySuffix
Description: Delete files by file's suffix name.
Input      : pcDirName - the file's directory.
Return     : VOID
Other      :
*****************************************************************************/
VOS_VOID NV_DeleteFilesBySuffix(VOS_CHAR *pcDirPath, VOS_CHAR *pcSuffixName)
{
    DRV_DIR_S                          *pstTmpDir;
    DRV_DIRENT_S                       *pstTmpDirent;
    VOS_UINT32                          ulNameLen;
    VOS_CHAR                            acSuffixSrc[NV_XML_SUFFIX_STR_SIZE];
    VOS_UINT32                          i;
    VOS_UINT32                          ulLoopNum = 0;
    VOS_UINT32                          ulFileNum = 0;

    pstTmpDir = mdrv_file_opendir(pcDirPath);

    if (VOS_NULL_PTR == pstTmpDir)
    {
        NV_Printf("NV_DeleteFilesBySuffix, mdrv_file_opendir %s fail.\r\n", pcDirPath);

        return;
    }

    do
    {
        pstTmpDirent = mdrv_file_readdir(pstTmpDir);

        /* readdir's return value is zero, so the loop should be over. */
        if (VOS_NULL_PTR != pstTmpDirent)
        {
            /* ulNumLen includes the ending of string. */
            ulNameLen = VOS_StrLen(pstTmpDirent->d_name) + 1;

            if (NV_XML_SUFFIX_STR_SIZE < ulNameLen)
            {
                for (i = 0; i < NV_XML_SUFFIX_STR_SIZE; i++)
                {
                    acSuffixSrc[i] = (VOS_CHAR)tolower(pstTmpDirent->d_name[ulNameLen - (NV_XML_SUFFIX_STR_SIZE - i)]);
                }

                if (VOS_OK == VOS_StrCmp(acSuffixSrc, pcSuffixName))
                {
                    NV_File_Remove(pcDirPath, pstTmpDirent->d_name);
                    ulFileNum++;
                }
            }
        }

        /* Avoid dead loop.*/
        ulLoopNum++;
    }while ((VOS_NULL_PTR != pstTmpDirent) && (ulLoopNum < NV_XML_FILE_MAX_NUM));

    if (VOS_OK != mdrv_file_closedir(pstTmpDir))
    {
        NV_Printf("NV_DeleteFilesBySuffix, mdrv_file_closedir fail.\r\n");
    }

    if (NV_XML_FILE_MAX_NUM == ulLoopNum)
    {
        NV_Printf("NV_DeleteFilesBySuffix, File system crashed.\r\n");
    }

    /* Record the number of deleted files. */
    if (0 != ulFileNum)
    {
        NV_Printf("NV_DeleteFilesBySuffix, the num of deleted files: %d.\r\n", ulFileNum);
    }

    return;
}

#endif

/*****************************************************************************
Function   : NV_GetFileAbsolutPath
Description: concatenate one string to another
Input      : VOS_CHAR       *pcFolderPath -> Folder absolute path
             VOS_CHAR       *pcFileName -> File name
             VOS_UINT32      ulFilePathStrLen->File path len
Return     : A pointer to destination
Other      :
*****************************************************************************/
VOS_CHAR *NV_GetFileAbsltPath(const VOS_CHAR        *pcFolderPath,
                                     const VOS_CHAR *pcFileName ,
                                     VOS_CHAR       *pcFilePath,
                                     VOS_UINT32      ulFilePathLen)
{
    /*lint -e534*/
    VOS_StrNCpy(pcFilePath, (VOS_CHAR*)pcFolderPath, (ulFilePathLen - 1));
    /*lint +e534*/

    strncat(pcFilePath, pcFileName, (ulFilePathLen - VOS_StrLen(pcFilePath) - 1));

    /* make coverity happy */
    pcFilePath[VOS_StrLen(pcFilePath)] = '\0';

    return pcFilePath;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




