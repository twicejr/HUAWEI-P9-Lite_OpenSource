/*!
 *****************************************************************************
 *
 * @File       resource.h
 * @Title      VDECDD Resource Component
 * @Description    This file contains the structure and function prototypes
 *  for the VDECDD resource component.
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

#ifndef __VDECDD_RESOURCE_H__
#define __VDECDD_RESOURCE_H__

#include <img_defs.h>
#include <vdecdd.h>
#include <vdecdd_int.h>

#ifdef __cplusplus
extern "C" {
#endif



/*!
******************************************************************************

 @Function                RESOURCE_pfnFreeItem

 @Description

 This is a function prototype for the free item callback functions.

 @Input     pvItem : A pointer to item.

 @Input     pvFreeCbParam : Pointer to free callback parameter.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
typedef IMG_RESULT ( * RESOURCE_pfnFreeItem) (
    IMG_VOID  * pvItem,
    IMG_VOID  * pvFreeCbParam
);


/*!
******************************************************************************

 @Function              RESOURCE_ItemUse

 @Description

 Marks an item as used by incrementing the reference count.

 @Input     pui32RefCount : Pointer to item's reference count.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

 ******************************************************************************/
extern IMG_RESULT 
RESOURCE_ItemUse(
    IMG_UINT32 *  pui32RefCount
);


/*!
******************************************************************************

 @Function              RESOURCE_ItemReturn

 @Description

 Returns an item by decrementing the reference count.

 @Input     pui32RefCount : Pointer to item's reference count.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

 ******************************************************************************/
extern IMG_RESULT 
RESOURCE_ItemReturn(
    IMG_UINT32 *  pui32RefCount
);


/*!
******************************************************************************

 @Function              RESOURCE_ItemRelease

 @Description

 Releases an item by setting reference count to 1 (original owner).

 @Input     pui32RefCount : Pointer to item's reference count.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

 ******************************************************************************/
extern IMG_RESULT 
RESOURCE_ItemRelease(
    IMG_UINT32 *  pui32RefCount
);


/*!
******************************************************************************

 @Function              RESOURCE_ItemIsAvailable

 @Description

 Indicates whether an item is free to be used (no owners).

 @Input     pui32RefCount : Pointer to item's reference count.

 @Return    IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

 ******************************************************************************/
extern IMG_BOOL RESOURCE_ItemIsAvailable(
    IMG_UINT32 *  pui32RefCount
);


/*!
******************************************************************************

 @Function              RESOURCE_ListAdd

 @Description

 Adds an item (and associated ID) to a resource list.

 @Input     psList  : Pointer to resource list.

 @Input     pvItem  : Pointer to item.

 @Input     ui32Id  : Item identifier.

 @Input     pui32RefCount : Pointer to item's reference count.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
RESOURCE_ListAdd(
    LST_T *       psList,
    IMG_VOID *    pvItem,
    IMG_UINT32    ui32Id,
    IMG_UINT32 *  pui32RefCount
);


/*!
******************************************************************************

 @Function              RESOURCE_ListPeekHead

 @Description

 Obtains pointer to item at head of resource list.

 @Input     psList  : Pointer to resource list.

 @Return   IMG_VOID * : Pointer to item at head of list (or IMG_NULL if empty).

******************************************************************************/
extern IMG_VOID *
RESOURCE_ListPeekHead(
    LST_T *  psList
);


/*!
******************************************************************************

 @Function              RESOURCE_ListRemove

 @Description

 Removes item from resource list.

 @Input     psList  : Pointer to resource list.

 @Input     pvItem  : Pointer to item.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
RESOURCE_ListRemove(
    LST_T     *  psList,
    IMG_VOID  *  pvItem
);


/*!
******************************************************************************

 @Function              RESOURCE_ListRemoveHead

 @Description

 Removes item at head of resource list.

 @Input     psList  : Pointer to resource list.

 @Return   IMG_VOID * : Pointer to item at head of list (or IMG_NULL if empty).

******************************************************************************/
extern IMG_VOID *
RESOURCE_ListRemoveHead(
    LST_T *  psList
);


/*!
******************************************************************************

 @Function              RESOURCE_ListRemoveNextAvail

 @Description

 Removes next available item from resource list. Item is freed if no longer used.

 @Input     psList  : Pointer to resource list.

 @Input     pfnFreeItem : Function used to free item otherwise IMG_FREE used.

 @Input     pvFreeCbParam : Pointer to free callback parameter.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
RESOURCE_ListRemoveNextAvail(
    LST_T                 * psList,
    RESOURCE_pfnFreeItem    pfnFreeItem,
    IMG_VOID              * pvFreeCbParam
);


/*!
******************************************************************************

 @Function              RESOURCE_ListGetAvail

 @Description

 Obtains pointer to an available item from the resource list.

 @Input     psList  : Pointer to resource list.

 @Return   IMG_VOID * : Pointer to item at head of list (or IMG_NULL if empty).

******************************************************************************/
extern IMG_VOID *
RESOURCE_ListGetAvail(
    LST_T *  psList
);


/*!
******************************************************************************

 @Function              RESOURCE_ListReuseItem

 @Description

 Signal duplicate use of specified item with resource list.

 @Input     psList  : Pointer to resource list.

 @Input     pvItem  : Pointer to item.

 @Return   IMG_VOID * : Pointer to item at head of list (or IMG_NULL if empty).

******************************************************************************/
extern IMG_VOID *
RESOURCE_ListReuseItem(
    LST_T *     psList,
    IMG_VOID *  pvItem
);


/*!
******************************************************************************

 @Function              RESOURCE_ListGetById

 @Description

 Obtain pointer to item from resource list with ID.

 @Input     psList  : Pointer to resource list.

 @Input     ui32Id  : Item identifier.

 @Return   IMG_VOID * : Pointer to item at head of list (or IMG_NULL if empty).

******************************************************************************/
extern IMG_VOID *
RESOURCE_ListGetById(
    LST_T *     psList,
    IMG_UINT32  ui32Id
);


/*!
******************************************************************************

 @Function              RESOURCE_ListGetNumAvail

 @Description

 Obtain the number of available (unused) items within list.

 @Input     psList  : Pointer to resource list.

 @Return    IMG_UINT32  : Number of items.

******************************************************************************/
extern IMG_UINT32
RESOURCE_ListGetNumAvail(
    LST_T *  psList
);


/*!
******************************************************************************

 @Function              RESOURCE_ListGetNum

 @Description

 Obtain the number of items within list.

 @Input     psList  : Pointer to resource list.

 @Return    IMG_UINT32  : Number of items.

******************************************************************************/
extern IMG_UINT32
RESOURCE_ListGetNum(
    LST_T *  psList
);


/*!
******************************************************************************

 @Function              RESOURCE_ListReplace

 @Description

 Replaces an item (of specified id) within a resource list.

 @Input     psList  : Pointer to resource list.

 @Input     pvItem  : Pointer to item.

 @Input     ui32Id  : Item identifier.

 @Input     pui32RefCount : Pointer to item's reference count.

 @Input     pfnFreeItem : Free function to use if old item is also unused.
                          Otherwise IMG_FREE will be used.

 @Input     pvFreeCbParam : Pointer to free callback parameter.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
RESOURCE_ListReplace(
    LST_T                 * psList,
    IMG_VOID              * pvItem,
    IMG_UINT32              ui32Id,
    IMG_UINT32            * pui32RefCount,
    RESOURCE_pfnFreeItem    pfnFreeItem,
    IMG_VOID              * pvFreeCbParam
);


/*!
******************************************************************************

 @Function              RESOURCE_ListEmpty

 @Description

 Removes all items from a resource list.

 @Input     psList  : Pointer to resource list.

 @Input     bReleaseItems : Release items to owner instead of freeing (reference count = 1).

 @Input     pfnFreeItem : Free function to use if removed items are also unused.
                          Otherwise IMG_FREE will be used.

 @Input     pvFreeCbParam : Pointer to free callback parameter.

 @Return   IMG_RESULT : This function returns either IMG_SUCCESS or an error code.

******************************************************************************/
extern IMG_RESULT
RESOURCE_ListEmpty(
    LST_T                 * psList,
    IMG_BOOL                bReleaseItems,
    RESOURCE_pfnFreeItem    pfnFreeItem,
    IMG_VOID              * pvFreeCbParam
);


/*!
******************************************************************************

 @Function              RESOURCE_GetNumPict

 @Description

 Obtain the number of pictures within list.

 @Input     psList  : Pointer to resource list.

 @Return    IMG_UINT32  : Number of pictures.

******************************************************************************/
extern IMG_UINT32
RESOURCE_GetNumPict(
    LST_T *  psList
);


#if defined(__cplusplus)
}
#endif

#endif /* __VDECDD_RESOURCE_H__    */
