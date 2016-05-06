/*!
 *****************************************************************************
 *
 * @File       page_alloc_km.h
 * @Title      The Page Allocator Kernel Mode API.
 * @Description    This file contains the header file information for the
 *  Page Allocator Kernel Mode API.
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

#if !defined (__PAGE_ALLOCKM_H__)
#define __PAGE_ALLOCKM_H__

#include <img_errors.h>
#include <img_types.h>
#include <img_defs.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
******************************************************************************
 This structure contains information relating to the allocation.
******************************************************************************/
typedef struct
{	
	IMG_UINT32 			ui32Size;			//!< The size of the allocation (in bytes)
	IMG_PHYSADDR *			ppaPAddr; 		//!< Array of CPU Physical page addresses of the allocation
	IMG_BOOL 			bIsContiguous;		//!< IMG_TRUE if the allocation is contiguous
	IMG_BOOL			bMappingOnly;		//!< IMG_TRUE if this is a mapping rather than an allocation

} PALLOCKM_sAllocInfo;

/*!
******************************************************************************

 @Function				PALLOCKM_Initialise

 @Description

 This function is used to initialise the Page Allocator component
 and should be called at start-up.

 @Input		None.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PALLOCKM_Initialise(IMG_VOID);


/*!
******************************************************************************

 @Function				PALLOCKM_Deinitialise

 @Description

 This function is used to deinitialises the Page Allocator component and
 would normally be called at shutdown.

 @Input		None.

 @Return	None.

******************************************************************************/
extern IMG_VOID PALLOCKM_Deinitialise(IMG_VOID);


/*!
******************************************************************************

 @Function				PALLOCKM_GetAllocInfo
 
 @Description 
 
 This function is used to get details of an allocation.
 
 @Input		ui32AllocId :	The allocation Id returned by PALLOC_Alloc()

 @Output	psAllocInfo	:	 A pointer used to a #PALLOCKM_sAllocInfo structure
							 in which the allocation information is returned

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PALLOCKM_GetAllocInfo(
	IMG_UINT32  			ui32AllocId,
	PALLOCKM_sAllocInfo *	psAllocInfo
);

/*!
******************************************************************************

 @Function				PALLOCKM_GetPagesHandle
 
 @Description 
 
 This function is used to get the page information of an allocation
 
 @Input		ui32AllocId :	The allocation Id returned by PALLOC_Alloc()

 @Output	pPagesHandle	:  A pointer used to return a handle to page information

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PALLOCKM_GetPagesHandle(
    IMG_UINT32   ui32AllocId,
    IMG_HANDLE * pPagesHandle
);

/*!
******************************************************************************

 @Function				PALLOCKM_CloneAlloc
 
 @Description 
 
 This function is used to clone a allocation - this creates an additional
 reference to the allocation. 
 
 NOTE: An allocation is only freed when the last reference to the allocation is
 freed.

 @Input		ui32AllocId :	The allocation Id returned by PALLOC_Alloc()

 @Input		hResBHandle :	The handle for the bucket into which the cloned
							resource will be placed.

 @Output	phResHandle :	A pointer used to return a handle to the resource.
							IMG_NULL if the resource handle is not required.

 @Output	pui32AllocId :	A pointer used to return the aloocation Id.
							IMG_NULL if the resource Id is not required.

 @Return	IMG_RESULT :	This function returns either IMG_SUCCESS or an
							error code.

******************************************************************************/
extern IMG_RESULT PALLOCKM_CloneAlloc(
	IMG_UINT32  			ui32AllocId,
	IMG_HANDLE 				hResBHandle,
	IMG_HANDLE *			phResHandle,
	IMG_UINT32 *  			pui32AllocId
);


#if defined(__cplusplus)
}
#endif
 
#endif /* __PAGE_ALLOCKM_H__	*/

