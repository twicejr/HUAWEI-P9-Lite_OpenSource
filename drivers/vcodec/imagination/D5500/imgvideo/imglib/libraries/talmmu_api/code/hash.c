/*!
 *****************************************************************************
 *
 * @File       hash.c
 * @Title      Self scaling hash tables.
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

#include "hash.h"
#include "pool.h"
#include "trace.h"
#include "img_types.h"
#include "img_defs.h"
#include "img_errors.h"

#define private_max(a,b) ((a)>(b)?(a):(b))

//pool of struct hash objects
static struct sPool * gpsHashpool = IMG_NULL;

//pool of struct sBucket objects
static struct sPool * gpsBucketPool = IMG_NULL;

static IMG_BOOL gbInitialised = IMG_FALSE;

//Each entry in a hash table is placed into a sBucket
struct sBucket
{
	//the ->psNext sBucket on the same chain
	struct sBucket * psNext;

	//entry key
	IMG_UINT64 ui64Key;

	//entry value
	IMG_UINTPTR uipValue;
};

struct sHash 
{
	//the hash table array
	struct sBucket ** ppsTable;
	
	//current size of the hash table
	IMG_UINT32 ui32Size;	

	//number of entries currently in the hash table
	IMG_UINT32 ui32Count;

	//the minimum size that the hash table should be re-sized to
	IMG_UINT32 ui32MinimumSize;
};

/*!
******************************************************************************

 @Function				hash_Func

 @Description

 Hash function intended for hashing addresses.

 @Input	    ui64Vale    : The key to hash.

 @Input	    ui32Size    : The size of the hash table

 @Return    ui32Hash	: The hash value.

*******************************************************************************/
static IMG_UINT32 hash_Func(
    IMG_UINT64 ui64Vale, 
    IMG_UINT32 ui32Size)
{ 
	IMG_UINT32 ui32Hash = (IMG_UINT32)(ui64Vale);
	ui32Hash += (ui32Hash << 12);
	ui32Hash ^= (ui32Hash >> 22);
	ui32Hash += (ui32Hash << 4);
	ui32Hash ^= (ui32Hash >> 9);
	ui32Hash += (ui32Hash << 10);
	ui32Hash ^= (ui32Hash >> 2);
	ui32Hash += (ui32Hash << 7);
	ui32Hash ^= (ui32Hash >> 12);
	ui32Hash &= (ui32Size-1);
	return ui32Hash;
}

/*!
******************************************************************************

 @Function				hash_ChainInsert

 @Description

 Hash function intended for hashing addresses.

 @Input	    psBucket    : The sBucket

 @Input	    ppsTable    : The hash table

 @Input	    ui32Size    : The size of the hash table

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
static IMG_RESULT hash_ChainInsert(
    struct sBucket * psBucket, 
    struct sBucket ** ppsTable, 
    IMG_UINT32 ui32Size
)
{
	IMG_UINT32 ui32ui32Idx;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

	IMG_ASSERT(IMG_NULL != psBucket);
	IMG_ASSERT(IMG_NULL != ppsTable);
	IMG_ASSERT(0 != ui32Size);

    if (IMG_NULL == psBucket ||
        IMG_NULL == ppsTable ||
        0 == ui32Size)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

	ui32ui32Idx = hash_Func(psBucket->ui64Key, ui32Size);

    IMG_ASSERT(ui32ui32Idx < ui32Size);
    if(ui32ui32Idx < ui32Size)
    {
        ui32Result = IMG_SUCCESS;
        psBucket->psNext = ppsTable[ui32ui32Idx];
        ppsTable[ui32ui32Idx] = psBucket;
    }

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				hash_Rehash

 @Description

 Iterate over every entry in an old hash table and rehash into the new table.
                	
 @Input	    ppsOldTable : The old hash table

 @Input	    ui32OldSize : The size of the old hash table

 @Input	    ppsNewTable : The new hash table

 @Input	    ui32NewSize : The size of the new hash table

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
static IMG_RESULT hash_Rehash (
    struct sBucket ** ppsOldTable, 
    IMG_UINT32 ui32OldSize,
    struct sBucket ** ppsNewTable,
    IMG_UINT32 ui32NewSize)
{
	IMG_UINT32 ui32ui32Idx;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != ppsOldTable);
    IMG_ASSERT(IMG_NULL != ppsNewTable);

    if (IMG_NULL == ppsOldTable ||
        IMG_NULL == ppsNewTable)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

	for (ui32ui32Idx = 0; ui32ui32Idx < ui32OldSize; ui32ui32Idx++)
    {
		struct sBucket * psBucket;
        struct sBucket * psNexBucket;

		psBucket = ppsOldTable[ui32ui32Idx];
		while (IMG_NULL != psBucket)
		{
			psNexBucket = psBucket->psNext;
            ui32Result = hash_ChainInsert (psBucket, ppsNewTable, ui32NewSize);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {
                ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                goto error;
            }
			psBucket = psNexBucket;
		}
    }
    ui32Result = IMG_SUCCESS;

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				hash_Resize

 @Description

 Attempt to resize a hash table, failure to allocate a new larger hash table 
 is not considered a hard failure. We simply continue and allow the table to
 fill up, the effect is to allow hash chains to become longer.
                	
 @Input	    psTable : Pointer to the hash table

 @Input	    ui32NewSize : The size of the new hash table

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
static IMG_RESULT hash_Resize(
    struct sHash * psHash, 
    IMG_UINT32 ui32NewSize
)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psHash);
    if (IMG_NULL == psHash)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

	if (ui32NewSize != psHash->ui32Size)
    {
		struct sBucket ** ppsNewTable;

		trace (("hash resize: oldsize=%d  newsize=%d  count=%d\n", psHash->ui32Size, ui32NewSize, psHash->ui32Countcount));

		ppsNewTable = IMG_MALLOC(sizeof (struct sBucket *) * ui32NewSize);
        IMG_ASSERT(IMG_NULL != ppsNewTable);
        if(IMG_NULL == ppsNewTable)
        {
            ui32Result = IMG_ERROR_MALLOC_FAILED;
            goto error;
        }
		if (IMG_NULL != ppsNewTable)
		{
			IMG_UINT32 ui32Idx;
			for (ui32Idx = 0; ui32Idx < ui32NewSize; ui32Idx++)
            {
				ppsNewTable[ui32Idx] = IMG_NULL;
            }
			ui32Result = hash_Rehash(psHash->ppsTable, psHash->ui32Size, ppsNewTable, ui32NewSize);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {
                IMG_FREE(ppsNewTable);
                ppsNewTable = IMG_NULL;
                ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                goto error;
            }

            if(IMG_NULL != psHash->ppsTable)
            {
                IMG_FREE(psHash->ppsTable);
            }
			psHash->ppsTable = ppsNewTable;
			psHash->ui32Size = ui32NewSize;
		}
    }
    ui32Result = IMG_SUCCESS;

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_HASH_Initialise

 @Description

 To initialise the hash module.

 @Input	    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT VID_HASH_Initialise(IMG_VOID)
{
    IMG_UINT32 ui32Result = IMG_ERROR_ALREADY_COMPLETE;

	trace(("VID_HASH_Initialise ()\n"));

    IMG_ASSERT(IMG_FALSE == gbInitialised);
    if(!gbInitialised)
    {
        IMG_ASSERT(IMG_NULL == gpsHashpool);
        IMG_ASSERT(IMG_NULL == gpsBucketPool);
        if (IMG_NULL != gpsHashpool ||
            IMG_NULL != gpsBucketPool)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

        ui32Result = POOL_Create("img-hash", sizeof (struct sHash), &gpsHashpool);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

        ui32Result = POOL_Create("img-sBucket", sizeof (struct sBucket), &gpsBucketPool);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            if(IMG_NULL != gpsBucketPool)
            {
                ui32Result = POOL_Delete(gpsBucketPool);
                IMG_ASSERT(IMG_SUCCESS == ui32Result);
                gpsBucketPool = IMG_NULL;
            }
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
        gbInitialised = IMG_TRUE;
        ui32Result = IMG_SUCCESS;
    }

error:
	return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_HASH_Finalise

 @Description

 To finalise the hash module. All allocated hash tables should
	            be deleted before calling this function.

 @Input	    None

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT VID_HASH_Finalise (IMG_VOID)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    trace (("VID_HASH_Finalise ()\n"));

    IMG_ASSERT(IMG_TRUE == gbInitialised);
    if(gbInitialised)
    {
        if(IMG_NULL != gpsHashpool)
        {
            ui32Result = POOL_Delete(gpsHashpool);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {
                //Error Handling
            }
            gpsHashpool = IMG_NULL;
        }

        if(IMG_NULL != gpsBucketPool)
        {
            ui32Result = POOL_Delete(gpsBucketPool);
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {
                //Error Handling
            }
            gpsBucketPool = IMG_NULL;
        }

        gbInitialised = IMG_FALSE;
        ui32Result = IMG_SUCCESS;
    }

    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_HASH_Create

 @Description

 Create a self scaling hash table.

 @Input	    ui32InitialSize : Initial and minimum size of the hash table.

 @Output    ppsHash         : Will countin the hash table handle or IMG_NULL.

 @Return    IMG_RESULT      : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT VID_HASH_Create(
    IMG_UINT32      ui32InitialSize, 
    struct sHash ** const  ppsHash
)
{
	IMG_UINT32 ui32Idx;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    struct sHash * psHash = IMG_NULL;

    IMG_ASSERT(IMG_NULL != ppsHash);
    if (IMG_NULL == ppsHash)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    trace (("VID_HASH_Create (%d)\n", ui32InitialSize));

    IMG_ASSERT(IMG_TRUE == gbInitialised);
    if(gbInitialised)
    {
        POOL_Alloc(gpsHashpool, ((IMG_HANDLE *)&psHash));
        if (IMG_NULL == psHash)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            (*ppsHash) = IMG_NULL;
            goto error;
        }

        psHash->ui32Count = 0;
        psHash->ui32Size = ui32InitialSize;
        psHash->ui32MinimumSize = ui32InitialSize;

        psHash->ppsTable = IMG_MALLOC(sizeof (struct sBucket *) * psHash->ui32Size);
        if (IMG_NULL == psHash->ppsTable)
        {
            ui32Result = POOL_Free(gpsHashpool, psHash);
            IMG_ASSERT(IMG_SUCCESS != ui32Result);
            if (IMG_SUCCESS != ui32Result)
            {
                ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            }
            ui32Result |= IMG_ERROR_MALLOC_FAILED;
            (*ppsHash) = IMG_NULL;
            goto error;
        }

        for (ui32Idx = 0; ui32Idx < psHash->ui32Size; ui32Idx++)
        {
            psHash->ppsTable[ui32Idx] = IMG_NULL;
        }

        (*ppsHash) = psHash;
        ui32Result = IMG_SUCCESS;
    }

error:
	return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_HASH_Delete

 @Description

 To delete a hash table, all entries in the table should be
	            removed before calling this function.

 @Input	    psHash      : Hash table pointer

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT VID_HASH_Delete (struct sHash * const psHash)
{
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psHash);
    if (IMG_NULL == psHash)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    IMG_ASSERT(IMG_TRUE == gbInitialised);
    if(gbInitialised)
    {
        IMG_ASSERT(0 == psHash->ui32Count);
        if(0 != psHash->ui32Count)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

        if(IMG_NULL != psHash->ppsTable)
        {
            IMG_FREE(psHash->ppsTable);
            psHash->ppsTable = IMG_NULL;
        }

        ui32Result = POOL_Free(gpsHashpool, psHash);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if (IMG_SUCCESS != ui32Result)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
    }

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_HASH_Insert

 @Description

 To insert a key value pair into a hash table.

 @Input	    psHash      : Hash table pointer

 @Input	    ui64Key     : Key value

 @Input	    uipValue    : The value associated with the key.

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT VID_HASH_Insert(
    struct  sHash * const   psHash, 
            IMG_UINT64      ui64Key, 
            IMG_UINTPTR     uipValue
)
{
	struct sBucket * psBucket = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;

    IMG_ASSERT(IMG_NULL != psHash);
    if (IMG_NULL == psHash)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    IMG_ASSERT(IMG_TRUE == gbInitialised);
    if(gbInitialised)
    {
        ui32Result = POOL_Alloc(gpsBucketPool, ((IMG_HANDLE *)&psBucket));
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        IMG_ASSERT(IMG_NULL != psBucket);
	    if (IMG_SUCCESS != ui32Result ||
            IMG_NULL == psBucket)
        {
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }
        psBucket->psNext = IMG_NULL;
	    psBucket->ui64Key = ui64Key;
	    psBucket->uipValue = uipValue;

	    ui32Result = hash_ChainInsert(psBucket, psHash->ppsTable, psHash->ui32Size);
        IMG_ASSERT(IMG_SUCCESS == ui32Result);
        if(IMG_SUCCESS != ui32Result)
        {
            POOL_Free(gpsBucketPool, ((IMG_HANDLE *)&psBucket));
            ui32Result = IMG_ERROR_UNEXPECTED_STATE;
            goto error;
        }

	    psHash->ui32Count++;

	    //check if we need to think about re-balancing
	    if ((psHash->ui32Count << 1) > psHash->ui32Size)
        {
            ui32Result = hash_Resize(psHash, (psHash->ui32Size << 1));
            IMG_ASSERT(IMG_SUCCESS == ui32Result);
            if(IMG_SUCCESS != ui32Result)
            {   ui32Result = IMG_ERROR_UNEXPECTED_STATE;
                goto error;
            }
        }
        ui32Result = IMG_SUCCESS;
    }

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				VID_HASH_Remove

 @Description

 To remove a key value pair from a hash table

 @Input	    psHash      : Hash table pointer

 @Input	    ui64Key     : Key value

 @Input	    uipResult   : 0 if the key is missing or the value associated with the key.

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT VID_HASH_Remove(
    struct  sHash * const       psHash, 
            IMG_UINT64          ui64Key, 
            IMG_UINTPTR * const puipResult
)
{
	IMG_UINT32 ui32Idx;
    IMG_UINT32 ui32Result = IMG_ERROR_FATAL;
    struct sBucket ** ppsBucket = IMG_NULL;

    IMG_ASSERT(IMG_NULL != psHash);
    if (IMG_NULL == psHash)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

	ui32Idx = hash_Func(ui64Key, psHash->ui32Size);
  
	for (ppsBucket = &(psHash->ppsTable[ui32Idx]); IMG_NULL != (*ppsBucket); ppsBucket = &((*ppsBucket)->psNext))
    {
		if ((*ppsBucket)->ui64Key == ui64Key)
		{
			struct sBucket * psBucket = (*ppsBucket);
			IMG_UINTPTR uipValue = psBucket->uipValue;

			(*ppsBucket) = psBucket->psNext;
			ui32Result = POOL_Free(gpsBucketPool, psBucket);

			psHash->ui32Count--;

			//check if we need to think about re-balencing
			if (psHash->ui32Size > (psHash->ui32Count << 2) && psHash->ui32Size > psHash->ui32MinimumSize)
            {
				ui32Result = hash_Resize(psHash, private_max((psHash->ui32Size >> 1), psHash->ui32MinimumSize));
            }
			(*puipResult) = uipValue;
            ui32Result = IMG_SUCCESS;
            break;
		}
    }

error:
    return ui32Result;
}

#ifdef HASH_TRACE
/*!
******************************************************************************

 @Function				VID_HASH_Dump

 @Description

 To dump the contents of a hash table in human readable form.

 @Input	    psHash      : The hash table to dump

 @Return    IMG_RESULT  : IMG_SUCCESS or an error code.

********************************************************************************/
IMG_RESULT VID_HASH_Dump(const struct sHash * const psHash)
{
	IMG_UINT32 ui32Idx;
	IMG_UINT32 ui32MaxLength = 0;
	IMG_UINT32 ui32EmptyCount = 0;
    IMG_UINT32 ui32Result;

    IMG_ASSERT(IMG_NULL != psHash);
    if (IMG_NULL == psHash)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

	for (ui32Idx = 0; ui32Idx < psHash->ui32Size; ui32Idx++)
    {
		struct sBucket * psBucket = IMG_NULL;
		IMG_UINT32 ui32Length = 0;
		if (IMG_NULL == psHash->ppsTable[ui32Idx])
        {
			ui32EmptyCount++;
        }
		for (psBucket = psHash->ppsTable[ui32Idx]; psBucket != IMG_NULL; psBucket = psBucket->psNext)
        {
			ui32Length++;
        }
		ui32MaxLength = private_max(ui32MaxLength, ui32Length);
    }

	printf ("hash table: minimum_size=%d  size=%d  count=%d\n", psHash->ui32MinimumSize, psHash->ui32Size, psHash->ui32Count);
	printf ("  empty=%d  max=%d\n", ui32EmptyCount, ui32MaxLength);

error:
    return ui32Result;
}
#endif
