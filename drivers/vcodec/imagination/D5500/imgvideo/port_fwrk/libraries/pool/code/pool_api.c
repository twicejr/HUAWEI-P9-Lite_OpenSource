/*!
 *****************************************************************************
 *
 * @File       pool_api.c
 * @Title      Resource Pool Manager API.
 * @Description    This file contains the Resource Pool Manager API.
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

#include "pool_api.h"
#include "sysos_api_km.h"
#include "idgen_api.h"
#include "system.h"


#define POOL_IDGEN_MAX_ID      (0xFFFFFFFF)  /*!< Max resource ID.              */
#define POOL_IDGEN_BLOCK_SIZE  (50)          /*!< Size of blocks used for ids.  */

static IMG_BOOL gInitialised = IMG_FALSE;  /*!< Indicates where the API has been initialised.  */

static LST_T    gsPoolList;                /*!< List of resource pools.  */

/*!
******************************************************************************
 This structure contains the resource pool information.
******************************************************************************/
typedef struct
{
    LST_LINK;     /*!< List link (allows the structure to be part of a MeOS list).  */

    IMG_HANDLE    hMutexHandle;  /*!< Mutex handle.                                 */
    LST_T         sFreeResList;  /*!< List of free resource structures.             */
    LST_T         sActResList;   /*!< List of active resource structures.           */
    POOL_pfnFree  pfnFree;       /*!< Pool free callback function.                  */
    IMG_HANDLE    hIdGenHandle;  /*!< Id generator context handle.                  */

} POOL_sResPool;

/*!
******************************************************************************
 This structure contains the resource pool information.
******************************************************************************/
typedef struct POOL_tag_sResource POOL_sResource;
struct POOL_tag_sResource
{
    LST_LINK;           /*!< List link (allows the structure to be part of a MeOS list).                     */

    IMG_UINT32          ui32ResId;       /*!< Resource id.                                                   */
    POOL_pfnDestructor  pfnDestructor;   /*!< Pointer to destructor function.                                */
    IMG_VOID *          pvParam;         /*!< Resource pvParam.                                              */
    IMG_UINT32          ui32SizevParam;  /*!< Size of pvParam data (in bytes).                               */
    POOL_sResPool *     psResPool;       /*!< Pointer to resource pool.                                      */
    IMG_BOOL            bIsClone;        /*!< IMG_TRUE if this is a clone of the original resource.          */
    POOL_sResource *    psOrigResource;  /*!< Pointer to the original resource.                              */
    LST_T               sCloneResList;   /*!< List of cloned resource structures. ONLY used on the original  */
    IMG_UINT32          ui32RefCnt;      /*!< Reference count.  ONLY used on the original.                   */

};

/*!
******************************************************************************

 @Function                POOL_Initialise

******************************************************************************/
IMG_RESULT POOL_Initialise(IMG_VOID)
{
    /* Disable interrupts.  */
    SYSOSKM_DisableInt();

    /* If not initialised...*/
    if (!gInitialised)
    {
        /* Initialise the list of pools. */
        LST_init(&gsPoolList);

        /* Set initialised flag...*/
        gInitialised = IMG_TRUE;
    }

    /* Enable interrupts.  */
    SYSOSKM_EnableInt();

    /* Return success...*/
    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(POOL_Initialise)

/*!
******************************************************************************

 @Function                POOL_Deinitialise

******************************************************************************/
IMG_VOID POOL_Deinitialise(IMG_VOID)
{
    POOL_sResPool *  psResPool;
    IMG_ASSERT(0);

    /* Disable interrupts.  */
    SYSOSKM_DisableInt();

    /* If not initialised...*/
    if (!gInitialised)
    {
        /* Destroy any active pools...*/
        psResPool = (POOL_sResPool *)LST_first(&gsPoolList);
        while (psResPool != IMG_NULL)
        {
            POOL_PoolDestroy(psResPool);
            psResPool = (POOL_sResPool *)LST_first(&gsPoolList);
        }

        /* Set initialised flag...*/
        gInitialised = IMG_FALSE;
    }

    /* Enable interrupts.  */
    SYSOSKM_EnableInt();
}


/*!
******************************************************************************

 @Function                POOL_PoolCreate

******************************************************************************/
IMG_RESULT POOL_PoolCreate(
    IMG_HANDLE *  phPoolHandle
)
{
    POOL_sResPool *  psResPool;
    IMG_UINT32       ui32Result;

    IMG_ASSERT(gInitialised);

    /* Allocate a pool structure...*/
    psResPool = IMG_MALLOC(sizeof(*psResPool));
    IMG_ASSERT(psResPool != IMG_NULL);
    if (psResPool == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psResPool, 0, sizeof(*psResPool));

    /* Initialise the pool info...*/
    LST_init(&psResPool->sFreeResList);
    LST_init(&psResPool->sActResList);

    /* Create mutex...*/
    ui32Result = SYSOSKM_CreateMutex(&psResPool->hMutexHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_create_mutex;
    }

    /* Create context for the Id generator...*/
    ui32Result = IDGEN_CreateContext(POOL_IDGEN_MAX_ID, POOL_IDGEN_BLOCK_SIZE,IMG_FALSE, &psResPool->hIdGenHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_create_context;
    }

    /* Disable interrupts.  */
    SYSOSKM_DisableInt();

    /* Add to list of pools...*/
    LST_add(&gsPoolList, psResPool);

    /* Enable interrupts.  */
    SYSOSKM_EnableInt();

    /* Return handle to pool...*/
    *phPoolHandle = psResPool;

    return IMG_SUCCESS;

    /* Error handling. */
error_create_context:
    SYSOSKM_DestroyMutex(psResPool->hMutexHandle);
error_create_mutex:
    IMG_FREE(psResPool);

    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(POOL_PoolCreate)

/*!
******************************************************************************

 @Function                POOL_PoolDestroy

******************************************************************************/
IMG_RESULT POOL_PoolDestroy(
    IMG_HANDLE  hPoolHandle
)
{
    POOL_sResPool *   psResPool = hPoolHandle;
    POOL_sResource *  psResource;
    POOL_sResource *  psCloneResource;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResPool != IMG_NULL);

    if (!gInitialised ||
        psResPool == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    /* Disable interrupts.  */
    SYSOSKM_DisableInt();

    /* Remove the pool from the active list...*/
    LST_remove(&gsPoolList, psResPool);

    /* Enable interrupts.  */
    SYSOSKM_EnableInt();

    /* Destroy any resources in the free list...*/
    psResource = (POOL_sResource *)LST_removeHead(&psResPool->sFreeResList);
    while (psResource != IMG_NULL)
    {
        psResource->pfnDestructor(psResource->pvParam);
        IMG_FREE(psResource);

        psResource = (POOL_sResource *)LST_removeHead(&psResPool->sFreeResList);
    }

    /* Destroy any resources in the active list...*/
    psResource = (POOL_sResource *)LST_removeHead(&psResPool->sActResList);
    while (psResource != IMG_NULL)
    {
        psCloneResource = (POOL_sResource *)LST_removeHead(&psResource->sCloneResList);
        while (psCloneResource != IMG_NULL)
        {
            /* If we created a copy of the resources pvParam then free it...*/
            if (psCloneResource->pvParam != IMG_NULL)
            {
                IMG_FREE(psCloneResource->pvParam );
            }
            IMG_FREE(psCloneResource);
            psCloneResource = (POOL_sResource *)LST_removeHead(&psResource->sCloneResList);
        }

        /* Call the resource destructor...*/
        psResource->pfnDestructor(psResource->pvParam);
        IMG_FREE(psResource);

        psResource = (POOL_sResource *)LST_removeHead(&psResPool->sActResList);
    }

    /* Destroy the context for the Id generator...*/
    if (psResPool->hIdGenHandle != IMG_NULL)
    {
        ui32Result = IDGEN_DestroyContext(psResPool->hIdGenHandle);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
    }

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

    /* Destroy mutex...*/
    SYSOSKM_DestroyMutex(psResPool->hMutexHandle);

    /* Free the pool structure */
    IMG_FREE(psResPool);
    
	return IMG_SUCCESS;

error_nolock:
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(POOL_PoolDestroy)

/*!
******************************************************************************

 @Function                POOL_PoolSetFreeCallback

******************************************************************************/
IMG_RESULT POOL_PoolSetFreeCallback(
    IMG_HANDLE    hPoolHandle,
    POOL_pfnFree  pfnFree
)
{
    POOL_sResPool *   psResPool = hPoolHandle;
    POOL_sResource *  psResource;
    IMG_UINT32              ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResPool != IMG_NULL);

    if (!gInitialised ||
        psResPool == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    psResPool->pfnFree = pfnFree;

    /* If free callback set...*/
    if (psResPool->pfnFree != IMG_NULL)
    {
        /* Move resources from free to active list...*/
        psResource = (POOL_sResource *)LST_removeHead(&psResPool->sFreeResList);
        while (psResource != IMG_NULL)
        {
            /* Add to active list...*/
            LST_add(&psResPool->sActResList, psResource);
            psResource->ui32RefCnt++;

            /* Unlock the pool...*/
            SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

            /* Call the free callback...*/
            psResPool->pfnFree(psResource->ui32ResId, psResource->pvParam);

            /* Lock the pool...*/
            SYSOSKM_LockMutex(psResPool->hMutexHandle);

            /* Get next free resource...*/
            psResource = (POOL_sResource *)LST_removeHead(&psResPool->sFreeResList);
        }
    }

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;

error_nolock:
    return ui32Result;
}


/*!
******************************************************************************

 @Function                POOL_ResRegister

******************************************************************************/
IMG_RESULT POOL_ResRegister(
    IMG_HANDLE          hPoolHandle,
    POOL_pfnDestructor  pfnDestructor,
    IMG_VOID *          pvParam,
    IMG_UINT32          ui32SizevParam,
    IMG_BOOL            bAlloc,
    IMG_UINT32 *        pui32ResId,
    IMG_HANDLE *        phPoolResHandle
)
{
    POOL_sResPool *   psResPool = hPoolHandle;
    POOL_sResource *  psResource;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResPool != IMG_NULL);

    if (!gInitialised ||
        psResPool == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    /* Allocate a resource structure...*/
    psResource = IMG_MALLOC(sizeof(*psResource));
    IMG_ASSERT(psResource != IMG_NULL);
    if (psResource == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psResource, 0, sizeof(*psResource));

    /* Setup the resource...*/
    psResource->pfnDestructor  = pfnDestructor;
    psResource->pvParam        = pvParam;
    psResource->ui32SizevParam = ui32SizevParam;
    psResource->psResPool      = psResPool;
    LST_init(&psResource->sCloneResList);

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    /* Set resource id...*/
    ui32Result = IDGEN_AllocId(psResPool->hIdGenHandle, (IMG_HANDLE)psResource, &psResource->ui32ResId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        IMG_FREE(psResource);
        /* Unlock the pool...*/
        SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

        return ui32Result;
    }

    /* If allocated or free callback not set...*/
    if ( (bAlloc) || (psResPool->pfnFree != IMG_NULL) )
    {
        /* Add to active list...*/
        LST_add(&psResPool->sActResList, psResource);
        psResource->ui32RefCnt++;
    }
    else
    {
        /* Add to free list...*/
        LST_add(&psResPool->sFreeResList, psResource);
    }

    /* Return the resource id...*/
    if (pui32ResId != IMG_NULL)
    {
        *pui32ResId = psResource->ui32ResId;
    }

    /* Return the handle to the resource...*/
    if (phPoolResHandle != IMG_NULL)
    {
        *phPoolResHandle = psResource;
    }

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);


    /* If free callback set...*/
    if (psResPool->pfnFree != IMG_NULL)
    {
        /* Call the free callback...*/
        psResPool->pfnFree(psResource->ui32ResId, psResource->pvParam);
    }

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;

error_nolock:
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(POOL_ResRegister)

/*!
******************************************************************************

 @Function                POOL_ResDestroy

******************************************************************************/
IMG_RESULT POOL_ResDestroy(
    IMG_HANDLE  hPoolResHandle,
    IMG_BOOL    bForce
)
{
    POOL_sResource *  psResource = hPoolResHandle;
    POOL_sResPool *   psResPool;
    POOL_sResource *  psOrigResource;
    POOL_sResource *  psCloneResource;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResource != IMG_NULL);

    if (!gInitialised ||
        psResource == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    psResPool = psResource->psResPool;

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    /* If this is a clone...*/
    if (psResource->bIsClone)
    {
        IMG_ASSERT(0);        // We need to check this works.

        /* Get access to the original...*/
        psOrigResource = psResource->psOrigResource;
        IMG_ASSERT(psOrigResource != IMG_NULL);
        if (psOrigResource == IMG_NULL)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
		
        IMG_ASSERT(!psOrigResource->bIsClone);
        if (psOrigResource->bIsClone)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

        /* Remove from the clone list...*/
        LST_remove(&psOrigResource->sCloneResList, psResource);

        /* Free resource id...*/
        ui32Result = IDGEN_FreeId(psResPool->hIdGenHandle, psResource->ui32ResId);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            /* Unlock the pool...*/
            SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

            return ui32Result;
        }

        /* If we created a copy of the resources pvParam then free it...*/
        if (psResource->pvParam != IMG_NULL)
        {
            IMG_FREE(psResource->pvParam );
        }
        /* Free the clone resource structure...*/
        IMG_FREE(psResource);

        /* Set resource to be "freed" to the original...*/
        psResource = psOrigResource;
    }

    /* If there are still outstanding references...*/
    if ( (!bForce) && (psResource->ui32RefCnt != 0) )
    {
        IMG_ASSERT(0);      // We may need to mark the resource and destroy it when
                            // there are no outstanding references
        /* Unlock the pool...*/
        SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

        /* Return IMG_SUCCESS...*/
        return IMG_SUCCESS;
    }

    /* Check clone list is empty...*/
    psCloneResource = LST_first(&psResource->sCloneResList);
    IMG_ASSERT(psCloneResource == IMG_NULL);

    /* Has the resource outstanding references...*/
    if (psResource->ui32RefCnt != 0)
    {
        /* Remove the resource from the active list...*/
        LST_remove(&psResPool->sActResList, psResource);
    }
    else
    {
        /* Remove the resource from the free list...*/
        LST_remove(&psResPool->sFreeResList, psResource);
    }

    /* Free resource id...*/
    ui32Result = IDGEN_FreeId(psResPool->hIdGenHandle, psResource->ui32ResId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        /* Unlock the pool...*/
        SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

        return ui32Result;
    }

    /* Call the resource destructor...*/
    psResource->pfnDestructor(psResource->pvParam);
    IMG_FREE(psResource);

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;

error:
	SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

error_nolock:
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(POOL_ResDestroy)

/*!
******************************************************************************

 @Function                POOL_ResDestroy1

******************************************************************************/
IMG_RESULT POOL_ResDestroy1(
    IMG_HANDLE  hPoolHandle,
    IMG_UINT32  ui32ResId,
    IMG_BOOL    bForce
)
{
    POOL_sResPool *  psResPool = hPoolHandle;
    IMG_UINT32       ui32Result;
    IMG_HANDLE       hPoolResHandle;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResPool != IMG_NULL);

    if (!gInitialised ||
        psResPool == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    ui32Result = IDGEN_GetHandle(psResPool->hIdGenHandle, ui32ResId, &hPoolResHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        /* Unlock the pool...*/
        SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

        return ui32Result;
    }

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

    /* Call on to destroy resource...*/
    return POOL_ResDestroy(hPoolResHandle, bForce);

error_nolock:
    return ui32Result;
}


/*!
******************************************************************************

 @Function                POOL_ResAlloc

******************************************************************************/
IMG_RESULT POOL_ResAlloc(
    IMG_HANDLE  hPoolHandle,
    IMG_HANDLE  hPoolResHandle
)
{
    POOL_sResPool *   psResPool  = hPoolHandle;
    POOL_sResource *  psResource = hPoolResHandle;
    IMG_UINT32              ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResPool != IMG_NULL);
    IMG_ASSERT(hPoolResHandle != IMG_NULL);

    if (!gInitialised ||
        psResPool == IMG_NULL ||
        hPoolResHandle == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    /* Remove resource from free list...*/
    LST_remove(&psResPool->sFreeResList, psResource);

    /* Add to active list...*/
    LST_add(&psResPool->sActResList, psResource);
    psResource->ui32RefCnt++;

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;

error_nolock:
    return ui32Result;
}

IMGVIDEO_EXPORT_SYMBOL(POOL_ResAlloc)
/*!
******************************************************************************

 @Function                POOL_ResFree

******************************************************************************/
IMG_RESULT POOL_ResFree(
    IMG_HANDLE  hPoolResHandle
)
{
    POOL_sResource *  psResource = hPoolResHandle;
    POOL_sResPool *   psResPool;
    POOL_sResource *  psOrigResource;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResource != IMG_NULL);

    if (!gInitialised ||
        psResource == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    psResPool = psResource->psResPool;

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    /* If this is a clone...*/
    if (psResource->bIsClone)
    {
        /* Get access to the original...*/
        psOrigResource = psResource->psOrigResource;
        IMG_ASSERT(psOrigResource != IMG_NULL);
        if (psOrigResource == IMG_NULL)
        {
            SYSOSKM_UnlockMutex(psResPool->hMutexHandle);
            return IMG_ERROR_INVALID_PARAMETERS;
        }
        IMG_ASSERT(!psOrigResource->bIsClone);

        /* Remove from the clone list...*/
        LST_remove(&psOrigResource->sCloneResList, psResource);

        /* Free resource id...*/
        ui32Result = IDGEN_FreeId(psResPool->hIdGenHandle, psResource->ui32ResId);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if (ui32Result != IMG_SUCCESS)
        {
            /* Unlock the pool...*/
            SYSOSKM_UnlockMutex(psResPool->hMutexHandle);
            return ui32Result;
        }

        /* If we created a copy of the resources pvParam then free it...*/
        if (psResource->pvParam != IMG_NULL)
        {
            IMG_FREE(psResource->pvParam );
        }
        /* Free the clone resource structure...*/
        IMG_FREE(psResource);

        /* Set resource to be "freed" to the original...*/
        psResource = psOrigResource;
    }

    /* Update the reference count...*/
    IMG_ASSERT(psResource->ui32RefCnt != 0);
    psResource->ui32RefCnt--;

    /* If there are still outstanding references...*/
    if (psResource->ui32RefCnt != 0)
    {
        /* Unlock the pool...*/
        SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

        /* Return IMG_SUCCESS...*/
        return IMG_SUCCESS;
    }

    /* Remove the resource from the active list...*/
    LST_remove(&psResPool->sActResList, psResource);

    /* If free callback set...*/
    if (psResPool->pfnFree != IMG_NULL)
    {
        /* Add to active list...*/
        LST_add(&psResPool->sActResList, psResource);
        psResource->ui32RefCnt++;
    }
    else
    {
        /* Add to free list...*/
        LST_add(&psResPool->sFreeResList, psResource);
    }

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

    /* If free callback set...*/
    if (psResPool->pfnFree != IMG_NULL)
    {
        /* Call the free callback...*/
        psResPool->pfnFree(psResource->ui32ResId, psResource->pvParam);
    }

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;

error_nolock:
    return ui32Result;
}

IMGVIDEO_EXPORT_SYMBOL(POOL_ResFree)

/*!
******************************************************************************

 @Function                POOL_ResFree1

******************************************************************************/
IMG_RESULT POOL_ResFree1(
    IMG_HANDLE  hPoolHandle,
    IMG_UINT32  ui32ResId
)
{
    POOL_sResPool *  psResPool = hPoolHandle;
    IMG_UINT32       ui32Result;
    IMG_HANDLE       hPoolResHandle;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResPool != IMG_NULL);

    if (!gInitialised ||
        psResPool == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    ui32Result = IDGEN_GetHandle(psResPool->hIdGenHandle, ui32ResId, &hPoolResHandle);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        /* Unlock the pool...*/
        SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

        return ui32Result;
    }

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

    /* Call on to free resource...*/
    return POOL_ResFree(hPoolResHandle);

error_nolock:
    return ui32Result;
}


/*!
******************************************************************************

 @Function                POOL_ResClone

******************************************************************************/
IMG_RESULT POOL_ResClone(
    IMG_HANDLE    hPoolResHandle,
    IMG_HANDLE *  phClonePoolResHandle,
    IMG_VOID **   ppvParam
)
{
    POOL_sResource *  psResource = hPoolResHandle;
    POOL_sResPool *   psResPool;
    POOL_sResource *  psOrigResource = psResource;
    POOL_sResource *  psCloneResource;
    IMG_UINT32        ui32Result;

    IMG_ASSERT(gInitialised);
    IMG_ASSERT(psResource != IMG_NULL);

    if (!gInitialised ||
        psResource == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error_nolock;
    }

    /* Allocate a resource structure...*/
    psCloneResource = IMG_MALLOC(sizeof(*psCloneResource));
    IMG_ASSERT(psCloneResource != IMG_NULL);
    if (psCloneResource == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psCloneResource, 0, sizeof(*psCloneResource));

    psResPool = psResource->psResPool;
    IMG_ASSERT(psResPool != IMG_NULL);
    if(psResPool == IMG_NULL)
    {
        return IMG_ERROR_FATAL;
    }

    /* Lock the pool...*/
    SYSOSKM_LockMutex(psResPool->hMutexHandle);

    /* Set resource id...*/
    ui32Result = IDGEN_AllocId(psResPool->hIdGenHandle, (IMG_HANDLE)psCloneResource, &psCloneResource->ui32ResId);
    IMG_ASSERT(ui32Result == IMG_SUCCESS);
    if (ui32Result != IMG_SUCCESS)
    {
        goto error_alloc_id;
    }

    /* If this is a clone, set the original...*/
    if (psResource->bIsClone)
    {
        psOrigResource = psResource->psOrigResource;
    }
    IMG_ASSERT(psOrigResource->ui32RefCnt > 0);

    /* Setup the cloned resource...*/
    psCloneResource->bIsClone       = IMG_TRUE;
    psCloneResource->psResPool      = psResPool;
    psCloneResource->psOrigResource = psOrigResource;

    /* Add to clone list...*/
    LST_add(&psOrigResource->sCloneResList, psCloneResource);
    psOrigResource->ui32RefCnt++;

    /* If ppvParam is not IMG_NULL...*/
    if (ppvParam !=IMG_NULL)
    {
        /* If the size of the original vParam is 0...*/
        if (psOrigResource->ui32SizevParam == 0)
        {
            *ppvParam = IMG_NULL;
        }
        else
        {
            /* Allocate memory for a copy of the original vParam...*/
            *ppvParam = IMG_MALLOC(psOrigResource->ui32SizevParam);
            IMG_ASSERT(*ppvParam != IMG_NULL);
            if (*ppvParam == IMG_NULL)
            {
                ui32Result = IMG_ERROR_OUT_OF_MEMORY;
                goto error_copy_param;
            }
            IMG_MEMCPY(*ppvParam, psOrigResource->pvParam, psOrigResource->ui32SizevParam);
        }
    }

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

    /* Return the cloned resource...*/
    *phClonePoolResHandle = psCloneResource;

    /* Return IMG_SUCCESS...*/
    return IMG_SUCCESS;

    /* Error handling. */
error_copy_param:
    LST_remove(&psOrigResource->sCloneResList, psCloneResource);
    psOrigResource->ui32RefCnt--;
error_alloc_id:
    IMG_FREE(psCloneResource);

    /* Unlock the pool...*/
    SYSOSKM_UnlockMutex(psResPool->hMutexHandle);

error_nolock:
    return ui32Result;
}
