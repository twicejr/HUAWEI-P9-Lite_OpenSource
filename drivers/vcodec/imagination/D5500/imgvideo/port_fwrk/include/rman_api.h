/*!
 *****************************************************************************
 *
 * @File       rman_api.h
 * @Title      The Resource Manager API.
 * @Description    This file contains the header file information for the
 *  Resource Manager API.
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

#if !defined (__RMAN_API_H__)
#define __RMAN_API_H__	//!< Defined to prevent file being included more than once

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>

#if defined(__cplusplus)
extern "C" {
#endif

#include <lst.h>

#define	RMAN_ALL_TYPES		(0xFFFFFFFF)	//!< Use to signify all "types" of resource. ( non-sticky ones )			
#define	RMAN_TYPE_P1		(0xFFFFFFFE)	//!< Use to signify priority 1 "type" resource.			
#define	RMAN_TYPE_P2		(0xFFFFFFFE)	//!< Use to signify priority 2 "type" resource.			
#define	RMAN_TYPE_P3		(0xFFFFFFFE)	//!< Use to signify priority 3 "type" resource.			
#define RMAN_STICKY		(0xFFFFFFFD)	//!< Use to allocate it among the last components.

/*!
******************************************************************************

 @Function				RMAN_Initialise
 
 @Description 
 
 This function is used to initialises the Resource Manager component and should 
 be called at start-up.
 
 @Input		None. 

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT RMAN_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				RMAN_Deinitialise
 
 @Description 
 
 This function is used to deinitialises the Resource Manager component and 
 would normally be called at shutdown.

 NOTE: This destroys any active resource buckets using RMAN_DestroyBucket().  
 
 @Input		None. 

 @Return	None.

******************************************************************************/
extern IMG_VOID RMAN_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function				RMAN_CreateBucket
 
 @Description 
 
 This function is used to create a resource bucket into which resources can be
 placed.
 
 @Output	phResBHandle :	A pointer used to return the bucket handle.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT RMAN_CreateBucket(
	IMG_HANDLE *		phResBHandle
);

/*!
******************************************************************************

 @Function				RMAN_DestroyBucket
 
 @Description 
 
 This function is used to destroy a resource bucket.

 NOTE: Destroying a resource bucket frees all of the resources within the bucket
 by calling the associated free function #RMAN_pfnFree defined when the resoure 
 what registered using RMAN_RegisterResource().

 NOTE: When a bucket is restroyed the resources are freed in the order:
	-	#RMAN_TYPE_P1
 	-	#RMAN_TYPE_P2			
 	-	#RMAN_TYPE_P3			
 	-	#RMAN_ALL_TYPES			

 By using these predefined types it is possible to control the order in which
 resources are freed.

 @Input		hResBHandle :	The handle for the bucket returned by RMAN_CreateBucket().

 @Return	None.

******************************************************************************/
extern IMG_VOID RMAN_DestroyBucket(
	IMG_HANDLE			hResBHandle
);


/*!
******************************************************************************

 @Function				RMAN_GetGlobalBucket
 
 @Description 
 
 This function is used to obtain the global resource bucket into which global
 resources can be placed.
 
 @Input		None.

 @Return	IMG_HANDLE :	This function returns a handle to the resource
							bucket.  IMG_NULL if the global bucket is not available

******************************************************************************/
extern IMG_HANDLE RMAN_GetGlobalBucket(IMG_VOID);



/*!
******************************************************************************

 @Function              RMAN_pfnFree

 @Description

 This is the prototype for "free" callback functions.  This function is called
 when a resource registered with the Resource Manager is to be freed.

 @Input		pvParam :		Pointer parameter, defined when the
						    resource was registered using RMAN_RegisterResource().

 @Return	None.

******************************************************************************/
typedef IMG_VOID ( * RMAN_pfnFree) (
    IMG_VOID *                  pvParam
);


/*!
******************************************************************************

 @Function				RMAN_RegisterResource
 
 @Description 
 
 This function is used to register a resource with the Resource Manager.

 @Input		hResBHandle :	The handle for the bucket returned by RMAN_CreateBucket().

 @Input		ui32TypeId :	Normally used to identify the "type" of resource.

 @Input		pfnFree :		A pointer to the "free" function - called to free
							the resource.  IMG_NULL if no free function is
							to be called - freeing of the resource must be
							handled outside of the Resource Manager.

 @Input		pvParam :		An IMG_VOID * value passed to the "free" function
							when freeing this resource.

 @Output	phResHandle :	A pointer used to return a handle to the resource.
							IMG_NULL if the resource handle is not required.

 @Output	pui32ResId :	A pointer used to return the resource Id.
							IMG_NULL if the resource Id is not required.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT RMAN_RegisterResource(
	IMG_HANDLE				hResBHandle,
	IMG_UINT32				ui32TypeId,
	RMAN_pfnFree			pfnFree,
    IMG_VOID *				pvParam,
    IMG_HANDLE *			phResHandle,
    IMG_UINT32 *			pui32ResId
);



/*!
******************************************************************************

 @Function              RMAN_pfnAlloc

 @Description

 This is the prototype for "alloc" callback functions.  This function is called
 when a named resource is to be created.

 @Input		pvAllocInfo :	A pointer to the allcation info passed into the
							RMAN_GetNamedResource() function.

 @Output	ppvParam :		A pointer used to return the resource.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
typedef IMG_RESULT ( * RMAN_pfnAlloc) (
	IMG_VOID *				pvAllocInfo,
    IMG_VOID **				ppvParam
);


/*!
******************************************************************************

 @Function				RMAN_GetNamedResource
 
 @Description 
 
 This function is used to get or allocate a "named" resource.

 If the resource does not exist then a resource is allocated by calling the
 #RMAN_pfnAlloc function and the ppvParam is used by the allocate function
 to return the resource and the resource manage returns a handle to the
 resource via phResHandle.

 If the resource exists then the resource manager returns the ppvParam and
 handle to the resource via phResHandle.

 NOTE: A count of allocates is maintained for named resources which is
 decremented when the resources is freed.  Only on the last free is the
 resource free function called.

 @Input		pszResName :	The resource name.

 @Input		pfnAlloc :		A pointer to the "alloc" function - called to
							allocate the resource.

 @Input		pvAllocInfo :	A pointer used to pass infomation to the pfnAlloc functions.

 @Input		hResBHandle :	The handle for the bucket into which the named
							resource will be placed.

 @Input		ui32TypeId :	Normally used to identify the "type" of resource.

 @Input		pfnFree :		A pointer to the "free" function - called to free
							the resource.  IMG_NULL if no free function is
							to be called - freeing of the resource must be
							handled outside of the Resource Manager.

 @Output	ppvParam :		A pointer used to return the allocate resource
							as returned by the #RMAN_pfnAlloc function.  This
							is also used passed to the "free" function
							when freeing this resource.

 @Output	phResHandle :	A pointer used to return a handle to the resource.
							IMG_NULL if the resource handle is not required.

 @Output	pui32ResId :	A pointer used to return the resource Id.
							IMG_NULL if the resource Id is not required.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT RMAN_GetNamedResource(
	IMG_CHAR *				pszResName,
	RMAN_pfnAlloc			pfnAlloc,
	IMG_VOID *				pvAllocInfo,
	IMG_HANDLE				hResBHandle,
	IMG_UINT32				ui32TypeId,
	RMAN_pfnFree			pfnFree,
    IMG_VOID **             ppvParam,
    IMG_HANDLE *			phResHandle,
    IMG_UINT32 *			pui32ResId
);


/*!
******************************************************************************

 @Function				RMAN_GetResourceId
 
 @Description 
 
 This function is used to get the resource ID allocated to the resource by the
 Resource Manager.

 @Input		hResHandle :	The resource handle returned by 
							RMAN_RegisterResource()

 @Return	IMG_UINT32 :	The allocated resource Id.

******************************************************************************/
extern IMG_UINT32 RMAN_GetResourceId(
    IMG_HANDLE			hResHandle
);


/*!
******************************************************************************

 @Function				RMAN_GetResource
 
 @Description 
 
 This function is used to get the resource given the bucket in which the resource
 is to be found and the resource Id.

 @Input		ui32ResId :		The resource ID returned by RMAN_GetResourceId();

 @Input		ui32TypeId :	The "type" of resource specified when the resource
							was registered using RMAN_RegisterResource().
							NOTE: This parameter MUST match and us used as a 
							cross check that the id matches the type id.

 @Output	ppvParam :		A pointer use to return the pvParam parameter defined 
							when the resource was registered using RMAN_RegisterResource().

 @Output	phResHandle :	A pointer used to return a handle to the resource.
							IMG_NULL if the resource handle is not required.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT RMAN_GetResource(
	IMG_UINT32				ui32ResId,
	IMG_UINT32				ui32TypeId,
    IMG_VOID **				ppvParam,
    IMG_HANDLE *			phResHandle
);


/*!
******************************************************************************

 @Function				RMAN_CloneResourceHandle
 
 @Description 
 
 This function is used to clone a resource - this creates an additional
 reference to the resource.

 NOTE: A resource is only freed when the last reference to the resource is
 freed.

 @Input		hResHandle :	The resource handle returned by 
							RMAN_RegisterResource()

 @Input		hResBHandle :	The handle for the bucket into which the cloned
							resource will be placed.

 @Output	phResHandle :	A pointer used to return a handle to the resource.
							IMG_NULL if the resource handle is not required.

 @Output	pui32ResId :	A pointer used to return the resource Id.
							IMG_NULL if the resource Id is not required.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT RMAN_CloneResourceHandle(
    IMG_HANDLE				hResHandle,
	IMG_HANDLE				hResBHandle,
    IMG_HANDLE *			phResHandle,
    IMG_UINT32 *			pui32ResId
);


/*!
******************************************************************************

 @Function				RMAN_FreeResource
 
 @Description 
 
 This function is used to free resource a individual resource.  This function
 calls the "free" function for the resource defined in the call to 
 RMAN_RegisterResource() and de-registers the resource.

 @Input		hResHandle :	The resource handle returned by 
							RMAN_RegisterResource()

 @Return	None.

******************************************************************************/
extern IMG_VOID RMAN_FreeResource(
    IMG_HANDLE				hResHandle
);


/*!
******************************************************************************

 @Function				RMAN_LockResource
 
 @Description 
 
 This function is used to lock a resource.

 @Input		hResHandle :	The resource handle returned by 
							RMAN_RegisterResource()

 @Return	None.

******************************************************************************/
extern IMG_VOID RMAN_LockResource(
    IMG_HANDLE				hResHandle
);


/*!
******************************************************************************

 @Function				RMAN_UnlockResource
 
 @Description 
 
 This function is used to unlock a resource.

 @Input		hResHandle :	The resource handle returned by 
							RMAN_RegisterResource()

 @Return	None.

******************************************************************************/
extern IMG_VOID RMAN_UnlockResource(
    IMG_HANDLE				hResHandle
);


/*!
******************************************************************************

 @Function				RMAN_FreeResources
 
 @Description 
 
 This function is used to free resources.  The function calls the "free" 
 functions for the resources and de-registers the resources.
 
 @Input		hResBHandle :	The handle for the bucket returned by RMAN_CreateBucket().
 
 @Input		ui32TypeId :	Normally used to identify the "type" of resource to be
							freed. #RMAN_ALL_TYPES to free for all "type".

 @Return	None.

******************************************************************************/
extern IMG_VOID RMAN_FreeResources(
	IMG_HANDLE				hResBHandle,
	IMG_UINT32				ui32TypeId
);

#if defined(__cplusplus)
}
#endif
 
#endif /* __RMAN_API_H__	*/


