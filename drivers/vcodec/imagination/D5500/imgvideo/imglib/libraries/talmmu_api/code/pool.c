/*!
 *****************************************************************************
 *
 * @File       pool.c
 * @Title      Object Pool Memory Allocator
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

#include <img_defs.h>
#include <img_types.h>
#include <img_errors.h>

#include "pool.h"

#define BUFF_MAX_SIZE 4096
#define BUFF_MAX_GROW 32

//64 bits
#define ALIGN_SIZE (sizeof(long long) - 1)

struct sPool
{
    IMG_CHAR * pszName;
    IMG_UINT32 ui32Size;
    IMG_UINT32 ui32Grow;
    struct sBuffer * psBuffers;
    struct sObject * psObjects;
};

struct sBuffer
{
    struct sBuffer * psNext;
};

struct sObject
{
    struct sObject * psNext;
};


/*!
********************************************************************************

 @Function				POOL_Create

 @Description

 Create an sObject sPool

 @Input     pszName     : Name of sObject sPool for diagnostic purposes

 @Input     ui32Size    : size of each sObject in the sPool in bytes

 @Output    ppsPool     : Will contain NULL or sObject sPool handle

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT POOL_Create(
    const   IMG_CHAR * const    pszName,
            IMG_UINT32          ui32Size,
    struct  sPool ** const      ppsPool
)
{
    struct sPool * psPool = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != pszName);
    IMG_ASSERT(IMG_NULL != ppsPool);
    if (IMG_NULL == pszName ||
        IMG_NULL == ppsPool)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psPool = IMG_MALLOC(sizeof (*psPool));
    IMG_ASSERT(IMG_NULL != psPool);
    if (IMG_NULL == psPool)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psPool->pszName = IMG_STRDUP((IMG_CHAR *)pszName);
    psPool->ui32Size = ui32Size;
    psPool->psBuffers = IMG_NULL;
    psPool->psObjects = IMG_NULL;
    psPool->ui32Grow = (BUFF_MAX_SIZE - sizeof (struct sBuffer)) / (ui32Size + ALIGN_SIZE);

    if(psPool->ui32Grow == 0)
    {
        psPool->ui32Grow = 1;
    }
    else if(psPool->ui32Grow > BUFF_MAX_GROW)
    {
        psPool->ui32Grow = BUFF_MAX_GROW;
    }

    (*ppsPool) = psPool;
    ui32Result = IMG_SUCCESS;

error:
    return ui32Result;
}

/*!
********************************************************************************

 @Function				POOL_Delete

 @Description

 Delete an sObject sPool. All psObjects allocated from the sPool must
 be free'd with pool_free() before deleting the sObject sPool.

 @Input	    psPool      : Object Pool pointer

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT POOL_Delete(
    struct sPool * const psPool
)
{
    struct sBuffer * psBuffer = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psPool);
    if (IMG_NULL == psPool)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psBuffer = psPool->psBuffers;
    while (IMG_NULL != psBuffer)
    {
        psBuffer = psBuffer->psNext;
        if(IMG_NULL != psPool->psBuffers)
        {
            IMG_FREE(psPool->psBuffers);
        }
        psPool->psBuffers = psBuffer;
    }
    if (IMG_NULL != psPool->pszName)
    {
        IMG_FREE(psPool->pszName);
        psPool->pszName = IMG_NULL;
    }
	IMG_FREE(psPool);
    ui32Result = IMG_SUCCESS;

error:
    return ui32Result;
}

/*!
********************************************************************************

 @Function				POOL_Alloc

 @Description

 Allocate an sObject from an sObject sPool.

 @Input	    psPool      : Object Pool

 @Output    phObject    : Pointer containing the handle to
                           the object created or IMG_NULL

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT POOL_Alloc(
    struct  sPool * const       psPool,
            IMG_HANDLE * const  phObject
)
{
    struct sObject * psObject = IMG_NULL;
    struct sBuffer * psBuffer = IMG_NULL;
    IMG_UINT32 ui32Idx = 0;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psPool);
    IMG_ASSERT(IMG_NULL != phObject);
    if (IMG_NULL == psPool ||
        IMG_NULL == phObject)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    if (IMG_NULL == psPool->psObjects)
    {
        psBuffer = IMG_MALLOC((psPool->ui32Size + ALIGN_SIZE) * psPool->ui32Grow + sizeof (struct sBuffer));
        IMG_ASSERT(IMG_NULL != psBuffer);
        if (IMG_NULL == psBuffer)
        {
            ui32Result = IMG_ERROR_MALLOC_FAILED;
            goto error;
        }

        //IMG_MEMSET(psBuffer, 0x00, sizeof(*psBuffer));
        psBuffer->psNext = psPool->psBuffers;
        psPool->psBuffers = psBuffer;

        for (ui32Idx = 0; ui32Idx < psPool->ui32Grow; ui32Idx++)
        {
            struct sObject * psObject;
            IMG_UINT8 * ui8TempPtr = IMG_NULL;

            psObject = (struct sObject *)(((IMG_UINT8 *)(psBuffer+1)) + (ui32Idx * (psPool->ui32Size + ALIGN_SIZE)));
            //align to 64bit
            ui8TempPtr = (IMG_UINT8 *)psObject;
            if ((IMG_UINTPTR)ui8TempPtr & ALIGN_SIZE)
            {
                ui8TempPtr += ((ALIGN_SIZE + 1) - ((IMG_UINTPTR)ui8TempPtr & ALIGN_SIZE));
                psObject = (struct sObject*)ui8TempPtr;
            }

            psObject->psNext = psPool->psObjects;
            psPool->psObjects = psObject;
        }
    }

    if (IMG_NULL == psPool->psObjects)
    {
        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
        goto error;
    }

    psObject = psPool->psObjects;
    psPool->psObjects = psObject->psNext;

    (*phObject) = (IMG_HANDLE)(psObject);
    ui32Result = IMG_SUCCESS;

error:
    return ui32Result;
}

/*!
********************************************************************************

 @Function				POOL_Free

 @Description

 Free an sObject previously allocated from an sObject sPool.

 @Input	    psPool      : Object Pool pointer.

 @Output    hObject     : Handle to the object to be freed.

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT POOL_Free(
    struct  sPool * const       psPool,
            IMG_HANDLE const    hObject
)
{
    struct sObject * psObject = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psPool);
    IMG_ASSERT(IMG_NULL != hObject);
    if (IMG_NULL == psPool ||
        IMG_NULL == hObject)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    psObject = (struct sObject *)hObject;
    psObject->psNext = psPool->psObjects;
    psPool->psObjects = psObject;

    ui32Result = IMG_SUCCESS;

error:
    return ui32Result;
}
