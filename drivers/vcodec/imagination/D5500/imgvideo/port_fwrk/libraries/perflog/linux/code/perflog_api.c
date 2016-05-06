/*!
 *****************************************************************************
 *
 * @File       perflog_api.c
 * @Title      Performance Logger API
 * @Description    This file contains implementation of
 *  Performance Logger API for linux kernel space
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>

#include "system.h"
#include "perflog_api.h"
#include "sysos_api_km.h"
#include "report_api.h"
#include "lst.h"

#include <linux/module.h>
#include <linux/string.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>

#define ONE_BUFFER_SIZE 512

/*!
******************************************************************************

 A structure to represent single buffer

******************************************************************************/
typedef struct{
    LST_LINK;

    IMG_UINT64                  *pui64Buffer;
    IMG_SIZE                     stIter;
    IMG_SIZE                     stBufferSize;

} perflog_Buffer;

static IMG_RESULT perflog_CreateBuffer(perflog_Buffer **ppBuffer, IMG_SIZE stBuffSize);
static IMG_VOID perflog_DestroyBuffer(perflog_Buffer *pBuffer);

/*!
******************************************************************************

 A structure to represent perflog file

******************************************************************************/
typedef struct{
    LST_T                        sBufferList;
    struct dentry               *psFile;
    IMG_HANDLE                   hMutexHandle;

} perflog_FileHandler;

static IMG_RESULT perflog_InitialiseFile(perflog_FileHandler *pFileHandler, const IMG_CHAR *pszFileName, struct dentry *psPerfLogDir);
static IMG_VOID perflog_DeinitialiseFile(perflog_FileHandler *pFileHandler);
static IMG_RESULT perflog_CleanFile(perflog_FileHandler *pFileHandler);
static IMG_RESULT perflog_WriteFile(perflog_FileHandler *pFileHandler, IMG_UINT64 uiMsg);

static IMG_BOOL                      gbInitialised = IMG_FALSE;
static struct dentry                *gpsPerfLogDir = NULL;
static perflog_FileHandler           gsPerfFile;

static int perflog_open(struct inode *inode, struct file *file);

static struct file_operations perflog_FileOps = {
    .owner   = THIS_MODULE,
    .open    = perflog_open,
    .read    = seq_read,
    .llseek  = seq_lseek,
    .release = seq_release
};

static void *perflog_start(struct seq_file *s, loff_t *pos);
static void *perflog_next(struct seq_file *s, void *v, loff_t *pos);
static void perflog_stop(struct seq_file *s, void *v);
static int perflog_show(struct seq_file *s, void *v);

static struct seq_operations perflog_SeqOps = {
    .start = perflog_start,
    .next  = perflog_next,
    .stop  = perflog_stop,
    .show  = perflog_show
};

static int perflog_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &perflog_SeqOps);
}

static void *perflog_start(struct seq_file *s, loff_t *pos)
{
    perflog_Buffer  *psBuffer;
    loff_t           tmpPos = *pos;

    //prevent from writing while one reads file
    SYSOSKM_LockMutex(gsPerfFile.hMutexHandle);

    //jump to appropriate buffer
    psBuffer = LST_first(&gsPerfFile.sBufferList);
    while(psBuffer && tmpPos > 0)
    {
        tmpPos--;
        psBuffer = LST_next(psBuffer);
    }

    return psBuffer;
}

static void *perflog_next(struct seq_file *s, void *buffer, loff_t *pos)
{
    perflog_Buffer  *psBuffer = (perflog_Buffer*)buffer;

    //iterate to next buffer
    psBuffer = LST_next(psBuffer);
    (*pos)++;

    return psBuffer;
}

static void perflog_stop(struct seq_file *s, void *buffer)
{
    //release file
    SYSOSKM_UnlockMutex(gsPerfFile.hMutexHandle);
}

static int perflog_show(struct seq_file *s, void *buffer)
{
    perflog_Buffer  *psBuffer = (perflog_Buffer*)buffer;

    //write relevant part of buffer to output
    seq_write(s, psBuffer->pui64Buffer, psBuffer->stIter * sizeof(IMG_UINT64));

    return 0;
}

/*!
******************************************************************************

 @Function      perflog_CreateBuffer

 @Description

 Allocates and initialises new buffer.

 @Output    ppsBuffer : new buffer

 @Input     stBuffSize : buffer size

 @Return    IMG_SUCCESS in case when buffer has been created successfully,
            error code otherwise

******************************************************************************/

static IMG_RESULT perflog_CreateBuffer(perflog_Buffer **ppsBuffer, IMG_SIZE stBuffSize)
{
    perflog_Buffer  *psBuffer = NULL;

    if(ppsBuffer == NULL || *ppsBuffer != NULL)
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                "Performance logger cannot create buffer: invalid parameters");
        return IMG_ERROR_INVALID_PARAMETERS;
    }
    //alloc buffer struct
    *ppsBuffer = (perflog_Buffer*) IMG_MALLOC(sizeof(perflog_Buffer));
    IMG_ASSERT(*ppsBuffer != IMG_NULL);
    if(*ppsBuffer == IMG_NULL)
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                "Performance logger cannot allocate memory for buffer struct");
        return IMG_ERROR_MALLOC_FAILED;
    }

    psBuffer = *ppsBuffer;

    //alloc buffer itself
    psBuffer->pui64Buffer = (IMG_UINT64*) IMG_MALLOC(sizeof(IMG_UINT64) * stBuffSize);
    IMG_ASSERT(psBuffer->pui64Buffer != IMG_NULL);
    if(psBuffer->pui64Buffer == IMG_NULL)
    {
        IMG_FREE(psBuffer);
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                "Performance logger cannot allocate buffers");
        return IMG_ERROR_MALLOC_FAILED;
    }
    IMG_MEMSET(psBuffer->pui64Buffer, 0,sizeof(IMG_UINT64) * stBuffSize);
    psBuffer->stIter = 0;
    psBuffer->stBufferSize = stBuffSize;

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function      perflog_DestroyBuffer

 @Description

 Frees buffer.

 @Input     psBuffer : buffer to be freed

 @Return    IMG_SUCCESS in case when buffer has been freed successfully,
            error code otherwise

******************************************************************************/

static IMG_VOID perflog_DestroyBuffer(perflog_Buffer *psBuffer)
{
    IMG_FREE(psBuffer->pui64Buffer);
    IMG_FREE(psBuffer);
}

/*!
******************************************************************************

 @Function      PERFLOG_Initialise

******************************************************************************/
IMG_RESULT PERFLOG_Initialise(
    IMG_VOID
)
{
    if(gbInitialised == IMG_FALSE)
    {
        IMG_RESULT ret;

        //creates directory in debug file system
        gpsPerfLogDir = debugfs_create_dir("perfLog", NULL);
        if (gpsPerfLogDir == IMG_NULL) 
        {
            REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                   "Performance logger cannot create directory");
            return IMG_ERROR_FATAL;
        }

        //creates file in debug file system
        if( (ret = perflog_InitialiseFile(&gsPerfFile, "perfLog.xpl",gpsPerfLogDir)) != IMG_SUCCESS)
        {
            debugfs_remove_recursive(gpsPerfLogDir); 
            REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                   "Performance logger cannot create file");
            return ret;
        }

        gbInitialised = IMG_TRUE;
    }

    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(PERFLOG_Initialise);

/*!
******************************************************************************

 @Function      perflog_InitialiseFile

 @Description

 Initialises new file in performance logger directory.

 @Output    pFileHandler : file to be initialised

 @Input     pszFileName : name of created file

 @Input     psPerfLogDir : directory where new file will be stored

 @Return    IMG_SUCCESS in case when file has been initialised successfully,
            error code otherwise

******************************************************************************/
static IMG_RESULT perflog_InitialiseFile(
    perflog_FileHandler *pFileHandler,
    const IMG_CHAR *pszFileName,
    struct dentry *psPerfLogDir
)
{
    if(pFileHandler == NULL || pszFileName == NULL || psPerfLogDir == NULL)
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                "Performance logger cannot create buffer: invalid parameters");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    //creates mutex that sync access to list of buffers
    if( SYSOSKM_CreateMutex(&pFileHandler->hMutexHandle) != IMG_SUCCESS)
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
               "Performance logger cannot create internal mutex");
        return IMG_ERROR_FATAL;
    }

    //initialises list of buffers
    LST_init(&pFileHandler->sBufferList);

    //creates new file in debug file system
    pFileHandler->psFile = debugfs_create_file(pszFileName, 0644, psPerfLogDir, NULL, &perflog_FileOps);
    IMG_ASSERT(pFileHandler->psFile != IMG_NULL);
    if(pFileHandler->psFile == IMG_NULL)
    {
        SYSOSKM_DestroyMutex(pFileHandler->hMutexHandle);
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
               "Performance logger cannot create file in debug file system");
        return IMG_ERROR_FATAL;
    }

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function      perflog_DeinitialiseFile

 @Description

 Deinitialises file.

 @Input    pFileHandler : file to be deinitialised

 @Return    IMG_SUCCESS in case when file has been deinitialised successfully,
            error code otherwise

******************************************************************************/
static IMG_VOID perflog_DeinitialiseFile(
    perflog_FileHandler *pFileHandler
)
{
    if(pFileHandler == IMG_NULL)
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                "Performance logger cannot deinitialise file: invalid parameters");
        return;
    }

    SYSOSKM_LockMutex(pFileHandler->hMutexHandle);

    //removes file from debug filesystem...
    debugfs_remove(pFileHandler->psFile);

    //removes all internal structures
    perflog_CleanFile(pFileHandler);

    SYSOSKM_UnlockMutex(pFileHandler->hMutexHandle);

    //and file mutex
    SYSOSKM_DestroyMutex(pFileHandler->hMutexHandle);

}

/*!
******************************************************************************

 @Function      perflog_CleanFile

 @Description

 Truncates performance file to zero length.

 @Input    pFileHandler : file to be cleand

 @Return    IMG_SUCCESS in case when file has been cleand successfully,
            error code otherwise

******************************************************************************/
static IMG_RESULT perflog_CleanFile(perflog_FileHandler *pFileHandler)
{
    perflog_Buffer  *psBuffer;

    if(pFileHandler == IMG_NULL)
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                "Performance logger cannot clean file: invalid parameters");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    SYSOSKM_LockMutex(pFileHandler->hMutexHandle);

    //removes all buffers
    psBuffer = LST_removeHead(&pFileHandler->sBufferList);
    while(psBuffer)
    {
        perflog_DestroyBuffer(psBuffer);

        psBuffer = LST_removeHead(&pFileHandler->sBufferList);
    }

    SYSOSKM_UnlockMutex(pFileHandler->hMutexHandle);

    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function      perflog_WriteFile

 @Description

 Writes to the file.

 @Input    pFileHandler : file where data will be written

 @Input    uiMsg        : performance data

 @Return    IMG_SUCCESS in case when data has been written successfully,
            error code otherwise

******************************************************************************/
static IMG_RESULT perflog_WriteFile(perflog_FileHandler *pFileHandler, IMG_UINT64 uiMsg)
{
    perflog_Buffer  *psBuffer;

    if(pFileHandler == IMG_NULL)
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                "Performance logger cannot clean file: invalid parameters");
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    SYSOSKM_LockMutex(pFileHandler->hMutexHandle);

    //search for buffer that has place to store perf data
    psBuffer = LST_first(&pFileHandler->sBufferList);
    while(psBuffer)
    {
        if(psBuffer->stIter < psBuffer->stBufferSize)
        {
            break;
        }
        psBuffer = LST_next(psBuffer);
    }

    //new buffer is needed
    if(psBuffer == IMG_NULL)
    {
        IMG_RESULT result;

        //create new buffer
        if( (result = perflog_CreateBuffer(&psBuffer, ONE_BUFFER_SIZE)) != IMG_SUCCESS )
        {
            SYSOSKM_UnlockMutex(pFileHandler->hMutexHandle);
            REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                "Performance logger cannot allocate buffers");
            return result;
        }

        //add buffer to a list
        LST_add(&pFileHandler->sBufferList, psBuffer);
    }

    //write data
    psBuffer->pui64Buffer[(psBuffer->stIter)++] = uiMsg;

    SYSOSKM_UnlockMutex(pFileHandler->hMutexHandle);

    return IMG_SUCCESS;
}
/*!
******************************************************************************

 @Function      PERFLOG_WritePerfMsg

******************************************************************************/
IMG_RESULT PERFLOG_WritePerfMsg(
    IMG_UINT64  uiMsg
)
{
    if( gbInitialised == IMG_TRUE )
    {
        IMG_RESULT result;

        if( (result = perflog_WriteFile(&gsPerfFile, uiMsg)) != IMG_SUCCESS)
        {
             REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                    "Performance logger write to a file");
             return result;
        }
    }
    else
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
               "Performance logger has not been initilaised");
        return IMG_ERROR_NOT_INITIALISED;
    }

    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(PERFLOG_WritePerfMsg);

/*!
******************************************************************************

 @Function      PERFLOG_Open

******************************************************************************/
IMG_RESULT PERFLOG_Open(
    IMG_VOID
)
{
    if(gbInitialised == IMG_TRUE)
    {
        IMG_RESULT result;

        if( (result = perflog_CleanFile(&gsPerfFile)) != IMG_SUCCESS)
        {
            REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
                  "Performance logger: error while opening a file");
            return result;
        }
    }
    else
    {
        REPORT(REPORT_MODULE_PERFLOG, REPORT_ERR,
               "Performance logger has not been initilaised");
        return IMG_ERROR_NOT_INITIALISED;
    }

    return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(PERFLOG_Open);

/*!
******************************************************************************

 @Function      PERFLOG_Deinitialise

 @Description

 Deinitialises Performance Logger API

 @Input     None.

 @Return    None.

******************************************************************************/
IMG_VOID PERFLOG_Deinitialise(
    IMG_VOID
)
{
    if(gbInitialised == IMG_TRUE)
    {
        gbInitialised = IMG_FALSE;

        //removes file
        perflog_DeinitialiseFile(&gsPerfFile);

        //removes file from debug filesystem...
        debugfs_remove_recursive(gpsPerfLogDir);
    }
}

IMGVIDEO_EXPORT_SYMBOL(PERFLOG_Deinitialise);
