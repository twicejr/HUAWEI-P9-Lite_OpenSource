/*!
 *****************************************************************************
 *
 * @File       rman_api.c
 * @Description    This file contains the Resource Manager API.
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

#include "rman_api.h"
#include "sysos_api_km.h"
#include "dq.h"
#include "idgen_api.h"
#include "system.h"

#ifdef IMG_KERNEL_MODULE
#include <linux/module.h>
#endif

/*!
******************************************************************************
 The follwing macros are used to build/decompose the composite resource Id
 made up from the bucket index + 1 and the allocated resource Id.
******************************************************************************/
#define RMAN_CRESID_BUCKET_INDEX_BITS	(8)										//!< Bits in comp res Id allocated to the bucket index
#define RMAN_CRESID_RES_ID_BITS			(32-RMAN_CRESID_BUCKET_INDEX_BITS)		//!< Bits in comp res Id allocated to the resource Id
#define RMAN_CRESID_MAX_RES_ID			((1<<RMAN_CRESID_RES_ID_BITS)-1)		//!< Max valid resource Id
#define RMAN_CRESID_RES_ID_MASK			(RMAN_CRESID_MAX_RES_ID)				//!< Resource Id mask
#define RMAN_CRESID_BUCKET_SHIFT		(RMAN_CRESID_RES_ID_BITS)				//!< Bits to shift bucket index
#define RMAN_CRESID_MAX_BUCKET_INDEX	((1<<RMAN_CRESID_BUCKET_INDEX_BITS)-1)	//!< Max valid bucket index

#define RMAN_MAX_ID 		4096		// max number of ids per bucket
#define RMAN_ID_BLOCKSIZE	256			// size of hash table for ids

/*!
******************************************************************************
 This structure contains the resource details for a resource registered with
 the resource manager.
******************************************************************************/
typedef struct RMAN_tag_sResource RMAN_sResource;

/*!
******************************************************************************
 This structure contains the bucket information.
******************************************************************************/
typedef struct
{
	LST_LINK;			/*!< List link (allows the structure to be part of a MeOS list).*/
	DQ_T				sResList;				//!< List of active resource structures
	IMG_UINT32			ui32BucketIndex;		//!< Bucket index
	IMG_HANDLE			hIdGenerator;			//!< Pointer to the resource from which resource ids are to be allocated
	IMG_UINT32			ui32ResCnt;				//!< Count of resources in the bucket

} RMAN_sBucket;

/*!
******************************************************************************
 This structure contains the resource details for a resource registered with
 the resource manager.
******************************************************************************/
struct RMAN_tag_sResource
{
	DQ_LINK;			/*!< DQ link (allows the structure to be part of a MeOS DQ list).*/
	RMAN_sBucket *		psBucket;				//!< Pointer to the bucket
	IMG_UINT32			ui32TypeId;				//!< "Type" id
	RMAN_pfnFree		pfnFree;				//!< Pointer to free callback function
    IMG_VOID *          pvParam;				//!< IMG_VOID * parameter
	IMG_UINT32			ui32ResId;				//!< Resource Id.
    IMG_HANDLE			hMutexHandle;			//!< Mutex handle, IMG_NULL of no mutex allocated
	IMG_CHAR *			pszResName;				//!< Resource name, IMG_NULL if no name
	RMAN_sResource *	psSharedResource;		//!< Pointer to shared resource - only valid for shared resources
	IMG_UINT32			ui32ReferenceCnt;		//!< Reference count - only used with the shared resource

};

static IMG_BOOL	gInitialised = IMG_FALSE;			//!< Indicates where the API has been initialised

static RMAN_sBucket *	gapsBucket[RMAN_CRESID_MAX_BUCKET_INDEX];	//!< Array of pointers to buckets

static RMAN_sBucket *	gpsGlobalResBucket = IMG_NULL;	//!< Global resource bucket

static RMAN_sBucket *	gpsSharedResBucket = IMG_NULL;		//!< Shared resource bucket
static IMG_HANDLE		ghSharedResMutexHandle = IMG_NULL;	//!< Shared resource mutex


static IMG_HANDLE globalMutext;
/*!
******************************************************************************

 @Function				RMAN_Initialise

******************************************************************************/
IMG_RESULT RMAN_Initialise(IMG_VOID)
{
	IMG_UINT32			ui32Result;

	/* If not initialised...*/
	if (!gInitialised)
	{
		/* Initialise the active buckets list...*/
		IMG_MEMSET(&gapsBucket[0], 0, sizeof(gapsBucket));

		/* Create mutex...*/
		ui32Result = SYSOSKM_CreateMutex(&ghSharedResMutexHandle);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS)
		{
			return ui32Result;
		}

		/* Set initialised flag...*/
		gInitialised = IMG_TRUE;

		/* Create the global resource bucket...*/
		ui32Result = RMAN_CreateBucket((IMG_HANDLE *)&gpsGlobalResBucket);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS)
		{
			return ui32Result;
		}

		/* Create the shared resource bucket...*/
		ui32Result = RMAN_CreateBucket((IMG_HANDLE *)&gpsSharedResBucket);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS)
		{
			return ui32Result;
		}

		SYSOSKM_CreateMutex(&globalMutext);
	}

	/* Return success...*/
	return IMG_SUCCESS;
}

IMGVIDEO_EXPORT_SYMBOL(RMAN_Initialise)

/*!
******************************************************************************

 @Function				RMAN_Deinitialise

******************************************************************************/
IMG_VOID RMAN_Deinitialise(IMG_VOID)
{
	IMG_UINT32				i;

	/* Make sure no other cpu is using the shared resources.  */
	SYSOSKM_DisableInt();

	/* If initialised...*/
	if (gInitialised)
	{
		/* Destroy the golbal resource bucket...*/
		RMAN_DestroyBucket(gpsGlobalResBucket);

		/* Destroy the shared resource bucket...*/
		RMAN_DestroyBucket(gpsSharedResBucket);

        /* Make sure we destroy the mutex after destroying the bucket. */
        SYSOSKM_DestroyMutex(globalMutext);

		/* Destroy mutex...*/
		SYSOSKM_DestroyMutex(ghSharedResMutexHandle);

		/* Check all buckets destroyed...*/
		for (i=0; i<RMAN_CRESID_MAX_BUCKET_INDEX; i++)
		{
			IMG_ASSERT(gapsBucket[i] == IMG_NULL);
		}

		/* Reset initialised flag...*/
		gInitialised = IMG_FALSE;
	}

	SYSOSKM_EnableInt();
}


/*!
******************************************************************************

 @Function				RMAN_CreateBucket

******************************************************************************/
IMG_RESULT RMAN_CreateBucket(
	IMG_HANDLE *		phResBHandle
)
{
	RMAN_sBucket *			psBucket;
	IMG_UINT32				i;
	IMG_RESULT              i32Result;

	IMG_ASSERT(gInitialised);

	/* Allocate a bucket structure...*/
	psBucket = IMG_MALLOC(sizeof(*psBucket));
	IMG_ASSERT(psBucket != IMG_NULL);
	if (psBucket == IMG_NULL)
	{
		return IMG_ERROR_OUT_OF_MEMORY;
	}
	IMG_MEMSET(psBucket, 0, sizeof(*psBucket));

	/* Intialise the resource list...*/
	DQ_init(&psBucket->sResList);

	/* The start allocating resource ids at the first...*/
    i32Result = IDGEN_CreateContext(RMAN_MAX_ID, RMAN_ID_BLOCKSIZE, IMG_FALSE, &psBucket->hIdGenerator);
	if(i32Result != IMG_SUCCESS)
	{
		IMG_FREE(psBucket);
		IMG_ASSERT(!"failed to create IDGEN context");
		return i32Result;
	}

	/* Locate free bucket index within the table...*/
	SYSOSKM_DisableInt();
	for (i=0; i<RMAN_CRESID_MAX_BUCKET_INDEX; i++)
	{
		if (gapsBucket[i] == IMG_NULL)
		{
			break;
		}
	}
	if (i >= RMAN_CRESID_MAX_BUCKET_INDEX) {
	    SYSOSKM_EnableInt();
        IDGEN_DestroyContext(psBucket->hIdGenerator);
        IMG_FREE(psBucket);
	    IMG_ASSERT(!"No free buckets left");
	    return IMG_ERROR_GENERIC_FAILURE;
	}

	/* Allocate bucket index...*/
	psBucket->ui32BucketIndex = i;
	gapsBucket[i] = psBucket;

	SYSOSKM_EnableInt();

	/* Return the bucket handle...*/
	*phResBHandle = psBucket;

	return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(RMAN_CreateBucket)


/*!
******************************************************************************

 @Function				RMAN_DestroyBucket

******************************************************************************/
IMG_VOID RMAN_DestroyBucket(
	IMG_HANDLE				hResBHandle
)
{
	RMAN_sBucket *			psBucket = (RMAN_sBucket *)hResBHandle;

	IMG_ASSERT(gInitialised);

	IMG_ASSERT(psBucket != IMG_NULL);
	if (psBucket== IMG_NULL)
	{
		return;
	}

	IMG_ASSERT(psBucket->ui32BucketIndex < RMAN_CRESID_MAX_BUCKET_INDEX);
	IMG_ASSERT(gapsBucket[psBucket->ui32BucketIndex] != IMG_NULL);

	/* Free all resources from the bucket...*/
	RMAN_FreeResources(hResBHandle, RMAN_TYPE_P1);
	RMAN_FreeResources(hResBHandle, RMAN_TYPE_P2);
	RMAN_FreeResources(hResBHandle, RMAN_TYPE_P3);
	RMAN_FreeResources(hResBHandle, RMAN_ALL_TYPES);

    /* free sticky resources last: other resources are dependent on them */
	RMAN_FreeResources(hResBHandle, RMAN_STICKY);
	/* Use proper locking around global buckets.  */
	SYSOSKM_DisableInt();

	/* Free from array of bucket pointers...*/
	gapsBucket[psBucket->ui32BucketIndex] = IMG_NULL;

	SYSOSKM_EnableInt();

	/* Free the bucket itself...*/
	IDGEN_DestroyContext(psBucket->hIdGenerator);
	IMG_FREE(psBucket);
}
IMGVIDEO_EXPORT_SYMBOL(RMAN_DestroyBucket)

/*!
******************************************************************************

 @Function				RMAN_GetGlobalBucket

******************************************************************************/
IMG_HANDLE RMAN_GetGlobalBucket(IMG_VOID)
{
	IMG_ASSERT(gInitialised);
	IMG_ASSERT(gpsGlobalResBucket != IMG_NULL);

	/* Return the handle of the global resource bucket...*/
	return gpsGlobalResBucket;
}

/*!
******************************************************************************

 @Function				RMAN_RegisterResource

******************************************************************************/
IMG_RESULT RMAN_RegisterResource(
	IMG_HANDLE				hResBHandle,
	IMG_UINT32				ui32TypeId,
	RMAN_pfnFree			pfnFree,
    IMG_VOID *              pvParam,
    IMG_HANDLE *			phResHandle,
    IMG_UINT32 *			pui32ResId
)
{
	RMAN_sBucket *				psBucket = (RMAN_sBucket *) hResBHandle;
	RMAN_sResource *			psResource;
	IMG_RESULT                  i32Result;

	IMG_ASSERT(gInitialised);
	IMG_ASSERT(ui32TypeId		!= RMAN_ALL_TYPES);

	IMG_ASSERT(hResBHandle != IMG_NULL);
	if (hResBHandle == IMG_NULL)
	{
		return IMG_ERROR_GENERIC_FAILURE;
	}

	/* Allocate a resource structure...*/
	psResource = IMG_MALLOC(sizeof(*psResource));
	IMG_ASSERT(psResource != IMG_NULL);
	if (psResource == IMG_NULL)
	{
		return IMG_ERROR_OUT_OF_MEMORY;
	}
	IMG_MEMSET(psResource, 0, sizeof(*psResource));

	/* Fill in the resource structure...*/
	psResource->psBucket		= psBucket;
	psResource->ui32TypeId		= ui32TypeId;
	psResource->pfnFree			= pfnFree;
	psResource->pvParam         = pvParam;

	/* Allocate resource Id...*/
	SYSOSKM_LockMutex(globalMutext);
    i32Result = IDGEN_AllocId(psBucket->hIdGenerator, psResource, &psResource->ui32ResId);
    SYSOSKM_UnlockMutex(globalMutext);
    if(i32Result != IMG_SUCCESS)
    {
        IMG_ASSERT(!"failed to allocate RMAN id");
        return i32Result;
    }
    IMG_ASSERT(psResource->ui32ResId <= RMAN_CRESID_MAX_RES_ID);

    // add this resource to the bucket
	SYSOSKM_DisableInt();
    DQ_addTail(&psBucket->sResList, psResource);

	/* Update count of resources...*/
	psBucket->ui32ResCnt++;
	SYSOSKM_EnableInt();

	/* If resource handle required...*/
	if (phResHandle != IMG_NULL)
	{
		*phResHandle = psResource;
	}

	/* If resource id required...*/
	if (pui32ResId != IMG_NULL)
	{
		*pui32ResId = RMAN_GetResourceId(psResource);
	}

	/* Return success...*/
	return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(RMAN_RegisterResource)


/*!
******************************************************************************

 @Function				RMAN_GetResourceId

******************************************************************************/
IMG_UINT32 RMAN_GetResourceId(
    IMG_HANDLE			hResHandle
)
{
	RMAN_sResource *			psResource = hResHandle;
	IMG_UINT32					ui32ExtResId;

	IMG_ASSERT(hResHandle != IMG_NULL);
	if (hResHandle == IMG_NULL)
	{
		return 0;
	}

	IMG_ASSERT(psResource->ui32ResId <= RMAN_CRESID_MAX_RES_ID);
	IMG_ASSERT(psResource->psBucket->ui32BucketIndex < RMAN_CRESID_MAX_BUCKET_INDEX);
	if (psResource->psBucket->ui32BucketIndex >= RMAN_CRESID_MAX_BUCKET_INDEX) {
	    return 0;
	}

	ui32ExtResId = (((psResource->psBucket->ui32BucketIndex + 1)<<RMAN_CRESID_BUCKET_SHIFT) | psResource->ui32ResId);

	return ui32ExtResId;
}


/*!
******************************************************************************

 @Function				rman_GetResource

******************************************************************************/
static IMG_VOID * rman_GetResource(
	IMG_HANDLE				hResBHandle,
	IMG_UINT32				ui32ResId,
	IMG_UINT32				ui32TypeId,
    IMG_HANDLE *			phResHandle
)
{
	RMAN_sBucket *				psBucket = (RMAN_sBucket *) hResBHandle;
	RMAN_sResource *			psResource;
	IMG_RESULT					i32Result;

	IMG_ASSERT(ui32ResId <= RMAN_CRESID_MAX_RES_ID);

	/* Loop over the resources in this bucket till we find the required id...*/
	//SYSOSKM_DisableInt();
	SYSOSKM_LockMutex(globalMutext);
	i32Result = IDGEN_GetHandle(psBucket->hIdGenerator, ui32ResId, (void**)&psResource);
	SYSOSKM_UnlockMutex(globalMutext);
	//SYSOSKM_EnableInt();
	if(i32Result != IMG_SUCCESS)
	{
		IMG_ASSERT(!"failed to get RMAN resource");
		return IMG_NULL;
	}

	/* If the resource handle is required...*/
	if (phResHandle != IMG_NULL)
	{
		/* Return it...*/
		*phResHandle = psResource;
	}

	/* If the resource was not found...*/
	IMG_ASSERT(psResource != IMG_NULL);
	IMG_ASSERT((IMG_VOID*)psResource != &psBucket->sResList);
	if ( (psResource == IMG_NULL) || ((IMG_VOID*)psResource == &psBucket->sResList) )
	{
		return IMG_NULL;
	}

	/* Cross check the type...*/
	IMG_ASSERT(ui32TypeId == psResource->ui32TypeId);

	/* Return the resource....*/
	return psResource->pvParam;
}


/*!
******************************************************************************

 @Function				RMAN_GetResource

******************************************************************************/
IMG_RESULT RMAN_GetResource(
	IMG_UINT32				ui32ResId,
	IMG_UINT32				ui32TypeId,
    IMG_VOID **				ppvParam,
    IMG_HANDLE *			phResHandle
)
{
	IMG_UINT32				ui32BucketIndex = (ui32ResId>>RMAN_CRESID_BUCKET_SHIFT)-1;
	IMG_UINT32				ui32IntResId	= (ui32ResId & RMAN_CRESID_RES_ID_MASK);
    IMG_VOID *				pvParam;

	//IMG_ASSERT(ui32BucketIndex < RMAN_CRESID_MAX_BUCKET_INDEX);
	if (ui32BucketIndex >= RMAN_CRESID_MAX_BUCKET_INDEX) {
	    /* Happens when ui32BucketIndex == 0 */
	    return IMG_ERROR_INVALID_ID;
	}
	//IMG_ASSERT(ui32IntResId <= RMAN_CRESID_MAX_RES_ID);
	if (ui32IntResId > RMAN_CRESID_MAX_RES_ID) {
	    return IMG_ERROR_INVALID_ID;
	}
	//IMG_ASSERT(gapsBucket[ui32BucketIndex] != IMG_NULL);
	if (gapsBucket[ui32BucketIndex] == NULL) {
	    return IMG_ERROR_INVALID_ID;
	}

	pvParam = rman_GetResource(gapsBucket[ui32BucketIndex], ui32IntResId, ui32TypeId, phResHandle);

	/* If we didn't find the resource...*/
	if (pvParam == IMG_NULL)
	{
		return IMG_ERROR_INVALID_ID;
	}

	/* Return the resource...*/
	if (ppvParam != IMG_NULL)
	{
		*ppvParam = pvParam;
	}

	return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(RMAN_GetResource)

/*!
******************************************************************************

 @Function				rman_CloneResourceHandle

******************************************************************************/
static IMG_RESULT rman_CloneResourceHandle(
    IMG_HANDLE				hResHandle,
	IMG_HANDLE				hResBHandle,
    IMG_HANDLE *			phResHandle,
    IMG_UINT32 *			pui32ResId
)
{
	RMAN_sResource *			psResource = hResHandle;
	RMAN_sResource *			psCloneResourceHandle;
	IMG_UINT32					ui32Result;

	/* If this resource is not already shared...*/
	if (psResource->psSharedResource == IMG_NULL)
	{
		ui32Result = RMAN_RegisterResource(gpsSharedResBucket, psResource->ui32TypeId, psResource->pfnFree, psResource->pvParam, (IMG_HANDLE *)&psResource->psSharedResource, IMG_NULL);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS)
		{
			return ui32Result;
		}

		/* Update the no. of references to the shared resource...*/
		psResource->psSharedResource->ui32ReferenceCnt++;
	}

	/* Register this resource...*/
	ui32Result = RMAN_RegisterResource(hResBHandle, psResource->ui32TypeId, psResource->pfnFree, psResource->pvParam, (IMG_HANDLE *)&psCloneResourceHandle, IMG_NULL);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	/* Update reference to shared resource...*/
	psResource->psSharedResource->ui32ReferenceCnt++;
	psCloneResourceHandle->psSharedResource = psResource->psSharedResource;

	/* If resource handle required...*/
	if (phResHandle != IMG_NULL)
	{
		*phResHandle = psCloneResourceHandle;
	}

	/* If resource id required...*/
	if (pui32ResId != IMG_NULL)
	{
		*pui32ResId = RMAN_GetResourceId(psResource);
	}

	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function				RMAN_CloneResourceHandle

******************************************************************************/
IMG_RESULT RMAN_CloneResourceHandle(
    IMG_HANDLE				hResHandle,
	IMG_HANDLE				hResBHandle,
    IMG_HANDLE *			phResHandle,
    IMG_UINT32 *			pui32ResId
)
{
	IMG_UINT32				ui32Result;

	IMG_ASSERT(gInitialised);

	IMG_ASSERT(hResHandle != IMG_NULL);
	if (hResHandle == IMG_NULL)
	{
		return IMG_ERROR_GENERIC_FAILURE;
	}

	IMG_ASSERT(hResBHandle != IMG_NULL);
	if (hResBHandle == IMG_NULL)
	{
		return IMG_ERROR_GENERIC_FAILURE;
	}

	/* Lock the shared resources...*/
	SYSOSKM_LockMutex(ghSharedResMutexHandle);

	/* Create the clone...*/
	ui32Result = rman_CloneResourceHandle(hResHandle, hResBHandle, phResHandle, pui32ResId);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		SYSOSKM_UnlockMutex(ghSharedResMutexHandle);
		return ui32Result;
	}

	/* Exit...*/
	SYSOSKM_UnlockMutex(ghSharedResMutexHandle);
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function				RMAN_GetNamedResource

******************************************************************************/
IMG_RESULT RMAN_GetNamedResource(
	IMG_CHAR *				pszResName,
	RMAN_pfnAlloc			pfnAlloc,
	IMG_VOID *				pvAllocInfo,
	IMG_HANDLE				hResBHandle,
	IMG_UINT32				ui32TypeId,
	RMAN_pfnFree			pfnFree,
    IMG_VOID **             ppvParam,
    IMG_HANDLE *			phResHandle,
    IMG_UINT32 *			pui32ResId
)
{
	RMAN_sBucket *				psBucket = hResBHandle;
	RMAN_sResource *			psResource;
	IMG_UINT32					ui32Result;
	IMG_VOID *					pvParam;
	IMG_BOOL					bFound = IMG_FALSE;
	IMG_CHAR*                   pszResNameDup;

	IMG_ASSERT(gInitialised);

	IMG_ASSERT(hResBHandle != IMG_NULL);
	if (hResBHandle == IMG_NULL)
	{
		return IMG_ERROR_GENERIC_FAILURE;
	}

	/* Lock the shared resources...*/
	SYSOSKM_DisableInt();
	psResource = (RMAN_sResource *)DQ_first(&psBucket->sResList);
	while ( (psResource != IMG_NULL) && ((IMG_VOID *)psResource != &psBucket->sResList) )
	{
		/* If resource already in the shared list...*/
		if ( (psResource->pszResName != IMG_NULL) && (IMG_STRCMP(pszResName, psResource->pszResName) == 0) )
		{
			IMG_ASSERT(psResource->pfnFree == pfnFree);
			bFound = IMG_TRUE;
			break;
		}

		/* Move to next resource...*/
		psResource = (RMAN_sResource *)DQ_next(psResource);
	}
	SYSOSKM_EnableInt();

	/* If the named resource was not found...*/
	if (!bFound)
	{
		/* Allocate the resource...*/
		ui32Result = pfnAlloc(pvAllocInfo, &pvParam);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS)
		{
			return ui32Result;
		}

		/* Register the named resource...*/
		ui32Result = RMAN_RegisterResource(hResBHandle, ui32TypeId, pfnFree, pvParam, (IMG_HANDLE *)&psResource, IMG_NULL);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS)
		{
			SYSOSKM_EnableInt();
			return ui32Result;
		}

		/* Set resource name...*/
		pszResNameDup = IMG_STRDUP(pszResName);
		SYSOSKM_DisableInt();
		psResource->pszResName = pszResNameDup;
		SYSOSKM_EnableInt();
	}

	/* Return the pvParam value...*/
	*ppvParam = psResource->pvParam;

	/* If resource handle required...*/
	if (phResHandle != IMG_NULL)
	{
		*phResHandle = psResource;
	}

	/* If resource id required...*/
	if (pui32ResId != IMG_NULL)
	{
		*pui32ResId = RMAN_GetResourceId(psResource);
	}

	/* Exit...*/
	return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function				rman_FreeResource

******************************************************************************/
static IMG_VOID rman_FreeResource(
	RMAN_sResource *		psResource
)
{
	RMAN_sBucket *				psBucket = psResource->psBucket;

	/* Remove the resource from the active list...*/
	SYSOSKM_DisableInt();

	/* Remove from list...*/
	DQ_remove(psResource);

	/* Update count of resources...*/
	psBucket->ui32ResCnt--;

	SYSOSKM_EnableInt();

	/* If mutex associated with the resource...*/
	if (psResource->hMutexHandle != IMG_NULL)
	{
		/* Destroy mutex...*/
		SYSOSKM_DestroyMutex(psResource->hMutexHandle);
	}

	/* If this resource is not already shared...*/
	if (psResource->psSharedResource != IMG_NULL)
	{
		/* Lock the shared resources...*/
		SYSOSKM_LockMutex(ghSharedResMutexHandle);

		/* Update the reference count...*/
		IMG_ASSERT(psResource->psSharedResource->ui32ReferenceCnt != 0);
		psResource->psSharedResource->ui32ReferenceCnt--;

		/* If this is the last free for the shared resource...*/
		if (psResource->psSharedResource->ui32ReferenceCnt == 0)
		{
			/* Free the shared resource...*/
			rman_FreeResource(psResource->psSharedResource);
		}
		/* UnLock the shared resources...*/
		SYSOSKM_UnlockMutex(ghSharedResMutexHandle);
	}
	else
	{
		/* If there is a free callback function....*/
		if (psResource->pfnFree != IMG_NULL)
		{
			/* Call resource free callback...*/
			psResource->pfnFree(psResource->pvParam);
		}
	}

	/* If the resource has a name then free it...*/
	if (psResource->pszResName != IMG_NULL)
	{
		IMG_FREE(psResource->pszResName);
	}

    /* Free the resource ID. */
	SYSOSKM_LockMutex(globalMutext);
    IDGEN_FreeId(psBucket->hIdGenerator, psResource->ui32ResId);
    SYSOSKM_UnlockMutex(globalMutext);

	/* Free a resource structure...*/
	IMG_FREE(psResource);
}


/*!
******************************************************************************

 @Function				RMAN_FreeResource

******************************************************************************/
IMG_VOID RMAN_FreeResource(
    IMG_HANDLE				hResHandle
)
{
	RMAN_sResource *			psResource;

	IMG_ASSERT(gInitialised);

	IMG_ASSERT(hResHandle != IMG_NULL);
	if (hResHandle == IMG_NULL)
	{
		return;
	}

	/* Get access to the resource structure...*/
	psResource = (RMAN_sResource *)hResHandle;


	/* Free resource...*/
	rman_FreeResource(psResource);
}
IMGVIDEO_EXPORT_SYMBOL(RMAN_FreeResource)

/*!
******************************************************************************

 @Function				RMAN_LockResource

******************************************************************************/
IMG_VOID RMAN_LockResource(
    IMG_HANDLE			hResHandle
)
{
	RMAN_sResource *			psResource;
	IMG_UINT32					ui32Result;

	IMG_ASSERT(gInitialised);

	IMG_ASSERT(hResHandle != IMG_NULL);
	if (hResHandle == IMG_NULL)
	{
		return;
	}

	/* Get access to the resource structure...*/
	psResource = (RMAN_sResource *)hResHandle;

	/* If this is a shared resource...*/
	if (psResource->psSharedResource != IMG_NULL)
	{
		/* We need to lock/unlock the underlying shared resource...*/
		psResource = psResource->psSharedResource;
	}

	/* If no mutex associated with this resource...*/
	if (psResource->hMutexHandle == IMG_NULL)
	{
		/* Create one...*/
		ui32Result = SYSOSKM_CreateMutex(&psResource->hMutexHandle);
		IMG_ASSERT(ui32Result == IMG_SUCCESS);
		if (ui32Result != IMG_SUCCESS)
		{
			return;
		}
	}

	/* lock it...*/
	SYSOSKM_LockMutex(psResource->hMutexHandle);
}

/*!
******************************************************************************

 @Function				RMAN_UnlockResource

******************************************************************************/
IMG_VOID RMAN_UnlockResource(
    IMG_HANDLE			hResHandle
)
{
	RMAN_sResource *			psResource;

	IMG_ASSERT(gInitialised);

	IMG_ASSERT(hResHandle != IMG_NULL);
	if (hResHandle == IMG_NULL)
	{
		return;
	}

	/* Get access to the resource structure...*/
	psResource = (RMAN_sResource *)hResHandle;

	/* If this is a shared resource...*/
	if (psResource->psSharedResource != IMG_NULL)
	{
		/* We need to lock/unlock the underlying shared resource...*/
		psResource = psResource->psSharedResource;
	}

	IMG_ASSERT (psResource->hMutexHandle != IMG_NULL);

	/* Unlock mutex...*/
	SYSOSKM_UnlockMutex(psResource->hMutexHandle);
}


/*!
******************************************************************************

 @Function				RMAN_FreeResources

******************************************************************************/
IMG_VOID RMAN_FreeResources(
	IMG_HANDLE					hResBHandle,
	IMG_UINT32					ui32TypeId
)
{
	RMAN_sBucket *				psBucket = (RMAN_sBucket *) hResBHandle;
	RMAN_sResource *			psResource;

	IMG_ASSERT(gInitialised);

	IMG_ASSERT(hResBHandle != IMG_NULL);
	if (hResBHandle == IMG_NULL)
	{
		return;
	}

	/* Scan the active list looking for the resources to be freed...*/
	SYSOSKM_DisableInt();
	psResource = (RMAN_sResource *)DQ_first(&psBucket->sResList);
	while (
			(psResource != IMG_NULL) &&
			((IMG_VOID*)psResource != &psBucket->sResList)
			)
	{
		/* If this is resource is to be removed...*/
		if ( ((ui32TypeId == RMAN_ALL_TYPES)  && (psResource->ui32TypeId != RMAN_STICKY)) || (psResource->ui32TypeId == ui32TypeId) )
		{
			/* Yes, remove it...*/
			/* Free current resource...*/
			SYSOSKM_EnableInt();
			rman_FreeResource(psResource);
			SYSOSKM_DisableInt();

			/* Restart from the begining of the list...*/
			psResource = (RMAN_sResource *)DQ_first(&psBucket->sResList);
		}
		else
		{
			/* Move to next resource...*/
			psResource = (RMAN_sResource *)LST_next(psResource);
		}
	}
	SYSOSKM_EnableInt();
}


