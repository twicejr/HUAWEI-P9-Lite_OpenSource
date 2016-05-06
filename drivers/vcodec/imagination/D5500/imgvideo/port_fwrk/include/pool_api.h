/*!
 *****************************************************************************
 *
 * @File       pool_api.h
 * @Title      Resource Pool Manager API.
 * @Description    This file contains the header file information for the
 *  Resource Pool Manager API.
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

#if !defined (__POOL_API_H__)
#define __POOL_API_H__	//!< Defined to prevent file being included more than once


#if defined(__cplusplus)
extern "C" {
#endif

#include "img_errors.h"
#include "img_types.h"
#include "img_defs.h"
#include "lst.h"

/*!
******************************************************************************

 @Function				POOL_Initialise
 
 @Description 
 
 This function is used to initialises the resource pool manager component 
 and should be called at start-up.
 
 @Input		None. 

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				POOL_Deinitialise
 
 @Description 
 
 This function is used to deinitialises the resource pool manager component 
 and would normally be called at shutdown.

 NOTE: This destroys any active resource pools using POOL_PoolDestroy().  
 
 @Input		None. 

 @Return	None.

******************************************************************************/
extern IMG_VOID POOL_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function				POOL_PoolCreate
 
 @Description 
 
 This function is used to create a resource pool into which resources can be
 placed.
 
 @Output	phPoolHandle :	A pointer used to return the pool handle.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_PoolCreate(
	IMG_HANDLE *		phPoolHandle
);


/*!
******************************************************************************

 @Function				POOL_PoolDestroy
 
 @Description 
 
 This function is used to destroy a resource pool.

 NOTE: Destroying a resource pool destroys all of the resources within the pool
 by calling the associated destructor function #POOL_pfnDestructor defined when 
 the resource what registered using POOL_ResRegister().

 NOTE: All of the pools resources must be in the pools free list - the allocated
 list must be empty.

 @Input		hPoolHandle :	The handle for the pool.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_PoolDestroy(
	IMG_HANDLE			hPoolHandle
);


/*!
******************************************************************************

 @Function              POOL_pfnFree

 @Description

 This is the prototype for "free" callback functions.  This function 
 is called when resources are returned to the pools list of free resources.

 NOTE: The "freed" resource is then allocated and passed to the callback
 function.

 @Input		ui32ResId	: Resource Id.

 @Input		pvParam		: Pointer parameter, defined when the
						  resource was registered using POOL_ResRegister().

 @Return	None.

******************************************************************************/
typedef IMG_VOID ( * POOL_pfnFree) (
	IMG_UINT32				ui32ResId,
    IMG_VOID *              pvParam
);


/*!
******************************************************************************

 @Function				POOL_PoolSetFreeCallback
 
 @Description 
 
 This function is used to set or remove a free callback function on a pool.
 The free callback function gets call for any resources already in the
 pools free list or for any resources that subsequently get freed.  
 
 NOTE: The resource passed to the callback function has been allocated before 
 the callback is made.

 @Input		hPoolHandle :	The handle for the pool.

 @Input		pfnFree		:	A pointer to the "free" callback function - called 
							when resources are available in the pools free
							list.  IMG_NULL to remove the callback function from
							the pool.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_PoolSetFreeCallback(
	IMG_HANDLE				hPoolHandle,
	POOL_pfnFree			pfnFree
);


/*!
******************************************************************************

 @Function              POOL_pfnDestructor

 @Description

 This is the prototype for "destructor" callback functions.  This function 
 is called when a resource registered with the resource pool manager is to 
 be destroyed.

 @Input		pvParam :		Pointer parameter, defined when the
						    resource was registered using POOL_ResRegister().

 @Return	None.

******************************************************************************/
typedef IMG_VOID ( * POOL_pfnDestructor) (
    IMG_VOID *                  pvParam
);


/*!
******************************************************************************

 @Function				POOL_ResRegister
 
 @Description 
 
 This function is used to register a resource within a resource pool.  The 
 resource is added to the pools allocated or free list based on the value
 of bAlloc.

 @Input		hPoolHandle :	The handle for the pool.

 @Input		pfnDestructor :	A pointer to the "destructor" function - called to 
							destroy	the resource.  IMG_NULL if no destructor
							function is	to be called - destruction of the 
							resource must be handled outside of the resource 
							pool manager.

 @Input		pvParam :		An IMG_VOID * value passed to the "destructor" function
							when destroying this resource.

 @Input		ui32SizevParam : The size (in bytes) of the pvParam data.  Used by
							 POOL_ResClone() to clone/copy the pvParam data.

 @Input		bAlloc :		IMG_TRUE if the resource is to be pre-allocate.
							IMG_FALSE if the resource is free.

 @Output	pui32ResId :	A pointer used to return the resource Id.
							IMG_NULL if the handle is not required.

 @Output	phPoolResHandle :	A pointer used to return a handle to the resource.
							IMG_NULL if the handle is not required.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_ResRegister(
	IMG_HANDLE				hPoolHandle,
	POOL_pfnDestructor		pfnDestructor,
    IMG_VOID *				pvParam,
    IMG_UINT32				ui32SizevParam,
	IMG_BOOL				bAlloc,
    IMG_UINT32 *			pui32ResId,
    IMG_HANDLE *			phPoolResHandle
);


/*!
******************************************************************************

 @Function				POOL_ResDestroy
 
 @Description 
 
 This function is used to destroy a resource.

 @Input		hPoolResHandle :	The resource handle.

 @Input		bForce :	Force destruction of resources which are still referenced.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_ResDestroy(
    IMG_HANDLE				hPoolResHandle,
	IMG_BOOL				bForce
);


/*!
******************************************************************************

 @Function				POOL_ResDestroy1
 
 @Description 
 
 This function is used to destroy a resource.

 @Input		hPoolHandle :	The handle for the pool.

 @Input		ui32ResId	:	The resource Id.

 @Input		bForce :	Force destruction of resources which are still referenced.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_ResDestroy1(
	IMG_HANDLE				hPoolHandle,
    IMG_UINT32				ui32ResId,
	IMG_BOOL				bForce
);


/*!
******************************************************************************

 @Function				POOL_ResAlloc
 
 @Description 
 
 This function is used to get/allocate a resource from a pool.  This moves
 the resource from the free to allocated list.

 @Input		hPoolHandle :	The handle for the pool.

 @Input		hPoolResHandle :	A pointer used to return a handle to the 
							resource.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_ResAlloc(
	IMG_HANDLE				hPoolHandle,
    IMG_HANDLE 				hPoolResHandle
);


/*!
******************************************************************************

 @Function				POOL_ResFree
 
 @Description 
 
 This function is used to free a resource and return it to the pools lists of
 free resources.

 NOTE: The resources is only moved to the free list when all references to
 the resource have been freed.

 @Input		hPoolResHandle :	The resource handle.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_ResFree(
    IMG_HANDLE				hPoolResHandle
);


/*!
******************************************************************************

 @Function				POOL_ResFree1
 
 @Description 
 
 This function is used to free a resource and return it to the pools lists of
 free resources.

 NOTE: The resources is only moved to the free list when all references to
 the resource have been freed.

 @Input		hPoolHandle :	The handle for the pool.

 @Input		ui32ResId	:	The resource Id.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_ResFree1(
	IMG_HANDLE				hPoolHandle,
    IMG_UINT32				ui32ResId
);


/*!
******************************************************************************

 @Function				POOL_ResClone
 
 @Description 
 
 This function is used to clone a resource - this creates an additional
 reference to the resource.

 NOTE: The resources is only moved to the free list when all references to
 the resource have been freed.

 NOTE: If this function is used to clone the resource's pvParam data then
 the clone of the data is freed when the clone of the resource is freed.
 The resource destructor is NOT used for this - simply an IMG_FREE.

 @Input		hPoolResHandle :	The resource handle.

 @Output	phClonePoolResHandle :	A pointer used to return a handle to the
								cloned resource.

 @Output	ppvParam	: A pointer used to return a clone/copy of the 
							resource's pvParam data.  IMG_NULL if this 
							clone/copy is not required.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT POOL_ResClone(
    IMG_HANDLE				hPoolResHandle,
    IMG_HANDLE *			phClonePoolResHandle,
    IMG_VOID **				ppvParam
);


#if defined(__cplusplus)
}
#endif
 
#endif /* __POOL_API_H__	*/


