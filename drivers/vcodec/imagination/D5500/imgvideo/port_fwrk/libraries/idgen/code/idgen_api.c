/*!
 *****************************************************************************
 *
 * @File       idgen_api.c
 * @Title      The ID Generation API.
 * @Description    This file contains the ID Generation API.
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

#include <idgen_api.h>

#include "system.h"

/*!
******************************************************************************
 This structure contains the ID context.
 @brief  ID Context Structure
 ******************************************************************************/
typedef struct
{
    LST_T       sHdlBlkList;       /*!< List of handle block structures.                */
    IMG_UINT32  ui32MaxId;         /*!< Max ID - set by IDGEN_CreateContext().          */
    IMG_UINT32  ui32BlkSize;       /*!< The number of handle per block. In case of
                                        incrementing ids, size of the Hash table.       */
    IMG_UINT32  ui32FreeSlot;      /*!< Next free slot.                                 */
    IMG_UINT32  ui32MaxSlotPlus1;  /*!< Max slot+1 for which we have allocated blocks.  */

    /* Incrementing IDs */
    IMG_BOOL    bIncIds;           /*!< API needed to return incrementing IDs           */
    IMG_UINT32  ui32IncNumber;     /*!< Latest ID given back                            */
    LST_T *     asIncIdsList;      /*!< Array of list to hold IDGEN_sHdlId              */

} IDGEN_sContext;

/*!
******************************************************************************
 This structure represents internal representation of an Incrementing ID
 @brief  ID Structure
 ******************************************************************************/
typedef struct
{
    LST_LINK;               /*!< List link (allows the structure to be part of a MeOS list).  */

    IMG_UINT32  ui32IncId;  /*!< Incrementing ID returned                                     */
    IMG_HANDLE  hId;

} IDGEN_sId;

/*!
******************************************************************************
 This structure contains the ID context.
 @brief  ID Context Structure
 ******************************************************************************/
typedef struct
{
    LST_LINK;   /*!< List link (allows the structure to be part of a MeOS list).  */

    IMG_HANDLE  ahHandles[1];  /*!< Array of handles in this block.               */

} IDGEN_sHdlBlk;


/*!
******************************************************************************

 @Function                idgen_func

 A hashing function could go here. Currently just makes a circular list of max
 number of concurrent Ids (psContext->ui32BlkSize) in the system.
******************************************************************************/
static IMG_UINT32  idgen_func(
    IDGEN_sContext *  psContext,
    IMG_UINT32        ui32Id)
{
    return ((ui32Id-1) % psContext->ui32BlkSize);
}

/*!
******************************************************************************

 @Function                IDGEN_CreateContext

******************************************************************************/
IMG_RESULT IDGEN_CreateContext(
    IMG_UINT32    ui32MaxId,
    IMG_UINT32    ui32BlkSize,
    IMG_BOOL      bIncId,
    IMG_HANDLE *  phIdGenHandle
)
{
    IDGEN_sContext *  psContext;

    IMG_ASSERT(ui32MaxId > 0);
    IMG_ASSERT(ui32BlkSize > 0);

    /* Create context structure...*/
    psContext = IMG_MALLOC(sizeof(*psContext));
    IMG_ASSERT(psContext != IMG_NULL);
    if (psContext == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    IMG_MEMSET(psContext, 0, sizeof(*psContext));

    /* InitIalise the context...*/
    LST_init(&psContext->sHdlBlkList);
    psContext->ui32MaxId   = ui32MaxId;
    psContext->ui32BlkSize = ui32BlkSize;

    /* If we need incrementing Ids */
    psContext->bIncIds       = bIncId;
    psContext->ui32IncNumber = 0;
    psContext->asIncIdsList  = IMG_NULL;
    if(psContext->bIncIds)
    {
        IMG_UINT32  i=0;

        // Initialise the hash table of lists of length ui32BlkSize
        psContext->asIncIdsList = IMG_MALLOC(sizeof(*psContext->asIncIdsList) * psContext->ui32BlkSize);
        IMG_ASSERT(psContext->asIncIdsList != IMG_NULL);
        if (psContext == IMG_NULL)
        {
            IMG_FREE(psContext);
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        IMG_MEMSET(psContext->asIncIdsList, 0, sizeof(*psContext->asIncIdsList) * psContext->ui32BlkSize);

        // Initialise all the lists in the hash table
        for(i = 0; i < psContext->ui32BlkSize; i++)
        {
            LST_init(&psContext->asIncIdsList[i]);
        }
    }

    /* Return context structure as handle...*/
    *phIdGenHandle = psContext;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(IDGEN_CreateContext)

/*!
******************************************************************************

 @Function                IDGEN_DestroyContext

******************************************************************************/
IMG_RESULT IDGEN_DestroyContext(
    IMG_HANDLE  hIdGenHandle
)
{
    IDGEN_sContext *  psContext = (IDGEN_sContext *) hIdGenHandle;
    IDGEN_sHdlBlk *   psHdlBlk;

    IMG_ASSERT(psContext != IMG_NULL);
    if(psContext == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    /* If incrementing Ids, free the List of Incrementing Ids */
    if(psContext->bIncIds)
    {
        IDGEN_sId *  psId;
        IMG_UINT32   i=0;

        for(i = 0; i < psContext->ui32BlkSize; i++)
        {
            psId = LST_removeHead(&psContext->asIncIdsList[i]);
            while(psId != IMG_NULL)
            {
                IMG_FREE(psId);
                psId = LST_removeHead(&psContext->asIncIdsList[i]);
            }
        }
        IMG_FREE(psContext->asIncIdsList);
    }

    /* Remove and free all handle blocks...*/
    psHdlBlk = (IDGEN_sHdlBlk *)LST_removeHead(&psContext->sHdlBlkList);
    while (psHdlBlk != IMG_NULL)
    {
        IMG_FREE(psHdlBlk);
        psHdlBlk = (IDGEN_sHdlBlk *)LST_removeHead(&psContext->sHdlBlkList);
    }

    /* Free context structure...*/
    IMG_FREE(psContext);

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(IDGEN_DestroyContext)

/*!
******************************************************************************

 @Function                IDGEN_AllocId

******************************************************************************/
static IMG_RESULT idgen_FindNextFreeSlot(
    IMG_HANDLE  hIdGenHandle,
    IMG_UINT32  ui32PrevFreeSlot
)
{
    IDGEN_sContext *  psContext = (IDGEN_sContext *) hIdGenHandle;
    IDGEN_sHdlBlk *   psHdlBlk;
    IMG_UINT32        ui32FreeSlotBlk;
    IMG_UINT32        ui32FreeSlot;

    IMG_ASSERT(psContext != IMG_NULL);
    if(psContext == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }
    /* Find the block containing the current free slot...*/
    ui32FreeSlot    = ui32PrevFreeSlot;
    ui32FreeSlotBlk = ui32PrevFreeSlot;
    psHdlBlk = (IDGEN_sHdlBlk *)LST_first(&psContext->sHdlBlkList);

    IMG_ASSERT(psHdlBlk != IMG_NULL);
    if(psHdlBlk == IMG_NULL)
    {
        return IMG_ERROR_FATAL;
    }

    while (ui32FreeSlotBlk >= psContext->ui32BlkSize)
    {
        ui32FreeSlotBlk -= psContext->ui32BlkSize;
        psHdlBlk = (IDGEN_sHdlBlk *)LST_next(psHdlBlk);
        IMG_ASSERT(psHdlBlk != IMG_NULL);
    }

    /* Locate the next free slot...*/
    while (psHdlBlk != IMG_NULL)
    {
        while (ui32FreeSlotBlk < psContext->ui32BlkSize)
        {
            if (psHdlBlk->ahHandles[ui32FreeSlotBlk] == IMG_NULL)
            {
                /* Found...*/
                psContext->ui32FreeSlot = ui32FreeSlot;
				return IMG_SUCCESS;
            }
            ui32FreeSlot++;
            ui32FreeSlotBlk++;
        }
        ui32FreeSlotBlk = 0;
        psHdlBlk = (IDGEN_sHdlBlk *)LST_next(psHdlBlk);
    }

    /* Beyond the last block...*/
    psContext->ui32FreeSlot = ui32FreeSlot;
    IMG_ASSERT(psContext->ui32FreeSlot <= psContext->ui32MaxId);
    IMG_ASSERT(psContext->ui32FreeSlot == psContext->ui32MaxSlotPlus1);
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                idgen_GetId

 This function returns ID structure (IDGEN_sId) for ui32Id.

******************************************************************************/
static IDGEN_sId * idgen_GetId(
    LST_T *     psIdList,
    IMG_UINT32  ui32Id
)
{
    IDGEN_sId * psId;
    psId = LST_first(psIdList);
    while(psId)
    {
        if(psId->ui32IncId == ui32Id)
        {
            break;
        }
        psId = LST_next(psId);
    }

    return psId;
}


/*!
******************************************************************************

 @Function                IDGEN_AllocId

******************************************************************************/
IMG_RESULT IDGEN_AllocId(
    IMG_HANDLE    hIdGenHandle,
    IMG_HANDLE    hHandle,
    IMG_UINT32 *  pui32Id
)
{
    IDGEN_sContext *  psContext = (IDGEN_sContext *) hIdGenHandle;
    IDGEN_sHdlBlk *   psHdlBlk;
    IMG_UINT32        ui32Size;
    IMG_UINT32        ui32FreeSlot;
    IMG_UINT32        ui32Result = IMG_SUCCESS;

    IMG_ASSERT(psContext != IMG_NULL);
    IMG_ASSERT(hHandle != IMG_NULL);
    if(psContext == IMG_NULL ||
        hHandle == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    if(!psContext->bIncIds)
    {
        /* If the free slot is >= to the max id...*/
        if (psContext->ui32FreeSlot >= psContext->ui32MaxId)
        {
            ui32Result = IMG_ERROR_INVALID_ID;
            goto error;
        }

        /* If all of the allocated Ids have been used...*/
        if (psContext->ui32FreeSlot >= psContext->ui32MaxSlotPlus1)
        {
            /* Allocate a stream context...*/
            ui32Size = sizeof(*psHdlBlk) + (sizeof(IMG_HANDLE) * (psContext->ui32BlkSize-1));
            psHdlBlk = IMG_MALLOC(ui32Size);
            IMG_ASSERT(psHdlBlk != IMG_NULL);
            if (psHdlBlk == IMG_NULL)
            {
                ui32Result = IMG_ERROR_OUT_OF_MEMORY;
                goto error;
            }
            IMG_MEMSET(psHdlBlk, 0, ui32Size);

            LST_add(&psContext->sHdlBlkList, psHdlBlk);
            psContext->ui32MaxSlotPlus1 += psContext->ui32BlkSize;
        }

        /* Find the block containing the next free slot...*/
        ui32FreeSlot = psContext->ui32FreeSlot;
        psHdlBlk = (IDGEN_sHdlBlk *)LST_first(&psContext->sHdlBlkList);
        IMG_ASSERT(psHdlBlk != IMG_NULL);
        if(psHdlBlk == IMG_NULL)
        {
            ui32Result = IMG_ERROR_FATAL;
            goto error;
        }
        while (ui32FreeSlot >= psContext->ui32BlkSize)
        {
            ui32FreeSlot -= psContext->ui32BlkSize;
            psHdlBlk = (IDGEN_sHdlBlk *)LST_next(psHdlBlk);
            IMG_ASSERT(psHdlBlk != IMG_NULL);
            if(psHdlBlk == IMG_NULL)
            {
                ui32Result = IMG_ERROR_FATAL;
                goto error;
            }
        }

        /* Put handle in the next free slot...*/
        IMG_ASSERT(psHdlBlk->ahHandles[ui32FreeSlot] == IMG_NULL);
        psHdlBlk->ahHandles[ui32FreeSlot] = hHandle;

        *pui32Id = psContext->ui32FreeSlot + 1;

        /* Find a new free slot...*/
        ui32Result = idgen_FindNextFreeSlot(psContext, psContext->ui32FreeSlot);
        IMG_ASSERT(ui32Result == IMG_SUCCESS);
        if(ui32Result != IMG_SUCCESS)
        {
            goto error;
        }
    }
    /* If incrementing IDs, just add the ID node to the correct hash table list */
    else
    {
        IDGEN_sId *  psId;

        /* If incrementing IDs, increment the id for returning back, and save the ID node in the list
         * of ids, indexed by hash function (idgen_func). We might want to use a better hashing function */

        /* Increment the id. Wraps if greater then Max Id */
        psContext->ui32IncNumber = (psContext->ui32IncNumber + 1) % psContext->ui32MaxId;
        if(psContext->ui32IncNumber == 0)
        {
            /* Do not want to have zero as a pic id. */
            psContext->ui32IncNumber++;
        }

        psId = IMG_MALLOC(sizeof(*psId));
        IMG_ASSERT(psId != IMG_NULL);
        if(psId == IMG_NULL)
        {
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto error;
        }

        psId->ui32IncId = psContext->ui32IncNumber;
        psId->hId       = hHandle;

        /* Add to list in the correct hash table entry */
        if( idgen_GetId(&psContext->asIncIdsList[idgen_func(psContext,psContext->ui32IncNumber)], psId->ui32IncId) == IMG_NULL )
        {
            LST_add(&psContext->asIncIdsList[idgen_func(psContext,psContext->ui32IncNumber)], psId);
        }
        else
        {
            IMG_FREE(psId);
            /* We have reached a point where we have wrapped allowed Ids (MaxId)
             * and we want to overwrite ID still not released. */
            ui32Result = IMG_ERROR_INVALID_ID;
            goto error;
        }

        *pui32Id = psId->ui32IncId;
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}
IMGVIDEO_EXPORT_SYMBOL(IDGEN_AllocId)

/*!
******************************************************************************

 @Function                IDGEN_FreeId

******************************************************************************/
IMG_RESULT IDGEN_FreeId(
    IMG_HANDLE  hIdGenHandle,
    IMG_UINT32  ui32Id
)
{
    IDGEN_sContext *  psContext = (IDGEN_sContext *) hIdGenHandle;
    IDGEN_sHdlBlk *   psHdlBlk;
    IMG_UINT32        ui32OrigSlot;
    IMG_UINT32        ui32Slot;

    IMG_ASSERT(ui32Id != 0);

    if(psContext->bIncIds)
    {
        // Find the slot in the correct hash table entry, and remove the ID
        IDGEN_sId * psId;
        psId = idgen_GetId(&psContext->asIncIdsList[idgen_func(psContext,ui32Id)], ui32Id);
        if(psId != IMG_NULL)
        {
            LST_remove(&psContext->asIncIdsList[idgen_func(psContext,ui32Id)], psId);
            IMG_FREE(psId);
        }
        else
        {
            return IMG_ERROR_INVALID_ID;
        }
    }
    else
    {
        // If not incrementing id
        ui32Slot = ui32Id - 1;
        ui32OrigSlot = ui32Slot;

        IMG_ASSERT(ui32Slot < psContext->ui32MaxSlotPlus1);
        if (ui32Slot >= psContext->ui32MaxSlotPlus1)
        {
            return IMG_ERROR_INVALID_ID;
        }

        /* Find the block containing the id...*/
        psHdlBlk = (IDGEN_sHdlBlk *)LST_first(&psContext->sHdlBlkList);
        IMG_ASSERT(psHdlBlk != IMG_NULL);
        if(psHdlBlk == IMG_NULL)
        {
            return IMG_ERROR_FATAL;
        }
        while (ui32Slot >= psContext->ui32BlkSize)
        {
            ui32Slot -= psContext->ui32BlkSize;
            psHdlBlk = (IDGEN_sHdlBlk *)LST_next(psHdlBlk);
            IMG_ASSERT(psHdlBlk != IMG_NULL);
            if(psHdlBlk == IMG_NULL)
            {
                return IMG_ERROR_FATAL;
            }
        }

        /* Slot should be occupied...*/
        IMG_ASSERT(psHdlBlk->ahHandles[ui32Slot] != IMG_NULL);
        if (psHdlBlk->ahHandles[ui32Slot] == IMG_NULL)
        {
            return IMG_ERROR_INVALID_ID;
        }

        /* Free slot...*/
        psHdlBlk->ahHandles[ui32Slot] = IMG_NULL;

        /* If this slot is before the previous free slot...*/
        if ((ui32OrigSlot) < psContext->ui32FreeSlot)
        {
            psContext->ui32FreeSlot = ui32OrigSlot;
        }
    }

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(IDGEN_FreeId)

/*!
******************************************************************************

 @Function                IDGEN_GetHandle

******************************************************************************/
IMG_RESULT IDGEN_GetHandle(
    IMG_HANDLE    hIdGenHandle,
    IMG_UINT32    ui32Id,
    IMG_HANDLE *  phHandle
)
{
    IDGEN_sContext *  psContext = (IDGEN_sContext *) hIdGenHandle;
    IDGEN_sHdlBlk *   psHdlBlk;
    IMG_UINT32        ui32Slot;

    IMG_ASSERT(psContext != IMG_NULL);
    if(psContext == IMG_NULL)
    {
        return IMG_ERROR_INVALID_PARAMETERS;
    }

    IMG_ASSERT(ui32Id != 0);

    if(psContext->bIncIds)
    {
        // Find the slot in the correct hash table entry, and return the handle
        IDGEN_sId *  psId;
        psId = idgen_GetId(&psContext->asIncIdsList[idgen_func(psContext,ui32Id)], ui32Id);
        if(psId != IMG_NULL)
        {
            *phHandle = psId->hId;
        }
        else
        {
            return IMG_ERROR_INVALID_ID;
        }
    }
    else
    {
        // If not incrementing IDs
        ui32Slot = ui32Id - 1;

        IMG_ASSERT(ui32Slot < psContext->ui32MaxSlotPlus1);
        if (ui32Slot >= psContext->ui32MaxSlotPlus1)
        {
            return IMG_ERROR_INVALID_ID;
        }

        /* Find the block containing the id...*/
        psHdlBlk = (IDGEN_sHdlBlk *)LST_first(&psContext->sHdlBlkList);
        IMG_ASSERT(psHdlBlk != IMG_NULL);
        if (psHdlBlk == IMG_NULL)
            return IMG_ERROR_INVALID_PARAMETERS;
        while (ui32Slot >= psContext->ui32BlkSize)
        {
            ui32Slot -= psContext->ui32BlkSize;
            psHdlBlk = (IDGEN_sHdlBlk *)LST_next(psHdlBlk);
            IMG_ASSERT(psHdlBlk != IMG_NULL);
            if (psHdlBlk == IMG_NULL)
                return IMG_ERROR_INVALID_PARAMETERS;
        }

        /* Slot should be occupied...*/
        IMG_ASSERT(psHdlBlk->ahHandles[ui32Slot] != IMG_NULL);
        if (psHdlBlk->ahHandles[ui32Slot] == IMG_NULL)
        {
            return IMG_ERROR_INVALID_ID;
        }

        /* Return the handle...*/
        *phHandle = psHdlBlk->ahHandles[ui32Slot];
    }

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(IDGEN_GetHandle)
