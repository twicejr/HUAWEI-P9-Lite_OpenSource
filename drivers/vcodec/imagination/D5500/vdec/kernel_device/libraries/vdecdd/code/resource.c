/*!
 *****************************************************************************
 *
 * @File       resource.c
 * @Title      VDECDD resource management.
 * @Description    This file contains the implementation of the VDECDD resource
 *  management component.
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

#include "vdecdd.h"
#include "vdecdd_utils.h"
#include "core_api.h"
#include "resource.h"
#include "rman_api.h"
#include "dman_api_km.h"
#include "report_api.h"

#include "img_errors.h"

#include "lst.h"
#include "dq.h"

/*****************************************************************************
 * LOCAL TYPES
 *****************************************************************************/

typedef struct RESOURCE_sListElem_tag
{
    DQ_LINK;

    IMG_VOID *    pvItem;
    IMG_UINT32    ui32Id;
    IMG_UINT32 *  pui32RefCount;

} RESOURCE_sListElem;



/*****************************************************************************
 * LOCAL FUNCTIONS
 *****************************************************************************/




/*!
******************************************************************************

 @Function              RESOURCE_ItemUse

 ******************************************************************************/
IMG_RESULT RESOURCE_ItemUse(
    IMG_UINT32 *  pui32RefCount
)
{
    if (pui32RefCount)
    {
        (*pui32RefCount)++;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              RESOURCE_ItemReturn

 ******************************************************************************/
IMG_RESULT RESOURCE_ItemReturn(
    IMG_UINT32 *  pui32RefCount
)
{
    if (pui32RefCount && *pui32RefCount > 0)
    {
        (*pui32RefCount)--;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              RESOURCE_ItemRelease

 ******************************************************************************/
IMG_RESULT RESOURCE_ItemRelease(
    IMG_UINT32 *  pui32RefCount
)
{
    if (pui32RefCount)
    {
        *pui32RefCount = 1;
    }

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              RESOURCE_ItemIsAvailable

 ******************************************************************************/
IMG_BOOL RESOURCE_ItemIsAvailable(
    IMG_UINT32 *  pui32RefCount
)
{
    if (pui32RefCount)
    {
        return (*pui32RefCount == 0) ? IMG_TRUE : IMG_FALSE;
    }
    else
    {
        return IMG_FALSE;
    }
}




/*!
******************************************************************************

 @Function              RESOURCE_ListAdd

******************************************************************************/
IMG_RESULT
RESOURCE_ListAdd(
    LST_T *       psList,
    IMG_VOID *    pvItem,
    IMG_UINT32    ui32Id,
    IMG_UINT32 *  pui32RefCount
)
{
    RESOURCE_sListElem *  psListElem = IMG_NULL;
    IMG_BOOL bFound = IMG_FALSE;
    IMG_UINT32  ui32Result;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    IMG_ASSERT(IMG_NULL != pvItem);

    if (psList == IMG_NULL ||
        pvItem == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    /* Decrement the reference count on the item
       to signal that the owner has relinquished it. */
    ui32Result = RESOURCE_ItemReturn(pui32RefCount);
    if (ui32Result != IMG_SUCCESS)
    {
        ui32Result = IMG_ERROR_UNEXPECTED_STATE;
        goto error;
    }

    /* Determine whether this buffer is already in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (psListElem->pvItem == pvItem)
        {
            bFound = IMG_TRUE;
            break;
        }

        psListElem = LST_next(psListElem);
    }

    if (!bFound)
    {
        /* Allocate the image buffer list element structure. */
        VDEC_MALLOC(psListElem);
        if (IMG_NULL == psListElem)
        {
            REPORT(REPORT_MODULE_RESOURCE, REPORT_ERR,
                "Failed to allocate memory for RESOURCE list element");
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto error;
        }
        VDEC_BZERO(psListElem);

        /* Setup the list element. */
        psListElem->pvItem = pvItem;
        psListElem->ui32Id = ui32Id;
        psListElem->pui32RefCount = pui32RefCount;

        /* Add the element to the list. */
        LST_add(psList, (IMG_VOID *)psListElem);
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListPeekHead

******************************************************************************/
IMG_VOID *
RESOURCE_ListPeekHead(
    LST_T *  psList
)
{
    RESOURCE_sListElem *  psListElem = IMG_NULL;
    IMG_VOID * pvItem = IMG_NULL;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        goto error;
    }

    /* Peek the head item of the list. */
    psListElem = LST_first(psList);
    if (psListElem)
    {
        pvItem = psListElem->pvItem;
    }

error:
    return pvItem;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListRemove

******************************************************************************/
IMG_RESULT
RESOURCE_ListRemove(
    LST_T     *  psList,
    IMG_VOID  *  pvItem
)
{
    RESOURCE_sListElem    * psListElem = IMG_NULL;
    IMG_UINT32              ui32Result;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    IMG_ASSERT(IMG_NULL != pvItem);
    if (psList == IMG_NULL ||
        pvItem == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    /* Find the specified item in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (psListElem->pvItem == pvItem)
        {
            if (*psListElem->pui32RefCount != 0)
            {
                REPORT(REPORT_MODULE_RESOURCE, REPORT_WARNING,
                    "Element removed from list whilst still in use");
            }

            /* Remove the item from the list. */
            LST_remove(psList, psListElem);

            /* Free the stream unit queue element. */
            IMG_FREE(psListElem);
            psListElem = IMG_NULL;
            return IMG_SUCCESS;
        }

        psListElem = LST_next(psListElem);
    }

    DEBUG_REPORT(REPORT_MODULE_RESOURCE,
        "Item could not be located to remove from RESOURCE list");

    return IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListRemoveHead

******************************************************************************/
IMG_VOID *
RESOURCE_ListRemoveHead(
    LST_T *  psList
)
{
    RESOURCE_sListElem *  psListElem = IMG_NULL;
    IMG_VOID * pvItem = IMG_NULL;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        goto error;
    }

    /* Peek the head item of the list. */
    psListElem = LST_removeHead(psList);
    if (psListElem)
    {
        pvItem = psListElem->pvItem;

        /* Free the list element. */
        IMG_FREE(psListElem);
        psListElem = IMG_NULL;
    }

error:
    return pvItem;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListRemoveNextAvail

******************************************************************************/
IMG_RESULT
RESOURCE_ListRemoveNextAvail(
    LST_T                 * psList,
    RESOURCE_pfnFreeItem    pfnFreeItem,
    IMG_VOID              * pvFreeCbParam
)
{
    RESOURCE_sListElem *  psListElem = IMG_NULL;
    IMG_UINT32 ui32Result = IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    /* Find the next unused item in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (RESOURCE_ItemIsAvailable(psListElem->pui32RefCount))
        {
            /* Return and free. */
            RESOURCE_ItemReturn(psListElem->pui32RefCount);

            if (psListElem->pui32RefCount == IMG_NULL ||
                *psListElem->pui32RefCount == 0)
            {
                if (pfnFreeItem)
                {
                    pfnFreeItem(psListElem->pvItem, pvFreeCbParam);
                }
                else
                {
                    IMG_FREE(psListElem->pvItem);
                }
                psListElem->pvItem = IMG_NULL;
            }

            /* Get the next element from the list. */
            LST_remove(psList, psListElem);

            /* Free the buffer list element. */
            IMG_FREE(psListElem);
            psListElem = IMG_NULL;

            ui32Result = IMG_SUCCESS;
            break;
        }

        psListElem = LST_next(psListElem);
    }

    if (ui32Result == IMG_ERROR_COULD_NOT_OBTAIN_RESOURCE)
    {
        DEBUG_REPORT(REPORT_MODULE_RESOURCE,
            "Failed to locate an available RESOURCE element to remove");
    }

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListGetAvail

******************************************************************************/
IMG_VOID *
RESOURCE_ListGetAvail(
    LST_T *  psList
)
{
    RESOURCE_sListElem *  psListElem = IMG_NULL;
    IMG_VOID * pvItem = IMG_NULL;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        goto error;
    }

    /* Find the next unused item in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (RESOURCE_ItemIsAvailable(psListElem->pui32RefCount))
        {
            /* Take a copy to the item. */
            RESOURCE_ItemUse(psListElem->pui32RefCount);
            pvItem = psListElem->pvItem;
            break;
        }

        psListElem = LST_next(psListElem);
    }

error:
    return pvItem;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListReuseItem

******************************************************************************/
IMG_VOID *
RESOURCE_ListReuseItem(
    LST_T *     psList,
    IMG_VOID *  pvItem
)
{
    RESOURCE_sListElem *    psListElem = IMG_NULL;
    IMG_VOID *              pvRetItem  = IMG_NULL;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    IMG_ASSERT(IMG_NULL != pvItem);
    if (psList == IMG_NULL ||
        pvItem == IMG_NULL)
    {
        goto error;
    }

    /* Find the specified item in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (psListElem->pvItem == pvItem)
        {
            /* Take a copy to the item. */
            RESOURCE_ItemUse(psListElem->pui32RefCount);
            pvRetItem = pvItem;
            break;
        }

        psListElem = LST_next(psListElem);
    }

error:
    return pvRetItem;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListGetById

******************************************************************************/
IMG_VOID *
RESOURCE_ListGetById(
    LST_T *     psList,
    IMG_UINT32  ui32Id
)
{
    RESOURCE_sListElem *  psListElem = IMG_NULL;
    IMG_VOID * pvItem = IMG_NULL;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        goto error;
    }

    /* Find the next unused buffer in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (psListElem->ui32Id == ui32Id)
        {
            /* Take a copy of the item. */
            RESOURCE_ItemUse(psListElem->pui32RefCount);
            pvItem = psListElem->pvItem;
            break;
        }

        psListElem = LST_next(psListElem);
    }

error:
    return pvItem;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListGetNumAvail

******************************************************************************/
IMG_UINT32
RESOURCE_ListGetNumAvail(
    LST_T *  psList
)
{
    RESOURCE_sListElem *  psListElem = IMG_NULL;
    IMG_UINT32 ui32NumItems = 0;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        goto error;
    }

    /* Find the next unused buffer in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (RESOURCE_ItemIsAvailable(psListElem->pui32RefCount))
        {
            ui32NumItems++;
        }

        psListElem = LST_next(psListElem);
    }

error:
    return ui32NumItems;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListGetNum

******************************************************************************/
IMG_UINT32
RESOURCE_ListGetNum(
    LST_T *  psList
)
{
    RESOURCE_sListElem *  psListElem = IMG_NULL;
    IMG_UINT32 ui32NumItems = 0;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        goto error;
    }

    /* Find the next unused buffer in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        ui32NumItems++;

        psListElem = LST_next(psListElem);
    }

error:
    return ui32NumItems;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListReplace

******************************************************************************/
IMG_RESULT
RESOURCE_ListReplace(
    LST_T                 * psList,
    IMG_VOID              * pvItem,
    IMG_UINT32              ui32Id,
    IMG_UINT32            * pui32RefCount,
    RESOURCE_pfnFreeItem    pfnFreeItem,
    IMG_VOID              * pvFreeCbParam
)
{
    RESOURCE_sListElem    * psListElem = IMG_NULL;
    IMG_UINT32              ui32Result;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    IMG_ASSERT(IMG_NULL != pvItem);
    if (psList == IMG_NULL ||
        pvItem == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    /* Determine whether this sequence header is already in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (psListElem->ui32Id == ui32Id)
        {
            /* Free old version. */
            RESOURCE_ItemReturn(psListElem->pui32RefCount);
            if (*psListElem->pui32RefCount == 0)
            {
                if (pfnFreeItem)
                {
                    pfnFreeItem(psListElem->pvItem, pvFreeCbParam);
                }
                else
                {
                    IMG_FREE(psListElem->pvItem);
                }
                psListElem->pvItem = IMG_NULL;
            }

            LST_remove(psList, psListElem);
            break;
        }

        psListElem = LST_next(psListElem);
    }

    if (psListElem == IMG_NULL)
    {
        /* Allocate the sequence header list element structure. */
        VDEC_MALLOC(psListElem);
        if (IMG_NULL == psListElem)
        {
            REPORT(REPORT_MODULE_RESOURCE, REPORT_ERR,
                "Failed to allocate memory for RESOURCE list element");
            return IMG_ERROR_OUT_OF_MEMORY;
        }
    }
    VDEC_BZERO(psListElem);

    /* Setup the sequence header list element. */
    RESOURCE_ItemUse(pui32RefCount);

    psListElem->pvItem = pvItem;
    psListElem->ui32Id = ui32Id;
    psListElem->pui32RefCount = pui32RefCount;

    /* Add the sequence header list element to the sequence header list. */
    LST_add(psList, (IMG_VOID *)psListElem);

    return IMG_SUCCESS;

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              RESOURCE_ListEmpty

******************************************************************************/
IMG_RESULT
RESOURCE_ListEmpty(
    LST_T                 * psList,
    IMG_BOOL                bReleaseItems,
    RESOURCE_pfnFreeItem    pfnFreeItem,
    IMG_VOID              * pvFreeCbParam
)
{
    RESOURCE_sListElem    * psListElem = IMG_NULL;
    IMG_UINT32              ui32Result;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        ui32Result = IMG_ERROR_INVALID_PARAMETERS;
        goto error;
    }

    /* Remove all the buffer list elements from the image buffer list. */
    psListElem = LST_removeHead(psList);
    while (IMG_NULL != psListElem)
    {
        if (bReleaseItems)
        {
            RESOURCE_ItemRelease(psListElem->pui32RefCount);
        }
        else
        {
            /* Return and free. */
            RESOURCE_ItemReturn(psListElem->pui32RefCount);

            if (psListElem->pui32RefCount == IMG_NULL ||
                *psListElem->pui32RefCount == 0)
            {
                if (pfnFreeItem)
                {
                    pfnFreeItem(psListElem->pvItem, pvFreeCbParam);
                }
                else
                {
                    IMG_FREE(psListElem->pvItem);
                }
                psListElem->pvItem = IMG_NULL;
            }
        }

        /* Free the buffer list element. */
        IMG_FREE(psListElem);
        psListElem = IMG_NULL;

        /* Get the next element from the list. */
        psListElem = LST_removeHead(psList);
    }

    return IMG_SUCCESS;

error:
    return ui32Result;
}



/*!
******************************************************************************

 @Function              RESOURCE_GetNumPict

******************************************************************************/
IMG_UINT32
RESOURCE_GetNumPict(
    LST_T *  psList
)
{
    RESOURCE_sListElem *  psListElem = NULL;
    IMG_UINT32 ui32NumPict = 0;

    /* Check input params. */
    IMG_ASSERT(IMG_NULL != psList);
    if (psList == IMG_NULL)
    {
        goto error;
    }

    /* Find the next unused buffer in the list. */
    psListElem = LST_first(psList);
    while (psListElem)
    {
        if (((VDECDD_sStrUnit*)psListElem->pvItem)->eStrUnitType == VDECDD_STRUNIT_PICTURE_START)
        {
            ui32NumPict++;
        }

        psListElem = LST_next(psListElem);
    }

error:
    return ui32NumPict;
}







